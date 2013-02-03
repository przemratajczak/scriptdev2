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
SDName: Silithus
SD%Complete: 100
SDComment: Quest support: 7785, 8304.
SDCategory: Silithus
EndScriptData */

/* ContentData
npc_highlord_demitrian
npcs_rutgar_and_frankal
EndContentData */

#include "precompiled.h"

/*###
## npc_highlord_demitrian
###*/

#define GOSSIP_ITEM_DEMITRIAN1 "What do you know of it?"
#define GOSSIP_ITEM_DEMITRIAN2 "I am listening , Demitrian."
#define GOSSIP_ITEM_DEMITRIAN3 "Continue, please."
#define GOSSIP_ITEM_DEMITRIAN4 "A battle?"
#define GOSSIP_ITEM_DEMITRIAN5 "<Nod>"
#define GOSSIP_ITEM_DEMITRIAN6 "Caught unaware? How?"
#define GOSSIP_ITEM_DEMITRIAN7 "So what did Ragnaros do next?"

enum
{
    QUEST_EXAMINE_THE_VESSEL        =   7785,
    ITEM_BINDINGS_WINDSEEKER_LEFT   =   18563,
    ITEM_BINDINGS_WINDSEEKER_RIGHT  =   18564,
    ITEM_VESSEL_OF_REBIRTH          =   19016,
    GOSSIP_TEXTID_DEMITRIAN1        =   6842,
    GOSSIP_TEXTID_DEMITRIAN2        =   6843,
    GOSSIP_TEXTID_DEMITRIAN3        =   6844,
    GOSSIP_TEXTID_DEMITRIAN4        =   6867,
    GOSSIP_TEXTID_DEMITRIAN5        =   6868,
    GOSSIP_TEXTID_DEMITRIAN6        =   6869,
    GOSSIP_TEXTID_DEMITRIAN7        =   6870
};

bool GossipHello_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_EXAMINE_THE_VESSEL) == QUEST_STATUS_NONE &&
        (pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_LEFT,1,false) || pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_RIGHT,1,false)))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN6, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN7, pCreature->GetObjectGuid());

            if (Item* pItem = pPlayer->StoreNewItemInInventorySlot(ITEM_VESSEL_OF_REBIRTH, 1))
                pPlayer->SendNewItem(pItem, 1, true, false);

            break;
    }
    return true;
}

/*###
## npcs_rutgar_and_frankal
###*/

//gossip item text best guess
#define GOSSIP_ITEM_SEEK1 "I seek information about Natalia"

#define GOSSIP_ITEM_RUTGAR2 "That sounds dangerous!"
#define GOSSIP_ITEM_RUTGAR3 "What did you do?"
#define GOSSIP_ITEM_RUTGAR4 "Who?"
#define GOSSIP_ITEM_RUTGAR5 "Women do that. What did she demand?"
#define GOSSIP_ITEM_RUTGAR6 "What do you mean?"
#define GOSSIP_ITEM_RUTGAR7 "What happened next?"

#define GOSSIP_ITEM_FRANKAL11 "Yes, please continue"
#define GOSSIP_ITEM_FRANKAL12 "What language?"
#define GOSSIP_ITEM_FRANKAL13 "The Priestess attacked you?!"
#define GOSSIP_ITEM_FRANKAL14 "I should ask the monkey about this"
#define GOSSIP_ITEM_FRANKAL15 "Then what..."

enum
{
    QUEST_DEAREST_NATALIA       =   8304,
    NPC_RUTGAR                  =   15170,
    NPC_FRANKAL                 =   15171,
    TRIGGER_RUTGAR              =   15222,
    TRIGGER_FRANKAL             =   15221,
    GOSSIP_TEXTID_RF            =   7754,
    GOSSIP_TEXTID_RUTGAR1       =   7755,
    GOSSIP_TEXTID_RUTGAR2       =   7756,
    GOSSIP_TEXTID_RUTGAR3       =   7757,
    GOSSIP_TEXTID_RUTGAR4       =   7758,
    GOSSIP_TEXTID_RUTGAR5       =   7759,
    GOSSIP_TEXTID_RUTGAR6       =   7760,
    GOSSIP_TEXTID_RUTGAR7       =   7761,
    GOSSIP_TEXTID_FRANKAL1      =   7762,
    GOSSIP_TEXTID_FRANKAL2      =   7763,
    GOSSIP_TEXTID_FRANKAL3      =   7764,
    GOSSIP_TEXTID_FRANKAL4      =   7765,
    GOSSIP_TEXTID_FRANKAL5      =   7766,
    GOSSIP_TEXTID_FRANKAL6      =   7767
};

bool GossipHello_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
        pCreature->GetEntry() == NPC_RUTGAR &&
        !pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
        pCreature->GetEntry() == NPC_FRANKAL &&
        pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RF, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR6, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR7, pCreature->GetObjectGuid());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_RUTGAR, pCreature->GetObjectGuid());
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL12, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL13, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL14, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL15, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 14:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL6, pCreature->GetObjectGuid());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_FRANKAL, pCreature->GetObjectGuid());
            break;
    }
    return true;
}

