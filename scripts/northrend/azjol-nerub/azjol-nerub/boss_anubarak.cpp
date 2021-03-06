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
SDName: Boss_Anubarak
SD%Complete: 20%
SDComment:
SDCategory: Azjol'NerubstrInstData
EndScriptData */

#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    SAY_INTRO                       = -1601014,
    SAY_AGGRO                       = -1601015,
    SAY_KILL_1                      = -1601016,
    SAY_KILL_2                      = -1601017,
    SAY_KILL_3                      = -1601018,
    SAY_SUBMERGE_1                  = -1601019,
    SAY_SUBMERGE_2                  = -1601020,
    SAY_LOCUST_1                    = -1601021,
    SAY_LOCUST_2                    = -1601022,
    SAY_LOCUST_3                    = -1601023,
    SAY_DEATH                       = -1601024,

    SPELL_CARRION_BEETLES           = 53520,
    SPELL_SUBMERGE                  = 53421,
    SPELL_EMERGE                    = 53500,
    SPELL_SUMMON_CARRION_BEETLES    = 53521,
    SPELL_IMPALE_PERIODIC           = 53456,
    SPELL_SUMMON_ANUBAR_DARTER      = 53599,
    SPELL_SUMMON_ANUBAR_GUARD_TRIG  = 53613,
    SPELL_SUMMON_ANUBAR_ASSASSIN    = 53609,
    SPELL_SUMMON_ANUBAR_VENOMANCER  = 53615,
    SPELL_LEECHING_SWARM_N          = 53467,
    SPELL_LEECHING_SWARM_H          = 59430,
    SPELL_IMPALE_N                  = 53454,
    SPELL_IMPALE_H                  = 59446,
    SPELL_POUND_N                   = 53472,
    SPELL_POUND_H                   = 59433,

    POINT_ANUBARAK_SPAWN_POS        = 0,
    NPC_ANUBAR_GUARDIAN             = 29216,
    NPC_ANUBAR_VENOMANCER           = 29217
};

float fSummonPosition[3] = {550.0f, 345.0f, 240.0f};

/*######
## boss_anubarak
######*/

