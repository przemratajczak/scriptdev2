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
    SPELL_BERSERK                   = 47008,

    // controlled abomination
    SPELL_MUTATED_TRANSFORMATION    = 70311,
    SPELL_EAT_OOZE                  = 72527,
    SPELL_REGURGITATED_OOZE         = 70539,
    SPELL_MUTATED_SLASH             = 70542,
    SPELL_MUTATED_AURA              = 70405,
    SPELL_ABOMINATION_POWER_DRAIN   = 70385, // prevents normal regen of abomination's power

    SPELL_UNSTABLE_EXPERIMENT       = 70351,
    SPELL_VOLATILE_EXPERIMENT       = 72842, // heroic
    SPELL_GREEN_OOZE_SUMMON         = 71412,
    SPELL_ORANGE_OOZE_SUMMON        = 71415,

    SPELL_SLIME_PUDDLE_SUMMON       = 70342,
    SPELL_SLIME_PUDDLE_MISSILE      = 70341,
    SPELL_SLIME_PUDDLE_AURA         = 70343,
 // SPELL_SLIME_PUDDLE_TRIGGER      = 71424, // trigger summon spell from target?
 // SPELL_SLIME_PUDDLE_SUMMON_TRIG  = 71425,

    SPELL_CHOKING_GAS_BOMB          = 71255,
    SPELL_CHOKING_GAS_BOMB_AURA     = 71259,
    SPELL_CHOKING_GAS_BOMB_EXPL_AUR = 71280,

    // phase transitions
    SPELL_TEAR_GAS_1                = 71615,
    SPELL_TEAR_GAS                  = 71617,
    SPELL_TEAR_GAS_2                = 71618,
    SPELL_TEAR_GAS_PERIODIC_AURA    = 73170,
    SPELL_TEAR_GAS_CANCEL           = 71620,

    SPELL_CREATE_CONCOCTION         = 71621,
    SPELL_GUZZLE_POTIONS            = 71893,


    NPC_GREEN_ORANGE_OOZE_STALKER   = 37824, // casts orange and green visual spell and then summons add
    NPC_GROWING_OOZE_PUDDLE         = 37690,
    NPC_GROWING_OOZE_PUDDLE_TRIG    = 38234,
    NPC_CHOKING_GAS_BOMB            = 38159,
    NPC_VOLATILE_OOZE               = 37697,
    NPC_MUTATED_ABOMINATION         = 37672,

/*
    SPELL_OOZE_ADHESIVE           = 70447,
    SPELL_OOZE_ERUPTION           = 70492,

    SPELL_OOZE_GAS_PROTECTION     = 70812,
    SPELL_OOZE_BEAM_PROTECTION    = 71530,
    SPELL_OOZE_TANK_PROTECTION    = 71770,

    SPELL_ORANGE_RADIATION        = 45857, //Additional visual

    QUEST_24749                   = 71518,
    SHADOW_INFUSION_AURA          = 71516,

    VIEW_1                        = 30881,
    VIEW_2                        = 30881,
    VIEW_3                        = 30993,
*/
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
    {4388.1f, 3213.29f, 408.7399f, 3.8397f},            // 3 Ooze stalker - green
    {4324.7212f, 3214.6428f, 408.7399f, 5.5764f},       // 3 Ooze stalker - orange
};

#define POINT_PUTRICIDE_SPAWN 1

enum Phases
{
    PHASE_ONE = 1,
    PHASE_RUNNING_ONE = 2,
    PHASE_TRANSITION_ONE = 3,
    PHASE_TWO = 4,
    PHASE_RUNNING_TWO = 5,
    PHASE_TRANSITION_TWO = 6,
    PHASE_THREE = 7
};


/**
 * boss_professor_putricide
 */
struct MANGOS_DLL_DECL boss_professor_putricideAI : public base_icc_bossAI
{
    boss_professor_putricideAI(Creature* pCreature) : base_icc_bossAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiPhase;

