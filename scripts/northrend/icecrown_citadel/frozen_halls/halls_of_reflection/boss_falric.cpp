/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: boss_falric
SD%Complete: 70%
SDComment:
SDAuthor: /dev/rsa, changed by MaxXx2021 aka Mioka
SDCategory: Halls of Reflection
EndScriptData */

#include "precompiled.h"
#include "halls_of_reflection.h"

enum
{
    SAY_FALRIC_AGGRO                        = -1668507,
    SAY_FALRIC_DEATH                        = -1668508,
    SAY_FALRIC_SLAY01                       = -1668509,
    SAY_FALRIC_SLAY02                       = -1668510,
    SAY_FALRIC_SP01                         = -1668511,
    SAY_FALRIC_SP02                         = -1668512,

    SPELL_HOPELESSNESS                      = 72395,
    SPELL_IMPENDING_DESPAIR                 = 72426,
    SPELL_DEFILING_HORROR                   = 72435,
    //SPELL_DEFILING_HORROR_H                 = 72452,
    SPELL_QUIVERING_STRIKE                  = 72422,
    //SPELL_QUIVERING_STRIKE_H                = 72453,

    SPELL_BERSERK                           = 47008
};

struct MANGOS_DLL_DECL boss_falricAI : public BSWScriptedAI
{
    boss_falricAI(Creature *pCreature) : BSWScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsCall;

    uint32 m_uiSummonTimer;
    uint32 m_uiLocNo;
    GuidList m_uiSummonGuids;
    GuidList m_uiWaveGuids;
    uint8 SummonCount;
    uint32 pSummon;

    void Reset()
    {
        m_uiWaveGuids.clear();
      SummonCount = 0;
      m_bIsCall = false;
      m_uiSummonTimer = 11000;
      m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
      m_creature->SetVisibility(VISIBILITY_OFF);
    }

    void Aggro(Unit* pVictim)
    {
      m_creature->SetWalk(false);
      DoScriptText(SAY_FALRIC_AGGRO, m_creature);
      DoCast(m_creature, SPELL_HOPELESSNESS);
    }

    void KilledUnit(Unit* pVictim)
    {
        switch(urand(0,1))
        {
            case 0: DoScriptText(SAY_FALRIC_SLAY01, m_creature); break;
            case 1: DoScriptText(SAY_FALRIC_SLAY02, m_creature); break;
        }
    }

    void EnterEvadeMode()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EVENT, 5);
        ScriptedAI::EnterEvadeMode();
    }

    void JustDied(Unit* pKiller)
    {
        if(!m_pInstance)
            return;
        m_pInstance->SetData(TYPE_MARWYN, SPECIAL);
        DoScriptText(SAY_FALRIC_DEATH, m_creature);
    }

    void AttackStart(Unit* who)
    {
        if(!m_pInstance) return;

        if(m_pInstance->GetData(TYPE_FALRIC) != IN_PROGRESS)
             return;

        ScriptedAI::AttackStart(who);
    }

    void Summon()
    {
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        m_uiWaveGuids.erase(pSummoned->GetObjectGuid());
    }

    void CallFallSoldier()
    {
        for (uint8 i = 0; i < 4 && m_uiSummonGuids.size(); i++)
        {
            if(Creature* pSummon = m_creature->GetMap()->GetCreature(m_uiSummonGuids.back()))
            {
               pSummon->setFaction(14);
               pSummon->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
               pSummon->SetInCombatWithZone();
               m_uiWaveGuids.push_back(pSummon->GetObjectGuid());
            }
            m_uiSummonGuids.pop_back();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_EVENT) == 5)
        {
            m_pInstance->SetData(TYPE_EVENT, 6);
            for (GuidList::iterator itr = m_uiSummonGuids.begin(); itr != m_uiSummonGuids.end(); ++itr)
                if (Creature* pSummoned = m_creature->GetMap()->GetCreature(*itr))
                    pSummoned->ForcedDespawn();

            Summon();
        }

        if (m_pInstance->GetData(TYPE_FALRIC) == SPECIAL)
        {
            if (m_uiWaveGuids.empty())
                m_uiSummonTimer = 0;

            if (m_uiSummonTimer < uiDiff)
            {
                    ++SummonCount;
                    m_pInstance->SetData(DATA_WAVE_COUNT,SummonCount);
                    if(SummonCount > 4)
                    {
                        m_pInstance->SetData(TYPE_FALRIC, IN_PROGRESS);
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        m_creature->SetInCombatWithZone();
                    }
                    else CallFallSoldier();
                    m_uiSummonTimer = 60000;
            } else m_uiSummonTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        timedCast(SPELL_QUIVERING_STRIKE, uiDiff);
        timedCast(SPELL_IMPENDING_DESPAIR, uiDiff);
        timedCast(SPELL_DEFILING_HORROR, uiDiff);

        timedCast(SPELL_BERSERK, uiDiff);

        DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_boss_falric(Creature* pCreature)
{
    return new boss_falricAI(pCreature);
}

void AddSC_boss_falric()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_falric";
    newscript->GetAI = &GetAI_boss_falric;
    newscript->RegisterSelf();
}
