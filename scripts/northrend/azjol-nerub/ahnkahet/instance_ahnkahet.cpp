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
SDName: instance_ahnkahet
SD%Complete: 0
SDComment:
SDCategory: Ahn'kahet
EndScriptData */

#include "precompiled.h"
#include "ahnkahet.h"

instance_ahnkahet::instance_ahnkahet(Map* pMap) : ScriptedInstance(pMap),
m_uiDevicesActivated(0),m_bRespectEldersFailed(false),m_bVolunteerWorkFailed(false),
m_bQuickDemiseFailed(false)
{
    Initialize();
}

void instance_ahnkahet::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_ahnkahet::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_ELDER_NADOX:
        case NPC_JEDOGA_SHADOWSEEKER:
        case NPC_TALDARAM:
        case NPC_JEDOGA_CONTROLLER:
            m_mNpcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}

void instance_ahnkahet::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_DOOR_TALDARAM:
            if (m_auiEncounter[1] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ANCIENT_DEVICE_L:
            if (m_auiEncounter[1] == NOT_STARTED)
                pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
        case GO_ANCIENT_DEVICE_R:
            if (m_auiEncounter[1] == NOT_STARTED)
                pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
        case GO_VORTEX:
            if (m_auiEncounter[1] != NOT_STARTED)
                pGo->SetGoState(GO_STATE_READY);
            break;
    }
    m_mGoEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_ahnkahet::SetData(uint32 uiType, uint32 uiData)
{
    debug_log("SD2: Instance Ahn'Kahet: SetData received for type %u with data %u",uiType,uiData);

    switch(uiType)
    {
        case TYPE_NADOX:
            m_auiEncounter[0] = uiData;
            if(uiData == IN_PROGRESS)
                m_bRespectEldersFailed = false;
            break;
        case TYPE_TALDARAM:
            if (uiData == SPECIAL)
            {
                if (m_uiDevicesActivated < 2)
                    ++m_uiDevicesActivated;

                if (m_uiDevicesActivated == 2)
                {
                    m_auiEncounter[1] = uiData;
                    DoUseDoorOrButton(GO_VORTEX);
                }
            }
            if (uiData == DONE)
            {
                m_auiEncounter[1] = uiData;
                DoUseDoorOrButton(GO_DOOR_TALDARAM);
            }
            break;
        case TYPE_JEDOGA:
            m_auiEncounter[2] = uiData;
            if(uiData == IN_PROGRESS)
                m_bVolunteerWorkFailed = false;
            break;
        case TYPE_VOLAZJ:
            m_auiEncounter[3] = uiData;
            if(uiData == IN_PROGRESS)
            {
                m_bQuickDemiseFailed = false;
                DoStartTimedAchievement(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, ACHIEV_QUICK_DEMISE_TIMER);
            }
            break;
        case TYPE_AMANITAR:
            m_auiEncounter[4] = uiData;
            break;
        default:
            error_log("SD2: Instance Ahn'Kahet: ERROR SetData = %u for type %u does not exist/not implemented.",uiType,uiData);
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3]
            << " " << m_auiEncounter[4];

        strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_ahnkahet::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3] >> m_auiEncounter[4];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_ahnkahet::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_NADOX:
            return m_auiEncounter[0];
        case TYPE_TALDARAM:
            return m_auiEncounter[1];
        case TYPE_JEDOGA:
            return m_auiEncounter[2];
        case TYPE_VOLAZJ:
            return m_auiEncounter[3];
        case TYPE_AMANITAR:
            return m_auiEncounter[4];
    }
    return 0;
}

bool instance_ahnkahet::CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/)
{    
    switch (uiCriteriaId)
    {
        case ACHIEV_CRIT_RESPECT_ELDERS:
            return !m_bRespectEldersFailed;
        case ACHIEV_CRIT_VOLUNTEER_WORK:
            return !m_bVolunteerWorkFailed;
        case ACHIEV_CRIT_QUICK_DEMISE:           
            return !m_bQuickDemiseFailed;            
        default:
            return false;
    }
}
InstanceData* GetInstanceData_instance_ahnkahet(Map* pMap)
{
    return new instance_ahnkahet(pMap);
}

void AddSC_instance_ahnkahet()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "instance_ahnkahet";
    newscript->GetInstanceData = &GetInstanceData_instance_ahnkahet;
    newscript->RegisterSelf();
}
