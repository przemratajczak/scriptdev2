#ifndef DEF_EYE_OF_ETERNITY_H
#define DEF_EYE_OF_ETERNITY_H

enum
{
    MAX_ENCOUNTER               = 1,

    TYPE_MALYGOS                = 1,

    NPC_MALYGOS                 = 28859,

    GO_PLATFORM                 = 193070,
    GO_EXIT_PORTAL              = 193908,
    GO_FOCUSING_IRIS            = 193958,
    GO_FOCUSING_IRIS_H          = 193960,
    GO_ALEXSTRASZAS_GIFT        = 193905,
    GO_ALEXSTRASZAS_GIFT_H      = 193967,
    GO_HEART_OF_MAGIC           = 194158,
    GO_HEART_OF_MAGIC_H         = 194159,

    // achievement criterias
    ACHIEV_CRIT_DENYING_THE_SCION_10   = 7573,
    ACHIEV_CRIT_DENYING_THE_SCION_25   = 7574
};

class MANGOS_DLL_DECL Instance_eye_of_eternity : public ScriptedInstance
{
 protected:
    std::string strInstData;
    uint32 m_auiEncounter[MAX_ENCOUNTER];

    void Initialize();
    void OnCreatureCreate(Creature* pCreature);
    void OnObjectCreate(GameObject* pGo);

    const char* Save();
    void Load(const char* chrIn);

 public:
    Instance_eye_of_eternity(Map* pMap);

    std::list<ObjectGuid> m_lDenyingScionGUIDList;

    void SetData(uint32 uiType, uint32 uiData);
    uint32 GetData(uint32 uiType);
    bool IsEncounterInProgress() const;
    bool CheckAchievementCriteriaMeet(uint32 uiCriteriaId, Player const* pSource, Unit const* pTarget, uint32 uiMiscValue1 /* = 0*/);
};

#endif