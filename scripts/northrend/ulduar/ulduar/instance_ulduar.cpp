/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Ulduar
SD%Complete:
SDComment:
SDCategory: Ulduar
EndScriptData */

#include "precompiled.h"
#include "ulduar.h"

instance_ulduar::instance_ulduar(Map* pMap) : ScriptedInstance(pMap),
    m_uiMimironPhase(0),
    m_uiYoggPhase(0),
    m_uiVisionPhase(0),
    m_bQuickShave(true),
    m_bShattered(false),
    m_bNerfEngi(true),
    m_bNerfGravity(true),
    m_bChooseMolg(false),
    m_bChooseBrun(false),
    m_bChooseSteel(false),
    m_bCantDoThat(true)
{
    Initialize();
}

void instance_ulduar::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    memset(&m_auiHardBoss, 0, sizeof(m_auiHardBoss));
    memset(&m_auiUlduarKeepers, 0, sizeof(m_auiUlduarKeepers));
    memset(&m_auiUlduarTeleporters, 0, sizeof(m_auiUlduarTeleporters));
    memset(&m_auiMiniBoss, NOT_STARTED, sizeof(m_auiMiniBoss));

    m_lIronDwarvesAchievList.clear();

    // Leviathan not implemented, so set it as DONE
    SetData(TYPE_LEVIATHAN, DONE);
    SetData(TYPE_LEVIATHAN_TP, DONE);
}

bool instance_ulduar::IsEncounterInProgress() const
{
    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            return true;
    }

    return false;
}

