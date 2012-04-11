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
SDName: boss_scourgelord_tyrannus
SD%Complete: 50%
SDComment: missing intro and outro; encounter need vehicle support
SDCategory: Pit of Saron
EndScriptData */
/*
ToDo:
intro
outro,
overlord's brand spell -> the most important
tunnel's gate
replace SummonCreature with normal spawn + enter/exit vehicle
*/
#include "precompiled.h"
#include "pit_of_saron.h"

enum
{
    SAY_PREFIGHT_1                      = -1658050,
    SAY_GENERAL_TRASH                   = -1658051,
    SAY_PREFIGHT_2                      = -1658052,
    SAY_AGGRO                           = -1658053,
    SAY_SLAY_1                          = -1658054,
    SAY_SLAY_2                          = -1658055,
    SAY_DEATH                           = -1658056,
    SAY_MARK                            = -1658057,
    SAY_SMASH                           = -1658058,

    EMOTE_RIMEFANG_ICEBOLT              = -1658059,
    EMOTE_SMASH                         = -1658060,

    SPELL_FORCEFUL_SMASH                = 69155,
    SPELL_FORCEFUL_SMASH_H              = 69627,
    SPELL_OVERLORDS_BRAND               = 69172,
    SPELL_DARK_MIGHT                    = 69167,
    SPELL_DARK_MIGHT_H                  = 69629,
    SPELL_HOARFROST                     = 69246,
    SPELL_MARK_OF_RIMEFANG              = 69275,
    SPELL_ICY_BLAST                     = 69233,
    SPELL_ICY_BLAST_H                   = 69646,
    SPELL_ICY_BLAST_SLOW                = 69238,
    SPELL_ICY_BLAST_SLOW_H              = 69628,

    NPC_ICY_BLAST                       = 36731,
    SPELL_ICY_BLAST_AURA                = 69238,
    SPELL_ICY_BLAST_AURA_H              = 69628,
};

struct MANGOS_DLL_DECL boss_rimefangAI : public ScriptedAI
{
    boss_rimefangAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_pit_of_saron*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        SetCombatMovement(false);
        Reset();
    }

    instance_pit_of_saron* m_pInstance;
    bool m_bIsRegularMode;
    bool m_bIntro;
    bool m_bIsSummoned;

    uint32 m_uiHoarfrostTimer;
    uint32 m_uiIcyBlastTimer;
    uint32 m_uiIcyBlastSlowTimer;
    ObjectGuid m_uiMainTargetGUID;

    void Reset()
    {
        m_uiHoarfrostTimer      = 16000;
        m_uiIcyBlastTimer       = 23000;
        m_uiIcyBlastSlowTimer   = 30000;
        m_uiMainTargetGUID.Clear();
        m_bIntro                = false;
        m_bIsSummoned           = false;
    }

    void SetMainTarget(ObjectGuid m_uiTargetGUID)
    {
        if(m_uiTargetGUID != m_creature->GetObjectGuid())
            m_uiMainTargetGUID = m_uiTargetGUID;
    }

    void MoveInLineOfSight(Unit *pWho)
    {      
        if(!m_bIsSummoned)
            if( !m_bIntro && pWho->GetTypeId() == TYPEID_PLAYER && pWho->GetDistance2d(m_creature) < 50 && m_pInstance->GetData(TYPE_TYRANNUS) != DONE)
                if(Creature* pTyran = m_creature->SummonCreature(NPC_TYRANNUS,m_creature->GetPositionX(),m_creature->GetPositionY(),m_creature->GetPositionZ(),0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT_OR_DEAD_DESPAWN, 300000, true))
                { 
                    pTyran->AddThreat(pWho, 1000.0f);  
                    m_creature->AddThreat(pWho, 1000.0f);              
                    pTyran->AI()->AttackStart(pWho);
                    m_creature->AI()->AttackStart(pWho);

                    // uncomment this when flying creatures won't be affected by mmaps
                    /*m_creature->GetMotionMaster()->MoveIdle();
                    m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                    m_creature->SetLevitate(true);
                    m_creature->GetMotionMaster()->MovePoint(0,m_creature->GetPositionX(),m_creature->GetPositionY(), m_creature->GetPositionZ() + 20, false);
                    */m_bIsSummoned = true;
                    m_bIntro = true;
                }
                
            
    }
    void JustSummoned(Creature* pSummoned)
    {
        if(pSummoned->GetEntry() == NPC_ICY_BLAST)
            pSummoned->CastSpell(pSummoned, SPELL_ICY_BLAST_AURA, false);
    }

    void UpdateAI(const uint32 uiDiff)
    {

        //FixMe
        //AddIntro
        if(m_bIntro)
        {
            m_bIntro = false;
        }
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiHoarfrostTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiMainTargetGUID))
                DoCastSpellIfCan(pTarget, SPELL_HOARFROST);
            else if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_HOARFROST);
            m_uiHoarfrostTimer = 15000;
        }
        else
            m_uiHoarfrostTimer -= uiDiff;

        if (m_uiIcyBlastTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiMainTargetGUID))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_ICY_BLAST : SPELL_ICY_BLAST_H);
            else if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_ICY_BLAST : SPELL_ICY_BLAST_H);
            m_uiIcyBlastTimer = 23000;
        }
        else
            m_uiIcyBlastTimer -= uiDiff;

        if (m_uiIcyBlastSlowTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->GetMap()->GetUnit(m_uiMainTargetGUID))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_ICY_BLAST_SLOW : SPELL_ICY_BLAST_SLOW_H);
            else if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, m_bIsRegularMode ? SPELL_ICY_BLAST_SLOW : SPELL_ICY_BLAST_SLOW_H);
            m_uiIcyBlastSlowTimer = 30000;
        }
        else
            m_uiIcyBlastSlowTimer -= uiDiff;
    }
};

