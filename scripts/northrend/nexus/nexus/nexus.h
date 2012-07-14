/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_NEXUS_H
#define DEF_NEXUS_H

enum
{
    MAX_ENCOUNTER                  = 5,

    TYPE_TELESTRA                  = 0,
    TYPE_ANOMALUS                  = 1,
    TYPE_ORMOROK                   = 2,
    TYPE_KERISTRASZA               = 3,
    TYPE_COMMANDER                 = 4,

    NPC_TELESTRA                   = 26731,
    NPC_ANOMALUS                   = 26763,
    NPC_ORMOROK                    = 26794,
    NPC_KERISTRASZA                = 26723,
    NPC_COMMANDER_H                = 26798, // horde
    NPC_COMMANDER_A                = 26796, // ally
    NPC_BREATH_CASTER              = 27048,
    NPC_CHAOTIC_RIFT               = 26918,

    GO_CONTAINMENT_SPHERE_TELESTRA = 188526,
    GO_CONTAINMENT_SPHERE_ANOMALUS = 188527,
    GO_CONTAINMENT_SPHERE_ORMOROK  = 188528,

    SPELL_FROZEN_PRISON             = 47854,                // may not be correct spell
    ACHIEV_CHAOS_THEORY             = 7316,
    ACHIEV_INTENSE_COLD             = 7315,
    ACHIEV_CRIT_SPLIT_PERSONALITY   = 7577
};

class MANGOS_DLL_DECL instance_nexus : public ScriptedInstance
{
    public:
        instance_nexus(Map* pMap);

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature);

        uint32 GetData(uint32 uiType);
        void SetData(uint32 uiType, uint32 uiData);

        const char* Save() { return m_strInstData.c_str(); }

        void Load(const char* chrIn);
        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);

        bool m_bKeristraszaAchievFailed;
        bool m_bTelestraAchievFailed;
    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
        bool m_bAnomalusAchievFailed;
};

#endif