struct MANGOS_DLL_DECL boss_anubarakAI : public ScriptedAI
{
    boss_anubarakAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_azjol_nerub*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        m_creature->GetRespawnCoord(fPosX, fPosY, fPozZ);
        Reset();
    }

    instance_azjol_nerub* m_pInstance;
    bool m_bIsRegularMode;

    float fHealthPercent;
    float fPosX, fPosY, fPozZ;
    uint32 m_uiSubmergePhase_Timer;
    uint32 m_uiCarrionBeetles_Timer;
    uint32 m_uiLeechingSwarm_Timer;
    uint32 m_uiImpale_Timer;
    uint32 m_uiPound_Timer;
    uint32 m_uiSummonEliteAdd_Timer;
    uint32 m_uiSummonNonEliteAdd_Timer;
    uint32 m_uiCombatProgress;
    uint32 m_uiGottaGoTimer;
    float fTimerPenalty;

    GuidList lSummons;

    void Reset()
    {
        m_uiCombatProgress = 25000;
        m_uiGottaGoTimer = 4*MINUTE*IN_MILLISECONDS;
        fTimerPenalty = 1.0f;
        fHealthPercent = 75.0f;
        m_uiSubmergePhase_Timer = 45000;
        m_uiCarrionBeetles_Timer = 8000;
        m_uiLeechingSwarm_Timer = 20000;
        m_uiImpale_Timer = 9000;
        m_uiPound_Timer = 15000;
        m_uiSummonEliteAdd_Timer = 10000;
        m_uiSummonNonEliteAdd_Timer = 5000;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        SetCombatMovement(true);
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUBARAK, IN_PROGRESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0, 2))
        {
            case 0: DoScriptText(SAY_KILL_1, m_creature); break;
            case 1: DoScriptText(SAY_KILL_2, m_creature); break;
            case 2: DoScriptText(SAY_KILL_3, m_creature); break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_ANUBARAK, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_ANUBARAK, NOT_STARTED);
            m_pInstance->m_bAnubAchievFailed = false;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        lSummons.push_back(pSummoned->GetObjectGuid());
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        DoCastSpellIfCan(m_creature, SPELL_IMPALE_PERIODIC, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_SUBMERGE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiGottaGoTimer < uiDiff)
        {
            m_pInstance->m_bAnubAchievFailed = true;
        }
        else
            m_uiGottaGoTimer -= uiDiff;

        if (m_uiCombatProgress < uiDiff)
        {
            fTimerPenalty = ((fTimerPenalty > 0.4f) ? (fTimerPenalty -= 0.1 * fTimerPenalty) : (fTimerPenalty));
            m_uiCombatProgress = 25000;
        }
        else
            m_uiCombatProgress -= uiDiff;

        if (m_creature->HasAura(SPELL_SUBMERGE))
        {
            if (m_uiSubmergePhase_Timer < uiDiff)
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                m_creature->RemoveAurasDueToSpell(SPELL_IMPALE_PERIODIC);
                DoCastSpellIfCan(m_creature, SPELL_EMERGE);
                SetCombatMovement(true);
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                m_uiSubmergePhase_Timer = 45000;
                return;
            }
            else
                m_uiSubmergePhase_Timer -= uiDiff;

            if (m_uiSummonEliteAdd_Timer < uiDiff)
            {
                Creature* pGuardian = m_creature->SummonCreature(NPC_ANUBAR_GUARDIAN, fSummonPosition[0], fSummonPosition[1], fSummonPosition[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
                Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                if (pGuardian && pTarget)
                {
                    pGuardian->AI()->AttackStart(pTarget);
                    if (!m_bIsRegularMode)
                        if (Creature* pVenomancer = m_creature->SummonCreature(NPC_ANUBAR_VENOMANCER, fSummonPosition[0], fSummonPosition[1] + 5, fSummonPosition[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000))
                            pVenomancer->AI()->AttackStart(pTarget);
                }
                
                //DoCastSpellIfCan(m_creature, SPELL_SUMMON_ANUBAR_GUARD_TRIG, CAST_TRIGGERED);
                //DoCastSpellIfCan(m_creature, SPELL_SUMMON_ANUBAR_VENOMANCER, CAST_TRIGGERED);
                m_uiSummonEliteAdd_Timer = 50000 * fTimerPenalty;
            }
            else
                m_uiSummonEliteAdd_Timer -= uiDiff;

            if (m_uiSummonNonEliteAdd_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_SUMMON_ANUBAR_ASSASSIN, CAST_TRIGGERED);
                DoCastSpellIfCan(m_creature, SPELL_SUMMON_ANUBAR_ASSASSIN, CAST_TRIGGERED);
                if (fTimerPenalty < 0.6f)
                    DoCastSpellIfCan(m_creature, SPELL_SUMMON_ANUBAR_DARTER, CAST_TRIGGERED);

                m_uiSummonNonEliteAdd_Timer = 15000 * fTimerPenalty;
            }
            else
                m_uiSummonNonEliteAdd_Timer -= uiDiff;
        }
        else
        {
            if (fHealthPercent)
                if (m_creature->GetHealthPercent() < fHealthPercent)
                {
                    fHealthPercent -= 25;
                    SetCombatMovement(false);
                    m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    m_creature->InterruptNonMeleeSpells(false);
                    m_creature->GetMotionMaster()->MovePoint(POINT_ANUBARAK_SPAWN_POS, fPosX, fPosY, fPozZ);
                    return;
                }

            if (m_uiCarrionBeetles_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUMMON_CARRION_BEETLES);
                m_uiCarrionBeetles_Timer = 8000;
            }
            else
                m_uiCarrionBeetles_Timer -= uiDiff;

            if (m_uiLeechingSwarm_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_LEECHING_SWARM_N : SPELL_LEECHING_SWARM_H);
                m_uiLeechingSwarm_Timer = 20000;
            }
            else
                m_uiLeechingSwarm_Timer -= uiDiff;

            if (m_uiPound_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_POUND_N : SPELL_POUND_H);
                m_uiPound_Timer = 15000;
            }
            else
                m_uiPound_Timer -= uiDiff; 

            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_anubarak(Creature* pCreature)
{
    return new boss_anubarakAI(pCreature);
}