void instance_ulduar::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        // used to handle the keepers images
        // set to invisible by default and only made visible if the encounter is done
        case HODIR_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if(m_auiEncounter[8] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case FREYA_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if(m_auiEncounter[10] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case THORIM_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if(m_auiEncounter[9] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case MIMIRON_IMAGE:
            pCreature->SetVisibility(VISIBILITY_OFF);
            if(m_auiEncounter[7] == DONE)
                pCreature->SetVisibility(VISIBILITY_ON);
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case NPC_LEVIATHAN:
        case NPC_IGNIS:
        case NPC_RAZORSCALE:
        case NPC_COMMANDER:
        case NPC_XT002:
        case NPC_KOLOGARN:
        case NPC_KOLOGARN_BRIDGE_DUMMY:
        case NPC_AURIAYA:
        case NPC_FERAL_DEFENDER:
        case NPC_MIMIRON:
        case NPC_LEVIATHAN_MK:
        case NPC_HODIR:
        case NPC_THORIM:
        case NPC_RUNIC_COLOSSUS:
        case NPC_RUNE_GIANT:
        case NPC_JORMUNGAR_BEHEMOTH:
        case NPC_FREYA:
        case NPC_BRIGHTLEAF:
        case NPC_IRONBRACH:
        case NPC_STONEBARK:
        case NPC_VEZAX:
        case NPC_ANIMUS:
        case NPC_YOGGSARON:
        case NPC_SARA:
        case NPC_YOGG_BRAIN:
        case NPC_ALGALON:
        case NPC_STEELBREAKER:
        case NPC_MOLGEIM:
        case NPC_BRUNDIR:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case NPC_IRON_CONSTRUCT:
            m_lIronConstructsGUIDs.push_back(pCreature->GetObjectGuid());
            break;

        default: break;
    }
}

void instance_ulduar::OnObjectCreate(GameObject *pGo)
{
    switch(pGo->GetEntry())
    {
        // doors & other
        // The siege
        case GO_LEVIATHAN_GATE:
            if(m_auiEncounter[TYPE_LEVIATHAN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_SHIELD_WALL:
            break;
        case GO_XT002_GATE:
            pGo->SetGoState(GO_STATE_READY);
            if(m_auiEncounter[TYPE_LEVIATHAN] == DONE || m_auiEncounter[TYPE_XT002] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_BROKEN_HARPOON:
            pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
            // Archivum
        case GO_IRON_ENTRANCE_DOOR:
            break;
        case GO_ARCHIVUM_DOOR:
            pGo->SetGoState(GO_STATE_READY);
            if(m_auiEncounter[TYPE_ASSEMBLY])
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ARCHIVUM_CONSOLE:
        case GO_UNIVERSE_FLOOR_ARCHIVUM:
            // Celestial Planetarium
        case GO_CELESTIAL_ACCES:
        case GO_CELESTIAL_DOOR:
        case GO_UNIVERSE_FLOOR_CELESTIAL:
        case GO_AZEROTH_GLOBE:
            break;
            // Shattered Hallway
        case GO_KOLOGARN_BRIDGE:
            pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_SHATTERED_DOOR:
            break;

            // The keepers
            // Hodir
        case GO_HODIR_EXIT:
        case GO_HODIR_ICE_WALL:
            if(m_auiEncounter[TYPE_HODIR] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_HODIR_ENTER:
            pGo->SetGoState(GO_STATE_ACTIVE);
            break;
            // Mimiron
        case GO_MIMIRON_TRAM:
            if (m_auiEncounter[TYPE_AURIAYA] == DONE)
            {
                pGo->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                pGo->SetGoState(GO_STATE_READY);
            }
            break;
        case GO_MIMIRON_BUTTON:
            if (m_auiEncounter[TYPE_MIMIRON] == NOT_STARTED)
                pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
        case GO_MIMIRON_DOOR_1:
        case GO_MIMIRON_DOOR_2:
        case GO_MIMIRON_DOOR_3:
        case GO_MIMIRON_ELEVATOR:
            break;
        case GO_MIMIRON_TEL1:
        case GO_MIMIRON_TEL2:
        case GO_MIMIRON_TEL3:
        case GO_MIMIRON_TEL4:
        case GO_MIMIRON_TEL5:
        case GO_MIMIRON_TEL6:
        case GO_MIMIRON_TEL7:
        case GO_MIMIRON_TEL8:
        case GO_MIMIRON_TEL9:
            // Thorim
        case GO_DARK_IRON_PORTCULIS:
        case GO_RUNED_STONE_DOOR:
        case GO_THORIM_STONE_DOOR:
        case GO_LIGHTNING_FIELD:
            break;
        case GO_DOOR_LEVER:
            pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;

            // Prison
        case GO_ANCIENT_GATE:
            DoOpenMadnessDoorIfCan();
            break;
        case GO_VEZAX_GATE:
            pGo->SetGoState(GO_STATE_READY);
            if(m_auiEncounter[TYPE_VEZAX])
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_YOGG_GATE:
        case GO_BRAIN_DOOR1:
        case GO_BRAIN_DOOR2:
        case GO_BRAIN_DOOR3:
        // loot
        // Kologarn
        case GO_CACHE_OF_LIVING_STONE_N:
        case GO_CACHE_OF_LIVING_STONE_H:
        // Hodir
        case GO_CACHE_OF_WINTER_N:
        case GO_CACHE_OF_WINTER_H:
        // Hodir rare
        case GO_CACHE_OF_RARE_WINTER_N:
        case GO_CACHE_OF_RARE_WINTER_H:
        // Freya
        case GO_FREYA_GIFT_N:
        case GO_FREYA_GIFT_H:
        // Freya hard modes
        case GO_FREYA_GIFT_HARD_N:
        case GO_FREYA_GIFT_HARD_H:
        // Thorim
        case GO_CACHE_OF_STORMS_N:
        case GO_CACHE_OF_STORMS_H:
        // Thorim rare
        case GO_CACHE_OF_RARE_STORMS_N:
        case GO_CACHE_OF_RARE_STORMS_H:
        // Mimiron
        case GO_CACHE_OF_INOV_N:
        case GO_CACHE_OF_INOV_H:
        case GO_CACHE_OF_INOV_HARD_N:
        case GO_CACHE_OF_INOV_HARD_H:
        // Alagon
        case GO_GIFT_OF_OBSERVER_N:
        case GO_GIFT_OF_OBSERVER_H:
            break;

        default: return;
    }
    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

// functions to open or close some doors
void instance_ulduar::OpenDoor(uint32 m_uiDoorEntry)
{
    if (GameObject* pGo = GetSingleGameObjectFromStorage(m_uiDoorEntry))
        pGo->SetGoState(GO_STATE_ACTIVE);
}

void instance_ulduar::CloseDoor(uint32 m_uiDoorEntry)
{
    if (GameObject* pGo = GetSingleGameObjectFromStorage(m_uiDoorEntry))
        pGo->SetGoState(GO_STATE_READY);
}

// used in order to unlock the door to Vezax and make vezax attackable
void instance_ulduar::DoOpenMadnessDoorIfCan()
{
    if(m_auiEncounter[TYPE_MIMIRON] == DONE && m_auiEncounter[TYPE_HODIR] == DONE && m_auiEncounter[TYPE_THORIM] == DONE && m_auiEncounter[TYPE_FREYA] == DONE)
        OpenDoor(GO_ANCIENT_GATE);
}

void instance_ulduar::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_LEVIATHAN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(GO_SHIELD_WALL);
            if (uiData == DONE)
                OpenDoor(GO_LEVIATHAN_GATE);
            break;
        case TYPE_IGNIS:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_RAZORSCALE:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_XT002:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE || uiData == FAIL)
                OpenDoor(GO_XT002_GATE);
            else if (uiData == IN_PROGRESS)
                CloseDoor(GO_XT002_GATE);
            break;
        case TYPE_ASSEMBLY:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                OpenDoor(GO_IRON_ENTRANCE_DOOR);
                OpenDoor(GO_ARCHIVUM_DOOR);
                OpenDoor(GO_SHATTERED_DOOR);
            }
            else if (uiData == IN_PROGRESS)
                CloseDoor(GO_IRON_ENTRANCE_DOOR);
            else if (uiData == FAIL)
                OpenDoor(GO_IRON_ENTRANCE_DOOR);
            break;
        case TYPE_KOLOGARN:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_LIVING_STONE_N : GO_CACHE_OF_LIVING_STONE_H, 30*MINUTE);
                if (GameObject* pGo = GetSingleGameObjectFromStorage(GO_KOLOGARN_BRIDGE))
                {
                    pGo->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                    pGo->SetGoState(GO_STATE_READY);
                }
            }
            break;
        case TYPE_AURIAYA:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                if (GameObject* pGO = GetSingleGameObjectFromStorage(GO_MIMIRON_TRAM))
                {
                    pGO->SetUInt32Value(GAMEOBJECT_LEVEL, 0);
                    pGO->SetGoState(GO_STATE_READY);
                }
            }
            break;

            // Keepers
        case TYPE_MIMIRON:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(GO_MIMIRON_DOOR_1);
            DoUseDoorOrButton(GO_MIMIRON_DOOR_2);
            DoUseDoorOrButton(GO_MIMIRON_DOOR_3);
            if (uiData == DONE)
            {
                if(m_auiHardBoss[3] != DONE)
                    DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_INOV_N : GO_CACHE_OF_INOV_H, 30*MINUTE);
                // used to make the friendly keeper visible
                if(Creature* pImage = GetSingleCreatureFromStorage(MIMIRON_IMAGE))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            break;
        case TYPE_HODIR:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                OpenDoor(GO_HODIR_ENTER);
                DoUseDoorOrButton(GO_HODIR_ICE_WALL);
                DoUseDoorOrButton(GO_HODIR_EXIT);
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_WINTER_N : GO_CACHE_OF_WINTER_H, 30*MINUTE);

                // used to make the friendly keeper visible
                if(Creature* pImage = GetSingleCreatureFromStorage(HODIR_IMAGE))
                    pImage->SetVisibility(VISIBILITY_ON);

                DoOpenMadnessDoorIfCan();
            }
            else if (uiData == IN_PROGRESS)
                CloseDoor(GO_HODIR_ENTER);
            else if (uiData == FAIL)
                OpenDoor(GO_HODIR_ENTER);
            break;
        case TYPE_THORIM:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(GO_LIGHTNING_FIELD);
            if (uiData == IN_PROGRESS)
                DoUseDoorOrButton(GO_DARK_IRON_PORTCULIS);
            if (uiData == DONE)
            {
                if(m_auiHardBoss[5] != DONE)
                    DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_STORMS_N : GO_CACHE_OF_STORMS_H, 30*MINUTE);
                // used to make the friendly keeper visible
                if(Creature* pImage = GetSingleCreatureFromStorage(THORIM_IMAGE))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            break;
        case TYPE_FREYA:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                // do this in order to see how many elders were alive and spawn the correct chest
                // hard mode drop
                if(m_auiHardBoss[6] == 3)
                    DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_FREYA_GIFT_HARD_N : GO_FREYA_GIFT_HARD_H, 30*MINUTE);
                // normal mode
                else
                    DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_FREYA_GIFT_N : GO_FREYA_GIFT_H, 30*MINUTE);
                // used to make the friendly keeper visible
                if(Creature* pImage = GetSingleCreatureFromStorage(FREYA_IMAGE))
                    pImage->SetVisibility(VISIBILITY_ON);
                DoOpenMadnessDoorIfCan();
            }
            break;
        // 1 elder up +1 emblem drops
        case TYPE_FREYA_1:
            m_auiFreyaElders[1] = uiData;
            break;
        // 2 elders up +2 emblems drop
        case TYPE_FREYA_2:
            m_auiFreyaElders[2] = uiData;
            break;
        // 3 elders up is TYPE_FREYA_HARD

            // Prison
        case TYPE_VEZAX:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(GO_VEZAX_GATE);
            break;
        case TYPE_YOGGSARON:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(GO_YOGG_GATE);
            break;

            // Celestial Planetarium
        case TYPE_ALGALON:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(GO_CELESTIAL_DOOR);
            DoUseDoorOrButton(GO_UNIVERSE_FLOOR_CELESTIAL);
            if (uiData == DONE)
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_GIFT_OF_OBSERVER_N : GO_GIFT_OF_OBSERVER_H, 30*MINUTE);
            break;

            // Hard modes
        case TYPE_LEVIATHAN_HARD:
            m_auiHardBoss[0] = uiData;
            break;
        case TYPE_XT002_HARD:
            m_auiHardBoss[1] = uiData;
            break;
        case TYPE_HODIR_HARD:
            m_auiHardBoss[4] = uiData;
            if(uiData == DONE)
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_RARE_WINTER_N : GO_CACHE_OF_RARE_WINTER_H, 30*MINUTE);
            break;
        case TYPE_ASSEMBLY_HARD:
            m_auiHardBoss[2] = uiData;
            break;
        case TYPE_FREYA_HARD:
            m_auiHardBoss[6] = uiData;
            break;
        case TYPE_THORIM_HARD:
            m_auiHardBoss[5] = uiData;
            if(uiData == DONE)
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_RARE_STORMS_N : GO_CACHE_OF_RARE_STORMS_H, 30*MINUTE);
            break;
        case TYPE_MIMIRON_HARD:
            m_auiHardBoss[3] = uiData;
            if(uiData == DONE)
                DoRespawnGameObject(instance->IsRegularDifficulty() ? GO_CACHE_OF_INOV_HARD_N : GO_CACHE_OF_INOV_HARD_H, 30*MINUTE);
            break;
        case TYPE_VEZAX_HARD:
            m_auiHardBoss[7] = uiData;
            break;
        case TYPE_YOGGSARON_HARD:
            m_auiHardBoss[8] = uiData;
            break;

            // Ulduar keepers
        case TYPE_KEEPER_HODIR:
            m_auiUlduarKeepers[0] = uiData;
            break;
        case TYPE_KEEPER_THORIM:
            m_auiUlduarKeepers[1] = uiData;
            break;
        case TYPE_KEEPER_FREYA:
            m_auiUlduarKeepers[2] = uiData;
            break;
        case TYPE_KEEPER_MIMIRON:
            m_auiUlduarKeepers[3] = uiData;
            break;

            // teleporters
        case TYPE_LEVIATHAN_TP:
            m_auiUlduarTeleporters[0] = uiData;
            break;
        case TYPE_XT002_TP:
            m_auiUlduarTeleporters[1] = uiData;
            break;
        case TYPE_MIMIRON_TP:
            m_auiUlduarTeleporters[2] = uiData;
            break;

            // mini boss
        case TYPE_RUNIC_COLOSSUS:
            m_auiMiniBoss[0] = uiData;
            if (uiData == DONE)
                OpenDoor(GO_RUNED_STONE_DOOR);
            else
                CloseDoor(GO_RUNED_STONE_DOOR);
            break;
        case TYPE_RUNE_GIANT:
            m_auiMiniBoss[1] = uiData;
            if (uiData == DONE)
                OpenDoor(GO_THORIM_STONE_DOOR);
            else
                CloseDoor(GO_THORIM_STONE_DOOR);
            break;
        case TYPE_LEVIATHAN_MK:
            m_auiMiniBoss[2] = uiData;
            break;
        case TYPE_VX001:
            m_auiMiniBoss[3] = uiData;
            if (uiData == DONE)     // just for animation :)
            {
                DoUseDoorOrButton(GO_MIMIRON_TEL9);
                DoUseDoorOrButton(GO_MIMIRON_TEL8);
                DoUseDoorOrButton(GO_MIMIRON_TEL7);
                DoUseDoorOrButton(GO_MIMIRON_TEL6);
                DoUseDoorOrButton(GO_MIMIRON_TEL5);
                DoUseDoorOrButton(GO_MIMIRON_TEL4);
                DoUseDoorOrButton(GO_MIMIRON_TEL3);
                DoUseDoorOrButton(GO_MIMIRON_TEL2);
                DoUseDoorOrButton(GO_MIMIRON_TEL1);
            }
            break;
        case TYPE_AERIAL_UNIT:
            m_auiMiniBoss[4] = uiData;
            break;
        case TYPE_YOGG_BRAIN:
            m_auiMiniBoss[5] = uiData;
            break;

            //phases
        case TYPE_MIMIRON_PHASE:
            m_uiMimironPhase = uiData;
            break;
        case TYPE_YOGG_PHASE:
            m_uiYoggPhase = uiData;
            break;
        case TYPE_VISION_PHASE:
            m_uiVisionPhase = uiData;
            break;

        // achievements
        case TYPE_ACHI_QUICK_SHAVE:
            m_bQuickShave = (uiData == DONE);
            break;
        case TYPE_ACHI_SHATTERED:
            m_bShattered = (uiData == DONE);
            break;
        case TYPE_ACHI_NERF_ENGI:
            m_bNerfEngi = (uiData == DONE);
            break;
        case TYPE_ACHI_NERF_GRAVITY:
            m_bNerfGravity = (uiData == DONE);
            break;
        case TYPE_ACHI_CHOOSE_MOLG:
            m_bChooseMolg = (uiData == DONE);
            break;
        case TYPE_ACHI_CHOOSE_BRUN:
            m_bChooseBrun = (uiData == DONE);
            break;
        case TYPE_ACHI_CHOOSE_STEEL:
            m_bChooseSteel = (uiData == DONE);
            break;
        case TYPE_ACHI_CANT_DO_THAT:
            m_bCantDoThat = (uiData == DONE);
            break;
        case TYPE_ACHI_OPEN_ARMS:
            m_bOpenArms = (uiData == DONE);
            break;
        case TYPE_ACHI_IF_LOOKS:
            m_bIfLooks = (uiData == DONE);
            break;
        case TYPE_ACHI_RUBBLE_ROLL:
            m_bRubbleRoll = (uiData == DONE);
            break;
        case TYPE_ACHI_CAT_LADY:
            m_bCatLady = (uiData == DONE);
            break;
        case TYPE_ACHI_NINE_LIVES:
            m_bNineLives = (uiData == DONE);
            break;
        }

        if (uiData == DONE || uiData == FAIL)
        {
            OUT_SAVE_INST_DATA;

            // save all encounters, hard bosses and keepers
            std::ostringstream saveStream;
            saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5] << " "
                << m_auiEncounter[6] << " " << m_auiEncounter[7] << " " << m_auiEncounter[8] << " "
                << m_auiEncounter[9] << " " << m_auiEncounter[10] << " " << m_auiEncounter[11] << " "
                << m_auiEncounter[12] << " " << m_auiEncounter[13] << " " << m_auiHardBoss[0] << " "
                << m_auiHardBoss[1] << " " << m_auiHardBoss[2] << " " << m_auiHardBoss[2] << " "
                << m_auiHardBoss[4] << " " << m_auiHardBoss[5] << " " << m_auiHardBoss[6] << " "
                << m_auiHardBoss[7] << " " << m_auiHardBoss[8] << " " << m_auiUlduarKeepers[0] << " "
                << m_auiUlduarKeepers[1] << " " << m_auiUlduarKeepers[2] << " " << m_auiUlduarKeepers[3] << " "
                << m_auiUlduarTeleporters[0] << " " << m_auiUlduarTeleporters[1] << " " << m_auiUlduarTeleporters[2];

            m_strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
}

