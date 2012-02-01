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
SDName: Boss_Hadronox
SD%Complete: 20%
SDComment:
SDCategory: Azjol'Nerub
EndScriptData */

#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    POINT_HADRONOX_CHAMBER              = 0,

    SUMMON_ANUBAR_CHAMPION_28924        = 53014, // 18 world trigger spell
    SUMMON_ANUBAR_NECROMANCER_28925     = 53015, // 18 world trigger spell
    SUMMON_ANUBAR_CRYPT_FIEND_29051     = 53016, // 18 world trigger spell
    SUMMON_ANUBAR_CHAMPION_PERIODIC     = 53035, // 1 world trigger spell
    SUMMON_ANUBAR_NECROMANCER_PERIODIC  = 53036, // 1 world trigger spell
    SUMMON_ANUBAR_CRYPT_FIEND_PERIODIC  = 53037, // 1 world trigger spell
    SUMMON_ANUBAR_CHAMPION_29062        = 53064, // 18
    SUMMON_ANUBAR_CRYPT_FIEND_29063     = 53065, // 18
    SUMMON_ANUBAR_NECROMANCER_29064     = 53066, // 18
    SUMMON_ANUBAR_CHAMPION_29096        = 53090, // 18
    SUMMON_ANUBAR_CRYPT_FIEND_29097     = 53091, // 18
    SUMMON_ANUBAR_NECROMANCER_29098     = 53092, // 18

    SUMMON_ANUBAR_CHAMPION              = 53826, // 140
    SUMMON_ANUBAR_NECROMANCER           = 53827, // 140
    SUMMON_ANUBAR_CRYPT_FIEND           = 53828, // 140

    SPELL_ACID_CLOUD                    = 53400, // Victim
    SPELL_LEECH_POISON                  = 53030, // Victim
    SPELL_PIERCE_ARMOR                  = 53418, // Victim
    SPELL_WEB_GRAB                      = 57731, // Victim
    SPELL_WEB_FRONT_DOORS               = 53177, // Self
    SPELL_WEB_SIDE_DOORS                = 53185  // Self
};

float fHadronoxLair[3] = {529.691f, 547.126f, 731.916f};

/*######
## boss_hadronox
######*/

struct MANGOS_DLL_DECL boss_hadronoxAI : public ScriptedAI
{
    boss_hadronoxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_azjol_nerub*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_azjol_nerub* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiAcidTimer;
    uint32 m_uiLeechTimer;
    uint32 m_uiPierceTimer;
    uint32 m_uiGrabTimer;
    uint32 m_uiDoorsTimer;

    void Reset()
    {
        m_uiAcidTimer = urand(10000, 14000);
        m_uiLeechTimer = urand(3000, 9000);
        m_uiPierceTimer = urand(1000, 3000);
        m_uiGrabTimer = urand(15000, 19000);
        m_uiDoorsTimer = urand(20000, 30000);
    }

    void KilledUnit(Unit* pVictim)
    {
        m_creature->SetHealth(m_creature->GetHealth() + (m_creature->GetMaxHealth() * 0.1));
    }


    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_HADRONOX_CHAMBER)
        {
            SetCombatMovement(true);
            if (m_pInstance)
                m_pInstance->SetData(TYPE_HADRONOX, IN_PROGRESS);
        }
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_HADRONOX, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_pInstance)
            if (m_pInstance->GetData(TYPE_HADRONOX) == SPECIAL && m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
            {
                m_creature->GetMotionMaster()->MovementExpired();
                SetCombatMovement(false);
                m_creature->GetMotionMaster()->MovePoint(POINT_HADRONOX_CHAMBER, fHadronoxLair[0], fHadronoxLair[1], fHadronoxLair[2]);
            }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiPierceTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_PIERCE_ARMOR);
            m_uiPierceTimer = 8000;
        }
        else
            m_uiPierceTimer -= uiDiff;

        if (m_uiAcidTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_ACID_CLOUD);

            m_uiAcidTimer = urand(20000, 30000);
        }
        else
            m_uiAcidTimer -= uiDiff;

        if (m_uiLeechTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_LEECH_POISON);

            m_uiLeechTimer = urand(11000, 14000);
        } else m_uiLeechTimer -= uiDiff;

        if (m_uiGrabTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0)) // Draws all players (and attacking Mobs) to itself.
                DoCastSpellIfCan(pTarget, SPELL_WEB_GRAB);

            m_uiGrabTimer = urand(15000, 30000);
        }
        else
            m_uiGrabTimer -= uiDiff;

        if (m_uiDoorsTimer < uiDiff)
        {
            //DoCastSpellIfCan(me, urand(SPELL_WEB_FRONT_DOORS, SPELL_WEB_SIDE_DOORS));
            m_uiDoorsTimer = urand(30000, 60000);
        }
        else
            m_uiDoorsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_hadronox(Creature* pCreature)
{
    return new boss_hadronoxAI(pCreature);
}