    uint32 m_uiHealthCheckTimer;
    uint32 m_uiTransitionTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiPuddleTimer;
    uint32 m_uiUnstableExperimentTimer;
    uint32 m_uiMalleableGooTimer;
    uint32 m_uiChokingGasBombTimer;

    // used to determine whether he is assisting one of his pupils or having his own encounter
    bool m_bIsAssistingOnly;

    bool m_bIsGreenOoze; // green or orange ooze to summon

    void Reset()
    {
        m_uiPhase                   = PHASE_ONE;
        m_bIsAssistingOnly          = false;
        SetCombatMovement(true);

        m_bIsGreenOoze              = true; // first ooze summoned is always green

        m_uiHealthCheckTimer        = 1000;
        m_uiTransitionTimer         = 20000;
        m_uiEnrageTimer             = 10 * MINUTE * IN_MILLISECONDS;
        m_uiPuddleTimer             = 10000;
        m_uiUnstableExperimentTimer = 20000;
        m_uiMalleableGooTimer       = 5000;
        m_uiChokingGasBombTimer     = urand(10000, 15000);
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

        if (m_pInstance->GetData(TYPE_FESTERGUT) == IN_PROGRESS || m_pInstance->GetData(TYPE_ROTFACE) == IN_PROGRESS)
        {
            SetCombatMovement(false);
            m_bIsAssistingOnly = true;
            return;
        }

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

        EnterEvadeMode();
    }

    void MovementInform(uint32 uiMovementType, uint32 uiData)
    {
        if (uiMovementType != POINT_MOTION_TYPE)
            return;

        if (uiData == POINT_PUTRICIDE_SPAWN)
        {
            if (m_uiPhase == PHASE_RUNNING_ONE)
            {
                if (m_bIsHeroic)
                {
                    DoScriptText(SAY_PHASE_CHANGE, m_creature);
                    m_uiTransitionTimer = 30000;
                }
                else
                {
                    DoCastSpellIfCan(m_creature, SPELL_CREATE_CONCOCTION);
                    DoScriptText(SAY_TRANSFORM_1, m_creature);
                }

                m_uiPhase = PHASE_TRANSITION_ONE; // counter for entering phase 2
            }
            else if (m_uiPhase == PHASE_RUNNING_TWO)
            {
                if (m_bIsHeroic)
                {
                    DoScriptText(SAY_PHASE_CHANGE, m_creature);
                    m_uiTransitionTimer = 30000;
                }
                else
                {
                    DoCastSpellIfCan(m_creature, SPELL_GUZZLE_POTIONS);
                    DoScriptText(SAY_TRANSFORM_2, m_creature);
                    m_uiPhase = PHASE_TRANSITION_TWO; // counter for entering phase 3
                }
            }
        }
    }

    void DoExperiment(bool green, bool both = false)
    {
        if (green || both)
        {
            if (Unit *pGreen = m_creature->SummonCreature(NPC_GREEN_ORANGE_OOZE_STALKER, SpawnLoc[3].x, SpawnLoc[3].y, SpawnLoc[3].z, SpawnLoc[3].o, TEMPSUMMON_TIMED_DESPAWN, 10000))
                DoCastSpellIfCan(m_creature, SPELL_GREEN_OOZE_SUMMON, CAST_TRIGGERED);
        }

        if (!green || both)
        {
            if (Unit *pOrange = m_creature->SummonCreature(NPC_GREEN_ORANGE_OOZE_STALKER, SpawnLoc[4].x, SpawnLoc[4].y, SpawnLoc[4].z, SpawnLoc[4].o, TEMPSUMMON_TIMED_DESPAWN, 10000))
                DoCastSpellIfCan(m_creature, SPELL_ORANGE_OOZE_SUMMON, CAST_TRIGGERED);
        }
    }