void instance_ulduar::IronDwarfPushBack(uint64 uiGuid)
{
    m_lIronDwarvesAchievList.push_back(uiGuid);
}

bool instance_ulduar::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{
    switch(uiCriteriaId)
    {
        case ACHIEV_CRIT_QUICK_SHAVE_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_QUICK_SHAVE);
        case ACHIEV_CRIT_QUICK_SHAVE_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_QUICK_SHAVE);
        case ACHIEV_CRIT_IRON_DWARF_10:
            if (!instance->IsRegularDifficulty())
                return false;

            for (GUIDList::const_iterator itr = m_lIronDwarvesAchievList.begin(); itr != m_lIronDwarvesAchievList.end(); ++itr)
            {
                if (pTarget && (*itr) == pTarget->GetObjectGuid())
                    return true;
            }
            break;
        case ACHIEV_CRIT_IRON_DWARF_25:
            if (instance->IsRegularDifficulty())
                return false;

            for (GUIDList::const_iterator itr = m_lIronDwarvesAchievList.begin(); itr != m_lIronDwarvesAchievList.end(); ++itr)
            {
                if (pTarget && (*itr) == pTarget->GetObjectGuid())
                    return true;
            }
            break;
        case ACHIEV_CRIT_SHATTERED_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_SHATTERED);
        case ACHIEV_CRIT_SHATTERED_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_SHATTERED);
        case ACHIEV_CRIT_NERF_ENGI_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NERF_ENGI);
        case ACHIEV_CRIT_NERF_ENGI_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NERF_ENGI);
        case ACHIEV_CRIT_NERF_GRAVITY_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NERF_GRAVITY);
        case ACHIEV_CRIT_NERF_GRAVITY_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NERF_GRAVITY);
        case ACHIEV_CRIT_CHOOSE_MOLG_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_MOLG);
        case ACHIEV_CRIT_CHOOSE_MOLG_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_MOLG);
        case ACHIEV_CRIT_CHOOSE_BRUN_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_BRUN);
        case ACHIEV_CRIT_CHOOSE_BRUN_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_BRUN);
        case ACHIEV_CRIT_CHOOSE_STEEL_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_STEEL);
        case ACHIEV_CRIT_CHOOSE_STEEL_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CHOOSE_STEEL);
        case ACHIEV_CRIT_UR_SIDE_MOLG_10:
        case ACHIEV_CRIT_UR_SIDE_BRUN_10:
        case ACHIEV_CRIT_UR_SIDE_STEEL_10:
            return instance->IsRegularDifficulty() && (GetData(TYPE_ASSEMBLY) == DONE);
        case ACHIEV_CRIT_UR_SIDE_MOLG_25:
        case ACHIEV_CRIT_UR_SIDE_BRUN_25:
        case ACHIEV_CRIT_UR_SIDE_STEEL_25:
            return !instance->IsRegularDifficulty() && (GetData(TYPE_ASSEMBLY) == DONE);
        case ACHIEV_CRIT_CANTDOTHAT_M_10:
        case ACHIEV_CRIT_CANTDOTHAT_B_10:
        case ACHIEV_CRIT_CANTDOTHAT_S_10:
            return (instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CANT_DO_THAT) && (GetData(TYPE_ASSEMBLY) == DONE));
        case ACHIEV_CRIT_CANTDOTHAT_M_25:
        case ACHIEV_CRIT_CANTDOTHAT_B_25:
        case ACHIEV_CRIT_CANTDOTHAT_S_25:
            return (!instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CANT_DO_THAT) && (GetData(TYPE_ASSEMBLY) == DONE));
        case ACHIEV_CRIT_OPEN_ARMS_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_OPEN_ARMS);
        case ACHIEV_CRIT_OPEN_ARMS_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_OPEN_ARMS);
        case ACHIEV_CRIT_IF_LOOKS_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_IF_LOOKS);
        case ACHIEV_CRIT_IF_LOOKS_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_IF_LOOKS);
        case ACHIEV_CRIT_RUBBLE_ROLL_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_RUBBLE_ROLL);
        case ACHIEV_CRIT_RUBBLE_ROLL_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_RUBBLE_ROLL);
        case ACHIEV_CRIT_CAT_LADY_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CAT_LADY);
        case ACHIEV_CRIT_CAT_LADY_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_CAT_LADY);
        case ACHIEV_CRIT_NINE_LIVES_10:
            return instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NINE_LIVES);
        case ACHIEV_CRIT_NINE_LIVES_25:
            return !instance->IsRegularDifficulty() && GetData(TYPE_ACHI_NINE_LIVES);
    }

    return false;
}

