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
SDName: GO_Scripts
SD%Complete: 100
SDComment: Quest support: 4296, 5088, 5097, 5098, 5381, 6481, 10990, 10991, 10992, 12557, 14092/14076. Field_Repair_Bot->Teaches spell 22704. Barov_journal->Teaches spell 26089
SDCategory: Game Objects
EndScriptData */

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_barov_journal
go_ethereum_prison
go_ethereum_stasis
go_field_repair_bot_74A
go_mysterious_snow_mound
go_orb_of_command
go_resonite_cask
go_sacred_fire_of_life
go_shrine_of_the_birds
go_tablet_of_madness
go_tablet_of_the_seven
go_tele_to_dalaran_crystal
go_tele_to_violet_stand
go_andorhal_tower
go_scourge_enclosure
go_lab_work_reagents
go_hand_of_iruxos_crystal
EndContentData */

#include "precompiled.h"

/*######
## go_cat_figurine
######*/

enum
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

bool GOUse_go_cat_figurine(Player* pPlayer, GameObject* pGo)
{
    pPlayer->CastSpell(pPlayer, SPELL_SUMMON_GHOST_SABER, true);
    return false;
}

/*######
## go_barov_journal
######*/

enum
{
    SPELL_TAILOR_FELCLOTH_BAG = 26086,
    SPELL_LEARN_FELCLOTH_BAG  = 26095
};

bool GOUse_go_barov_journal(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_TAILORING) && pPlayer->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !pPlayer->HasSpell(SPELL_TAILOR_FELCLOTH_BAG))
    {
        pPlayer->CastSpell(pPlayer, SPELL_LEARN_FELCLOTH_BAG, false);
    }
    return true;
}

/*######
## go_ethereum_prison
######*/

enum
{
    FACTION_LC     = 1011,
    FACTION_SHAT   = 935,
    FACTION_CE     = 942,
    FACTION_CON    = 933,
    FACTION_KT     = 989,
    FACTION_SPOR   = 970,

    SPELL_REP_LC   = 39456,
    SPELL_REP_SHAT = 39457,
    SPELL_REP_CE   = 39460,
    SPELL_REP_CON  = 39474,
    SPELL_REP_KT   = 39475,
    SPELL_REP_SPOR = 39476
};

const uint32 uiNpcPrisonEntry[] =
{
    22810, 22811, 22812, 22813, 22814, 22815,               //good guys
    20783, 20784, 20785, 20786, 20788, 20789, 20790         //bad guys
};