    void JustSummoned(Creature *pSummoned)
    {
        if (pSummoned->GetEntry() != NPC_GREEN_ORANGE_OOZE_STALKER)
            pSummoned->SetInCombatWithZone();

        if (pSummoned->GetEntry() == NPC_GROWING_OOZE_PUDDLE)
        {
            DoCastSpellIfCan(pSummoned, SPELL_SLIME_PUDDLE_MISSILE, CAST_TRIGGERED);
            pSummoned->CastSpell(pSummoned, SPELL_SLIME_PUDDLE_AURA, true);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // must move teleporting of profesor after assisting to scripts of the other bosses (to their JustDied)
        // m_creature->NearTeleportTo(SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z, SpawnLoc[0].o);

        if (m_bIsAssistingOnly)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Enrage
        if (m_uiEnrageTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiEnrageTimer = 30 * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiEnrageTimer -= uiDiff;

        switch(m_uiPhase)
        {
            case PHASE_ONE:
            {
                // health check
                if (m_uiHealthCheckTimer <= uiDiff)
                {
                    if (m_creature->GetHealthPercent() <= 80.0f)
                    {
                        if (m_bIsHeroic)
                        {
                            DoCastSpellIfCan(m_creature, SPELL_VOLATILE_EXPERIMENT);
                            DoExperiment(true, true);
                            DoScriptText(SAY_PHASE_CHANGE, m_creature);
                        }
                        else
                        {
                            DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS, CAST_TRIGGERED);
                            DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS_1, CAST_TRIGGERED);
                        }

                        m_creature->GetMotionMaster()->MovePoint(POINT_PUTRICIDE_SPAWN, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z);
                        m_uiPhase = PHASE_RUNNING_ONE;
                        return;
                    }
                    m_uiHealthCheckTimer = 1000;
                }
                else
                    m_uiHealthCheckTimer -= uiDiff;

                // Slime Puddle
                if (m_uiPuddleTimer <= uiDiff)
                {
                    /*for (int i = 0; i < 2; ++i)
                    {
                        if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, SPELL_SLIME_PUDDLE_SUMMON, SELECT_FLAG_PLAYER))
                            DoCastSpellIfCan(pTarget, SPELL_SLIME_PUDDLE_SUMMON, CAST_TRIGGERED);
                    }*/

                    m_uiPuddleTimer = 30000;
                }
                else
                    m_uiPuddleTimer -= uiDiff;

                // Unstable Experiment
                if (m_uiUnstableExperimentTimer <= uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_UNSTABLE_EXPERIMENT) == CAST_OK)
                    {
                        DoExperiment(m_bIsGreenOoze);
                        m_uiUnstableExperimentTimer = 30000;
                        m_bIsGreenOoze = !m_bIsGreenOoze;
                    }
                }
                else
                    m_uiUnstableExperimentTimer -= uiDiff;

                break;
            }
            case PHASE_TRANSITION_ONE:
            {
                if (m_uiTransitionTimer <= uiDiff)
                {
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_uiTransitionTimer = 20000;
                    m_uiPhase = PHASE_TWO;

                    if (m_bIsHeroic)
                    {
                        DoCastSpellIfCan(m_creature, SPELL_CREATE_CONCOCTION);
                        DoScriptText(SAY_TRANSFORM_1, m_creature);
                    }
                    else
                        DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS_CANCEL, CAST_TRIGGERED);
                }
                else
                    m_uiTransitionTimer -= uiDiff;