bool instance_ulduar::CheckConditionCriteriaMeet(Player const* source, uint32 map_id, uint32 instance_condition_id)
{
    if (map_id != instance->GetId())
        return false;

    if (GetData(instance_condition_id) == DONE)
        return true;

    return false;
}

uint32 instance_ulduar::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_LEVIATHAN:
        case TYPE_IGNIS:
        case TYPE_RAZORSCALE:
        case TYPE_XT002:
        case TYPE_ASSEMBLY:
        case TYPE_KOLOGARN:
        case TYPE_AURIAYA:
        case TYPE_MIMIRON:
        case TYPE_HODIR:
        case TYPE_THORIM:
        case TYPE_FREYA:
        case TYPE_VEZAX:
        case TYPE_YOGGSARON:
        case TYPE_ALGALON:
            return m_auiEncounter[uiType];

        case TYPE_FREYA_1:
            return m_auiFreyaElders[1];
        case TYPE_FREYA_2:
            return m_auiFreyaElders[2];

        // hard modes
        case TYPE_LEVIATHAN_HARD:
            return m_auiHardBoss[0];
        case TYPE_XT002_HARD:
            return m_auiHardBoss[1];
        case TYPE_ASSEMBLY_HARD:
            return m_auiHardBoss[2];
        case TYPE_MIMIRON_HARD:
            return m_auiHardBoss[3];
        case TYPE_HODIR_HARD:
            return m_auiHardBoss[4];
        case TYPE_THORIM_HARD:
            return m_auiHardBoss[5];
        case TYPE_FREYA_HARD:
            return m_auiHardBoss[6];
        case TYPE_VEZAX_HARD:
            return m_auiHardBoss[7];
        case TYPE_YOGGSARON_HARD:
            return m_auiHardBoss[8];

        // ulduar keepers
        case TYPE_KEEPER_HODIR:
            return m_auiUlduarKeepers[0];
        case TYPE_KEEPER_THORIM:
            return m_auiUlduarKeepers[1];
        case TYPE_KEEPER_FREYA:
            return m_auiUlduarKeepers[2];
        case TYPE_KEEPER_MIMIRON:
            return m_auiUlduarKeepers[3];

        // teleporters
        case TYPE_LEVIATHAN_TP:
            return m_auiUlduarTeleporters[0];
        case TYPE_XT002_TP:
            return m_auiUlduarTeleporters[1];
        case TYPE_MIMIRON_TP:
            return m_auiUlduarTeleporters[2];

        // mini boss
        case TYPE_RUNE_GIANT:
            return m_auiMiniBoss[1];
        case TYPE_RUNIC_COLOSSUS:
            return m_auiMiniBoss[0];
        case TYPE_LEVIATHAN_MK:
            return m_auiMiniBoss[2];
        case TYPE_VX001:
            return m_auiMiniBoss[3];
        case TYPE_AERIAL_UNIT:
            return m_auiMiniBoss[4];
        case TYPE_YOGG_BRAIN:
            return m_auiMiniBoss[5];

        case TYPE_MIMIRON_PHASE:
            return m_uiMimironPhase;
        case TYPE_YOGG_PHASE:
            return m_uiYoggPhase;
        case TYPE_VISION_PHASE:
            return m_uiVisionPhase;

        // achievements
        case TYPE_ACHI_QUICK_SHAVE:
            return m_bQuickShave;
        case TYPE_ACHI_SHATTERED:
            return m_bShattered;
        case TYPE_ACHI_NERF_ENGI:
            return m_bNerfEngi;
        case TYPE_ACHI_NERF_GRAVITY:
            return m_bNerfGravity;
        case TYPE_ACHI_CHOOSE_MOLG:
            return m_bChooseMolg;
        case TYPE_ACHI_CHOOSE_BRUN:
            return m_bChooseBrun;
        case TYPE_ACHI_CHOOSE_STEEL:
            return m_bChooseSteel;
        case TYPE_ACHI_CANT_DO_THAT:
            return m_bCantDoThat;
        case TYPE_ACHI_OPEN_ARMS:
            return m_bOpenArms;
        case TYPE_ACHI_IF_LOOKS:
            return m_bIfLooks;
        case TYPE_ACHI_RUBBLE_ROLL:
            return m_bRubbleRoll;
        case TYPE_ACHI_CAT_LADY:
            return m_bCatLady;
        case TYPE_ACHI_NINE_LIVES:
            return m_bNineLives;
    }
    return 0;
}