bool GOUse_go_ethereum_prison(Player* pPlayer, GameObject* pGo)
{
    uint8 uiRandom = urand(0, (sizeof(uiNpcPrisonEntry) / sizeof(uint32)) -1);

    if (Creature* pCreature = pPlayer->SummonCreature(uiNpcPrisonEntry[uiRandom],
        pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetAngle(pPlayer),
        TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
    {
        if (!pCreature->IsHostileTo(pPlayer))
        {
            uint32 uiSpell = 0;

            if (FactionTemplateEntry const* pFaction = pCreature->getFactionTemplateEntry())
            {
                switch(pFaction->faction)
                {
                    case FACTION_LC:   uiSpell = SPELL_REP_LC;   break;
                    case FACTION_SHAT: uiSpell = SPELL_REP_SHAT; break;
                    case FACTION_CE:   uiSpell = SPELL_REP_CE;   break;
                    case FACTION_CON:  uiSpell = SPELL_REP_CON;  break;
                    case FACTION_KT:   uiSpell = SPELL_REP_KT;   break;
                    case FACTION_SPOR: uiSpell = SPELL_REP_SPOR; break;
                }

                if (uiSpell)
                    pCreature->CastSpell(pPlayer,uiSpell,false);
                else
                    error_log("SD2: go_ethereum_prison summoned creature (entry %u) but faction (%u) are not expected by script.",pCreature->GetEntry(),pCreature->getFaction());
            }
        }
    }

    return false;
}

/*######
## go_ethereum_stasis
######*/

const uint32 uiNpcStasisEntry[] =
{
    22825, 20888, 22827, 22826, 22828
};

bool GOUse_go_ethereum_stasis(Player* pPlayer, GameObject* pGo)
{
    uint8 uiRandom = urand(0, (sizeof(uiNpcStasisEntry) / sizeof(uint32)) -1);

    pPlayer->SummonCreature(uiNpcStasisEntry[uiRandom],
        pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetAngle(pPlayer),
        TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

    return false;
}

/*######
## go_field_repair_bot_74A
######*/

enum
{
    SPELL_ENGINEER_FIELD_REPAIR_BOT_74A = 22704,
    SPELL_LEARN_FIELD_REPAIR_BOT_74A    = 22864
};

bool GOUse_go_field_repair_bot_74A(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ENGINEERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !pPlayer->HasSpell(SPELL_ENGINEER_FIELD_REPAIR_BOT_74A))
        pPlayer->CastSpell(pPlayer, SPELL_LEARN_FIELD_REPAIR_BOT_74A, false);

    return true;
}

/*######
## go_gilded_brazier
######*/

enum
{
    NPC_STILLBLADE = 17716,
};

bool GOUse_go_gilded_brazier(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
    {
        if (Creature* pCreature = pPlayer->SummonCreature(NPC_STILLBLADE, 8087.632f, -7542.740f, 151.568f, 0.122f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
            pCreature->AI()->AttackStart(pPlayer);
    }

    return true;
}

/*######
## go_jump_a_tron
######*/

enum
{
    SPELL_JUMP_A_TRON = 33382,
    NPC_JUMP_A_TRON   = 19041
};

bool GOUse_go_jump_a_tron(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_JUMP_A_TRON, INTERACTION_DISTANCE))
        pCreature->CastSpell(pPlayer, SPELL_JUMP_A_TRON, false);

    return false;
}

/*######
## go_mysterious_snow_mound
######*/

enum
{
    SPELL_SUMMON_DEEP_JORMUNGAR     = 66510,
    SPELL_SUMMON_MOLE_MACHINE       = 66492,
    SPELL_SUMMON_MARAUDER           = 66491,
};

bool GOUse_go_mysterious_snow_mound(Player* pPlayer, GameObject* pGo)
{
    if (urand(0,1))
    {
        pPlayer->CastSpell(pPlayer, SPELL_SUMMON_DEEP_JORMUNGAR, true);
    }
    else
    {
        // This is basically wrong, but added for support.
        // Mole machine would summon, along with unkonwn GO (a GO trap?) and then
        // the npc would summon with base of that location.
        pPlayer->CastSpell(pPlayer, SPELL_SUMMON_MOLE_MACHINE, true);
        pPlayer->CastSpell(pPlayer, SPELL_SUMMON_MARAUDER, true);
    }

    pGo->SetLootState(GO_JUST_DEACTIVATED);
    return true;
}

/*######
## go_orb_of_command
######*/

enum
{
    QUEST_BLACKHANDS_COMMAND = 7761,
    SPELL_TELEPORT_TO_BWL    = 23460
};

bool GOUse_go_orb_of_command(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(QUEST_BLACKHANDS_COMMAND))
        pPlayer->CastSpell(pPlayer, SPELL_TELEPORT_TO_BWL, true);

    return true;
}

/*######
## go_resonite_cask
######*/

enum
{
    NPC_GOGGEROC = 11920
};

bool GOUse_go_resonite_cask(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pGO->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

    return false;
}

/*######
## go_sacred_fire_of_life
######*/

enum
{
    NPC_ARIKARA = 10882,
};

bool GOUse_go_sacred_fire_of_life(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pPlayer->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

    return true;
}

/*######
## go_shrine_of_the_birds
######*/

enum
{
    NPC_HAWK_GUARD   = 22992,
    NPC_EAGLE_GUARD  = 22993,
    NPC_FALCON_GUARD = 22994,
    GO_SHRINE_HAWK   = 185551,
    GO_SHRINE_EAGLE  = 185547,
    GO_SHRINE_FALCON = 185553
};

bool GOUse_go_shrine_of_the_birds(Player* pPlayer, GameObject* pGo)
{
    uint32 uiBirdEntry = 0;

    float fX,fY,fZ;
    pGo->GetClosePoint(fX, fY, fZ, pGo->GetObjectBoundingRadius(), INTERACTION_DISTANCE);

    switch(pGo->GetEntry())
    {
        case GO_SHRINE_HAWK:
            uiBirdEntry = NPC_HAWK_GUARD;
            break;
        case GO_SHRINE_EAGLE:
            uiBirdEntry = NPC_EAGLE_GUARD;
            break;
        case GO_SHRINE_FALCON:
            uiBirdEntry = NPC_FALCON_GUARD;
            break;
    }

    if (uiBirdEntry)
        pPlayer->SummonCreature(uiBirdEntry, fX, fY, fZ, pGo->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

    return false;
}

/*######
## go_tablet_of_madness
######*/

enum
{
    SPELL_ALCHEMY_GURUBASHI_MOJO_MADNESS = 24266,
    SPELL_LEARN_GURUBASHI_MOJO_MADNESS   = 24267
};

bool GOUse_go_tablet_of_madness(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ALCHEMY) && pPlayer->GetSkillValue(SKILL_ALCHEMY) >= 300 && !pPlayer->HasSpell(SPELL_ALCHEMY_GURUBASHI_MOJO_MADNESS))
        pPlayer->CastSpell(pPlayer, SPELL_LEARN_GURUBASHI_MOJO_MADNESS, false);

    return true;
}

