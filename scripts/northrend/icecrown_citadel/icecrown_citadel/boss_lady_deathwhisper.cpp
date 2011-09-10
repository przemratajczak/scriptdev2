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
SDName: boss_lady_deathwhisper
SD%Complete: 
SDComment: 
SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

enum BossSpells
{
/*
        //yells

        //summons
        NPC_VENGEFUL_SHADE                      = 38222,
        NPC_FANATIC                             = 37890,
        NPC_REANIMATED_FANATIC                  = 38009,
        NPC_ADHERENT                            = 37949,
        NPC_REANIMATED_ADHERENT                 = 38010,

        //Abilities
        SPELL_DARK_EMPOWERMENT                  = 70901,

        SPELL_DOMINATE_MIND                     = 71289,

        SPELL_VENGEFUL_BLAST                    = 71494,
        SPELL_VENGEFUL_BLAST_0                  = 71544,

        // summons
        SPELL_FROST_FEVER                       = 71129,
        SPELL_DEATHCHILL_BOLT                   = 70594,
        SPELL_DEATHCHILL_BLAST                  = 70906,
        SPELL_DARK_MARTYRDROM                   = 70903,
        SPELL_CURSE_OF_TOPOR                    = 71237,
        SPELL_SHORUD_OF_THE_OCCULUT             = 70768,
        SPELL_ADHERENTS_DETERMINIATION          = 71234,
        SPELL_SUMMON_VISUAL                     = 41236,

        SPELL_NECROTIC_STRIKE                   = 70659,
        SPELL_SHADOW_CLEAVE                     = 70670,
        SPELL_VAMPIRIC_MIGHT                    = 70674,*/

        // my spells
        SPELL_BERSERK                           = 26662,
        SPELL_INSIGNIFICANCE                    = 71204,
        SPELL_DOMINATE_MIND                     = 71289,
        SPELL_MANA_BARRIER                      = 70842,
        SPELL_DEATH_AND_DECAY                   = 71001,
        SPELL_SHADOW_BOLT                       = 71254,
        SPELL_FROSTBOLT                         = 71420,
        SPELL_FROSTBOLT_VOLLEY                  = 72905,

        // summons related
        SPELL_DARK_TRANSFORMATION               = 70900, // dummy spell: 70895
        SPELL_DARK_EMPOWERMENT                  = 70901, // dummy spell: 70896

        // summons spells
        SPELL_VENGEFUL_BLAST_AURA               = 71494, // must proc on melee hit
};

// talks
enum
{
    SAY_SPEECH_1                = -1631011,
    SAY_SPEECH_2                = -1631012,
    SAY_SPEECH_3                = -1631013,
    SAY_SPEECH_4                = -1631014,
    SAY_SPEECH_5                = -1631015,
    SAY_SPEECH_6                = -1631016,
    SAY_SPEECH_7                = -1631017,
    SAY_AGGRO                   = -1631018,
    SAY_PHASE_TWO               = -1631019,
    SAY_DARK_EMPOWERMENT        = -1631020,
    SAY_DARK_TRANSFORMATION     = -1631021,
    SAY_ANIMATE_DEAD            = -1631022,
    SAY_DOMINATE_MIND           = -1631023,
    SAY_BERSERK                 = -1631024,
    SAY_DEATH                   = -1631025,
    SAY_SLAY_1                  = -1631026,
    SAY_SLAY_2                  = -1631027,
};

static Locations SpawnLoc[]=
{
    {-623.055481f, 2211.326660f, 51.764259f},  // 0 Lady's stay point
    {-620.197449f, 2272.062256f, 50.848679f},  // 1 Right Door 1
    {-598.636353f, 2272.062256f, 50.848679f},  // 2 Right Door 2
    {-578.495728f, 2272.062256f, 50.848679f},  // 3 Right Door 3
    {-578.495728f, 2149.211182f, 50.848679f},  // 4 Left Door 1
    {-598.636353f, 2149.211182f, 50.848679f},  // 5 Left Door 2
    {-620.197449f, 2149.211182f, 50.848679f},  // 6 Left Door 3
    {-525.652466f, 2216.611328f, 62.823681f},  // 7 Upper marsh 1
    {-525.652466f, 2211.611328f, 62.823681f},  // 8 Upper marsh 2
    {-525.652466f, 2206.611328f, 62.823681f},  // 9 Upper marsh 3
};

