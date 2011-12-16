/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_professor_putricide
SD%Complete:
SDComment:
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
    SPELL_UNSTABLE_EXPERIMENT     = 70351, // Script effect not work on 10154. Spawn manually.
    SPELL_TEAR_GAS                = 71617,
    SPELL_TEAR_GAS_1              = 71615,
    SPELL_TEAR_GAS_2              = 71618,
    SPELL_CREATE_CONCOCTION       = 71621,
    SPELL_MALLEABLE_GOO           = 70852,
    SPELL_GUZZLE_POTIONS          = 71893,
    SPELL_MUTATED_STRENGTH        = 71603,
    SPELL_MUTATED_PLAGUE          = 72672,
    SPELL_OOZE_THROW              = 70342, // is triggered spell

    SPELL_GREEN_BOTTLE_0          = 71826,
    SPELL_ORANGE_BOTTLE_0         = 71827,
    SPELL_GREEN_BOTTLE_1          = 71702,
    SPELL_ORANGE_BOTTLE_1         = 71703,

    SPELL_THROW_BOTTLE_1          = 71273,
    SPELL_THROW_BOTTLE_2          = 71275,
    SPELL_THROW_BOTTLE_3          = 71276,

    NPC_GAS_CLOUD                 = 37562,
    SPELL_GASEOUS_BLOAT           = 70672,
    SPELL_EXPUNGED_GAS            = 70701,

    NPC_VOLATILE_OOZE             = 37697,
    SPELL_OOZE_ADHESIVE           = 70447,
    SPELL_OOZE_ERUPTION           = 70492,

    SPELL_OOZE_GAS_PROTECTION     = 70812,
    SPELL_OOZE_BEAM_PROTECTION    = 71530,
    SPELL_OOZE_TANK_PROTECTION    = 71770,

    NPC_MUTATED_ABOMINATION       = 37672,
    SPELL_MUTATED_TRANSFORMATION  = 70311,
    SPELL_EAT_OOZE                = 72527,
    SPELL_REGURGITATED_OOZE       = 70539,
    SPELL_MUTATED_SLASH           = 70542,
    SPELL_MUTATED_AURA            = 70405,

    NPC_CHOKING_GAS_BOMB          = 38159,
    SPELL_CHOKING_GAS             = 71259,
    SPELL_CHOKING_GAS_AURA        = 71278,
    SPELL_CHOKING_GAS_EXPLODE     = 71279,
    SPELL_CHOKING_GAS_EXPLODE_TRIGGER = 71280,
    SPELL_ORANGE_RADIATION        = 45857, //Additional visual

    NPC_OOZE_PUDDLE               = 37690,
    SPELL_SLIME_PUDDLE            = 70343,
    SPELL_SLIME_PUDDLE_AURA       = 70346,

    SPELL_BERSERK                 = 47008,
    QUEST_24749                   = 71518,
    SHADOW_INFUSION_AURA          = 71516,

    VIEW_1                        = 30881,
    VIEW_2                        = 30881,
    VIEW_3                        = 30993,
};

// talks
enum
{
    SAY_AGGRO                   = -1631092,
    SAY_AIRLOCK                 = -1631093,
    SAY_PHASE_CHANGE            = -1631094,
    SAY_TRANSFORM_1             = -1631095,
    SAY_TRANSFORM_2             = -1631096,
    SAY_SLAY_1                  = -1631097,
    SAY_SLAY_2                  = -1631098,
    SAY_BERSERK                 = -1631099,
    SAY_DEATH                   = -1631100,

    // during other fights
    SAY_SLIME_FLOW_1            = -1631074,
    SAY_SLIME_FLOW_2            = -1631075,
    SAY_BLIGHT                  = -1631083,
    SAY_FESTERGUT_DEATH         = -1631091,
    SAY_ROTFACE_DEATH           = -1631080,
};

static Locations SpawnLoc[]=
{
    {4356.779785f, 3263.510010f, 389.398010f, 1.586f},  // 0 Putricide start point o=1.586
    {4295.081055f, 3188.883545f, 389.330261f, 4.270f},  // 1 Puticide Festergut say, o=4.27
    {4417.302246f, 3188.219971f, 389.332520f, 5.102f},  // 2 Putricide Rotface say o=5.102
};