/*######
## go_tablet_of_the_seven - OBSOLETE
######*/

//TODO: use gossip option ("Transcript the Tablet") instead, if Mangos adds support.
bool GOUse_go_tablet_of_the_seven(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
        return true;

    if (pPlayer->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
        pPlayer->CastSpell(pPlayer, 15065, false);

    return true;
}

/*######
## go_tele_to_dalaran_crystal
######*/

enum
{
    QUEST_LEARN_LEAVE_RETURN = 12790,
    QUEST_TELE_CRYSTAL_FLAG  = 12845
};

bool GOUse_go_tele_to_dalaran_crystal(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(QUEST_TELE_CRYSTAL_FLAG))
        return false;

    //TODO: must send error message (what kind of message? On-screen?)
    return true;
}

/*######
## go_tele_to_violet_stand
######*/

bool GOUse_go_tele_to_violet_stand(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(QUEST_LEARN_LEAVE_RETURN) || pPlayer->GetQuestStatus(QUEST_LEARN_LEAVE_RETURN) == QUEST_STATUS_INCOMPLETE)
        return false;

    return true;
}

enum
{
    NPC_ZELEMAR_THE_WRATHFULL = 17830,
    SAY_AGGRO                 = -1000579
};

float Position[4] = {-327.99f, 221.74f, -20.31f, 3.87f};

bool GOUse_go_blood_filled_orb(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pZelemar = pGo->SummonCreature(NPC_ZELEMAR_THE_WRATHFULL, Position[0], Position[1], Position[2], Position[3], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000))
    {
        DoScriptText(SAY_AGGRO, pZelemar);
        pZelemar->AI()->AttackStart(pPlayer);
    }
    return false;
}

/*######
## go_andorhal_tower
######*/

enum
{
    QUEST_ALL_ALONG_THE_WATCHTOWERS_ALLIANCE = 5097,
    QUEST_ALL_ALONG_THE_WATCHTOWERS_HORDE    = 5098,
    NPC_ANDORHAL_TOWER_1                     = 10902,
    NPC_ANDORHAL_TOWER_2                     = 10903,
    NPC_ANDORHAL_TOWER_3                     = 10904,
    NPC_ANDORHAL_TOWER_4                     = 10905,
    GO_ANDORHAL_TOWER_1                      = 176094,
    GO_ANDORHAL_TOWER_2                      = 176095,
    GO_ANDORHAL_TOWER_3                      = 176096,
    GO_ANDORHAL_TOWER_4                      = 176097
};