struct MANGOS_DLL_DECL boss_tyrannusAI : public ScriptedAI
{
    boss_tyrannusAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_pit_of_saron*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_pit_of_saron* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiForcefulSmashTimer;
    uint32 m_uiOverlordsBrandTimer;
    uint32 m_uiDarkMightTimer;
    uint32 m_uiMarkOfRimefangTimer;
    uint32 m_uiCheckDistanceTimer;

    void Reset()
    {
        m_uiForcefulSmashTimer  = 10000;
        m_uiOverlordsBrandTimer = 25000;
        m_uiDarkMightTimer      = 30000;
        m_uiMarkOfRimefangTimer = 15000;
        m_uiCheckDistanceTimer  = 5000;
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_TYRANNUS, FAIL);        
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn();
    }

    //FixMe
    //Overlord's brand doesn't work so let's emulate though a part
    //"Brands an enemy with the mark of Tyrannus, causing all damage dealt by 
    //the Branded foe to be mirrored to the caster's primary target"
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if(pDoneBy->HasAura(SPELL_OVERLORDS_BRAND))
        {            
            pDoneBy->DealDamage(m_creature->getVictim(), uiDamage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            uiDamage = 0;
        }
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_TYRANNUS, IN_PROGRESS);

        if (Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG)) 
        {
            ((boss_rimefangAI*)pRimefang->AI())->SetMainTarget(pWho->GetObjectGuid());
            pRimefang->AddThreat(pWho, 1000.0f);
            pRimefang->AI()->AttackStart(pWho);
        }

        DoScriptText(SAY_AGGRO, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(urand(0, 1) ? SAY_SLAY_1 : SAY_SLAY_2, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(SAY_DEATH, m_creature);

        // Temp hack until outro is implemented
        if (Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG))
        {
            pRimefang->ForcedDespawn();
            /*pRimefang->GetMotionMaster()->Clear();
            pRimefang->GetMotionMaster()->MovePoint(0, 844.752f, 358.993f, 645.330f);
            pRimefang->setFaction(35);
            pRimefang->DeleteThreatList();
            pRimefang->RemoveAllAuras();*/
            
        }

        if (m_pInstance)
            m_pInstance->SetData(TYPE_TYRANNUS, DONE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
            return;

        if( m_creature->getVictim()->GetEntry() == NPC_RIMEFANG )
            EnterEvadeMode();

        //To prevent pulling him out of arena
        if (m_uiCheckDistanceTimer < uiDiff)
        {
            if(Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG))
                if(m_creature->GetDistance2d(pRimefang) > 80)
                {
                    m_creature->AI()->EnterEvadeMode();
                    pRimefang->AI()->EnterEvadeMode();
                }
               m_uiCheckDistanceTimer = 8000;
        }
        else
            m_uiCheckDistanceTimer -= uiDiff;

        if (m_uiForcefulSmashTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode ? SPELL_FORCEFUL_SMASH : SPELL_FORCEFUL_SMASH_H) == CAST_OK)
                m_uiForcefulSmashTimer = 30000;
        }
        else
            m_uiForcefulSmashTimer -= uiDiff;

        if (m_uiOverlordsBrandTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_OVERLORDS_BRAND) == CAST_OK)
                    m_uiOverlordsBrandTimer = 25000;
            }
        }
        else
            m_uiOverlordsBrandTimer -= uiDiff;

        if (m_uiDarkMightTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_DARK_MIGHT : SPELL_DARK_MIGHT_H) == CAST_OK)
            {
                DoScriptText(SAY_SMASH, m_creature);
                DoScriptText(EMOTE_SMASH, m_creature);

                m_uiDarkMightTimer = 35000;
            }
        }
        else
            m_uiDarkMightTimer -= uiDiff;

        if (m_uiMarkOfRimefangTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MARK_OF_RIMEFANG) == CAST_OK)
                {
                    if (Creature* pRimefang = m_pInstance->GetSingleCreatureFromStorage(NPC_RIMEFANG))
                        ((boss_rimefangAI*)pRimefang->AI())->SetMainTarget(pTarget->GetObjectGuid());

                    DoScriptText(SAY_MARK, m_creature);
                    m_uiMarkOfRimefangTimer = 15000;
                }
            }
        }
        else
            m_uiMarkOfRimefangTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_tyrannus(Creature* pCreature)
{
    return new boss_tyrannusAI (pCreature);
}

CreatureAI* GetAI_boss_rimefang(Creature* pCreature)
{
    return new boss_rimefangAI (pCreature);
}

void AddSC_boss_tyrannus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name="boss_scourgelord_tyrannus";
    pNewScript->GetAI = &GetAI_boss_tyrannus;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name="boss_rimefang";
    pNewScript->GetAI = &GetAI_boss_rimefang;
    pNewScript->RegisterSelf();
}
