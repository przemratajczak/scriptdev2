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
SDName: Zuldrak
SD%Complete: 100
SDComment: Quest support: 12934.
SDCategory: Zuldrak
EndScriptData */

/* ContentData
npc_gurgthock
EndContentData */

#include "precompiled.h"
#include "follower_ai.h"

/*######
## npc_gurgthock
######*/

enum
{
    QUEST_FROM_BEYOND = 12934,

    NPC_AZBARIN       = 30026,
    NPC_DUKE_SINGEN   = 30019,
    NPC_ERATHIUS      = 30025,
    NPC_GARGORAL      = 30024
};

static float m_afSpawnLocation[] = {5768.71f, -2969.29f, 273.816f};
static uint32 m_auiBosses[] = {NPC_AZBARIN, NPC_DUKE_SINGEN, NPC_ERATHIUS, NPC_GARGORAL};

struct MANGOS_DLL_DECL npc_gurgthockAI : public ScriptedAI
{
    npc_gurgthockAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint64 m_uiPlayerGUID;

    void SetPlayerGUID(uint64 uiPlayerGUID) { m_uiPlayerGUID = uiPlayerGUID; }

    void Reset()
    {
        m_uiPlayerGUID = 0;
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        uint32 uiEntry = pSummoned->GetEntry();
        for(uint8 i = 0; i < 4; ++i)
        {
            if (uiEntry == m_auiBosses[i])
            {
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                    pPlayer->GroupEventHappens(QUEST_FROM_BEYOND, m_creature);

                m_uiPlayerGUID = 0;
                return;
            }
        }
    }
};

bool QuestAccept_npc_gurgthock(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_FROM_BEYOND)
    {
        pCreature->SummonCreature(m_auiBosses[urand(0, 3)], m_afSpawnLocation[0], m_afSpawnLocation[1], m_afSpawnLocation[2], 0.0f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 600000);

        if (npc_gurgthockAI* pGurthockAI = dynamic_cast<npc_gurgthockAI*>(pCreature->AI()))
            pGurthockAI->SetPlayerGUID(pPlayer->GetGUID());
    }
    return true;
}

CreatureAI* GetAI_npc_gurgthock(Creature* pCreature)
{
    return new npc_gurgthockAI(pCreature);
}

/*###################
# Quest: Leave no one behind
###################*/

enum Crusaders
{
    NPC_LAMOOF                          = 28142,
    NPC_LAMOOF_TRIGGER                  = 28141,
    NPC_JONATHAN                        = 28136,
    NPC_JONATHAN_TRIGGER                = 28133,
    NPC_JOSEPHINE_TRIGGER               = 28143,
    NPC_JOSEPHINE                       = 28148,
    NPC_DR_ROGERS                       = 28125,

    // forcing cast summon spell spells
    SPELL_SUMMON_LAMOOF                 = 50673,
    SPELL_SUMMON_JONATHAN               = 50663,
    SPELL_SUMMON_JOSEPHINE              = 50691,

    SPELL_DYING_LAMOOF                  = 50679,
    SPELL_DYING_JONATHAN                = 50666,
    SPELL_DYING_JOSEPHINE               = 50693,

    SPELL_KILLCREDIT_LAMOOF             = 50684,
    SPELL_KILLCREDIT_JONATHAN           = 50680,
    SPELL_KILLCREDIT_JOSEPHINE          = 50699,

    // unfortunately found only for LAMOOF :(
    SAY_LAMOOF_MOAN                     = -1999855,

    SAY_LAMOOF_QUESTCREDIT              = -1999854,
    SAY_JONATHAN_QUESTCREDIT            = -1999853,
    SAY_JOSEPHINE_QUESTCREDIT           = -1999852,

    QUEST_LEAVENOONEBEHID               = 12512
};

struct MANGOS_DLL_DECL mob_crusaderAI : public FollowerAI
{
    mob_crusaderAI(Creature* pCreature) : FollowerAI(pCreature)
    {
        bBleeding = false;
        bReady = true;
        bApplied = false;
        Reset();
    }

    bool bBleeding;
    bool bReady;
    bool bApplied;

    void Reset() {}