bool GOUse_go_andorhal_tower(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_ALL_ALONG_THE_WATCHTOWERS_ALLIANCE) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_ALL_ALONG_THE_WATCHTOWERS_HORDE) == QUEST_STATUS_INCOMPLETE)
    {
        uint32 uiKillCredit = 0;
        switch(pGo->GetEntry())
        {
            case GO_ANDORHAL_TOWER_1:   uiKillCredit = NPC_ANDORHAL_TOWER_1;   break;
            case GO_ANDORHAL_TOWER_2:   uiKillCredit = NPC_ANDORHAL_TOWER_2;   break;
            case GO_ANDORHAL_TOWER_3:   uiKillCredit = NPC_ANDORHAL_TOWER_3;   break;
            case GO_ANDORHAL_TOWER_4:   uiKillCredit = NPC_ANDORHAL_TOWER_4;   break;
        }
        if (uiKillCredit)
            pPlayer->KilledMonsterCredit(uiKillCredit);
    }
    return true;
}

/*######
## go_scourge_enclosure
######*/

enum
{
    SPELL_GYMER_LOCK_EXPLOSION      = 55529,
    NPC_GYMER_LOCK_DUMMY            = 29928

};

bool GOUse_go_scourge_enclosure(Player* pPlayer, GameObject* pGo)
{
    std::list<Creature*> m_lResearchersList;
    GetCreatureListWithEntryInGrid(m_lResearchersList, pGo, NPC_GYMER_LOCK_DUMMY, 15.0f);
    if (!m_lResearchersList.empty())
    {
        for(std::list<Creature*>::iterator itr = m_lResearchersList.begin(); itr != m_lResearchersList.end(); ++itr)
        {
            (*itr)->CastSpell((*itr),SPELL_GYMER_LOCK_EXPLOSION,true);
        }
    }
    pPlayer->KilledMonsterCredit(NPC_GYMER_LOCK_DUMMY);
    return true;
}

/*######
## go_lab_work_reagents
######*/

enum
{
    QUEST_LAB_WORK                          = 12557,

    SPELL_WIRHERED_BATWING_KILL_CREDIT      = 51226,
    SPELL_MUDDY_MIRE_MAGGOT_KILL_CREDIT     = 51227,
    SPELL_AMBERSEED_KILL_CREDIT             = 51228,
    SPELL_CHILLED_SERPENT_MUCUS_KILL_CREDIT = 51229,

    GO_AMBERSEED                            = 190459,
    GO_CHILLED_SERPENT_MUCUS                = 190462,
    GO_WITHERED_BATWING                     = 190473,
    GO_MUDDY_MIRE_MAGGOTS                   = 190478,
};

bool GOUse_go_lab_work_reagents(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_LAB_WORK) == QUEST_STATUS_INCOMPLETE)
    {
        uint32 uiCreditSpellId = 0;
        switch (pGo->GetEntry())
        {
            case GO_AMBERSEED:              uiCreditSpellId = SPELL_AMBERSEED_KILL_CREDIT; break;
            case GO_CHILLED_SERPENT_MUCUS:  uiCreditSpellId = SPELL_CHILLED_SERPENT_MUCUS_KILL_CREDIT; break;
            case GO_WITHERED_BATWING:       uiCreditSpellId = SPELL_WIRHERED_BATWING_KILL_CREDIT; break;
            case GO_MUDDY_MIRE_MAGGOTS:     uiCreditSpellId = SPELL_MUDDY_MIRE_MAGGOT_KILL_CREDIT; break;
        }

        if (uiCreditSpellId)
            pPlayer->CastSpell(pPlayer, uiCreditSpellId, true);
    }

    return false;
}

/*######
## go_hand_of_iruxos_crystal
######*/

/* TODO
 * Actually this script is extremely vague, but as long as there is no valid information
 * hidden in some dark places, this will be the best we can do here :(
 * Do not consider this a well proven script.
 */