/*******************
**Lesser Wind Stone
********************/
#define GOSSIP_ITEM_1 "I am not cultist, you monster! Come to me and face yout destruction!"
#define GOSSIP_ITEM_2 "You will listen to this, wille duke! I am not your Twillight's Hammer lapdog! I am here to challenge you! Come! Come, and meet your death..."
#define GOSSIP_ITEM_3 "The day of judgement has come, friend! I challenge you, no battle!"

#define GOSSIP_TEXT_1 "A faint whisper is heard form within the stone... Greetings, little one. Do you have news for the Templar?"
#define GOSSIP_TEXT_2 "A clear voice rises form within the stone...You come to us with litle and so we will listen, but do not try our patience. The council has no time for idle gossip from one such as you."
#define GOSSIP_TEXT_3 "A thunderous voice bellows form the stone... Greetings, commander. What news of Sillithus do you bring the Lords of the Council?"

enum
{
    //Lesser Wind Stone
    NPC_HOARY_TEMPLAR       = 15212,
    NPC_CRIMSON_TEMPLAR     = 15209,
    NPC_EARTHEN_TEMPLAR     = 15307,
    NPC_AZURE_TEMPLAR       = 15211,

    //Wind Stone
    NPC_DUKE_CYNDERS        = 15206,
    NPC_DUKE_FATHOMS        = 15207,
    NPC_DUKE_SHARDS         = 15208,
    NPC_DUKE_ZEPHYRS        = 15220,

    //Great Wind Stone
    NPC_LORD                = 15305,
    NPC_PRINCE              = 15203,
    NPC_BARON               = 15205,
    NPC_MARSHAL             = 15204,

    SPELL_TEMPLAR_RANDOM    = 24745,
    SPELL_DUKE_RANDOM       = 24763,    
    SPELL_ROYAL_RANDOM      = 24784, 
    SPELL_ARCANE_LIGHT      = 52921,    //When player dont have all items

    GO_LESSER_WIND_STONE    = 180456,
    GO_WIND_STONE           = 180461,
    GO_GREATH_WIND_STONE    = 180466,

    ITEM_MANTLE             = 20406,
    ITEM_COWL               = 20408,
    ITEM_ROBE               = 20407,
    ITEM_MEDALION           = 20422,
    ITEM_RING               = 20451,
};

bool GOGossipHello_go_lesser_wind_stone(Player* pPlayer,  GameObject* pGo)
{
    //pPlayer->CastSpell(pPlayer, SPELL_ARCANE_LIGHT, true);

    if(pPlayer->HasItemOrGemWithIdEquipped(ITEM_MANTLE, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_COWL, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_ROBE, 1))
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(100001, pGo->GetObjectGuid());
    }

    return true;
}