struct MANGOS_DLL_DECL npc_hadronox_OOC_addAI : public ScriptedAI
{
    npc_hadronox_OOC_addAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_azjol_nerub*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_HADRONOX) != IN_PROGRESS)
            if (Creature* pHadronox = m_pInstance->GetSingleCreatureFromStorage(NPC_HADRONOX))
                m_creature->GetMotionMaster()->MoveFollow(pHadronox, 0, 0);
    }
};

CreatureAI* GetAI_npc_hadronox_OOC_add(Creature* pCreature)
{
    return new npc_hadronox_OOC_addAI(pCreature);
}

void AddSC_boss_hadronox()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_hadronox";
    pNewScript->GetAI = &GetAI_boss_hadronox;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_hadronox_OOC_add";
    pNewScript->GetAI = &GetAI_npc_hadronox_OOC_add;
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
SDName: boss_hadronox
SD%Complete: ?%
SDComment: by MaxXx2021
SDCategory: Azjol-Nerub instance
EndScriptData */
/*
* Comment: No Waves atm and the doors spells are crazy...
*
* When your group enters the main room (the one after the bridge), you will notice a group of 3 Nerubians.
* When you engage them, 2 more groups like this one spawn behind the first one - it is important to pull the first group back,
* so you don't aggro all 3. Hadronox will be under you, fighting Nerubians.
*
* This is the timed gauntlet - waves of non-elite spiders
* will spawn from the 3 doors located a little above the main room, and will then head down to fight Hadronox. After clearing the
* main room, it is recommended to just stay in it, kill the occasional non-elites that will attack you instead of the boss, and wait for
* Hadronox to make his way to you. When Hadronox enters the main room, she will web the doors, and no more non-elites will spawn.
*/

/*#include "precompiled.h"
#include "azjol-nerub.h"

enum
{
    SPELL_PIERCE_ARMOR          = 53418,
    SPELL_ACID_CLOUD            = 53400,
    SPELL_ACID_CLOUD_H          = 59419,
    SPELL_LEECH_POISON          = 53030,
    SPELL_LEECH_POISON_H        = 59417,
    SPELL_WEB_GRAB              = 57731,
    SPELL_WEB_GRAB_H            = 59421,
    SPELL_WEB_FRONT_DOORS       = 53177, // Self
    SPELL_WEB_SIDE_DOORS        = 53185, // Self

    // Gauntlet end spells - send events 19101 and 19102
    //SPELL_WEB_FRONT_DOORS     = 53177,
    //SPELL_WEB_SIDE_DOORS      = 53185,

    // Gauntlet summoned npcs
    //NPC_ANUBAR_CHAMPION_1     = 29062,
    //NPC_ANUBAR_CRYPT_FIEND_1  = 29063,
    //NPC_ANUBAR_NECROMANCER_1  = 29064,
    //NPC_ANUBAR_CHAMPION_2     = 29096,
    //NPC_ANUBAR_CRYPT_FIEND_2  = 29097,
    //NPC_ANUBAR_NECROMANCER_2  = 29098,
};

 /* ##### Gauntlet description #####
  * This is the timed gauntlet - waves of non-elite spiders will spawn from the 3 doors located a little above the main room
  * They will make their way down to fight Hadronox but she will head to the main room, fighting the spiders
  * When Hadronox enters the main room, she will web the doors, and no more spiders will spawn.
  */