                return;
            }
            case PHASE_TWO:
            {
                // health check
                if (m_uiHealthCheckTimer <= uiDiff)
                {
                    if (m_creature->GetHealthPercent() <= 35.0f)
                    {
                        if (m_bIsHeroic)
                        {
                            DoCastSpellIfCan(m_creature, SPELL_VOLATILE_EXPERIMENT);
                            DoExperiment(true, true);
                            DoScriptText(SAY_PHASE_CHANGE, m_creature);
                        }
                        else
                        {
                            DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS, CAST_TRIGGERED);
                            DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS_1, CAST_TRIGGERED);
                        }

                        m_creature->GetMotionMaster()->MovePoint(POINT_PUTRICIDE_SPAWN, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z);
                        m_uiPhase = PHASE_RUNNING_TWO;
                        return;
                    }
                    m_uiHealthCheckTimer = 1000;
                }
                else
                    m_uiHealthCheckTimer -= uiDiff;

                // Slime Puddle
                if (m_uiPuddleTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiPuddleTimer = 30000;
                }
                else
                    m_uiPuddleTimer -= uiDiff;

                // Unstable Experiment
                if (m_uiUnstableExperimentTimer <= uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_UNSTABLE_EXPERIMENT) == CAST_OK)
                    {
                        DoExperiment(m_bIsGreenOoze);
                        m_uiUnstableExperimentTimer = 30000;
                        m_bIsGreenOoze = !m_bIsGreenOoze;
                    }
                }
                else
                    m_uiUnstableExperimentTimer -= uiDiff;

                // Malleable Goo
                if (m_uiMalleableGooTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiMalleableGooTimer = 20000;
                }
                else
                    m_uiMalleableGooTimer -= uiDiff;

                // Choking Gas
                if (m_uiChokingGasBombTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiChokingGasBombTimer = urand(25000, 30000);
                }
                else
                    m_uiChokingGasBombTimer -= uiDiff;

                break;
            }
            case PHASE_TRANSITION_TWO:
            {
                if (m_uiTransitionTimer <= uiDiff)
                {
                    m_creature->GetMotionMaster()->Clear();
                    m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                    m_uiTransitionTimer = 20000;
                    m_uiPhase = PHASE_THREE;

                    if (m_bIsHeroic)
                    {
                        DoCastSpellIfCan(m_creature, SPELL_GUZZLE_POTIONS);
                        DoScriptText(SAY_TRANSFORM_2, m_creature);
                    }
                    else
                        DoCastSpellIfCan(m_creature, SPELL_TEAR_GAS_CANCEL, CAST_TRIGGERED);
                }
                else
                    m_uiTransitionTimer -= uiDiff;

                return;
            }
            case PHASE_THREE:
            {
                // Slime Puddle
                if (m_uiPuddleTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiPuddleTimer = 30000;
                }
                else
                    m_uiPuddleTimer -= uiDiff;

                // Malleable Goo
                if (m_uiMalleableGooTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiMalleableGooTimer = 20000;
                }
                else
                    m_uiMalleableGooTimer -= uiDiff;

                // Choking Gas
                if (m_uiChokingGasBombTimer <= uiDiff)
                {
                    // if (DoCastSpellIfCan() == CAST_OK)
                        m_uiChokingGasBombTimer = urand(25000, 30000);
                }
                else
                    m_uiChokingGasBombTimer -= uiDiff;

                break;
            }
            case PHASE_RUNNING_ONE:
            case PHASE_RUNNING_TWO:
                // wait for arriving at the table (during phase transition)
                break;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_professor_putricide(Creature* pCreature)
{
    return new boss_professor_putricideAI(pCreature);
}

/**
 * mob_icc_gas_cloud
 */
struct MANGOS_DLL_DECL mob_icc_gas_cloudAI : public ScriptedAI
{
    mob_icc_gas_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetInCombatWithZone();
    }

    void Reset(){}

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

/**
 * mob_icc_volatile_ooze
 */
struct MANGOS_DLL_DECL mob_icc_volatile_oozeAI : public ScriptedAI
{
    mob_icc_volatile_oozeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetInCombatWithZone();
    }

    void Reset(){}

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

// passive mob AI struct
struct MANGOS_DLL_DECL mob_choking_gas_bombAI : public ScriptedAI
{
    mob_choking_gas_bombAI(Creature *pCreature) : ScriptedAI(pCreature){SetCombatMovement(false);}
    void Reset(){}
    void AttackStart(Unit *pWho){}
    void UpdateAI(const uint32 uiDiff){}
};
CreatureAI* GetAI_mob_choking_gas_bomb(Creature* pCreature)
{
    return new mob_choking_gas_bombAI(pCreature);
}

// passive mob AI struct
struct MANGOS_DLL_DECL mob_ooze_puddleAI : public ScriptedAI
{
    mob_ooze_puddleAI(Creature *pCreature) : ScriptedAI(pCreature){SetCombatMovement(false);}
    void Reset(){}
    void AttackStart(Unit *who){}
    void UpdateAI(const uint32 uiDiff){}
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