bool GOGossipSelect_go_lesser_wind_stone(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
{
    pPlayer->CLOSE_GOSSIP_MENU();

    switch(urand(0, 3))
    {
        case 0:
            pPlayer->CastSpell(pPlayer, SPELL_TEMPLAR_RANDOM, false);
            pPlayer->SummonCreature(NPC_HOARY_TEMPLAR, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 1:
            pPlayer->CastSpell(pPlayer, SPELL_TEMPLAR_RANDOM, false);
            pPlayer->SummonCreature(NPC_CRIMSON_TEMPLAR, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 2:
            pPlayer->CastSpell(pPlayer, SPELL_TEMPLAR_RANDOM, false);
            pPlayer->SummonCreature(NPC_EARTHEN_TEMPLAR, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 3:
            pPlayer->CastSpell(pPlayer, SPELL_TEMPLAR_RANDOM, false);
            pPlayer->SummonCreature(NPC_AZURE_TEMPLAR, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
    }
    return true;
}

/************
**Wind Stone
*************/
bool GOGossipHello_go_wind_stone(Player* pPlayer, GameObject* pGo)
{
    //pPlayer->CastSpell(pPlayer, SPELL_ARCANE_LIGHT, true);

    if(pPlayer->HasItemOrGemWithIdEquipped(ITEM_MANTLE, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_COWL, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_ROBE, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_MEDALION, 1))
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(100001, pGo->GetObjectGuid());
    }

    return true;
}

bool GOGossipSelect_go_wind_stone(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
{
    pPlayer->CLOSE_GOSSIP_MENU();
    switch(urand(0, 3))
    {
        case 0:
            pPlayer->CastSpell(pPlayer, SPELL_DUKE_RANDOM, false);
            pPlayer->SummonCreature(NPC_DUKE_CYNDERS, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 1:
            pPlayer->CastSpell(pPlayer, SPELL_DUKE_RANDOM, false);
            pPlayer->SummonCreature(NPC_DUKE_FATHOMS, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 2:
            pPlayer->CastSpell(pPlayer, SPELL_DUKE_RANDOM, false);
            pPlayer->SummonCreature(NPC_DUKE_SHARDS, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 3:
            pPlayer->CastSpell(pPlayer, SPELL_DUKE_RANDOM, false);
            pPlayer->SummonCreature(NPC_DUKE_ZEPHYRS, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
    }
    return true;
}

/******************
**Great Wind Stone
*******************/
bool GOGossipHello_go_great_wind_stone(Player* pPlayer, GameObject* pGo)
{
    //pPlayer->CastSpell(pPlayer, SPELL_ARCANE_LIGHT, true);

    if(pPlayer->HasItemOrGemWithIdEquipped(ITEM_MANTLE, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_COWL, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_ROBE, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_MEDALION, 1) && pPlayer->HasItemOrGemWithIdEquipped(ITEM_RING, 1))
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(100001, pGo->GetObjectGuid());
    }

    return true;
}

bool GOGossipSelect_go_great_wind_stone(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
{
    pPlayer->CLOSE_GOSSIP_MENU();

    switch(urand(0, 3))
    {
        case 0:
            pPlayer->CastSpell(pPlayer, SPELL_ROYAL_RANDOM, false);
            pGo->SummonCreature(NPC_LORD, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 1:
            pPlayer->CastSpell(pPlayer, SPELL_ROYAL_RANDOM, false);
            pGo->SummonCreature(NPC_PRINCE, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 2:
            pPlayer->CastSpell(pPlayer, SPELL_ROYAL_RANDOM, false);
            pGo->SummonCreature(NPC_BARON, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
        case 3:
            pPlayer->CastSpell(pPlayer, SPELL_ROYAL_RANDOM, false);
            pGo->SummonCreature(NPC_MARSHAL, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), pGo->GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
            break;
    }

    return true;
}


/*###
## npc_anachronos_the_ancient
###*/

enum
{
    // Dragons
    NPC_MERITHRA_OF_THE_DREAM           = 15378,
    NPC_CAELESTRASZ                     = 15379,
    NPC_ARYGOS                          = 15380,
    NPC_ANACHRONOS_THE_ANCIENT          = 15381,
    NPC_ANACHRONOS_QUEST_TRIGGER        = 15454,            // marks some movement for the dragons

    // Elfs
    NPC_FANDRAL_STAGHELM                = 15382,
    NPC_KALDOREI_INFANTRY               = 15423,

    // Qiraji warriors
    NPC_QIRAJI_WASP                     = 15414,
    NPC_QIRAJI_DRONE                    = 15421,
    NPC_QIRAJI_TANK                     = 15422,
    NPC_ANUBISATH_CONQUEROR             = 15424,

    QUEST_A_PAWN_ON_THE_ETERNAL_BOARD   = 8519,

    // Yells -> in chronological order
    SAY_ANACHRONOS_INTRO_1              = -1000740,
    SAY_FANDRAL_INTRO_2                 = -1000741,
    SAY_MERITHRA_INTRO_3                = -1000742,
    EMOTE_ARYGOS_NOD                    = -1000743,
    SAY_CAELESTRASZ_INTRO_4             = -1000744,
    EMOTE_MERITHRA_GLANCE               = -1000745,
    SAY_MERITHRA_INTRO_5                = -1000746,

    SAY_MERITHRA_ATTACK_1               = -1000747,
    SAY_ARYGOS_ATTACK_2                 = -1000748,
    SAY_ARYGOS_ATTACK_3                 = -1000749,
    SAY_CAELESTRASZ_ATTACK_4            = -1000750,
    SAY_CAELESTRASZ_ATTACK_5            = -1000751,

    SAY_ANACHRONOS_SEAL_1               = -1000752,
    SAY_FANDRAL_SEAL_2                  = -1000753,
    SAY_ANACHRONOS_SEAL_3               = -1000754,
    SAY_ANACHRONOS_SEAL_4               = -1000755,
    SAY_ANACHRONOS_SEAL_5               = -1000756,
    SAY_FANDRAL_SEAL_6                  = -1000757,

    EMOTE_FANDRAL_EXHAUSTED             = -1000758,
    SAY_ANACHRONOS_EPILOGUE_1           = -1000759,
    SAY_ANACHRONOS_EPILOGUE_2           = -1000760,
    SAY_ANACHRONOS_EPILOGUE_3           = -1000761,
    EMOTE_ANACHRONOS_SCEPTER            = -1000762,
    SAY_FANDRAL_EPILOGUE_4              = -1000763,
    SAY_FANDRAL_EPILOGUE_5              = -1000764,
    EMOTE_FANDRAL_SHATTER               = -1000765,
    SAY_ANACHRONOS_EPILOGUE_6           = -1000766,
    SAY_FANDRAL_EPILOGUE_7              = -1000767,
    EMOTE_ANACHRONOS_DISPPOINTED        = -1000768,
    EMOTE_ANACHRONOS_PICKUP             = -1000769,
    SAY_ANACHRONOS_EPILOGUE_8           = -1000770,

    // The transform spell for Anachronos was removed from DBC
    DISPLAY_ID_BRONZE_DRAGON            = 15500,

    // Spells
    SPELL_GREEN_DRAGON_TRANSFORM        = 25105,
    SPELL_RED_DRAGON_TRANSFORM          = 25106,
    SPELL_BLUE_DRAGON_TRANSFORM         = 25107,
    //SPELL_BRONZE_DRAGON_TRANSFORM       = 25108,          // Spell was removed - exists only before 2.0.1

    SPELL_MERITHRA_WAKE                 = 25145,            // should trigger 25172 on targets
    SPELL_ARYGOS_VENGEANCE              = 25149,
    SPELL_CAELESTRASZ_MOLTEN_RAIN       = 25150,

    SPELL_TIME_STOP                     = 25158,            // Anachronos stops the battle - should trigger 25171
    SPELL_GLYPH_OF_WARDING              = 25166,            // Sends event 9427 - should activate Go 176148
    SPELL_PRISMATIC_BARRIER             = 25159,            // Sends event 9425 - should activate Go 176146
    SPELL_CALL_ANCIENTS                 = 25167,            // Sends event 9426 - should activate Go 176147
    SPELL_SHATTER_HAMMER                = 25182,            // Breakes the scepter - needs DB coords

    POINT_ID_DRAGON_ATTACK              = 1,
    POINT_ID_EXIT                       = 2,
    POINT_ID_GATE                       = 3,
    POINT_ID_SCEPTER_1                  = 4,
    POINT_ID_SCEPTER_2                  = 5,
    POINT_ID_EPILOGUE                   = 6,
    DATA_HANDLE_SCEPTER                 = 7,        // dummy members - used in dialogue helper
    DATA_MERITHRA_ATTACK                = 8,
    DATA_CAELASTRASZ_ATTACK             = 9,

    MAX_DRAGONS                         = 4,
    MAX_CONQUERORS                      = 3,
    MAX_QIRAJI                          = 6,
    MAX_KALDOREI                        = 20,
};

/* Known event issues:
 * The Kaldorei and Qiraji soldiers don't have the correct flags and factions in DB
 * The Ahn'Qiraj gate gameobjects are missing from DB
 * The spells used by the dragons upon the Qiraji need core support
 * The script events sent by the spells which close the AQ gate needs DB support
 * Can't make Fandral equip the Scepter when Anachronos handles it to him
 */

static const DialogueEntry aEventDialogue[] =
{
    {NPC_ANACHRONOS_THE_ANCIENT,    0,                          2000},  // summon the dragons
    {SAY_ANACHRONOS_INTRO_1,        NPC_ANACHRONOS_THE_ANCIENT, 3000},
    {EMOTE_ONESHOT_SHOUT,           NPC_ANACHRONOS_THE_ANCIENT, 3000},  // make Anachronos shout and summon the warriors
    {SAY_FANDRAL_INTRO_2,           NPC_FANDRAL_STAGHELM,       6000},
    {EMOTE_MERITHRA_GLANCE,         NPC_MERITHRA_OF_THE_DREAM,  2000},
    {SAY_MERITHRA_INTRO_3,          NPC_MERITHRA_OF_THE_DREAM,  3000},
    {EMOTE_ARYGOS_NOD,              NPC_ARYGOS,                 4000},
    {SAY_CAELESTRASZ_INTRO_4,       NPC_CAELESTRASZ,            9000},
    {SAY_MERITHRA_INTRO_5,          NPC_MERITHRA_OF_THE_DREAM,  5000},
    {NPC_ANACHRONOS_QUEST_TRIGGER,  0,                          0},     // send Merithra to fight
    {DATA_MERITHRA_ATTACK,          0,                          5000},  // make Merithra wait
    {SAY_MERITHRA_ATTACK_1,         NPC_MERITHRA_OF_THE_DREAM,  1000},
    {SPELL_GREEN_DRAGON_TRANSFORM,  0,                          6000},
    {SAY_ARYGOS_ATTACK_2,           NPC_ARYGOS,                 5000},
    {NPC_ARYGOS,                    0,                          1000},  // send Arygos to fight
    {POINT_ID_EXIT,                 0,                          4000},  // make Merithra exit
    {SAY_ARYGOS_ATTACK_3,           NPC_ARYGOS,                 4000},
    {SPELL_BLUE_DRAGON_TRANSFORM,   0,                          5000},
    {SPELL_ARYGOS_VENGEANCE,        0,                          7000},
    {POINT_ID_DRAGON_ATTACK,        0,                          1000},  // make Arygos exit
    {SAY_CAELESTRASZ_ATTACK_4,      NPC_CAELESTRASZ,            5000},
    {NPC_CAELESTRASZ,               0,                          0},     // send Caelestrasz to fight
    {DATA_CAELASTRASZ_ATTACK,       0,                          3000},  // make Caelestrasz wait
    {SAY_CAELESTRASZ_ATTACK_5,      NPC_CAELESTRASZ,            5000},
    {SPELL_RED_DRAGON_TRANSFORM,    0,                          4000},  // transform Caelestrasz
    {SPELL_CAELESTRASZ_MOLTEN_RAIN, 0,                          6000},  // Caelestrasz casts molten rain
    {SAY_ANACHRONOS_SEAL_1,         NPC_ANACHRONOS_THE_ANCIENT, 5000},
    {SAY_FANDRAL_SEAL_2,            NPC_FANDRAL_STAGHELM,       3000},
    {SAY_ANACHRONOS_SEAL_3,         NPC_ANACHRONOS_THE_ANCIENT, 1000},
    {POINT_ID_GATE,                 0,                          1000},  // send Anachronos to the gate
    {NPC_FANDRAL_STAGHELM,          0,                          0},     // send Fandral to the gate
    {SPELL_TIME_STOP,               0,                          7000},  // Anachronos casts Time Stop
    {SPELL_PRISMATIC_BARRIER,       0,                          15000},
    {SPELL_GLYPH_OF_WARDING,        0,                          4000},
    {SAY_ANACHRONOS_SEAL_5,         NPC_ANACHRONOS_THE_ANCIENT, 3000},
    {SAY_FANDRAL_SEAL_6,            NPC_FANDRAL_STAGHELM,       9000},
    {EMOTE_FANDRAL_EXHAUSTED,       NPC_FANDRAL_STAGHELM,       1000},
    {SAY_ANACHRONOS_EPILOGUE_1,     NPC_ANACHRONOS_THE_ANCIENT, 6000},
    {SAY_ANACHRONOS_EPILOGUE_2,     NPC_ANACHRONOS_THE_ANCIENT, 5000},
    {SAY_ANACHRONOS_EPILOGUE_3,     NPC_ANACHRONOS_THE_ANCIENT, 15000},
    {DATA_HANDLE_SCEPTER,           NPC_ANACHRONOS_THE_ANCIENT, 3000},  // handle the scepter
    {SAY_FANDRAL_EPILOGUE_4,        NPC_FANDRAL_STAGHELM,       3000},
    {POINT_ID_SCEPTER_2,            0,                          4000},  // make Anachronos stand
    {SAY_FANDRAL_EPILOGUE_5,        NPC_FANDRAL_STAGHELM,       12000},
    {EMOTE_FANDRAL_SHATTER,         NPC_FANDRAL_STAGHELM,       3000},
    {SAY_ANACHRONOS_EPILOGUE_6,     NPC_ANACHRONOS_THE_ANCIENT, 0},
    {SAY_FANDRAL_EPILOGUE_7,        NPC_FANDRAL_STAGHELM,       8000},
    {POINT_ID_EPILOGUE,             0,                          4000}, // move Fandral to Anachronos
    {EMOTE_ANACHRONOS_DISPPOINTED,  NPC_ANACHRONOS_THE_ANCIENT, 1000},
    {POINT_ID_SCEPTER_1,            0,                          0},    // make Anachronos pick the pieces
    {0, 0, 0},
};

static EventLocations aEternalBoardNPCs[MAX_DRAGONS] =
{
    {-8029.301f, 1534.612f, 2.609f, 3.121f, NPC_FANDRAL_STAGHELM},
    {-8034.227f, 1536.580f, 2.609f, 6.161f, NPC_ARYGOS},
    {-8031.935f, 1532.658f, 2.609f, 1.012f, NPC_CAELESTRASZ},
    {-8034.106f, 1534.224f, 2.609f, 0.290f, NPC_MERITHRA_OF_THE_DREAM},
};

static StaticLocation aEternalBoardMovement[] =
{
    {-8159.951f, 1525.241f, 74.994f},           // 0 Flight position for dragons
    {-8106.238f, 1525.948f, 2.639f},            // 1 Anachronos gate location
    {-8103.861f, 1525.923f, 2.677f},            // 2 Fandral gate location
    {-8107.387f, 1523.641f, 2.609f},            // 3 Shattered scepter
    {-8100.921f, 1527.740f, 2.871f},            // 4 Fandral epilogue location
    {-8115.270f, 1515.926f, 3.305f},            // 5 Anachronos gather broken scepter 1
    {-8116.879f, 1530.615f, 3.762f},            // 6 Anachronos gather broken scepter 2
    {-7997.790f, 1548.664f, 3.738f},            // 7 Fandral exit location
    {-8061.933f, 1496.196f, 2.556f},            // 8 Anachronos launch location
    {-8008.705f, 1446.063f, 44.104f},           // 9 Anachronos flight location
    {-8085.748f, 1521.484f, 2.624f}             // 10 Anchor point for the army summoning
};

struct MANGOS_DLL_DECL npc_anachronos_the_ancientAI : public ScriptedAI, private DialogueHelper
{
    npc_anachronos_the_ancientAI(Creature* pCreature) : ScriptedAI(pCreature),
        DialogueHelper(aEventDialogue)
    {
        Reset();
    }

    uint32 m_uiEventTimer;

    uint8 m_uiEventStage;

    ObjectGuid m_fandralGuid;
    ObjectGuid m_merithraGuid;
    ObjectGuid m_CaelestraszGuid;
    ObjectGuid m_arygosGuid;
    ObjectGuid m_playerGuid;
    ObjectGuid m_triggerGuid;

    GuidList m_lQirajiWarriorsList;

    void Reset()
    {
        // We summon the rest of the dragons on timer
        m_uiEventTimer  = 100;
        m_uiEventStage  = 0;
    }

    void JustDidDialogueStep(int32 iEntry)
    {
        switch(iEntry)
        {
            case NPC_ANACHRONOS_THE_ANCIENT:
                // Call the other dragons
                DoSummonDragons();
                break;
            case EMOTE_ONESHOT_SHOUT:
                // Summon warriors
                DoSummonWarriors();
                m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
                break;
            case SAY_FANDRAL_INTRO_2:
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->SetFacingToObject(m_creature);
                break;
            case EMOTE_MERITHRA_GLANCE:
                if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_merithraGuid))
                {
                    if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                        pFandral->SetFacingToObject(pMerithra);
                }
                break;
            case NPC_ANACHRONOS_QUEST_TRIGGER:
                // Move Merithra to attack
                if (Creature* pTrigger = GetClosestCreatureWithEntry(m_creature, NPC_ANACHRONOS_QUEST_TRIGGER, 35.0f))
                {
                    m_triggerGuid = pTrigger->GetObjectGuid();
                    if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_merithraGuid))
                    {
                        pMerithra->SetWalk(false);
                        pMerithra->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                    }
                }
                break;
            case SPELL_GREEN_DRAGON_TRANSFORM:
                if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_merithraGuid))
                    pMerithra->CastSpell(pMerithra, SPELL_GREEN_DRAGON_TRANSFORM, false);
                break;
            case SAY_ARYGOS_ATTACK_2:
                if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_merithraGuid))
                    pMerithra->CastSpell(pMerithra, SPELL_MERITHRA_WAKE, false);
                break;
            case NPC_ARYGOS:
                // Move Arygos to attack
                if (Creature* pTrigger = m_creature->GetMap()->GetCreature(m_triggerGuid))
                {
                    if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_arygosGuid))
                    {
                        pArygos->SetWalk(false);
                        pArygos->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                    }
                }
                break;
            case POINT_ID_EXIT:
                // Move Merithra to the exit point
                if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_merithraGuid))
                {
                    pMerithra->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                    pMerithra->SetLevitate(true);
                    pMerithra->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].x, aEternalBoardMovement[0].y, aEternalBoardMovement[0].z);
                    pMerithra->ForcedDespawn(9000);
                }
                break;
            case SPELL_BLUE_DRAGON_TRANSFORM:
                if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_arygosGuid))
                    pArygos->CastSpell(pArygos, SPELL_BLUE_DRAGON_TRANSFORM, false);
                break;
            case SPELL_ARYGOS_VENGEANCE:
                if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_arygosGuid))
                    pArygos->CastSpell(pArygos, SPELL_ARYGOS_VENGEANCE, false);
                break;
            case POINT_ID_DRAGON_ATTACK:
                // Move Arygos to the exit point
                if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_arygosGuid))
                {
                    pArygos->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                    pArygos->SetLevitate(true);
                    pArygos->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].x, aEternalBoardMovement[0].y, aEternalBoardMovement[0].z);
                    pArygos->ForcedDespawn(9000);
                }
                break;
            case NPC_CAELESTRASZ:
                // Move Caelestrasz to attack
                if (Creature* pTrigger = m_creature->GetMap()->GetCreature(m_triggerGuid))
                {
                    if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_CaelestraszGuid))
                    {
                        pCaelestrasz->SetWalk(false);
                        pCaelestrasz->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                    }
                }
                break;
            case SPELL_RED_DRAGON_TRANSFORM:
                if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_CaelestraszGuid))
                    pCaelestrasz->CastSpell(pCaelestrasz, SPELL_RED_DRAGON_TRANSFORM, false);
                break;
            case SPELL_CAELESTRASZ_MOLTEN_RAIN:
                if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_CaelestraszGuid))
                    pCaelestrasz->CastSpell(pCaelestrasz, SPELL_CAELESTRASZ_MOLTEN_RAIN, false);
                break;
            case SAY_ANACHRONOS_SEAL_1:
                // Send Caelestrasz on flight
                if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_CaelestraszGuid))
                {
                    pCaelestrasz->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                    pCaelestrasz->SetLevitate(true);
                    pCaelestrasz->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].x, aEternalBoardMovement[0].y, aEternalBoardMovement[0].z);
                    pCaelestrasz->ForcedDespawn(9000);
                }
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    m_creature->SetFacingToObject(pFandral);
                break;
            case SAY_FANDRAL_SEAL_2:
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->SetFacingToObject(m_creature);
                break;
            case POINT_ID_GATE:
                // Send Anachronos to the gate
                m_creature->SetWalk(false);
                m_creature->GetMotionMaster()->MovePoint(POINT_ID_GATE, aEternalBoardMovement[1].x, aEternalBoardMovement[1].y, aEternalBoardMovement[1].z);
                break;
            case NPC_FANDRAL_STAGHELM:
                // Send Fandral to the gate
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                {
                    pFandral->SetWalk(false);
                    pFandral->GetMotionMaster()->MovePoint(POINT_ID_GATE, aEternalBoardMovement[2].x, aEternalBoardMovement[2].y, aEternalBoardMovement[2].z);
                }
                break;
            case SPELL_PRISMATIC_BARRIER:
                DoCastSpellIfCan(m_creature, SPELL_PRISMATIC_BARRIER);
                break;
            case SPELL_GLYPH_OF_WARDING:
                DoCastSpellIfCan(m_creature, SPELL_GLYPH_OF_WARDING);
                break;
            case SAY_FANDRAL_SEAL_6:
                // Here Anachronos should continue to cast something
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->CastSpell(pFandral, SPELL_CALL_ANCIENTS, false);
                break;
            case EMOTE_FANDRAL_EXHAUSTED:
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                {
                    pFandral->SetStandState(UNIT_STAND_STATE_KNEEL);
                    m_creature->SetFacingToObject(pFandral);
                }
                break;
            case DATA_HANDLE_SCEPTER:
                // Give the scepter to Fandral (it should equip it somehow)
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    DoScriptText(EMOTE_ANACHRONOS_SCEPTER, m_creature, pFandral);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case SAY_FANDRAL_EPILOGUE_4:
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->SetStandState(UNIT_STAND_STATE_STAND);
                break;
            case POINT_ID_SCEPTER_2:
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                break;
            case EMOTE_FANDRAL_SHATTER:
                // Shatter the scepter
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->CastSpell(pFandral, SPELL_SHATTER_HAMMER, false);
                break;
            case SAY_ANACHRONOS_EPILOGUE_6:
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                {
                    pFandral->SetWalk(true);
                    pFandral->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER_1, aEternalBoardMovement[3].x, aEternalBoardMovement[3].y, aEternalBoardMovement[3].z);
                }
                break;
            case POINT_ID_EPILOGUE:
                // Make Fandral leave
                if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_fandralGuid))
                    pFandral->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[7].x, aEternalBoardMovement[7].y, aEternalBoardMovement[7].z);
                break;
            case POINT_ID_SCEPTER_1:
                // Anachronos collects the pieces
                m_creature->SetWalk(true);
                m_creature->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER_1, aEternalBoardMovement[5].x, aEternalBoardMovement[5].y, aEternalBoardMovement[5].z);
                break;
        }
    }

    Creature* GetSpeakerByEntry(uint32 uiEntry)
    {
        switch (uiEntry)
        {
            case NPC_ANACHRONOS_THE_ANCIENT: return m_creature;
            case NPC_ARYGOS:                 return m_creature->GetMap()->GetCreature(m_arygosGuid);
            case NPC_CAELESTRASZ:            return m_creature->GetMap()->GetCreature(m_CaelestraszGuid);
            case NPC_MERITHRA_OF_THE_DREAM:  return m_creature->GetMap()->GetCreature(m_merithraGuid);
            case NPC_FANDRAL_STAGHELM:       return m_creature->GetMap()->GetCreature(m_fandralGuid);

            default:
                return NULL;
        }
    }

    void DoSummonDragons()
    {
        for (uint8 i = 0; i < MAX_DRAGONS; ++i)
            m_creature->SummonCreature(aEternalBoardNPCs[i].m_uiEntry, aEternalBoardNPCs[i].m_fX, aEternalBoardNPCs[i].m_fY, aEternalBoardNPCs[i].m_fZ, aEternalBoardNPCs[i].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0);

        // Also summon the 3 anubisath conquerors
        float fX, fY, fZ;
        for (uint8 i = 0; i < MAX_CONQUERORS; ++i)
        {
            m_creature->GetRandomPoint(aEternalBoardMovement[10].x, aEternalBoardMovement[10].y, aEternalBoardMovement[10].z, 20.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_ANUBISATH_CONQUEROR, fX, fY, fZ, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
        }
    }

    void DoSummonWarriors()
    {
        float fX, fY, fZ;
        // Summon kaldorei warriors
        for(uint8 i = 0; i < MAX_KALDOREI; ++i)
        {
            m_creature->GetRandomPoint(aEternalBoardMovement[10].x, aEternalBoardMovement[10].y, aEternalBoardMovement[10].z, 10.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_KALDOREI_INFANTRY, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
        }

        // Summon Qiraji warriors
        for(uint8 i = 0; i < MAX_QIRAJI; ++i)
        {
            m_creature->GetRandomPoint(aEternalBoardMovement[10].x, aEternalBoardMovement[10].y, aEternalBoardMovement[10].z, 15.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_WASP, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);

            m_creature->GetRandomPoint(aEternalBoardMovement[10].x, aEternalBoardMovement[10].y, aEternalBoardMovement[10].z, 15.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_DRONE, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);

            m_creature->GetRandomPoint(aEternalBoardMovement[10].x, aEternalBoardMovement[10].y, aEternalBoardMovement[10].z, 15.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_TANK, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
        }
    }

    void DoUnsummonArmy()
    {
        for (GuidList::const_iterator itr = m_lQirajiWarriorsList.begin(); itr != m_lQirajiWarriorsList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
                pTemp->ForcedDespawn();
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        // Also remove npc flags where needed
        switch(pSummoned->GetEntry())
        {
            case NPC_FANDRAL_STAGHELM:
                m_fandralGuid = pSummoned->GetObjectGuid();
                break;
            case NPC_MERITHRA_OF_THE_DREAM:
                m_merithraGuid = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_CAELESTRASZ:
                m_CaelestraszGuid = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_ARYGOS:
                m_arygosGuid = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_ANUBISATH_CONQUEROR:
            case NPC_QIRAJI_WASP:
            case NPC_QIRAJI_DRONE:
            case NPC_QIRAJI_TANK:
            case NPC_KALDOREI_INFANTRY:
                m_lQirajiWarriorsList.push_back(pSummoned->GetObjectGuid());
                break;
        }
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        switch(uiPointId)
        {
            case POINT_ID_GATE:
                // Cast time stop when he reaches the gate
                DoCastSpellIfCan(m_creature, SPELL_TIME_STOP);
                StartNextDialogueText(SPELL_TIME_STOP);
                break;
            case POINT_ID_SCEPTER_1:
                // Pickup the pieces
                DoScriptText(EMOTE_ANACHRONOS_PICKUP, m_creature);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                m_uiEventTimer = 2000;
                break;
            case POINT_ID_SCEPTER_2:
                // Pickup the pieces
                DoScriptText(SAY_ANACHRONOS_EPILOGUE_8, m_creature);
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                m_uiEventTimer = 4000;
                break;
            case POINT_ID_EXIT:
                // Spell was removed, manually change the display
                //DoCastSpellIfCan(m_creature, SPELL_BRONZE_DRAGON_TRANSFORM);
                m_creature->SetDisplayId(DISPLAY_ID_BRONZE_DRAGON);
                m_uiEventTimer = 4000;
                break;
        }
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (pSummoned->GetEntry() == NPC_FANDRAL_STAGHELM)
        {
            switch(uiPointId)
            {
                case POINT_ID_EPILOGUE:
                    // Face Anachronos and restart the dialogue
                    pSummoned->SetFacingToObject(m_creature);
                    StartNextDialogueText(SAY_FANDRAL_EPILOGUE_7);
                    DoUnsummonArmy();
                    break;
                case POINT_ID_SCEPTER_1:
                    pSummoned->GetMotionMaster()->MovePoint(POINT_ID_EPILOGUE, aEternalBoardMovement[4].x, aEternalBoardMovement[4].y, aEternalBoardMovement[4].z);
                    break;
                case POINT_ID_EXIT:
                    pSummoned->ForcedDespawn();
                    break;
            }
        }
        else if (uiPointId == POINT_ID_DRAGON_ATTACK)
        {
            switch(pSummoned->GetEntry())
            {
                case NPC_MERITHRA_OF_THE_DREAM:
                    StartNextDialogueText(DATA_MERITHRA_ATTACK);
                    break;
                case NPC_CAELESTRASZ:
                    StartNextDialogueText(DATA_CAELASTRASZ_ATTACK);
                    break;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        DialogueUpdate(uiDiff);

        if (m_uiEventTimer)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                switch(m_uiEventStage)
                {
                    case 0:
                        // Start the dialogue
                        StartNextDialogueText(NPC_ANACHRONOS_THE_ANCIENT);
                        m_uiEventTimer = 0;
                        break;
                    case 1:
                        // Do the epilogue movement
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER_2, aEternalBoardMovement[6].x, aEternalBoardMovement[6].y, aEternalBoardMovement[6].z);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 0;
                        break;
                    case 2:
                        // Complete quest and despawn gate
                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
                            pPlayer->GroupEventHappens(QUEST_A_PAWN_ON_THE_ETERNAL_BOARD, m_creature);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 4000;
                        break;
                    case 3:
                        // Move to exit
                        m_creature->SetWalk(false);
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[8].x, aEternalBoardMovement[8].y, aEternalBoardMovement[8].z);
                        m_uiEventTimer = 0;
                        break;
                    case 4:
                        // Take off and fly
                        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_UNK_2);
                        m_creature->SetLevitate(true);
                        m_creature->GetMotionMaster()->MovePoint(0, aEternalBoardMovement[9].x, aEternalBoardMovement[9].y, aEternalBoardMovement[9].z);
                        m_creature->ForcedDespawn(10000);
                        m_uiEventTimer = 0;
                        break;
                }
                ++m_uiEventStage;
            }
            else
                m_uiEventTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_anachronos_the_ancient(Creature* pCreature)
{
    return new npc_anachronos_the_ancientAI(pCreature);
}

bool QuestAcceptGO_crystalline_tear(Player* pPlayer, GameObject* pGo, const Quest* pQuest)
{
    // Summon the controller dragon at GO position (orientation is wrong - hardcoded)
    if (pQuest->GetQuestId() == QUEST_A_PAWN_ON_THE_ETERNAL_BOARD)
    {
        // Check if event is already in progress first
        if (Creature* pAnachronos = GetClosestCreatureWithEntry(pGo, NPC_ANACHRONOS_THE_ANCIENT, 90.0f))
            return true;

        if (Creature* pAnachronos = pPlayer->SummonCreature(NPC_ANACHRONOS_THE_ANCIENT, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), 3.75f, TEMPSUMMON_CORPSE_DESPAWN, 0))
        {
            // Send the player's guid in order to handle the quest complete
            if (npc_anachronos_the_ancientAI* pAnachronosAI = dynamic_cast<npc_anachronos_the_ancientAI*>(pAnachronos->AI()))
                pAnachronosAI->m_playerGuid = pPlayer->GetObjectGuid();
        }
    }

    return true;
}

void AddSC_silithus()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "npc_highlord_demitrian";
    newscript->pGossipHello =  &GossipHello_npc_highlord_demitrian;
    newscript->pGossipSelect = &GossipSelect_npc_highlord_demitrian;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npcs_rutgar_and_frankal";
    newscript->pGossipHello =  &GossipHello_npcs_rutgar_and_frankal;
    newscript->pGossipSelect = &GossipSelect_npcs_rutgar_and_frankal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_lesser_wind_stone";
    newscript->pGossipHelloGO  = &GOGossipHello_go_lesser_wind_stone;
    newscript->pGossipSelectGO = &GOGossipSelect_go_lesser_wind_stone;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_wind_stone";
    newscript->pGossipHelloGO  = &GOGossipHello_go_wind_stone;
    newscript->pGossipSelectGO = &GOGossipSelect_go_wind_stone;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_great_wind_stone";
    newscript->pGossipHelloGO  = &GOGossipHello_go_great_wind_stone;
    newscript->pGossipSelectGO = &GOGossipSelect_go_great_wind_stone;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_anachronos_the_ancient";
    newscript->GetAI = &GetAI_npc_anachronos_the_ancient;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_crystalline_tear";
    newscript->pQuestAcceptGO = &QuestAcceptGO_crystalline_tear;
    newscript->RegisterSelf();
}
