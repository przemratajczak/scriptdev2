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
SDName: instance_ruby_sanctum
SD%Complete: 50%
SDComment: by notagain, corrected by /dev/rsa
SDCategory: ruby_sanctum
EndScriptData */

//TODO:  Trash mobs, spawn and removal of fire ring/walls, spawn of halion

#include "precompiled.h"
#include "ruby_sanctum.h"

struct MANGOS_DLL_DECL instance_ruby_sanctum : public BSWScriptedInstance
{
    instance_ruby_sanctum(Map* pMap) : BSWScriptedInstance(pMap)
    {
        Initialize();
    }

    bool needSave;
    std::string strSaveData;

    //Creatures GUID
    uint32 m_auiEncounter[MAX_ENCOUNTERS+1];

    uint32 m_auiEventTimer;
    uint32 m_auiHalionEvent;

    uint32 m_auiOrbDirection;
    uint32 m_auiOrbNState;
    uint32 m_auiOrbSState;

    ObjectGuid m_uiHalion_pGUID;
    ObjectGuid m_uiHalion_tGUID;
    ObjectGuid m_uiHalionControlGUID;
    ObjectGuid m_uiRagefireGUID;
    ObjectGuid m_uiZarithrianGUID;
    ObjectGuid m_uiBaltharusGUID;
    ObjectGuid m_uiCloneGUID;
    ObjectGuid m_uiXerestraszaGUID;

    ObjectGuid m_uiOrbNGUID;
    ObjectGuid m_uiOrbSGUID;
    ObjectGuid m_uiOrbFocusGUID;
    ObjectGuid m_uiOrbCarrierGUID;

    //object GUID
    ObjectGuid m_uiHalionPortal1GUID;
    ObjectGuid m_uiHalionPortal2GUID;
    ObjectGuid m_uiHalionPortal3GUID;
    ObjectGuid m_uiHalionFireWallSGUID;
    ObjectGuid m_uiHalionFireWallMGUID;
    ObjectGuid m_uiHalionFireWallLGUID;
    ObjectGuid m_uiBaltharusTargetGUID;

    ObjectGuid m_uiFireFieldGUID;
    ObjectGuid m_uiFlameWallsGUID;
    ObjectGuid m_uiFlameRingGUID;

    void Initialize()
    {
        for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            m_auiEncounter[i] = NOT_STARTED;

        m_auiEventTimer = 1000;

        m_uiHalion_pGUID.Clear();
        m_uiHalion_tGUID.Clear();
        m_uiRagefireGUID.Clear();
        m_uiZarithrianGUID.Clear();
        m_uiBaltharusGUID.Clear();
        m_uiCloneGUID.Clear();
        m_uiHalionPortal1GUID.Clear();
        m_uiHalionPortal2GUID.Clear();
        m_uiHalionPortal3GUID.Clear();
        m_uiXerestraszaGUID.Clear();
        m_uiHalionFireWallSGUID.Clear();
        m_uiHalionFireWallMGUID.Clear();
        m_uiHalionFireWallLGUID.Clear();
        m_uiBaltharusTargetGUID.Clear();
        m_auiOrbDirection = 0;
        m_uiOrbNGUID.Clear();
        m_uiOrbSGUID.Clear();
        m_uiOrbFocusGUID.Clear();
        m_auiOrbNState = NOT_STARTED;
        m_auiOrbSState = NOT_STARTED;

    }