/*######
## boss_hadronox
######*/
/*
struct MANGOS_DLL_DECL boss_hadronoxAI : public ScriptedAI
{
    boss_hadronoxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
        bFirstTime = true;
    }

    ScriptedInstance* pInstance;

    uint32 uiAcidTimer;
    uint32 uiLeechTimer;
    uint32 uiPierceTimer;
    uint32 uiGrabTimer;
    uint32 uiDoorsTimer;
    uint32 uiCheckDistanceTimer;

    bool bFirstTime;

    float fMaxDistance;

    uint32 m_uiAcidTimer;
    uint32 m_uiLeechTimer;
    uint32 m_uiPierceTimer;
    uint32 m_uiGrabTimer;

    void Reset()
    {
        m_creature->SetFloatValue(UNIT_FIELD_BOUNDINGRADIUS, 9.0f);
        m_creature->SetFloatValue(UNIT_FIELD_COMBATREACH, 9.0f);

        uiAcidTimer = urand(10000,14000);
        uiLeechTimer = urand(3000,9000);
        uiPierceTimer = urand(1000,3000);
        uiGrabTimer = urand(15000,19000);
        uiDoorsTimer = urand(20000,30000);
        uiCheckDistanceTimer = 2000;

        fMaxDistance = 50.0f;

        if (pInstance && (pInstance->GetData(TYPE_HADRONOX) != DONE && !bFirstTime))
            pInstance->SetData(TYPE_HADRONOX, FAIL);

        bFirstTime = false;
    }

    //when Hadronox kills any enemy (that includes a party member) she will regain 10% of her HP if the target had Leech Poison on
    void KilledUnit(Unit* Victim)
    {
        // not sure if this aura check is correct, I think it is though
        if (!Victim || !Victim->HasAura(SPELL_LEECH_POISON) || !m_creature->isAlive())
            return;

        uint32 health = m_creature->GetMaxHealth()/10;

        if ((m_creature->GetHealth()+health) >= m_creature->GetMaxHealth())
            m_creature->SetHealth(m_creature->GetMaxHealth());
        else
            m_creature->SetHealth(m_creature->GetHealth()+health);
    }

    void JustDied(Unit* Killer)
    {
        if (pInstance)
            pInstance->SetData(TYPE_HADRONOX, DONE);
    }

    void EnterCombat(Unit* who)
    {
        if (pInstance)
            pInstance->SetData(TYPE_HADRONOX, IN_PROGRESS);
        m_creature->SetInCombatWithZone();
    }

    void CheckDistance(float dist, const uint32 uiDiff)
    {
        if (!m_creature->isInCombat())
            return;

        float x=0.0f, y=0.0f, z=0.0f;
        m_creature->GetRespawnCoord(x,y,z);

        if (uiCheckDistanceTimer <= uiDiff)
            uiCheckDistanceTimer = 5000;
        else
        {
            uiCheckDistanceTimer -= uiDiff;
            return;
        }
        if (m_creature->IsInEvadeMode() || !m_creature->getVictim())
            return;
        if (m_creature->GetDistance(x,y,z) > dist)
            EnterEvadeMode();
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Without he comes up through the air to players on the bridge after krikthir if players crossing this bridge!
        CheckDistance(fMaxDistance, diff);

        if (m_creature->HasAura(SPELL_WEB_FRONT_DOORS) || m_creature->HasAura(SPELL_WEB_SIDE_DOORS))
        {
            if (IsCombatMovement())
                SetCombatMovement(false);
        }
        else if (!IsCombatMovement())
            SetCombatMovement(true);

        if (uiPierceTimer <= diff)
        {
            DoCast(m_creature->getVictim(), SPELL_PIERCE_ARMOR);
            uiPierceTimer = 8000;
        } else uiPierceTimer -= diff;

        if (uiAcidTimer <= diff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_ACID_CLOUD);

            uiAcidTimer = urand(20000,30000);
        } else uiAcidTimer -= diff;

        if (uiLeechTimer <= diff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCast(pTarget, SPELL_LEECH_POISON);

            uiLeechTimer = urand(11000,14000);
        } else uiLeechTimer -= diff;

        if (uiGrabTimer <= diff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0)) // Draws all players (and attacking Mobs) to itself.
                DoCast(pTarget, SPELL_WEB_GRAB);

            uiGrabTimer = urand(15000,30000);
        } else uiGrabTimer -= diff;

        if (uiDoorsTimer <= diff)
        {
            //DoCast(me, urand(SPELL_WEB_FRONT_DOORS, SPELL_WEB_SIDE_DOORS));
            uiDoorsTimer = urand(30000,60000);
        } else uiDoorsTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_hadronox(Creature* pCreature)
{
    return new boss_hadronoxAI (pCreature);
}

void AddSC_boss_hadronox()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_hadronox";
    newscript->GetAI = &GetAI_boss_hadronox;
    newscript->RegisterSelf();
}
*/