enum
{
    // QUEST_HAND_OF_IRUXOS     = 5381,
    NPC_IRUXOS                  = 11876,
};

bool GOUse_go_hand_of_iruxos_crystal(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pIruxos = pGo->SummonCreature(NPC_IRUXOS, 0.0f, 0.0f, 0.0f, pPlayer->GetOrientation() + M_PI_F, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000))
        pIruxos->AI()->AttackStart(pPlayer);

    return false;
}

/*######
## go_Ethereal_Power_Pad
######*/
enum
{
	QUEST_NOT_SO_MODEST_PROPOSAL    = 10270,
	ITEM_TELEPORTER_POWER_PACK      = 28969,
	NPC_IMAGE_OF_WIND_TRADER_MARID  = 20518

};
bool GOUse_go_Ethereal_Teleport_pad(Player* pPlayer, GameObject* pGo)
{
	Creature* pMarid = GetClosestCreatureWithEntry(pPlayer, NPC_IMAGE_OF_WIND_TRADER_MARID, 30.0f);

    if (pMarid)
        return true;

	if ((pPlayer->GetQuestRewardStatus(QUEST_NOT_SO_MODEST_PROPOSAL) == QUEST_STATUS_COMPLETE)|| pPlayer->GetQuestStatus(QUEST_NOT_SO_MODEST_PROPOSAL) == QUEST_STATUS_COMPLETE )
	{
		pPlayer->SummonCreature(NPC_IMAGE_OF_WIND_TRADER_MARID, 4007.11f, 1517.15f, -116.363f, -0.453786f, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 30000);

	}
	return true;

}

/*#####
## go_corkis_prison
#####*/

enum
{
    QUEST_HELP                          = 9923,
    QUEST_CORKIS_GONE                   = 9924,
    QUEST_CHOWAR                        = 9955,
    
    GO_CORKIS_PRISON_1                  = 182349,
    GO_CORKIS_PRISON_2                  = 182350,
    GO_CORKIS_PRISON_3                  = 182521,
    
    NPC_CORKI                           = 18369,
    NPC_CORKI_GONE                      = 20812,
    NPC_CORKI_CHOWAR                    = 18445,
    NPC_CORKI_EVENT                     = 18444,
    
    SPELL_DESPAWN_SELF                  = 43014,
    
    SAY_THANKS_1                        = -1999851,
    SAY_THANKS_2                        = -1999891
};

