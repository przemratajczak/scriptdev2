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
SDName: Boss_Commander
SD%Complete: 
SDComment: 
SDCategory: Nexus
EndScriptData */


#include "precompiled.h"
#include "nexus.h"

enum Spells
{
    //Spells Commander
    SPELL_CHARGE		    = 60067,
	SPELL_BATTLE_SHOUT      = 31403,
	SPELL_FEAR			    = 19134,
	SPELL_WHIRLWIND	        = 38618,    //Cast spell
	SPELL_WHIRLWIND_E	    = 38619,    //Effect "dmg".

    //Spell Alliance Cleric
    SPELL_FLASH_HEAL        = 17843,
    SPELL_FLASH_HEAL_H      = 56919,
    SPELL_POWER_WORLD       = 17139,
    SPELL_POWER_WORLD_H     = 35944,
    SPELL_SHADOW_WORLD      = 47697,
    SPELL_SHADOW_WORLD_H    = 56920,
};

/*
enum Yells
{
    SAY_AGGRO           =       //What is this? Mok-thorin ka! Kill them!
    SAY_KILL            =       //Our task is not yet done!
    SAY_DEATH           =       //Gaagh...
}
*/

/*######
## boss_commander
######*/

struct MANGOS_DLL_DECL boss_commanderAI : public ScriptedAI
{
    boss_commanderAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    bool m_bWhirlwind_E;

    uint32 m_uiChargeTimer;
    uint32 m_uiBattleShoutTimer;
    uint32 m_uiFearTimer;
    uint32 m_uiWhirlwindTimer;
    
    void Reset()
    {
        m_uiChargeTimer = urand(5000, 15000);
        m_uiBattleShoutTimer = 120000;  // 2 minutes
        m_uiFearTimer = urand(18000, 25000);
        m_uiWhirlwindTimer = urand(8000, 18000);

        m_bWhirlwind_E = false;
    }

    void Aggro(Unit* pWho)
    {

        //DoScriptText(SAY_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_BATTLE_SHOUT);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        //DoScriptText(SAY_DEATH, m_creature);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_COMMANDER, DONE);
    }

    void KilledUnit(Unit* pVictim)
    {  
        //DoScriptText(SAY_KILL, m_creature);
    }

     void UpdateAI(const uint32 uiDiff) 
     {  
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiChargeTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if(DoCastSpellIfCan(pTarget, SPELL_CHARGE) == CAST_OK)
                m_uiChargeTimer = urand(5000, 15000);
            }
        }else m_uiChargeTimer -= uiDiff;

        if(m_uiFearTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FEAR);
            m_uiFearTimer = urand(18000, 25000);
        }else m_uiFearTimer -= uiDiff;

        if(m_uiWhirlwindTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_WHIRLWIND);
            m_bWhirlwind_E = true;
            m_uiWhirlwindTimer = urand(8000, 18000);
        }else m_uiWhirlwindTimer -= uiDiff;

        if(m_uiBattleShoutTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BATTLE_SHOUT);
            m_uiBattleShoutTimer = 120000;
        }else m_uiBattleShoutTimer -= uiDiff;

        DoMeleeAttackIfReady();
     } 
};


struct MANGOS_DLL_DECL mob_alliance_clericAI : public ScriptedAI
{
    mob_alliance_clericAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiFlashHealTimer;
    uint32 m_uiPowerWorldTimer;
    uint32 m_uiShadowWorldTimer;

    void Reset()
    {
        m_uiFlashHealTimer = 12000;
        m_uiPowerWorldTimer = 18000;
        m_uiShadowWorldTimer = 20000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if(m_uiFlashHealTimer < uiDiff)
        {
            Creature* pTarget = NULL;

            switch(urand(0, 1))
            {
                case 0:
                    if (m_pInstance)
                        pTarget = m_pInstance->GetSingleCreatureFromStorage(NPC_COMMANDER_H);
                    break;
                case 1:
                    pTarget = m_creature;
                    break;
            }

            if(pTarget)
            {
                DoCastSpellIfCan(pTarget, SPELL_FLASH_HEAL);
                m_uiFlashHealTimer = 12000;
            }       
        }else m_uiFlashHealTimer -= uiDiff;

        if(m_uiPowerWorldTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_POWER_WORLD);
            m_uiPowerWorldTimer = 18000;
        }else m_uiPowerWorldTimer -= uiDiff;

        if(m_uiShadowWorldTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_WORLD);
            m_uiShadowWorldTimer = 20000;
        }else m_uiShadowWorldTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_commander(Creature* pCreature)
{
    return new boss_commanderAI(pCreature);
}

CreatureAI* GetAI_mob_alliance_cleric(Creature* pCreature)
{
    return new mob_alliance_clericAI(pCreature);
}


void AddSC_boss_commander()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_commander";
    newscript->GetAI = &GetAI_boss_commander;
    newscript->RegisterSelf();
}
    
void AddSC_mob_alliance_cleric()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "mob_alliance_cleric";
    newscript->GetAI = &GetAI_mob_alliance_cleric;
    newscript->RegisterSelf();
}