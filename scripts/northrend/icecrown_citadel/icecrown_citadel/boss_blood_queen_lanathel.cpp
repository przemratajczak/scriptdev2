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
SDName: boss_blood_queen_lanathel
SD%Complete: 
SDComment: 
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
        SPELL_BERSERK                           = 47008,
        SPELL_SHROUD_OF_SORROW                  = 72981,
        SPELL_DELRIOUS_SLASH                    = 71623,
        SPELL_BLOOD_MIRROR                      = 70445,
        SPELL_BLOOD_MIRROR_MARK                 = 70451,
        SPELL_VAMPIRIC_BITE                     = 71726,
        SPELL_ESSENCE_OF_BLOOD_QWEEN            = 70867,
        SPELL_ESSENCE_OF_BLOOD_QWEEN_2          = 70871,
        SPELL_FRENZIED_BLOODTHIRST              = 70877,
        SPELL_UNCONTROLLABLE_FRENZY             = 70923,
        SPELL_PACT_OF_DARKFALLEN                = 71340,
        SPELL_SWARMING_SHADOWS                  = 71264,
        SPELL_TWILIGHT_BLOODBOLT                = 71446,
        SPELL_BLOODBOLT_WHIRL                   = 71772,
        SPELL_PRESENCE_OF_DARKFALLEN            = 71952,

        NPC_SWARMING_SHADOWS                    = 38163,
        SPELL_SWARMING_SHADOWS_VISUAL           = 71267,
        THIRST_QUENCHED_AURA                    = 72154,
};

// talks
enum
{
    SAY_AGGRO                   = -1631121,
    SAY_BITE_1                  = -1631122,
    SAY_BITE_2                  = -1631123,
    SAY_SHADOWS                 = -1631124,
    SAY_PACT                    = -1631125,
    SAY_MC                      = -1631126,
    SAY_AIR_PHASE               = -1631127,
    SAY_BERSERK                 = -1631128,
    SAY_DEATH                   = -1631129,
};

static Locations SpawnLoc[]=
{
    {4595.640137f, 2769.195557f, 400.137054f},  // 0 Phased
    {4595.904785f, 2769.315918f, 421.838623f},  // 1 Fly
};

#define PHASE_GROUND 1
#define PHASE_AIR 2

/**
 * Queen Lana'thel
 */
struct MANGOS_DLL_DECL boss_blood_queen_lanathelAI : public base_icc_bossAI
{
    boss_blood_queen_lanathelAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiPhase;

    void Reset()
    {
        m_uiPhase           = PHASE_GROUND;
    }

    void JustReachedHome()
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_LANATHEL, FAIL);
    }

    void KilledUnit(Unit* pVictim)
    {
        // entry missing in sd2 database
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            m_creature->MonsterYell("Is that all you got?", 0);
    }

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance) 
            m_pInstance->SetData(TYPE_LANATHEL, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit *pKiller)
    {
        if(m_pInstance)
            m_pInstance->SetData(TYPE_LANATHEL, DONE);

        DoScriptText(SAY_DEATH, m_creature);
    }


    void UpdateAI(const uint32 diff)
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiPhase == PHASE_GROUND)
        {
            DoMeleeAttackIfReady();
        }
        else
        {
            // do nothing
        }
    }
};

CreatureAI* GetAI_boss_blood_queen_lanathel(Creature* pCreature)
{
    return new boss_blood_queen_lanathelAI(pCreature);
}