    bool IsEncounterInProgress() const
    {
        for(uint8 i = 1; i < MAX_ENCOUNTERS ; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;

        return false;
    }

    void UpdateWorldState(bool command, uint32 value)
    {
        Map::PlayerList const &players = instance->GetPlayers();

        if (command)
        {
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                if(Player* pPlayer = i->getSource())
                {
                    if(pPlayer->isAlive())
                    {
                        pPlayer->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
                        if (pPlayer->HasAura(74807))
                        {
                            pPlayer->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_T, 100 - value);
                        }
                        else
                        {
                            pPlayer->SendUpdateWorldState(UPDATE_STATE_UI_COUNT_R, value);
                        }
                        pPlayer->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,1);
                    }
                }
            }
        }
        else
        {
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                if(Player* pPlayer = i->getSource())
                {
                    if(pPlayer->isAlive())
                    {
                        pPlayer->SendUpdateWorldState(UPDATE_STATE_UI_SHOW,0);
                    }
                }
            }
        }
    }

    void OpenAllDoors()
    {
        if (m_auiEncounter[TYPE_RAGEFIRE] == DONE &&
            m_auiEncounter[TYPE_BALTHARUS] == DONE &&
            m_auiEncounter[TYPE_XERESTRASZA] == DONE)
            DoOpenDoor(GO_FLAME_WALLS);
        else
            DoCloseDoor(GO_FLAME_WALLS);
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case NPC_HALION_REAL:
            case NPC_HALION_TWILIGHT:
            case NPC_HALION_CONTROL:
            case NPC_RAGEFIRE:
            case NPC_ZARITHRIAN:
            case NPC_BALTHARUS:
            case NPC_BALTHARUS_TARGET:
            case NPC_CLONE:
            case NPC_XERESTRASZA:
            case NPC_SHADOW_PULSAR_N:
            case NPC_SHADOW_PULSAR_S:
            case NPC_ORB_ROTATION_FOCUS:
            case NPC_ORB_CARRIER:
                m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
                break;
        }
    }

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_HALION_PORTAL_1:
            case GO_HALION_PORTAL_2:
            case GO_HALION_PORTAL_3:
                pGo->SetPhaseMask(0, true);
                m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
                break;
            case GO_FLAME_WALLS:
            case GO_FLAME_RING:
            case GO_FIRE_FIELD:
                m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
                break;
        }
        OpenAllDoors();
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_EVENT:        m_auiEncounter[uiType] = uiData; uiData = NOT_STARTED; break;
            case TYPE_RAGEFIRE:     m_auiEncounter[uiType] = uiData;
                                        OpenAllDoors();
                                    break;
            case TYPE_BALTHARUS:    m_auiEncounter[uiType] = uiData;
                                        OpenAllDoors();
                                    break;
            case TYPE_XERESTRASZA:  m_auiEncounter[uiType] = uiData;
                                    if (uiData == IN_PROGRESS)
                                        DoOpenDoor(GO_FIRE_FIELD);
                                    else if (uiData == NOT_STARTED)
                                    {
                                        DoCloseDoor(GO_FIRE_FIELD);
                                        OpenAllDoors();
                                    }
                                    else if (uiData == DONE)
                                    {
                                        OpenAllDoors();
                                        if (m_auiEncounter[TYPE_ZARITHRIAN] == DONE)
                                        {
                                            m_auiEncounter[TYPE_EVENT] = 200;
                                            m_auiEventTimer = 30000;
                                        };
                                    }
                                    break;
            case TYPE_ZARITHRIAN:   m_auiEncounter[uiType] = uiData;
                                    if (uiData == DONE)
                                    {
                                        DoOpenDoor(GO_FLAME_WALLS);
                                        m_auiEncounter[TYPE_EVENT] = 200;
                                        m_auiEventTimer = 30000;
                                    }
                                    else if (uiData == IN_PROGRESS)
                                        DoCloseDoor(GO_FLAME_WALLS);
                                    else if (uiData == FAIL)
                                        DoOpenDoor(GO_FLAME_WALLS);
                                    break;
            case TYPE_HALION:       m_auiEncounter[uiType] = uiData;
                                    if (uiData == IN_PROGRESS)
                                        DoCloseDoor(GO_FLAME_RING);
                                    else
                                        DoOpenDoor(GO_FLAME_RING);
                                    break;
            case TYPE_HALION_EVENT: m_auiHalionEvent  = uiData; uiData = NOT_STARTED; break;
            case TYPE_EVENT_TIMER:  m_auiEventTimer = uiData; uiData = NOT_STARTED; break;

            case DATA_ORB_DIRECTION:        m_auiOrbDirection = uiData; uiData = NOT_STARTED; break;
            case DATA_ORB_N:                m_auiOrbNState = uiData; uiData = NOT_STARTED; break;
            case DATA_ORB_S:                m_auiOrbSState = uiData; uiData = NOT_STARTED; break;
            case TYPE_COUNTER:
                                    if (uiData == COUNTER_OFF)
                                    {
                                        UpdateWorldState(false,0);
                                    }
                                    else
                                    {
                                        UpdateWorldState(true,uiData);
                                    }
                                    uiData = NOT_STARTED;
                                    break;
        }

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;

            for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                saveStream << m_auiEncounter[i] << " ";

            strSaveData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    const char* Save()
    {
        return strSaveData.c_str();
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_RAGEFIRE:      return m_auiEncounter[uiType];
            case TYPE_BALTHARUS:     return m_auiEncounter[uiType];
            case TYPE_XERESTRASZA:   return m_auiEncounter[uiType];
            case TYPE_ZARITHRIAN:    return m_auiEncounter[uiType];
            case TYPE_HALION:        return m_auiEncounter[uiType];

            case TYPE_EVENT:         return m_auiEncounter[uiType];

            case TYPE_HALION_EVENT:  return m_auiHalionEvent;

            case TYPE_EVENT_TIMER:   return m_auiEventTimer;
            case TYPE_EVENT_NPC:     switch (m_auiEncounter[TYPE_EVENT])
                                     {
                                          case 10:
                                          case 20:
                                          case 30:
                                          case 40:
                                          case 50:
                                          case 60:
                                          case 70:
                                          case 80:
                                          case 90:
                                          case 100:
                                          case 110:
                                          case 200:
                                          case 210:
                                                 return NPC_XERESTRASZA;
                                                 break;
                                          default:
                                                 break;
                                     };
                                     return 0;

            case DATA_ORB_DIRECTION:        return m_auiOrbDirection;
            case DATA_ORB_N:                return m_auiOrbNState;
            case DATA_ORB_S:                return m_auiOrbSState;

        }
        return 0;
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);

        for(uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
        {
            loadStream >> m_auiEncounter[i];

            if (m_auiEncounter[i] == IN_PROGRESS
                || m_auiEncounter[i] == FAIL)
                m_auiEncounter[i] = NOT_STARTED;
        }

        m_auiEncounter[TYPE_XERESTRASZA] = NOT_STARTED;

        OUT_LOAD_INST_DATA_COMPLETE;
        OpenAllDoors();
    }
};

InstanceData* GetInstanceData_instance_ruby_sanctum(Map* pMap)
{
    return new instance_ruby_sanctum(pMap);
}

void AddSC_instance_ruby_sanctum()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_ruby_sanctum";
    pNewScript->GetInstanceData = &GetInstanceData_instance_ruby_sanctum;
    pNewScript->RegisterSelf();
}