const char* instance_ulduar::Save()
{
    return m_strInstData.c_str();
}

void instance_ulduar::Load(const char* strIn)
{
    if (!strIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(strIn);

    std::istringstream loadStream(strIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
    >> m_auiEncounter[4] >> m_auiEncounter[5] >> m_auiEncounter[6] >> m_auiEncounter[7]
    >> m_auiEncounter[8] >> m_auiEncounter[9] >> m_auiEncounter[10] >> m_auiEncounter[11]
    >> m_auiEncounter[12] >> m_auiEncounter[13] >> m_auiHardBoss[0] >> m_auiHardBoss[1]
    >> m_auiHardBoss[2] >> m_auiHardBoss[3] >> m_auiHardBoss[4] >> m_auiHardBoss[5]
    >> m_auiHardBoss[6] >> m_auiHardBoss[7] >> m_auiHardBoss[8] >> m_auiUlduarKeepers[0]
    >> m_auiUlduarKeepers[1] >> m_auiUlduarKeepers[2] >> m_auiUlduarKeepers[3] >> m_auiUlduarTeleporters[0]
    >> m_auiUlduarTeleporters[1] >> m_auiUlduarTeleporters[2];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_ulduar(Map* pMap)
{
    return new instance_ulduar(pMap);
}

void AddSC_instance_ulduar()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "instance_ulduar";
    newscript->GetInstanceData = &GetInstanceData_instance_ulduar;
    newscript->RegisterSelf();
}