struct MANGOS_DLL_DECL boss_lady_deathwhisper_eventAI : public ScriptedAI
{
    boss_lady_deathwhisper_eventAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiStep = 0;
        m_uiEventTimer = 0;
        m_bIsEventStarted = false;
        m_bIsEventFinished = true;
    }

    uint32 m_uiStep;
    uint32 m_uiEventTimer;
    bool m_bIsEventStarted;
    bool m_bIsEventFinished;

    void Reset(){}

    void NextStep(uint32 uiTimer)
    {
        m_uiEventTimer = uiTimer;
        ++m_uiStep;
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!m_bIsEventStarted)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                m_bIsEventStarted = true;
                NextStep(0);
                return;
            }
        }

        ScriptedAI::MoveInLineOfSight(pWho);
    }

    // for the fight handler
    virtual void UpdateFightAI(const uint32 uiDiff){}

    void UpdateAI(const uint32 uiDiff)
    {
        UpdateFightAI(uiDiff);

        if (!m_bIsEventStarted || m_bIsEventFinished)
            return;

        if (m_uiEventTimer <= uiDiff)
        {
            switch (m_uiStep)
            {
                case 0:
                {
                    break;
                }
                case 1:
                {
                    DoScriptText(SAY_SPEECH_1, m_creature);
                    NextStep(10000);
                    break;
                }
                case 2:
                {
                    DoScriptText(SAY_SPEECH_2, m_creature);
                    NextStep(10000);
                    break;
                }
                case 3:
                {
                    DoScriptText(SAY_SPEECH_3, m_creature);
                    NextStep(10000);
                    break;
                }
                case 4:
                {
                    DoScriptText(SAY_SPEECH_4, m_creature);
                    NextStep(10000);
                    break;
                }
                case 5:
                {
                    DoScriptText(SAY_SPEECH_5, m_creature);
                    NextStep(10000);
                    break;
                }
                case 6:
                {
                    DoScriptText(SAY_SPEECH_6, m_creature);
                    NextStep(10000);
                    break;
                }
                case 7:
                {
                    DoScriptText(SAY_SPEECH_7, m_creature);
                    NextStep(10000);
                    break;
                }
                case 8:
                {
                    m_bIsEventFinished = true;
                    break;
                }
                default:
                    break;
            }
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

struct MANGOS_DLL_DECL boss_lady_deathwhisperAI : public boss_lady_deathwhisper_eventAI
{
    boss_lady_deathwhisperAI(Creature* pCreature) : boss_lady_deathwhisper_eventAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        Reset();
    }

    ScriptedInstance *m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    bool m_bIsPhaseOne;
    uint32 m_uiManaBarrierCheckTimer;

    uint32 m_uiBerserkTimer;
    uint32 m_uiSummonWaveTimer;
    uint32 m_uiTouchOfInsignificanceTimer;
    uint32 m_uiShadowBoltTimer;
    uint32 m_uiDeathAndDecayTimer;
    uint32 m_uiFrostboltTimer;
    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiDominateMindTimer;

    void Reset()
    {
        m_bIsPhaseOne                   = true;
        m_uiManaBarrierCheckTimer       = 1000;
        m_uiBerserkTimer                = 10 * MINUTE * IN_MILLISECONDS;
        m_uiSummonWaveTimer             = 5000;
        m_uiTouchOfInsignificanceTimer  = 10000;
        m_uiShadowBoltTimer             = urand(3000, 5000);
        m_uiDeathAndDecayTimer          = urand(10000, 15000);
        m_uiFrostboltTimer              = urand(5000, 10000);
        m_uiFrostboltVolleyTimer        = urand(10000, 20000);
        m_uiDominateMindTimer           = urand(30000, 45000);

        SetCombatMovement(false);
    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DEATHWHISPER, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_MANA_BARRIER, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DEATHWHISPER, FAIL);
    }

    void JustDied(Unit *pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_DEATHWHISPER, DONE);

        DoScriptText(SAY_DEATH, m_creature);
    }

    void KilledUnit(Unit *pVictim)
    {
        DoScriptText(SAY_SLAY_1 - urand(0, 1), m_creature);
    }

    void UpdateFightAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // ***********
        // Both Phases

        // Berserk - both phases
        if (m_uiBerserkTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BERSERK) == CAST_OK)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_uiBerserkTimer = 10 * MINUTE * IN_MILLISECONDS;
            }
        }
        else
            m_uiBerserkTimer -= uiDiff;

        // Death and Decay
        if (m_uiDeathAndDecayTimer <= uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_DEATH_AND_DECAY) == CAST_OK)
                    m_uiDeathAndDecayTimer = urand(10000, 15000);
            }
        }
        else
            m_uiDeathAndDecayTimer -= uiDiff;

        // Dominate Mind
        if (m_uiDominateMindTimer <= uiDiff)
        {
            DoScriptText(SAY_DOMINATE_MIND, m_creature);
            m_uiDominateMindTimer = urand(30000, 45000);
        }
        else
            m_uiDominateMindTimer -= uiDiff;

        // ******************
        // end of both phases


        if (m_bIsPhaseOne)
        {
            // Mana Barrier check
            if (m_uiManaBarrierCheckTimer <= uiDiff)
            {
                // phase ends when Mana Barrier wears off
                if (!m_creature->HasAura(SPELL_MANA_BARRIER))
                {
                    DoScriptText(SAY_PHASE_TWO, m_creature);
                    SetCombatMovement(true);
                    m_creature->AI()->AttackStart(m_creature->getVictim());
                    m_bIsPhaseOne = false;
                    return;
                }

                m_uiManaBarrierCheckTimer = 1000;
            }
            else
                m_uiManaBarrierCheckTimer -= uiDiff;

            // Shadow Bolt
            if (m_uiShadowBoltTimer <= uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_SHADOW_BOLT) == CAST_OK)
                        m_uiShadowBoltTimer = urand(3000, 5000);
                }
            }
            else
                m_uiShadowBoltTimer -= uiDiff;
        }
        else
        {
            // Summon wave
            if (m_uiSummonWaveTimer <= uiDiff)
            {
                //if ()
                //{
                    m_uiSummonWaveTimer = 60000;
                    DoScriptText(SAY_ANIMATE_DEAD, m_creature);
                //}
            }
            else
                m_uiSummonWaveTimer -= uiDiff;

            // Frostbolt
            if (m_uiFrostboltTimer <= uiDiff)
            {
                if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_FROSTBOLT) == CAST_OK)
                        m_uiFrostboltTimer = urand(5000, 10000);
                }
            }
            else
                m_uiFrostboltTimer -= uiDiff;

            // Frostbolt Volley
            if (m_uiFrostboltVolleyTimer <= uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                    m_uiFrostboltVolleyTimer = urand(5000, 10000);
            }
            else
                m_uiFrostboltVolleyTimer -= uiDiff;

            // melee attack in 2nd phase only
            DoMeleeAttackIfReady();
        }
    }
};