bool GOUse_go_corkis_prison(Player* pPlayer, GameObject* pGo)
{
    uint64 uiCorkiEntry;
    if (pPlayer->GetQuestStatus(QUEST_HELP) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_CORKIS_GONE) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_CHOWAR) == QUEST_STATUS_INCOMPLETE)
    {
        switch (pGo->GetEntry())
        {
        case GO_CORKIS_PRISON_1: uiCorkiEntry=NPC_CORKI;
            break;
        case GO_CORKIS_PRISON_2: uiCorkiEntry=NPC_CORKI_GONE;
            break;
        case GO_CORKIS_PRISON_3: uiCorkiEntry=NPC_CORKI_CHOWAR;
            break;
        }
        if(Creature *pCorki = GetClosestCreatureWithEntry(pPlayer, uiCorkiEntry, INTERACTION_DISTANCE))
        {
            switch (uiCorkiEntry)
            {
            case NPC_CORKI:
                pPlayer->KilledMonsterCredit(NPC_CORKI, pCorki->GetObjectGuid());
                DoScriptText(SAY_THANKS_1, pCorki);
                break;
            case NPC_CORKI_GONE:
                pPlayer->KilledMonsterCredit(NPC_CORKI_GONE, pCorki->GetObjectGuid());
                DoScriptText(SAY_THANKS_2, pCorki);
                break;
            case NPC_CORKI_CHOWAR:
                pPlayer->KilledMonsterCredit(NPC_CORKI_EVENT, pCorki->GetObjectGuid());
                break;
            }
            pCorki->CastSpell(pCorki, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

/*#####
## go_warmaul_prison
#####*/

enum
{
    QUEST_FINDING_THE_SURVIVORS        = 9948,
    NPC_MAGHAR_PRISONER                = 18428,
    SAY_MAGHAR_THANKS_1                = -1000040,
    SAY_MAGHAR_THANKS_2                = -1000041,
    SAY_MAGHAR_THANKS_3                = -1000042,
};

bool GOUse_go_warmaul_prison(Player* pPlayer, GameObject* pGo) 
{
    if (pPlayer->GetQuestStatus(QUEST_FINDING_THE_SURVIVORS) == QUEST_STATUS_INCOMPLETE)
    {

        if (Creature *pCreature = GetClosestCreatureWithEntry(pGo, NPC_MAGHAR_PRISONER, INTERACTION_DISTANCE))
        {
            pPlayer->CastedCreatureOrGO(NPC_MAGHAR_PRISONER, pCreature->GetObjectGuid(), 32347);
            switch(urand(0,2))
            {
                case 0: DoScriptText(SAY_MAGHAR_THANKS_1, pCreature); break;
                case 1: DoScriptText(SAY_MAGHAR_THANKS_2, pCreature); break;
                default: DoScriptText(SAY_MAGHAR_THANKS_3, pCreature); break;
            }
            pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

/*#####
## go_mammoth_trap
#####*/

enum
{
    QUEST_HELP_THOSE_THAT    =  11876,
    NPC_TRAPPED_MAMMOTH      =  25850
};

bool GOUse_go_mammoth_trap(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_HELP_THOSE_THAT) == QUEST_STATUS_INCOMPLETE)
    {
        Creature *pCreature = GetClosestCreatureWithEntry(pGo, NPC_TRAPPED_MAMMOTH, INTERACTION_DISTANCE);
        if(pCreature)
        {
            pPlayer->KilledMonsterCredit(NPC_TRAPPED_MAMMOTH, pCreature->GetObjectGuid());
            pCreature->CastSpell(pCreature, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

/*######
## go_demon_portal
######*/
enum
{
    QUEST_PORTAL_LEGIONS             = 5581,
    NPC_DEMON_PORTAL_GUARDIAN        = 11937

};

bool GOUse_go_demon_portal(Player* pPlayer, GameObject* pGo)
{
    Creature* pCreature = GetClosestCreatureWithEntry(pPlayer, NPC_DEMON_PORTAL_GUARDIAN, 5.0f);

    if (pCreature)
        return true;

    if (pPlayer->GetQuestStatus(QUEST_PORTAL_LEGIONS) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->SummonCreature(NPC_DEMON_PORTAL_GUARDIAN, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 99999999);
    }
    return true;
};

/*#####
## go_gjalerbron_cage
#####*/

enum
{
    QUEST_OF_KEY_AND_CAGES_A    = 11231,
    QUEST_OF_KEY_AND_CAGES_H    = 11265,
    NPC_GJALERBON_PRISONER      = 24035
};

bool GOUse_go_gjalerbon_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_OF_KEY_AND_CAGES_A) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_OF_KEY_AND_CAGES_H) == QUEST_STATUS_INCOMPLETE)
    {
            if(Creature *pPrisoner = GetClosestCreatureWithEntry(pPlayer, NPC_GJALERBON_PRISONER, 10))
            {
                pPlayer->KilledMonsterCredit(NPC_GJALERBON_PRISONER, pPrisoner->GetObjectGuid());
                pPrisoner->CastSpell(pPrisoner, SPELL_DESPAWN_SELF, false);
            }
    }
    return false;
};

bool GOUse_go_large_gjalerbon_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_OF_KEY_AND_CAGES_A) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_OF_KEY_AND_CAGES_H) == QUEST_STATUS_INCOMPLETE)
    {
        std::list<Creature*> lGjalerbronPrisoners;
        GetCreatureListWithEntryInGrid(lGjalerbronPrisoners, pPlayer,  NPC_GJALERBON_PRISONER, 20.0f);
        if (lGjalerbronPrisoners.empty())
            return false;

        for (std::list<Creature*>::iterator itr = lGjalerbronPrisoners.begin(); itr != lGjalerbronPrisoners.end(); ++itr)
        {
            pPlayer->KilledMonsterCredit(NPC_GJALERBON_PRISONER, (*itr)->GetObjectGuid());
                (*itr)->CastSpell(*itr, SPELL_DESPAWN_SELF, false);
        }
            
    }
    return false;
};