#define PHASE_ONE 1
#define PHASE_TRANSITION 2
#define PHASE_TWO 3
#define PHASE_THREE 4

struct MANGOS_DLL_DECL boss_professor_putricideAI : public base_icc_bossAI
{
    boss_professor_putricideAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiPhase;

    // used to determine whether he is assisting one of his pupils or having his own encounter
    bool m_bIsAssistingOnly;

    void Reset()
    {
        m_uiPhase = PHASE_ONE;
        m_bIsAssistingOnly = false;
        SetCombatMovement(true);
    }

    void DamageTaken(Unit *pDealer, uint32 &uiDamage)
    {
        if (m_bIsAssistingOnly)
            uiDamage = 0;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_SLAY_1 - urand(0, 1), m_creature);
    }

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        // need moving to other scripts
        /*if (m_pInstance->GetData(TYPE_FESTERGUT) == IN_PROGRESS || m_pInstance->GetData(TYPE_ROTFACE) == IN_PROGRESS)
        {
            // m_creature->NearTeleportTo(SpawnLoc[1].x, SpawnLoc[1].y, SpawnLoc[1].z, SpawnLoc[1].o);
            // m_creature->NearTeleportTo(SpawnLoc[2].x, SpawnLoc[2].y, SpawnLoc[2].z, SpawnLoc[2].o);
            SetCombatMovement(false);
            m_bIsAssistingOnly = true;
            return;
        }*/

        m_pInstance->SetData(TYPE_PUTRICIDE, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit *pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_PUTRICIDE, DONE);

        DoScriptText(SAY_DEATH, m_creature);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_PUTRICIDE, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // must move teleporting of profesor after assisting to scripts of the other bosses (to their JustDied)
        // m_creature->NearTeleportTo(SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, SpawnLoc[0].o);

        if (m_bIsAssistingOnly)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_uiPhase)
        {
            case PHASE_ONE:
                break;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_professor_putricide(Creature* pCreature)
{
    return new boss_professor_putricideAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_gas_cloudAI : public ScriptedAI
{
    mob_icc_gas_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_icc_gas_cloud(Creature* pCreature)
{
    return new mob_icc_gas_cloudAI(pCreature);
}

struct MANGOS_DLL_DECL mob_icc_volatile_oozeAI : public ScriptedAI
{
    mob_icc_volatile_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
    }
};

CreatureAI* GetAI_mob_icc_volatile_ooze(Creature* pCreature)
{
    return new mob_icc_volatile_oozeAI(pCreature);
}

struct MANGOS_DLL_DECL mob_choking_gas_bombAI : public ScriptedAI
{
    mob_choking_gas_bombAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
    }

    void AttackStart(Unit *pWho){}

    void UpdateAI(const uint32 uiDiff)
    {
    }
};

CreatureAI* GetAI_mob_choking_gas_bomb(Creature* pCreature)
{
    return new mob_choking_gas_bombAI(pCreature);
}

struct MANGOS_DLL_DECL mob_ooze_puddleAI : public ScriptedAI
{
    mob_ooze_puddleAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset()
    {
    }

    void AttackStart(Unit *who){}

    void UpdateAI(const uint32 uiDiff)
    {
    }
};

CreatureAI* GetAI_mob_ooze_puddle(Creature* pCreature)
{
    return new mob_ooze_puddleAI(pCreature);
}

void AddSC_boss_professor_putricide()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_professor_putricide";
    newscript->GetAI = &GetAI_boss_professor_putricide;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_volatile_ooze";
    newscript->GetAI = &GetAI_mob_icc_volatile_ooze;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_icc_gas_cloud";
    newscript->GetAI = &GetAI_mob_icc_gas_cloud;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_choking_gas_bomb";
    newscript->GetAI = &GetAI_mob_choking_gas_bomb;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_ooze_puddle";
    newscript->GetAI = &GetAI_mob_ooze_puddle;
    newscript->RegisterSelf();
}
