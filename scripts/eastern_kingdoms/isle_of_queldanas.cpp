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
SDName: Isle_of_Queldanas
SD%Complete: 100
SDComment: Quest support: 11524, 11525
SDCategory: Isle Of Quel'Danas
EndScriptData */

/* ContentData
npc_converted_sentry
EndContentData */

#include "precompiled.h"

/*######
## npc_converted_sentry
######*/

enum
{
    SAY_CONVERTED_1             = -1000188,
    SAY_CONVERTED_2             = -1000189,

    SPELL_CONVERT_CREDIT        = 45009,
    TIME_PET_DURATION           = 7500
};

struct MANGOS_DLL_DECL npc_converted_sentryAI : public ScriptedAI
{
    npc_converted_sentryAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiCreditTimer;

    void Reset()
    {
        m_uiCreditTimer = 2500;
    }

    void MoveInLineOfSight(Unit* pWho) {}

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiCreditTimer)
        {
            if (m_uiCreditTimer <= uiDiff)
            {
                DoScriptText(urand(0, 1) ? SAY_CONVERTED_1 : SAY_CONVERTED_2, m_creature);

                DoCastSpellIfCan(m_creature, SPELL_CONVERT_CREDIT);
                ((Pet*)m_creature)->SetDuration(TIME_PET_DURATION);
                m_uiCreditTimer = 0;
            }
            else
                m_uiCreditTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_converted_sentry(Creature* pCreature)
{
    return new npc_converted_sentryAI(pCreature);
}

enum
{
    NPC_SUNWELL_DEFFENDER   = 37211,
    NPC_MORLEN_COLDGRIP     = 37542,
    NPC_SCOURGE_ZOMBIE      = 37538,
    NPC_GHOUL_INVADER       = 37539,
    NPC_CRYPT_RAIDER        = 37541,

    SPELL_EMERGE_VISUAL     = 50142,
    SPELL_THALORIEN_CREDIT  = 70265,
    SPELL_TAUNT_GHOULS      = 70266, // UNUSED
    SPELL_TAUNT_RAIDERS     = 70267, // UNUSED
    SPELL_BLADESTORM        = 67541,
    SPELL_HEROIC_STRIKE     = 57846,
    SPELL_MORTAL_STRIKE     = 67542,
    SPELL_BLOOD_PRESENCE    = 50689
};

int32 m_iDialog[15] = {-1574950,-1574951,-1574952,-1574953,-1574954,-1574955,-1574956,-1574957,-1574958,-1574959,-1574960,-1574961,-1574962,-1574963,-1574964};

static float fEventRelatedPos[18][4] =
{
    {11797.8f, -7080.17f, 26.19f, 2.55f}, // D  S
    {11798.7f, -7077.02f, 26.43f, 2.49f}, // E  P
    {11799.3f, -7073.86f, 26.14f, 2.97f}, // F  A
    {11800.3f, -7070.63f, 25.66f, 3.03f}, // E  W
    {11800.8f, -7067.59f, 25.36f, 3.13f}, // N  N
    {11803.6f, -7069.12f, 25.33f, 3.19f}, // D  S
    {11802.7f, -7072.50f, 25.56f, 2.85f}, // E  :)
    {11801.9f, -7075.78f, 26.02f, 2.76f}, // R 
    {11800.7f, -7078.54f, 26.21f, 2.83f}, //
    {11799.8f, -7081.89f, 26.22f, 2.46f}, //
    {11875.3f, -7074.49f, 28.54f, 3.11f}, // destination for Defenders (10)
    {11778.0f, -7060.30f, 25.07f, 2.51f}, // Thalorien final pos (11)
    {11758.7f, -7050.66f, 26.11f, 5.51f}, // Morien pos (12)
    {11765.3f, -7067.45f, 24.34f, 6.15f}, // Morien Adds pos (13-18)
    {11762.9f, -7055.96f, 25.13f, 6.01f}, // 
    {11763.6f, -7059.01f, 24.82f, 0.00f}, // 
    {11764.3f, -7062.07f, 24.75f, 0.00f}, // 
    {11764.7f, -7064.95f, 24.67f, 0.35f}, //
};

struct MANGOS_DLL_DECL npc_thalorien_dawnseekerAI : public ScriptedAI
{
    GuidList m_DeffendersGuid;
    GuidList m_ScurgeWaveGuid;
    ObjectGuid m_MorlenGuid;
    uint32 uiEventTimer;
    uint32 uiEventStep;
    uint32 m_uiBladestormTimer;
    uint32 m_uiHeroicStrikeTimer;
    uint32 m_uiMortalStrikeTimer;

    npc_thalorien_dawnseekerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        uiEventStep = 0;
        uiEventTimer = 1000;
        m_DeffendersGuid.clear();
        m_ScurgeWaveGuid.clear();
        m_MorlenGuid.Clear();
        Reset();
    }

    void Reset()
    {
        m_uiBladestormTimer = urand(5000, 10000);
        m_uiHeroicStrikeTimer = urand(2000, 4000);
        m_uiMortalStrikeTimer = urand(1000, 5000);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        m_ScurgeWaveGuid.erase(pSummoned->GetObjectGuid());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (uiEventTimer < uiDiff)
        {
            switch(uiEventStep)
            {
                case 0:
                    for (uint8 i = 0; i < 10; ++i)
                        if (Creature* pDeffender = m_creature->SummonCreature(NPC_SUNWELL_DEFFENDER, fEventRelatedPos[i][0], fEventRelatedPos[i][1], fEventRelatedPos[i][2], fEventRelatedPos[i][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000))
                            m_DeffendersGuid.push_back(pDeffender->GetObjectGuid());
                    uiEventTimer = 2000;
                    break;

                case 1:
                    DoScriptText(m_iDialog[0], m_creature);
                    uiEventTimer = 3500;
                    break;

                case 2:
                    DoScriptText(m_iDialog[1], m_creature);
                    uiEventTimer = 5000;
                    break;

                case 3:
                    DoScriptText(m_iDialog[2], m_creature);
                    uiEventTimer = 7000;
                    break;

                case 4:
                    DoScriptText(m_iDialog[3], m_creature);
                    uiEventTimer = 6000;
                    break;

                case 5:
                    for (GuidList::const_iterator itr = m_DeffendersGuid.begin(); itr != m_DeffendersGuid.end(); ++itr)
                        if (Creature* pDefender = m_creature->GetMap()->GetCreature(*itr))
                            pDefender->HandleEmote(EMOTE_ONESHOT_SALUTE);
                    uiEventTimer = 2000;
                    break;

                case 6:
                    for (GuidList::const_iterator itr = m_DeffendersGuid.begin(); itr != m_DeffendersGuid.end(); ++itr)
                        if (Creature* pDefender = m_creature->GetMap()->GetCreature(*itr))
                        {
                            pDefender->GetMotionMaster()->MovePoint(0, fEventRelatedPos[10][0], fEventRelatedPos[10][1], fEventRelatedPos[10][2], true);
                            pDefender->ForcedDespawn(6000);
                            pDefender->SetWalk(false);
                        }
                        m_creature->SetRespawnCoord(fEventRelatedPos[11][0], fEventRelatedPos[11][1], fEventRelatedPos[11][2], fEventRelatedPos[11][3]);
                        m_creature->GetMotionMaster()->MoveTargetedHome();
                    uiEventTimer = 2500;
                    break;

                case 7:
                    m_creature->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                    if (Unit* pCreator = m_creature->GetMap()->GetUnit(m_creature->GetCreatorGuid()))
                    {
                        m_creature->SetFacingToObject(pCreator);
                        DoScriptText(m_iDialog[4], m_creature, pCreator);
                    }
                    if (Creature* pMorlen = m_creature->SummonCreature(NPC_MORLEN_COLDGRIP, fEventRelatedPos[12][0], fEventRelatedPos[12][1], fEventRelatedPos[12][2], fEventRelatedPos[12][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000))
                    {
                        pMorlen->CastSpell(pMorlen, SPELL_BLOOD_PRESENCE, false);
                        pMorlen->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        pMorlen->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        m_MorlenGuid = pMorlen->GetObjectGuid();
                    }
                    uiEventTimer = 8000;
                    break;

                case 8:
                    if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    {
                        m_creature->SetFacingToObject(pMorlen);
                        DoScriptText(m_iDialog[5], m_creature, pMorlen);
                    }
                    uiEventTimer = 8000;
                    break;

                case 9:
                    if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    {
                        DoScriptText(m_iDialog[6], pMorlen, m_creature);
                            for (uint8 i = 0; i < 5; ++i)
                            {
                                if (Creature* pZombie = m_creature->SummonCreature(NPC_SCOURGE_ZOMBIE, fEventRelatedPos[13+i][0], fEventRelatedPos[13+i][1], fEventRelatedPos[13+i][2], fEventRelatedPos[13+i][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000))
                                {
                                    m_ScurgeWaveGuid.push_back(pZombie->GetObjectGuid());
                                    pZombie->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                    pZombie->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                }
                            }
                    }
                    uiEventTimer = 5000;
                    break;

                case 10:
                    if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    {
                        pMorlen->SetFacingToObject(m_creature);
                        pMorlen->HandleEmote(EMOTE_ONESHOT_POINT);
                        DoScriptText(m_iDialog[7], pMorlen, m_creature);
                        for (GuidList::iterator itr = m_ScurgeWaveGuid.begin(); itr != m_ScurgeWaveGuid.end(); ++itr)
                            {
                                if (Creature* pZombie = m_creature->GetMap()->GetCreature(*itr))
                                {
                                    pZombie->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                    pZombie->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    pZombie->AI()->AttackStart(m_creature);
                                }
                            }
                    }
                    uiEventTimer = 5000;
                    break;

                case 11:
                   uiEventTimer = 2000;
                   break;


                case 12:
                    if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    {
                        DoScriptText(m_iDialog[8], pMorlen, m_creature);
                            for (uint8 i = 0; i < 5; ++i)
                            {
                                if (Creature* pGhoul = m_creature->SummonCreature(NPC_GHOUL_INVADER, fEventRelatedPos[13+i][0], fEventRelatedPos[13+i][1], fEventRelatedPos[13+i][2], fEventRelatedPos[13+i][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000))
                                {
                                    pGhoul->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                                    pGhoul->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                    pGhoul->setFaction(35);
                                    pGhoul->CastSpell(pGhoul, SPELL_EMERGE_VISUAL, true);
                                    m_ScurgeWaveGuid.push_back(pGhoul->GetObjectGuid());
                                }
                            }
                    }
                    uiEventTimer = 5000;
                    break;

                case 13:
                    for (GuidList::iterator itr = m_ScurgeWaveGuid.begin(); itr != m_ScurgeWaveGuid.end(); ++itr)
                    {
                        if (Creature* pGhoul = m_creature->GetMap()->GetCreature(*itr))
                        {
                            pGhoul->setFaction(14);
                            pGhoul->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            pGhoul->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            pGhoul->AI()->AttackStart(m_creature);
                        }
                    }
                    uiEventTimer = 1000;
                    break;

                case 14:
                   uiEventTimer = 2000;
                   break;

                case 15:
                    if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    {
                        DoScriptText(m_iDialog[9], pMorlen, m_creature);
                            for (uint8 i = 0; i < 3; ++i)
                            {
                                if (Creature* pRaider = m_creature->SummonCreature(NPC_CRYPT_RAIDER, fEventRelatedPos[13+i*2][0], fEventRelatedPos[13+i*2][1], fEventRelatedPos[13+i*2][2], fEventRelatedPos[13+i*2][3], TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 360000))
                                {
                                    m_ScurgeWaveGuid.push_back(pRaider->GetObjectGuid());
                                    pRaider->AI()->AttackStart(m_creature);
                                }
                            }
                    }
                    uiEventTimer = 4000;
                    break;

               case 17:
                   if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                   {
                        pMorlen->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                        pMorlen->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        pMorlen->AI()->AttackStart(m_creature);
                        DoScriptText(m_iDialog[10], pMorlen, m_creature);
                   }
                   uiEventTimer = 4000;
                   break;

               case 18:
                   uiEventTimer = 2000;
                   break;

               case 19:
                    if (Unit* pCreator = m_creature->GetMap()->GetUnit(m_creature->GetCreatorGuid()))
                    {
                        m_creature->SetFacingToObject(pCreator);
                        DoScriptText(m_iDialog[11], m_creature, pCreator);
                    }
                    uiEventTimer = 4500;
                    break;

               case 20:
                    if (Unit* pCreator = m_creature->GetMap()->GetUnit(m_creature->GetCreatorGuid()))
                    {
                        m_creature->SetFacingToObject(pCreator);
                        DoScriptText(m_iDialog[12], m_creature, pCreator);
                    }
                    uiEventTimer = 4500;
                    break;

               case 21:
                    if (Unit* pCreator = m_creature->GetMap()->GetUnit(m_creature->GetCreatorGuid()))
                    {
                        m_creature->SetFacingToObject(pCreator);
                        DoScriptText(m_iDialog[13], m_creature, pCreator);
                        // unk. spell shoul be casted here (visual disarming thalorien)
                    }
                    uiEventTimer = 4500;
                    break;

               case 22:
                    if (Unit* pCreator = m_creature->GetMap()->GetUnit(m_creature->GetCreatorGuid()))
                    {
                        m_creature->SetFacingToObject(pCreator);
                        DoScriptText(m_iDialog[14], m_creature, pCreator);
                    }
                    m_creature->ForcedDespawn(15000);
                    uiEventTimer = 20000;
                    return;
            }

            // when i moved part of this code to SummonedCreatureJustDied it was not always triggered. would be safer to check it periodically?            
            if (uiEventStep == 18)
            {
                if (Creature* pMorlen = m_creature->GetMap()->GetCreature(m_MorlenGuid))
                    if (!pMorlen->isAlive())
                    {
                        DoCastSpellIfCan(m_creature, SPELL_THALORIEN_CREDIT, CAST_TRIGGERED);
                        ++uiEventStep;
                    }
            }
            else if ((uiEventStep != 16 && uiEventStep != 14 && uiEventStep != 11) || m_ScurgeWaveGuid.empty())
                ++uiEventStep;

        }
        else
            uiEventTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiBladestormTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BLADESTORM);
            m_uiBladestormTimer = urand(10000, 20000);
        }
        else
            m_uiBladestormTimer -= uiDiff;

        if (m_uiHeroicStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_HEROIC_STRIKE);
            m_uiHeroicStrikeTimer = urand(5000, 10000);
        }
        else
            m_uiHeroicStrikeTimer -= uiDiff;

        if (m_uiMortalStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
            m_uiMortalStrikeTimer = urand(10000, 20000);
        }
        else
            m_uiMortalStrikeTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_thalorien_dawnseeker(Creature* pCreature)
{
    return new npc_thalorien_dawnseekerAI(pCreature);
}

void AddSC_isle_of_queldanas()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_converted_sentry";
    pNewScript->GetAI = &GetAI_npc_converted_sentry;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_thalorien_dawnseeker";
    pNewScript->GetAI = &GetAI_npc_thalorien_dawnseeker;
    pNewScript->RegisterSelf();
}