/*#####
## go_black_cage
#####*/

enum
{
    QUEST_YOUVE_REALLY_DONE_IT_THIS_TIME_KUL_A  = 14096,
    QUEST_YOUVE_REALLY_DONE_IT_THIS_TIME_KUL_H  = 14142,
    NPC_CAPTIVE_ASPIRANT                        = 34716,
    NPC_KUL_THE_RECKLESS                        = 34956,
    SPELL_SELF_DESPAWN                          = 43014,
    SAY_THANKS1                                = -3471601,
    SAY_THANKS2                                = -3495601
};
 
bool GOUse_go_black_cage(Player* pPlayer, GameObject* pGo)
{
    if(pPlayer->GetQuestStatus(QUEST_YOUVE_REALLY_DONE_IT_THIS_TIME_KUL_A) == QUEST_STATUS_INCOMPLETE 
        || pPlayer->GetQuestStatus(QUEST_YOUVE_REALLY_DONE_IT_THIS_TIME_KUL_H) == QUEST_STATUS_INCOMPLETE)
    {
        if(Creature *pAspirant = GetClosestCreatureWithEntry(pPlayer, NPC_CAPTIVE_ASPIRANT, 10.0f))
        {
            pPlayer->KilledMonsterCredit(NPC_CAPTIVE_ASPIRANT, pAspirant->GetObjectGuid());
            DoScriptText(SAY_THANKS1, pAspirant);
            pAspirant->CastSpell(pAspirant, SPELL_SELF_DESPAWN, false);
            return true;
        }

        if(Creature *pKul = GetClosestCreatureWithEntry(pPlayer, NPC_KUL_THE_RECKLESS, 10.0f))
        {
            pPlayer->KilledMonsterCredit(NPC_KUL_THE_RECKLESS, pKul->GetObjectGuid());
            DoScriptText(SAY_THANKS2, pKul);
            pKul->CastSpell(pKul, SPELL_SELF_DESPAWN, false);
            return true;
        }
    }
    return false;
};
/*#####
## go_cage_door
#####*/

enum
{
    QUEST_FREEDOM_FOR_ALL_CREATURES  = 2969,    
    NPC_CAPTURED_DARTER              = 7997,
};
 
bool GOUse_go_cage_door(Player* pPlayer, GameObject* pGo)
{
    if(pPlayer->GetQuestStatus(QUEST_FREEDOM_FOR_ALL_CREATURES) == QUEST_STATUS_INCOMPLETE)
    {
        if(Creature *pDarter = GetClosestCreatureWithEntry(pPlayer, NPC_CAPTURED_DARTER, 10.0f))
        {
            pPlayer->AreaExploredOrEventHappens(QUEST_FREEDOM_FOR_ALL_CREATURES);
            pDarter->CastSpell(pDarter, SPELL_SELF_DESPAWN, false);
            return true;
        }        
    }
    return false;
};

/*#####
## go_rusty_cage
#####*/

enum
{
    QUEST_THEY_TOOK_OUR_MEN = 12843,
    NPC_GOBLIN_PRISONER = 29466,
    SAY_GOBLIN_THANKS_1 = -1999778,
    SAY_GOBLIN_THANKS_2 = -1999777
};