/*
struct MANGOS_DLL_DECL boss_blood_queen_lanathelAI : public BSWScriptedAI
{
    boss_blood_queen_lanathelAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    uint8 stage;
    uint8 nextPoint;
    uint8 bloodbolts;
    uint32 UpdateTimer;
    bool movementstarted;

    void Reset()
    {
        if(!pInstance)
            return;
        if (m_creature->isAlive())
            pInstance->SetData(TYPE_LANATHEL, NOT_STARTED);
        stage = 0;
        UpdateTimer = 1000;
        bloodbolts = 0;
        movementstarted = false;
        resetTimers();
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
    }

    void JustReachedHome()
    {
        if (pInstance) pInstance->SetData(TYPE_LANATHEL, FAIL);
    }

    void KilledUnit(Unit* pVictim)
    {
        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR))
           doRemove(SPELL_BLOOD_MIRROR,pVictim);

        if (pVictim && pVictim->HasAura(SPELL_BLOOD_MIRROR_MARK))
           doRemove(SPELL_BLOOD_MIRROR_MARK,pVictim);
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if (type != POINT_MOTION_TYPE || !movementstarted) return;
        if (id == nextPoint)
        {
            movementstarted = false;
            m_creature->GetMotionMaster()->MovementExpired();
        }
    }

    void StartMovement(uint32 id)
    {
        nextPoint = id;
        m_creature->GetMotionMaster()->Clear();
        m_creature->GetMotionMaster()->MovePoint(id, SpawnLoc[id].x, SpawnLoc[id].y, SpawnLoc[id].z);
        movementstarted = true;
    }

    void Aggro(Unit* pWho)
    {
        if (!pInstance) 
            return;

        pInstance->SetData(TYPE_LANATHEL, IN_PROGRESS);

        doCast(SPELL_SHROUD_OF_SORROW);

        DoScriptText(SAY_AGGRO,m_creature,pWho);

        if (Unit* pTarget = doSelectRandomPlayer(SPELL_BLOOD_MIRROR_MARK, false, 100.0f))
        {
            if (doCast(SPELL_BLOOD_MIRROR_MARK,pTarget) == CAST_OK)
            {
                if (Unit* pTarget1 = doSelectRandomPlayer(SPELL_BLOOD_MIRROR_MARK, false, 100.0f))
                    pTarget->CastSpell(pTarget1,getSpellWithDifficulty(SPELL_BLOOD_MIRROR), true);
            };
        };

        if (Unit* pTarget = doSelectRandomPlayer(SPELL_SHADOWS_EDGE, true, 100.0f))
            doAura(THIRST_QUENCHED_AURA,pTarget);

    }

    void JustDied(Unit *killer)
    {
        if(!pInstance)
            return;

        pInstance->SetData(TYPE_LANATHEL, DONE);
        DoScriptText(SAY_DEATH,m_creature,killer);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
        m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);

        doRemoveFromAll(getSpellWithDifficulty(SPELL_ESSENCE_OF_BLOOD_QWEEN));
        doRemoveFromAll(SPELL_ESSENCE_OF_BLOOD_QWEEN_2);
        doRemoveFromAll(SPELL_PACT_OF_DARKFALLEN);
        doRemoveFromAll(SPELL_BLOOD_MIRROR);
        doRemoveFromAll(SPELL_BLOOD_MIRROR_MARK);
    }


    void UpdateAI(const uint32 diff)
    {

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(stage)
        {
            case 0:

                    if (timedQuery(SPELL_TWILIGHT_BLOODBOLT, diff))
                        bloodbolts = 1;

                    if (timedQuery(SPELL_DELRIOUS_SLASH, diff))
                        if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                            doCast(SPELL_DELRIOUS_SLASH, pTarget);

//                    timedCast(SPELL_PACT_OF_DARKFALLEN, diff);

                    timedCast(SPELL_SWARMING_SHADOWS, diff);

                    if (timedQuery(SPELL_VAMPIRIC_BITE,diff))
                    {
                       DoScriptText(SAY_BITE_1 - urand(0, 1),m_creature);
                       doCast(SPELL_VAMPIRIC_BITE);
                    }

                    if (timedQuery(SPELL_BLOODBOLT_WHIRL,diff) && m_creature->GetHealthPercent() > 10.0f)
                    {
                        stage = 1;
                    };

                    DoMeleeAttackIfReady();

                    break;
            case 1:             // Go in fly phase
                    m_creature->AttackStop();
                    SetCombatMovement(false);
                    StartMovement(1);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 50331648);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 50331648);
                    m_creature->SetLevitate(true);
                    stage = 2;
                    break;
            case 2:
                    if (movementstarted)
                        return;
                    DoScriptText(SAY_AIR_PHASE,m_creature);
                    doCast(SPELL_BLOODBOLT_WHIRL);
                    stage = 3;
                    return;
            case 3:
                    if (m_creature->IsNonMeleeSpellCasted(false))
                        return;
                    if (timedQuery(SPELL_TWILIGHT_BLOODBOLT,diff) || m_creature->GetHealthPercent() < 10.0f)
                    {
                        stage = 4;
                        bloodbolts = 3;
                    };
                    break;
            case 4:             // Go in grownd phase
                    m_creature->AttackStop();
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_0, 0);
                    m_creature->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                    m_creature->SetLevitate(false);
                    StartMovement(0);
                    stage = 5;
                    break;
            case 5:
                    if (movementstarted) return;
                    DoScriptText(SAY_SHADOWS,m_creature);
                    stage = 0;
                    SetCombatMovement(true);
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    return;
            default:
                    break;
        }

        if (bloodbolts > 0)
        {
            doCast(SPELL_TWILIGHT_BLOODBOLT);
            --bloodbolts;
        };

        if (timedQuery(SPELL_BERSERK, diff))
        {
             doCast(SPELL_BERSERK);
             DoScriptText(SAY_BERSERK,m_creature);
        };

    }
};


struct MANGOS_DLL_DECL mob_swarming_shadowsAI : public ScriptedAI
{
    mob_swarming_shadowsAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_lifetimer;

    void Reset()
    {
        m_creature->SetDisplayId(11686);
        m_creature->SetRespawnDelay(7*DAY);
        SetCombatMovement(false);
        m_creature->SetInCombatWithZone();
        m_lifetimer = 10000;
        DoCast(m_creature, SPELL_SWARMING_SHADOWS_VISUAL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_LANATHEL) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->HasAura(SPELL_SWARMING_SHADOWS_VISUAL))
              DoCast(m_creature, SPELL_SWARMING_SHADOWS_VISUAL);

        if (m_lifetimer <= uiDiff)
            m_creature->ForcedDespawn();
        else m_lifetimer -= uiDiff;

    }
};
*/

void AddSC_boss_blood_queen_lanathel()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_blood_queen_lanathel";
    newscript->GetAI = &GetAI_boss_blood_queen_lanathel;
    newscript->RegisterSelf();

    /*newscript = new Script;
    newscript->Name = "mob_swarming_shadows";
    newscript->GetAI = &GetAI_mob_swarming_shadows;
    newscript->RegisterSelf();*/
}