    void JustDied(Unit* pKiller)
    {
        Player* pFollowed = GetLeaderForFollower();
        if (!pFollowed)
            return;

        uint32 spell = 0;

        switch(m_creature->GetEntry())
        {
            case NPC_LAMOOF: spell = SPELL_DYING_LAMOOF; break;
            case NPC_JONATHAN: spell = SPELL_DYING_JONATHAN; break;
            case NPC_JOSEPHINE: spell = SPELL_DYING_JOSEPHINE; break;
            default: break;
        }

        if ((spell > 0) && pFollowed->HasAura(spell))
            pFollowed->RemoveAurasDueToSpellByCancel(spell);
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!pWho || !m_creature->isAlive())
            return;

        Player* pFollowed = GetLeaderForFollower();
        if (!pFollowed)
            return;

        if ((pWho->GetEntry() == NPC_DR_ROGERS) && (m_creature->GetDistance(pWho) < INTERACTION_DISTANCE))
        {
            uint32 spell = 0;
            uint32 dispell = 0;
            uint32 textid = 0;

            switch (m_creature->GetEntry())
            {
                case NPC_LAMOOF: 
                    spell = SPELL_KILLCREDIT_LAMOOF;
                    dispell = SPELL_DYING_LAMOOF;
                    textid = SAY_LAMOOF_QUESTCREDIT;
                    break;
                case NPC_JONATHAN: 
                    spell = SPELL_KILLCREDIT_JONATHAN;
                    dispell = SPELL_DYING_JONATHAN;
                    textid = SAY_JONATHAN_QUESTCREDIT;
                    break;
                case NPC_JOSEPHINE: 
                    spell = SPELL_KILLCREDIT_JOSEPHINE;
                    dispell = SPELL_DYING_JOSEPHINE;
                    textid = SAY_JOSEPHINE_QUESTCREDIT;
                    break;
                default: break;
            }

            if ((spell > 0) && (dispell > 0))
            {
                if (pFollowed->HasAura(dispell))
                {
                    pFollowed->InterruptNonMeleeSpells(false);
                    pFollowed->RemoveAurasDueToSpell(dispell);
                }
                if (m_creature->HasAura(dispell))
                    m_creature->RemoveAurasDueToSpell(dispell);
                pFollowed->CastSpell(pFollowed, spell, true);
                DoScriptText(textid, m_creature);
            }
            SetFollowComplete(true);
        }
    }

    void UpdateFollowerAI(const uint32 uiDiff)
    {
        if (m_creature->isInCombat() || m_creature->SelectHostileTarget())
            return;

        if (bBleeding & !bApplied)
        {
            if (Player* pFollowed = GetLeaderForFollower())
            {
                switch(m_creature->GetEntry())
                {
                    case NPC_LAMOOF: 
                        DoCastSpellIfCan(pFollowed, SPELL_DYING_LAMOOF, CAST_TRIGGERED);
                        DoCastSpellIfCan(m_creature, SPELL_DYING_LAMOOF, CAST_TRIGGERED);
                        break;
                    case NPC_JONATHAN: 
                        DoCastSpellIfCan(pFollowed, SPELL_DYING_JONATHAN, CAST_TRIGGERED);
                        DoCastSpellIfCan(m_creature, SPELL_DYING_JONATHAN, CAST_TRIGGERED);
                        break;
                    case NPC_JOSEPHINE: 
                        DoCastSpellIfCan(pFollowed, SPELL_DYING_JOSEPHINE, CAST_TRIGGERED);
                        DoCastSpellIfCan(m_creature, SPELL_DYING_JOSEPHINE, CAST_TRIGGERED);
                        break;
                }
            }
            bApplied = true;
        }
    }
};
CreatureAI* GetAI_mob_crusader(Creature* pCreature)
{
    return new mob_crusaderAI(pCreature);
}

struct MANGOS_DLL_DECL mob_crusader_triggerAI : public FollowerAI
{
    mob_crusader_triggerAI(Creature* pCreature) : FollowerAI(pCreature)
    {Reset();}

    uint32 m_uiMoan_Timer;

    void Reset() 
    {
        m_uiMoan_Timer = 45000;
    }

