/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef DEF_HALLS_OF_STONE_H
#define DEF_HALLS_OF_STONE_H

enum
{
    MAX_ENCOUNTER           = 4,

    DATA_KRYSTALLUS         = 1,
    DATA_GRIEF              = 2,
    DATA_BRANN              = 3,
    DATA_SJONNIR            = 4,

    DATA_KADDRAK            = 5,
    DATA_ABEDNEUM           = 6,
    DATA_MARNAK             = 7,

    DATA_GO_TRIBUNAL_CONSOLE = 8,
    DATA_GO_SKY_FLOOR       = 9,
    DATA_GO_KADDRAK         = 10,
    DATA_GO_ABEDNEUM        = 11,
    DATA_GO_MARNAK          = 12,
    
    TYPE_KRYSTALLUS         = 20,
    TYPE_GRIEF              = 21,
    TYPE_BRANN              = 22,
    TYPE_SJONNIR            = 23,

    NPC_KRYSTALLUS          = 27977,
    NPC_GRIEF               = 27975,
    NPC_BRANN               = 28070,
    NPC_SJONNIR             = 27978,

    NPC_KADDRAK             = 30898, // left
    NPC_ABEDNEUM            = 30899, // middle
    NPC_MARNAK              = 30897, // right

    GO_GRIEF_DOOR           = 191292,
    GO_BRANN_DOOR           = 191293,
    GO_SJONNIR_DOOR         = 191296,

    GO_KADDRAK              = 191671, // left
    GO_ABEDNEUM             = 191669, // middle
    GO_MARNAK               = 191670, // right

    GO_TRIBUNAL_CONSOLE     = 193907,
    GO_TRIBUNAL_CHEST       = 190586,
    GO_TRIBUNAL_CHEST_H     = 193996,
    GO_TRIBUNAL_SKY_FLOOR   = 191527,

    GO_SJONNIR_CONSOLE      = 193906,

    ACHIEV_SPANKIN_NEW      = 2154,
    ACHIEV_GOOD_GRIEF       = 7143
};


class MANGOS_DLL_DECL instance_halls_of_stone : public ScriptedInstance
{
    public:
        instance_halls_of_stone(Map* pMap);

        void Initialize();

        void OnCreatureCreate(Creature* pCreature);
        void OnObjectCreate(GameObject* pGo);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);

        const char* Save() { return strSaveData.c_str(); }
        void Load(const char* chrIn);

        bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);
        bool m_bGoodGriefAchievFailed;
    private:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        bool Regular;
        std::string strSaveData;
        
};
#endif