bool GOUse_go_rusty_cage(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_THEY_TOOK_OUR_MEN) == QUEST_STATUS_INCOMPLETE)
    {
        if(Creature *pGoblin = GetClosestCreatureWithEntry(pPlayer, NPC_GOBLIN_PRISONER, INTERACTION_DISTANCE))
        {
            pPlayer->KilledMonsterCredit(NPC_GOBLIN_PRISONER, pGoblin->GetObjectGuid());
            DoScriptText(urand(0, 1) ? SAY_GOBLIN_THANKS_1 : SAY_GOBLIN_THANKS_2, pGoblin);
            pGoblin->CastSpell(pGoblin, SPELL_DESPAWN_SELF, false);
        }
    }
    return false;
};

void AddSC_go_scripts()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_cat_figurine";
    pNewScript->pGOUse =          &GOUse_go_cat_figurine;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_barov_journal";
    pNewScript->pGOUse =          &GOUse_go_barov_journal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_ethereum_prison";
    pNewScript->pGOUse =          &GOUse_go_ethereum_prison;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_ethereum_stasis";
    pNewScript->pGOUse =          &GOUse_go_ethereum_stasis;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_field_repair_bot_74A";
    pNewScript->pGOUse =          &GOUse_go_field_repair_bot_74A;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_gilded_brazier";
    pNewScript->pGOUse =          &GOUse_go_gilded_brazier;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_jump_a_tron";
    pNewScript->pGOUse =          &GOUse_go_jump_a_tron;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_mysterious_snow_mound";
    pNewScript->pGOUse =          &GOUse_go_mysterious_snow_mound;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_orb_of_command";
    pNewScript->pGOUse =          &GOUse_go_orb_of_command;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_resonite_cask";
    pNewScript->pGOUse =          &GOUse_go_resonite_cask;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_sacred_fire_of_life";
    pNewScript->pGOUse =          &GOUse_go_sacred_fire_of_life;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_shrine_of_the_birds";
    pNewScript->pGOUse =          &GOUse_go_shrine_of_the_birds;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tablet_of_madness";
    pNewScript->pGOUse =          &GOUse_go_tablet_of_madness;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tablet_of_the_seven";
    pNewScript->pGOUse =          &GOUse_go_tablet_of_the_seven;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tele_to_dalaran_crystal";
    pNewScript->pGOUse =          &GOUse_go_tele_to_dalaran_crystal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tele_to_violet_stand";
    pNewScript->pGOUse =          &GOUse_go_tele_to_violet_stand;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_blood_filled_orb";
    pNewScript->pGOUse =          &GOUse_go_blood_filled_orb;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_andorhal_tower";
    pNewScript->pGOUse =          &GOUse_go_andorhal_tower;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_scourge_enclosure";
    pNewScript->pGOUse =          &GOUse_go_scourge_enclosure;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_lab_work_reagents";
    pNewScript->pGOUse =          &GOUse_go_lab_work_reagents;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_hand_of_iruxos_crystal";
    pNewScript->pGOUse =          &GOUse_go_hand_of_iruxos_crystal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_Ethereal_Teleport_pad";
    pNewScript->pGOUse = &GOUse_go_Ethereal_Teleport_pad;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_corkis_prison";
    pNewScript->pGOUse = &GOUse_go_corkis_prison;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_warmaul_prison";
    pNewScript->pGOUse = &GOUse_go_warmaul_prison;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_mammoth_trap";
    pNewScript->pGOUse = &GOUse_go_mammoth_trap;
    pNewScript->RegisterSelf();

    pNewScript = new Script;	
    pNewScript->Name = "go_demon_portal";
    pNewScript->pGOUse = &GOUse_go_demon_portal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_gjalerbon_cage";
    pNewScript->pGOUse = &GOUse_go_gjalerbon_cage;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_large_gjalerbon_cage";
    pNewScript->pGOUse = &GOUse_go_large_gjalerbon_cage;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_black_cage";
    pNewScript->pGOUse = &GOUse_go_black_cage;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_cage_door";
    pNewScript->pGOUse = &GOUse_go_cage_door;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_rusty_cage";
    pNewScript->pGOUse = &GOUse_go_rusty_cage;
    pNewScript->RegisterSelf();
}
