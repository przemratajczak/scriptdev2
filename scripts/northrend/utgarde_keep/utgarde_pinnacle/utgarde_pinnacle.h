/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_UTG_PINNACLE_H
#define DEF_UTG_PINNACLE_H

enum
{
    MAX_ENCOUNTER                   = 4,

    TYPE_SVALA                      = 0,
    TYPE_GORTOK                     = 1,
    TYPE_SKADI                      = 2,
    TYPE_YMIRON                     = 3,

    GO_DOOR_SKADI                   = 192173,

    NPC_GORTOK                      = 26687,
    NPC_FURLBORG                    = 26684,
    NPC_WORGEN                      = 26683,
    NPC_JORMUNGAR                   = 26685,
    NPC_RHINO                       = 26686,
    NPC_STASIS_CONTROLLER           = 26086,
    GO_STASIS_GENERATOR             = 188593,

    NPC_RANULF                      = 27308,
    NPC_HALDOR                      = 27307,
    NPC_BJORN                       = 27303,
    NPC_TOR                         = 27309,
    NPC_YMIRON                      = 26861,
    NPC_SPIRIT_SUMMONER             = 27392,
    GO_DOOR_YMIRON                  = 192174,

    NPC_SKADI                       = 26693,
    NPC_GRAUF                       = 26893,
    NPC_YMIRJAR_HARPOONER           = 26692,
    NPC_YMIRJAR_WARRIOR             = 26690,
    NPC_YMIRJAR_WITCH_DOCTOR        = 26691,
    NPC_FLAME_TRIGGER               = 28351,
    ITEM_HARPOON                    = 37372,
    GO_HARPOON                      = 192539,
    GO_HARPOON_LAUNCHER_1           = 192175,
    GO_HARPOON_LAUNCHER_2           = 192176,
    GO_HARPOON_LAUNCHER_3           = 192177,

    ACHIEV_KINGS_BANE               = 7598
};

class MANGOS_DLL_DECL instance_pinnacle : public ScriptedInstance
{
    public:
        instance_pinnacle(Map* pMap);

        void Initialize();

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);
        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);
        bool m_bKingsBaneAchievFailed;

    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
};

#endif