    void SpellHit(Unit *pCaster, const SpellEntry *pSpell)
    {
        if (!pCaster || !pSpell || (pCaster->GetTypeId() != TYPEID_PLAYER))
            return;
        
        uint32 spell;
        uint32 summon;
        float range = 15.0f; // summoning spell range

        switch(m_creature->GetEntry())
        {
            case NPC_LAMOOF_TRIGGER:
                spell = SPELL_SUMMON_LAMOOF;
                summon = NPC_LAMOOF;
                break;
            case NPC_JONATHAN_TRIGGER:
                spell = SPELL_SUMMON_JONATHAN;
                summon = NPC_JONATHAN;
                break;
            case NPC_JOSEPHINE_TRIGGER:
                spell = SPELL_SUMMON_JOSEPHINE;
                summon = NPC_JOSEPHINE;
                break;
            default: break;
        }
        DoCastSpellIfCan(pCaster, spell, CAST_TRIGGERED);
        if (Creature* pSummoned = GetClosestCreatureWithEntry(pCaster, summon, range))
            if (pSummoned->AI())
                if (mob_crusaderAI* pFollowerAI = dynamic_cast<mob_crusaderAI*>(pSummoned->AI()))
                    if (pFollowerAI->bReady)
                    {
                        pFollowerAI->StartFollow(((Player*)pCaster), FACTION_ESCORT_N_FRIEND_PASSIVE);
                        pFollowerAI->bBleeding = true;
                        pFollowerAI->bReady = false;
                    }
        m_creature->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_creature->isInCombat() || m_creature->SelectHostileTarget())
            return;

        if (m_uiMoan_Timer <= uiDiff)
        {
            switch(m_creature->GetEntry())
            {
                case NPC_LAMOOF_TRIGGER: DoScriptText(SAY_LAMOOF_MOAN, m_creature);break;
                default: break;
            }
            m_uiMoan_Timer = 45000;
        }
        else
            m_uiMoan_Timer -= uiDiff;
    }
};
CreatureAI* GetAI_mob_crusader_trigger(Creature* pCreature)
{
    return new mob_crusader_triggerAI(pCreature);
}


/*######
## npc_ghoul_feeding_bunny
######*/
enum 
{
    SPELL_ATTRACT_GHOUL     = 52037,
    POINT_NEAR_BOWL         = 0,
    SPELL_KILL_KREDIT       = 52030,
    SPELL_KC_SCRIPT_EFFECT  = 52038, // not used
    SPELL_KC                = 52039  // not used
};

struct MANGOS_DLL_DECL npc_deacying_ghoulAI : public ScriptedAI
{
    npc_deacying_ghoulAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint64 m_uiPlayerGUID;

    void Reset()
    {
        m_uiPlayerGUID = 0;
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_ATTRACT_GHOUL && pCaster->GetTypeId() == TYPEID_UNIT)
        {
            if (Player* pPlayer = m_creature->GetMap()->GetPlayer(((Creature*)pCaster)->GetCreatorGuid()))
                m_uiPlayerGUID = pPlayer->GetGUID();
            SetCombatMovement(false);
            float fDestX, fDestY, fDestZ;
            pCaster->GetNearPoint(pCaster, fDestX, fDestY, fDestZ, pCaster->GetObjectBoundingRadius(), 4.0f, pCaster->GetAngle(m_creature));
            m_creature->GetMotionMaster()->Clear();
            m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
            m_creature->GetMotionMaster()->MovePoint(POINT_NEAR_BOWL, fDestX, fDestY, fDestZ);
        }
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (uiPointId == POINT_NEAR_BOWL)
        {
            m_creature->HandleEmote(EMOTE_ONESHOT_EAT);
            m_creature->ForcedDespawn(3000);
            if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                DoCastSpellIfCan(pPlayer, SPELL_KILL_KREDIT);
        }
    }
};
CreatureAI* GetAI_npc_deacying_ghoul(Creature* pCreature)
{
    return new npc_deacying_ghoulAI(pCreature);
}

void AddSC_zuldrak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_gurgthock";
    pNewScript->GetAI = &GetAI_npc_gurgthock;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_gurgthock;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_crusader";
    pNewScript->GetAI = &GetAI_mob_crusader;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_crusader_trigger";
    pNewScript->GetAI = &GetAI_mob_crusader_trigger;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_deacying_ghoul";
    pNewScript->GetAI = &GetAI_npc_deacying_ghoul;
    pNewScript->RegisterSelf();
}