CreatureAI* GetAI_boss_lady_deathwhisper(Creature* pCreature)
{
    return new boss_lady_deathwhisperAI(pCreature);
}

/*
struct MANGOS_DLL_DECL boss_lady_deathwhisperAI : public BSWScriptedAI
{
    boss_lady_deathwhisperAI(Creature* pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    uint8 stage;
    bool MovementStarted;
    bool intro;

    void Reset()
    {
        if(!pInstance) return;
        if (m_creature->isAlive()) pInstance->SetData(TYPE_DEATHWHISPER, NOT_STARTED);
        stage = 0;
        MovementStarted = false;
        intro = false;
        resetTimers();
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (m_creature->CanInitiateAttack() && pWho->isTargetableForAttack() &&
        m_creature->IsHostileTo(pWho) && pWho->isInAccessablePlaceFor(m_creature))
        {
        if (m_creature->IsWithinDistInMap(pWho, m_creature->GetAttackDistance(pWho)) && m_creature->IsWithinLOSInMap(pWho))
        {
            if (!m_creature->getVictim())
            {
                pWho->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);
                AttackStart(pWho);
            }
            else if (m_creature->GetMap()->IsDungeon())
            {
                pWho->SetInCombatWith(m_creature);
                m_creature->AddThreat(pWho);
            }
        }
    }
        if (stage) return;
        else intro = true;
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(SAY_SLAY_1 - urand(0, 1), m_creature, pVictim);
    }

    void JustReachedHome()
    {
        if (pInstance)
            pInstance->SetData(TYPE_DEATHWHISPER, FAIL);
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if(!pInstance)
            return;

        if(type != POINT_MOTION_TYPE)
            return;

        if(MovementStarted && id != 1)
        {
            m_creature->GetMotionMaster()->MovePoint(1, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z);
        }
        else
        {
            m_creature->GetMotionMaster()->MovementExpired();
            MovementStarted = false;
            SetCombatMovement(false);
        }
    }

    void Aggro(Unit* pWho)
    {
        if (!pInstance)
            return;

        pInstance->SetData(TYPE_DEATHWHISPER, IN_PROGRESS);
        doCast(SPELL_MANA_BARRIER );
        MovementStarted = true;
        SetCombatMovement(false);
        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->GetMotionMaster()->MovePoint(1, SpawnLoc[0].x, SpawnLoc[0].y, SpawnLoc[0].z);
    }

    void JustDied(Unit *pKiller)
    {
        if(pInstance)
            pInstance->SetData(TYPE_DEATHWHISPER, DONE);

        DoScriptText(SAY_DEATH, m_creature, pKiller);
        doRemoveFromAll(SPELL_INSIGNIFICANCE);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if(!pInstance || !pSummoned)
            return;

        if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0) )
            pSummoned->AddThreat(pTarget, 100.0f);
    }

    void CallGuard(uint8 place)
    {
        if (place < 2)
        {
            doSummon(urand(0,1) ? NPC_FANATIC : NPC_ADHERENT, SpawnLoc[3*place+1].x, SpawnLoc[3*place+1].y, SpawnLoc[3*place+1].z);
            doSummon(urand(0,1) ? NPC_FANATIC : NPC_ADHERENT, SpawnLoc[3*place+3].x, SpawnLoc[3*place+3].y, SpawnLoc[3*place+3].z);
        }
        doSummon(urand(0,1) ? NPC_FANATIC : NPC_ADHERENT, SpawnLoc[3*place+2].x, SpawnLoc[3*place+2].y, SpawnLoc[3*place+2].z);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (!m_creature || !m_creature->isAlive())
            return;

        if (hasAura(SPELL_MANA_BARRIER, m_creature))
        {
            if (m_creature->GetPower(POWER_MANA) > uiDamage)
            {
                m_creature->SetPower(POWER_MANA,m_creature->GetPower(POWER_MANA)-uiDamage);
                uiDamage = 0;
            }
            else
            {
                m_creature->RemoveAurasDueToSpell(SPELL_DARK_EMPOWERMENT);
                m_creature->SetPower(POWER_MANA,0);
                doRemove(SPELL_MANA_BARRIER);
            }
        }
        else
            return;
    }

    void UpdateAI(const uint32 diff)
    {
        if (intro && timedQuery(SPELL_SHADOW_BOLT,diff))
        {
            switch (stage)
            {
                case 0:
                       DoScriptText(SAY_SPEECH_1, m_creature);
                       stage = 1;
                       break;
                case 1:
                       DoScriptText(SAY_SPEECH_4, m_creature);
                       stage = 2;
                       break;
                case 2:
                       DoScriptText(SAY_SPEECH_7, m_creature);
                       stage = 3;
                       break;
                default:
                       break;
            }
        }

        if (hasAura(SPELL_MANA_BARRIER, m_creature))
        {
            if(m_creature->GetHealth() <= m_creature->GetMaxHealth())
            {
                if (m_creature->GetPower(POWER_MANA) > (m_creature->GetMaxHealth() - m_creature->GetHealth()))
                {
                    m_creature->SetPower(POWER_MANA,m_creature->GetPower(POWER_MANA)-(m_creature->GetMaxHealth() - m_creature->GetHealth()));
                    m_creature->SetHealth(m_creature->GetMaxHealth());
                }
                else
                    m_creature->SetPower(POWER_MANA,0);
            }
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (MovementStarted)
            return;

        switch(stage)
        {
            case 3: {
                    if (IsCombatMovement())
                        SetCombatMovement(false);

                    timedCast(SPELL_SHADOW_BOLT,diff);

                    if (timedQuery(NPC_FANATIC, diff))
                        {
                        DoScriptText(SAY_ANIMATE_DEAD,m_creature);
                        switch (currentDifficulty) {
                             case RAID_DIFFICULTY_10MAN_NORMAL:
                                       CallGuard(urand(0,1));
                                       break;
                             case RAID_DIFFICULTY_10MAN_HEROIC:
                                       CallGuard(urand(0,1));
                                       if (urand(0,1)) CallGuard(2);
                                       break;
                             case RAID_DIFFICULTY_25MAN_NORMAL:
                                       CallGuard(0);
                                       CallGuard(1);
                                       if (urand(0,1)) CallGuard(2);
                                       break;
                             case RAID_DIFFICULTY_25MAN_HEROIC:
                                       CallGuard(0);
                                       CallGuard(1);
                                       CallGuard(2);
                                       break;
                             default:
                                       break;

                                            }
                        }

                    if (timedQuery(SPELL_DARK_EMPOWERMENT ,diff))
                    {
                    switch (urand(0,1)) {
                            case 0:
                                  if(Creature *pGuard = GetClosestCreatureWithEntry(m_creature, NPC_FANATIC, 100.0f))
                                  {
                                      doCast(SPELL_DARK_EMPOWERMENT, pGuard);
                                      DoScriptText(SAY_DARK_EMPOWERMENT, m_creature);
                                  };
                                  break;
                            case 1:
                                  if(Creature *pGuard = GetClosestCreatureWithEntry(m_creature, NPC_ADHERENT, 100.0f))
                                  {
                                      doCast(SPELL_DARK_EMPOWERMENT, pGuard);
                                      DoScriptText(SAY_DARK_EMPOWERMENT, m_creature);
                                  };
                                  break;
                                  }
                    }

                    break;}

            case 4: {
                    timedCast(SPELL_FROSTBOLT, diff);

                    timedCast(SPELL_INSIGNIFICANCE, diff);

                    timedCast(NPC_VENGEFUL_SHADE, diff);

                    if (is25()) timedCast(SPELL_DOMINATE_MIND, diff);

                    if (timedQuery(NPC_FANATIC, diff))
                        {
                        switch (currentDifficulty) {
                             case RAID_DIFFICULTY_10MAN_HEROIC:
                                       CallGuard(urand(0,1));
                                       if (urand(0,1)) CallGuard(2);
                                       break;
                             case RAID_DIFFICULTY_25MAN_HEROIC:
                                       CallGuard(0);
                                       CallGuard(1);
                                       CallGuard(2);
                                       break;
                             default:
                                       break;

                                            }
                        }

                    break;}
        }

                    timedCast(SPELL_DEATH_AND_DECAY, diff);


         if (!hasAura(SPELL_MANA_BARRIER, m_creature) && stage == 3)
               {
                stage = 4;
                DoScriptText(SAY_PHASE_TWO, m_creature);
                SetCombatMovement(true);
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
               }

         if (timedQuery(SPELL_BERSERK, diff))
                {
                doCast(SPELL_BERSERK);
                DoScriptText(SAY_BERSERK, m_creature);
                };

         DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_lady_deathwhisper(Creature* pCreature)
{
    return new boss_lady_deathwhisperAI(pCreature);
}

struct MANGOS_DLL_DECL mob_vengeful_shadeAI : public BSWScriptedAI
{
    mob_vengeful_shadeAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = ((ScriptedInstance*)pCreature->GetInstanceData());
        Reset();
    }

    ScriptedInstance *m_pInstance;

    void Reset()
    {
        m_creature->SetRespawnDelay(DAY);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetInCombatWithZone();
        if (Unit* pTarget= m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0) ) {
                m_creature->AddThreat(pTarget, 1000.0f);
                m_creature->GetMotionMaster()->MoveChase(pTarget);
                m_creature->SetSpeedRate(MOVE_RUN, 0.5);
                }
        doCast(SPELL_VENGEFUL_BLAST);
    }


    void UpdateAI(const uint32 uiDiff)
    {
        if(m_pInstance && m_pInstance->GetData(TYPE_DEATHWHISPER) != IN_PROGRESS)
            m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (timedQuery(SPELL_VENGEFUL_BLAST_0, uiDiff))
        {
            if (m_creature->IsWithinDist(m_creature->getVictim(), 5.0f, false))
            {
                doCast(SPELL_VENGEFUL_BLAST_0);
                m_creature->ForcedDespawn(500);
            }
            else
            {
                m_creature->GetMotionMaster()->MoveChase(m_creature->getVictim());
                m_creature->SetSpeedRate(MOVE_RUN, 0.5);
            }
        }
    }

};

CreatureAI* GetAI_mob_vengeful_shade(Creature* pCreature)
{
    return new mob_vengeful_shadeAI(pCreature);
}

struct MANGOS_DLL_DECL  mob_cult_adherentAI : public BSWScriptedAI
{
    mob_cult_adherentAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    bool bone;

    void Reset()
    {
        resetTimers();
        m_creature->SetRespawnDelay(DAY);
        doCast(SPELL_SUMMON_VISUAL);
        bone = false;
    }

    void Aggro(Unit *who)
    {
        doCast(SPELL_SHORUD_OF_THE_OCCULUT);
        DoStartMovement(who, 20.0f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!pInstance || pInstance->GetData(TYPE_DEATHWHISPER) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

            timedCast(SPELL_FROST_FEVER, uiDiff);

            timedCast(SPELL_DEATHCHILL_BOLT, uiDiff);

            timedCast( SPELL_DEATHCHILL_BLAST, uiDiff);

            if (m_creature->GetHealthPercent() < 15.0f && !bone)
            {
                if (!urand(0,3)) doCast(SPELL_DARK_MARTYRDROM); //30%
                bone = true;
            }
    }
};

CreatureAI* GetAI_mob_cult_adherent(Creature* pCreature)
{
    return new mob_cult_adherentAI(pCreature);
}

struct MANGOS_DLL_DECL  mob_cult_fanaticAI : public BSWScriptedAI
{
    mob_cult_fanaticAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    bool bone;

    void Reset()
    {
        resetTimers();
        m_creature->SetRespawnDelay(DAY);
        bone = false;
    }

    void Aggro(Unit *who)
    {
        doCast(SPELL_VAMPIRIC_MIGHT);
        DoStartMovement(who);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!pInstance || pInstance->GetData(TYPE_DEATHWHISPER) != IN_PROGRESS)
              m_creature->ForcedDespawn();

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

            timedCast(SPELL_NECROTIC_STRIKE, uiDiff);

            timedCast(SPELL_SHADOW_CLEAVE, uiDiff);

            if (m_creature->GetHealthPercent() < 15.0f && !bone)
            {
                if (!urand(0,3)) doCast(SPELL_DARK_MARTYRDROM); //30%
                bone = true;
            }
    }
};

CreatureAI* GetAI_mob_cult_fanatic(Creature* pCreature)
{
    return new mob_cult_fanaticAI(pCreature);
}
*/

void AddSC_boss_lady_deathwhisper()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_lady_deathwhisper";
    pNewScript->GetAI = &GetAI_boss_lady_deathwhisper;
    pNewScript->RegisterSelf();
/*
    pNewScript = new Script;
    pNewScript->Name = "mob_vengeful_shade";
    pNewScript->GetAI = &GetAI_mob_vengeful_shade;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_cult_adherent";
    pNewScript->GetAI = &GetAI_mob_cult_adherent;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_cult_fanatic";
    pNewScript->GetAI = &GetAI_mob_cult_fanatic;
    pNewScript->RegisterSelf();
*/
}