void AddSC_boss_anubarak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_anubarak";
    pNewScript->GetAI = &GetAI_boss_anubarak;
    pNewScript->RegisterSelf();
}

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
SDName: boss_anubarak
SD%Complete: ?%
SDComment: by MaxXx2021
SDCategory: Azjol-Nerub instance
EndScriptData */
/*

#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    SPELL_CARRION_BEETLES                         = 53520,
    SPELL_SUMMON_CARRION_BEETLES                  = 53521,
    SPELL_LEECHING_SWARM                          = 53467,
    SPELL_IMPALE                                  = 53454,
    SPELL_POUND                                   = 53472,
    SPELL_SUBMERGE                                = 53421,

    NPC_GUARDIAN                             = 29216,
    NPC_VENOMANCER                           = 29217,
    NPC_DATTER                               = 29213,

    SAY_INTRO                                     = -1601010,
    SAY_AGGRO                                     = -1601000,
    SAY_SLAY_1                                    = -1601001,
    SAY_SLAY_2                                    = -1601002,
    SAY_SLAY_3                                    = -1601003,
    SAY_LOCUST_1                                  = -1601005,
    SAY_LOCUST_2                                  = -1601006,
    SAY_LOCUST_3                                  = -1601007,
    SAY_SUBMERGE_1                                = -1601008,
    SAY_SUBMERGE_2                                = -1601009,
    SAY_DEATH                                     = -1601004
};

struct Locations
{
    float x, y, z;
    uint32 id;
};

static Locations SpawnPoint[2] =
{
    {550.7f, 282.8f, 224.3f},
    {551.1f, 229.4f, 224.3f}
};

struct MANGOS_DLL_DECL boss_anubarakAI : public ScriptedAI
{
    boss_anubarakAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;

    bool bChanneling;
    bool bGuardianSummoned;
    bool bVenomancerSummoned;
    bool bDatterSummoned;
    uint8 uiPhase;
    uint32 uiPhaseTimer;
    uint32 uiEmergeTimer;

    uint32 uiCarrionBeetlesTimer;
    uint32 uiLeechingSwarmTimer;
    uint32 uiImpaleTimer;
    uint32 uiPoundTimer;
    uint32 uiSubmergeTimer;
    uint32 uiUndergroundTimer;
    uint32 uiVenomancerTimer;
    uint32 uiDatterTimer;

    //SummonList lSummons;

    void Reset()
    {

        uiCarrionBeetlesTimer = 8000;
        uiLeechingSwarmTimer = 20000;
        uiImpaleTimer = 9000;
        uiPoundTimer = 15000;

        uiPhase = 0;
        uiPhaseTimer = 0;
        bChanneling = false;

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
        m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
        m_creature->SetDisplayId(27856);

        DespawnAll();

        if (pInstance)
            pInstance->SetData(TYPE_ANUBARAK, NOT_STARTED);
    }

    void AttackStart(Unit* who)
    {
       if(!who) return;

       if(uiPhase > 0) return;

       ScriptedAI::AttackStart(who);
    }

    void DespawnAll()
    {
        std::list<Creature*> m_pGuard;
        GetCreatureListWithEntryInGrid(m_pGuard, m_creature, NPC_GUARDIAN, DEFAULT_VISIBILITY_INSTANCE);

        if (!m_pGuard.empty())
            for(std::list<Creature*>::iterator itr = m_pGuard.begin(); itr != m_pGuard.end(); ++itr)
            {
                (*itr)->ForcedDespawn();
            }

        std::list<Creature*> m_pVen;
        GetCreatureListWithEntryInGrid(m_pVen, m_creature, NPC_VENOMANCER, DEFAULT_VISIBILITY_INSTANCE);

        if (!m_pVen.empty())
            for(std::list<Creature*>::iterator iter = m_pVen.begin(); iter != m_pVen.end(); ++iter)
            {
                (*iter)->ForcedDespawn();
            }

        std::list<Creature*> m_pDat;
        GetCreatureListWithEntryInGrid(m_pDat, m_creature, NPC_DATTER, DEFAULT_VISIBILITY_INSTANCE);

        if (!m_pDat.empty())
            for(std::list<Creature*>::iterator iter = m_pDat.begin(); iter != m_pDat.end(); ++iter)
            {
                (*iter)->ForcedDespawn();
            }
    }

    void EnterCombat(Unit *pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);

        if (pInstance)
            pInstance->SetData(TYPE_ANUBARAK, IN_PROGRESS);
    }

    void NextPhase()
    {
        m_creature->InterruptNonMeleeSpells(false);
        ++uiPhaseTimer;

        bGuardianSummoned = false;
        bVenomancerSummoned = false;
        bDatterSummoned = false;

        uiUndergroundTimer = 40000;
        uiVenomancerTimer = 25000;
        uiDatterTimer = 32000;

        DoCast(m_creature, SPELL_SUBMERGE);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);

        uiPhase = 1;
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (bChanneling == true)
        {
            for (uint8 i = 0; i < 4; ++i)
                DoCast(m_creature->getVictim(), SPELL_SUMMON_CARRION_BEETLES, true);
            bChanneling = false;
        }

        if (uiPhase == 1)
        {
            if (uiImpaleTimer <= diff)
            {
                if(m_creature->HasAura(SPELL_SUBMERGE))
                {
                   m_creature->RemoveAurasDueToSpell(SPELL_SUBMERGE);
                   m_creature->SetDisplayId(11686);       
                   m_creature->StopMoving();
                   m_creature->GetMotionMaster()->Clear(false);
                   m_creature->GetMotionMaster()->MoveIdle();
                }
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                    DoCast(pTarget, SPELL_IMPALE);
                uiImpaleTimer = 9000;
            } else uiImpaleTimer -= diff;

            if (!bGuardianSummoned)
            {
                for (uint8 i = 0; i < 2; ++i)
                {
                    if (Creature *Guardian = m_creature->SummonCreature(NPC_GUARDIAN,SpawnPoint[i].x,SpawnPoint[i].y,SpawnPoint[i].z,0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,30000))
                    {
                        Guardian->AddThreat(m_creature->getVictim(), 0.0f);
                        Guardian->SetInCombatWithZone();
                    }
                }
                bGuardianSummoned = true;
            }

            if (!bVenomancerSummoned)
            {
                if (uiVenomancerTimer <= diff)
                {
                    if (uiPhaseTimer > 1)
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Creature *Venomancer = m_creature->SummonCreature(NPC_VENOMANCER,SpawnPoint[i].x,SpawnPoint[i].y,SpawnPoint[i].z,0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,30000))
                            {
                                Venomancer->AddThreat(m_creature->getVictim(), 0.0f);
                                Venomancer->SetInCombatWithZone();
                            }
                        }
                        bVenomancerSummoned = true;
                    }
                } else uiVenomancerTimer -= diff;
            }

            if (!bDatterSummoned)
            {
                if (uiDatterTimer <= diff)
                {
                    if (uiPhaseTimer > 2)
                    {
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Creature *Datter = m_creature->SummonCreature(NPC_DATTER,SpawnPoint[i].x,SpawnPoint[i].y,SpawnPoint[i].z,0,TEMPSUMMON_CORPSE_TIMED_DESPAWN,30000))
                            {
                                Datter->AddThreat(m_creature->getVictim(), 0.0f);
                                Datter->SetInCombatWithZone();
                            }
                        }
                        bDatterSummoned = true;
                    }
                } else uiDatterTimer -= diff;
            }

            if (uiUndergroundTimer <= diff)
            {
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetDisplayId(27856);
                DoCast(m_creature, 50142);
                uiEmergeTimer = 2000;
                uiPhase = 2;
            } else uiUndergroundTimer -= diff;
        }

        if (uiPhase == 2)
        {
            if (uiEmergeTimer <= diff)
            {
                uiPhase = 0;
                m_creature->RemoveAurasDueToSpell(50142);
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
            } else uiEmergeTimer -= diff;
        }

        if (uiPhase == 0)
        {
            if (uiLeechingSwarmTimer <= diff)
            {
                DoCast(m_creature, SPELL_LEECHING_SWARM);
                uiLeechingSwarmTimer = 19000;
            } else uiLeechingSwarmTimer -= diff;

            if (uiCarrionBeetlesTimer <= diff)
            {
                bChanneling = true;
                DoCast(m_creature->getVictim(), SPELL_CARRION_BEETLES);
                uiCarrionBeetlesTimer = 25000;
            } else uiCarrionBeetlesTimer -= diff;

            if (uiPoundTimer <= diff)
            {
                 DoCast(m_creature->getVictim(), SPELL_POUND);
                 uiPoundTimer = 16500;
            } else uiPoundTimer -= diff;

            DoMeleeAttackIfReady();
        }

        if(uiPhaseTimer == 0 && m_creature->GetHealthPercent() < 75.0f)
            NextPhase();

        if(uiPhaseTimer == 1 && m_creature->GetHealthPercent() < 50.0f)
            NextPhase();

        if(uiPhaseTimer == 2 && m_creature->GetHealthPercent() < 25.0f)
            NextPhase();
    }

    void JustDied(Unit *pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        if (pInstance)
            pInstance->SetData(TYPE_ANUBARAK, DONE);
    }

    void KilledUnit(Unit *pVictim)
    {
        if (pVictim == m_creature)
            return;

        DoScriptText(urand(SAY_SLAY_1,SAY_SLAY_2), m_creature);
    }

};

CreatureAI* GetAI_boss_anubarak(Creature *pCreature)
{
    return new boss_anubarakAI (pCreature);
}

void AddSC_boss_anubarak()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_anubarak";
    newscript->GetAI = &GetAI_boss_anubarak;
    newscript->RegisterSelf();
}
*/
