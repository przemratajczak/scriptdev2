/*support for Q The Purification of Quel'Delar */

#include "precompiled.h"
#include "sunwell_plateau.h"

enum
{
    ITEM_TINED_QUELDELAR_1  = 49879,
    ITEM_TINED_QUELDELAR_2  = 49889,

    NPC_Q_HONOR_GUARD       = 37781,
    NPC_Q_BLOODELF_PILGRIM  = 38047,
    NPC_QUELDELAR_TARGET    = 37745,

    SPELL_SUNWELL_IGNITION  = 71183,
    SPELL_ICY_PRISON        = 70540,
    SPELL_QUELDELAR_WRATH   = 70493,
    SPELL_SUNWELL_LIGHTRAY  = 70474
};

int32 iLadrinStoryText[7] = {-1574970,-1574971,-1574972,-1574973,-1574974,-1574975,-1574976};

int32 iQuelDalarText[22] = {-1574977,-1574978,-1574979,
    -1574980,-1574981,-1574982,-1574983,-1574984,-1574985,-1574986,-1574987,-1574988,-1574989,
    -1574990,-1574991,-1574992,-1574993,-1574994,-1574995,-1574996,-1574997,-1574998};

float fPosQuelDalar [3][4] =
{
    {1683.4f, 613.1f, 28.4f, 0.5f},
    {1686.5f, 610.4f, 28.4f, 1.0f},
    {1691.0f, 616.6f, 27.9f, 0.8f}
};

uint32 m_uiQ_PurificationOfQuelDalar[6] = {24553,24564,24594,24595,24596,24598};

struct MANGOS_DLL_DECL npc_sunwell_bunnyAI : public ScriptedAI
{

    npc_sunwell_bunnyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    GuidList lPlayersGuids;
    GuidList lCloseGuardsGuids;
    ObjectGuid m_playerGuid;
    ObjectGuid m_guardGuid;
    ObjectGuid m_QuelDelarSpellTargetGuid;
    bool bBloodElfLine;
    uint32 uiEventPhase;
    uint8 uiLadrinStoryStep;

    uint32 m_uiLiadrinStoryTimer;
    uint32 m_uiCheckOutBladeTimer;
    uint32 m_uiEventTimer;

    void Reset()
    {
        m_playerGuid.Clear();
        m_guardGuid.Clear();
        m_QuelDelarSpellTargetGuid.Clear();
        lPlayersGuids.clear();

        uiEventPhase            = 0;
        uiLadrinStoryStep       = 0;

        m_uiCheckOutBladeTimer  = 1000;
        m_uiLiadrinStoryTimer   = 0;
        m_uiEventTimer          = 2000;
        DoCastSpellIfCan(m_creature, SPELL_SUNWELL_IGNITION);
    }

    /* maybe there exists triggered spell?
    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if ((pSpell->Id == 70477 || pSpell->Id ==  70548) && pCaster->GetTypeId() == TYPEID_PLAYER)
        {
            pCaster->getRace() == RACE_BLOODELF ? bBloodElfLine = true : false;
            m_playerGuid = pCaster->GetObjectGuid();
        }
    }*/

    void MoveInLineOfSight(Unit* pWho)
    {
        // welcome player on Quest
        if (m_pInstance && !lPlayersGuids.find(pWho->GetObjectGuid()) && pWho->GetTypeId() == TYPEID_PLAYER && m_creature->GetDistance(pWho) < 60.0f)
        {
            Player* pPlayer = ((Player*)pWho);
            // hacky part - there is no possibiluty to pass instance data by spell_effect 61 so we need workaround for )
            if (!pPlayer->GetItemByEntry(ITEM_TINED_QUELDELAR_1) && !pPlayer->GetItemByEntry(ITEM_TINED_QUELDELAR_2))
                return;

            for (uint8 i = 0; i < 6; ++i)
                if (pPlayer->GetQuestStatus(m_uiQ_PurificationOfQuelDalar[i]) == QUEST_STATUS_INCOMPLETE)
                {
                    if (Creature* pGaliros = m_pInstance->GetSingleCreatureFromStorage(NPC_Q_GALIROS))
                        DoScriptText(iQuelDalarText[0], pGaliros, pWho);

                    lPlayersGuids.push_back(pPlayer->GetObjectGuid());
                }
        }
    }

    void GoHomeCreatureURDrunk(Creature* pCreature)
    {
        pCreature->SetWalk(true);
        float x, y, z;
        pCreature->GetRespawnCoord(x, y, z);
        pCreature->GetMotionMaster()->MovePoint(0, x, y, z);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // no point of continuing
        if (!m_pInstance)
            return;

        if (!m_playerGuid)
        {
            if (m_uiCheckOutBladeTimer < uiDiff)
            {
                GameObject* pSword = m_pInstance->GetSingleGameObjectFromStorage(GO_Q_QUEL_DALAR);
                if (pSword && pSword->isSpawned())
                    for (GuidList::iterator itr = lPlayersGuids.begin(); itr != lPlayersGuids.end(); ++itr)
                    {
                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(*itr))
                            if (!pPlayer->GetItemByEntry(ITEM_TINED_QUELDELAR_1) && !pPlayer->GetItemByEntry(ITEM_TINED_QUELDELAR_2))
                            {
                                if (Creature* pQuelDelar = m_creature->SummonCreature(NPC_QUELDELAR_TARGET, pSword->GetPositionX(), pSword->GetPositionY(), pSword->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 360000))
                                {
                                    m_QuelDelarSpellTargetGuid = pQuelDelar->GetObjectGuid();
                                    DoCastSpellIfCan(m_creature, SPELL_SUNWELL_LIGHTRAY);
                                }
                                m_playerGuid = pPlayer->GetObjectGuid();
                                //could be done with propper item or spell (different quest/item/itemSpell for BE)
                                pPlayer->getRace() == RACE_BLOODELF ? bBloodElfLine = true : false;
                                return;
                            }
                    }
                m_uiCheckOutBladeTimer = 1000;
            }
            else
                m_uiCheckOutBladeTimer -= uiDiff;

            // idle Story Line by Lady Liadrin
            if (Creature* pLiadrin = m_pInstance->GetSingleCreatureFromStorage(NPC_Q_LIADRIN))
            {
                if (m_uiLiadrinStoryTimer < uiDiff)
                {
                    DoScriptText(iLadrinStoryText[uiLadrinStoryStep], pLiadrin);
                    ++uiLadrinStoryStep;
                    if (uiLadrinStoryStep >= 6)
                    {
                        if (Creature* pBloodElfPilgrim = GetClosestCreatureWithEntry(pLiadrin, NPC_Q_BLOODELF_PILGRIM, 10.0f, true))
                            DoScriptText(iLadrinStoryText[uiLadrinStoryStep], pBloodElfPilgrim, pLiadrin);
                        uiLadrinStoryStep = 0;
                    }

                    m_uiLiadrinStoryTimer = !uiLadrinStoryStep ? 30000 : 10000;
                }
                else
                    m_uiLiadrinStoryTimer -= uiDiff;
            }
            return;
        }

        Creature* pRommath = m_pInstance->GetSingleCreatureFromStorage(NPC_Q_ROMMATH);
        Creature* pTheron = m_pInstance->GetSingleCreatureFromStorage(NPC_Q_THERON);
        Creature* pAuric = m_pInstance->GetSingleCreatureFromStorage(NPC_Q_AURIC);
        GameObject* pSword = m_pInstance->GetSingleGameObjectFromStorage(GO_Q_QUEL_DALAR);
        Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid);

        // no point for continuing
        if (!pRommath || !pAuric || !pTheron || !pSword || !pPlayer)
        {
            error_log("SD2: npc_sunwell_bunny - couldn't find expected npcs or GOs to continue quest script.  Aborting!");
            m_creature->MonsterYell("SD2: npc_sunwell_bunny - couldn't find expected npcs or GOs to continue quest script. Aborting! Call GameMaster",0); // :)
            m_creature->ForcedDespawn();
            return;
        }

        if (m_uiEventTimer < uiDiff)
        {
            if (bBloodElfLine)
            {
                switch(uiEventPhase)
                {
                    case 0:
                        if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature, NPC_Q_HONOR_GUARD, 30.0f, true))
                            DoScriptText(iQuelDalarText[1], pGuard);
                        m_uiEventTimer = 1500;
                        break;

                    case 1:
                        // set near sunwell position
                        pTheron->GetMotionMaster()->MovePoint(0, fPosQuelDalar[1][0], fPosQuelDalar[1][1], fPosQuelDalar[1][2]);
                        DoScriptText(iQuelDalarText[2], pTheron);
                        pRommath->GetMotionMaster()->MovePoint(0, fPosQuelDalar[0][0], fPosQuelDalar[0][1], fPosQuelDalar[0][2]);
                        m_uiEventTimer = 11000;
                        break;

                    case 2:
                        pRommath->SetFacingToObject(pSword);
                        DoScriptText(iQuelDalarText[3], pRommath);
                        m_uiEventTimer = 4000;
                        break;

                    case 3:
                        pTheron->SetFacingToObject(pSword);
                        DoScriptText(iQuelDalarText[14], pTheron, pPlayer);
                        m_uiEventTimer = 4000;
                        break;

                    case 4:
                        pTheron->SetFacingToObject(pPlayer);
                        DoScriptText(iQuelDalarText[15], pTheron, pPlayer);
                        m_uiEventTimer = 4000;
                        break;

                    case 5:
                        pRommath->SetFacingToObject(pSword);
                        DoScriptText(iQuelDalarText[16], pRommath, pPlayer);
                        m_uiEventTimer = 4000;
                        break;

                    case 6:
                        DoScriptText(iQuelDalarText[17], pRommath);
                        m_uiEventTimer = 4000;
                        break;

                    case 7:
                        DoScriptText(iQuelDalarText[18], pRommath);
                        m_uiEventTimer = 4000;
                        break;

                    case 8:
                        DoScriptText(iQuelDalarText[19], pAuric);
                        m_uiEventTimer = 4000;
                        break;

                    case 9:
                        DoScriptText(iQuelDalarText[20], pAuric);
                        m_uiEventTimer = 4000;
                        break;

                    case 10:
                        DoScriptText(iQuelDalarText[21], pRommath, pPlayer);
                        pSword->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                        m_creature->RemoveAurasDueToSpell(SPELL_SUNWELL_LIGHTRAY);
                        if (Creature* pQuelDelar = m_creature->GetMap()->GetCreature(m_QuelDelarSpellTargetGuid))
                            pQuelDelar->ForcedDespawn();
                        m_uiEventTimer = 5000;
                        break;

                    case 11:
                        GoHomeCreatureURDrunk(pAuric);
                        GoHomeCreatureURDrunk(pRommath);
                        GoHomeCreatureURDrunk(pTheron);
                        m_uiEventTimer = 25000;
                        Reset();
                        break;
                }
            }
            else
            {
                switch(uiEventPhase)
                {
                    case 0:
                        if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature, NPC_Q_HONOR_GUARD, 30.0f, true))
                            DoScriptText(iQuelDalarText[1], pGuard);
                        m_uiEventTimer = 1500;
                        break;

                    case 1:
                        // set near sunwell position
                        pTheron->GetMotionMaster()->MovePoint(0, fPosQuelDalar[1][0], fPosQuelDalar[1][1], fPosQuelDalar[1][2]);
                        DoScriptText(iQuelDalarText[2], pTheron);
                        pRommath->GetMotionMaster()->MovePoint(0, fPosQuelDalar[0][0], fPosQuelDalar[0][1], fPosQuelDalar[0][2]);
                        m_uiEventTimer = 11000;
                        break;

                    case 2:
                        pRommath->SetFacingToObject(pSword);
                        DoScriptText(iQuelDalarText[3], pRommath);
                        m_uiEventTimer = 4000;
                        break;

                    case 3:
                        pTheron->SetFacingToObject(pSword);
                        // approach to sword
                        pTheron->GetMotionMaster()->MovePoint(0, fPosQuelDalar[2][0], fPosQuelDalar[2][1], fPosQuelDalar[2][2]);
                        DoScriptText(iQuelDalarText[4], pTheron, pPlayer);
                        m_uiEventTimer = 4000;
                        break;
                        /*** end of common path ***/

                    case 4:
                        // reach sword
                        pTheron->HandleEmote(EMOTE_ONESHOT_POINT);
                        m_uiEventTimer = 1000;
                        break;

                    case 5:
                        {
                            pTheron->KnockBackFrom(pTheron, 20.0f, 13.0f);
                            pTheron->CastSpell(pTheron, SPELL_QUELDELAR_WRATH, false);
                            std::list<Creature*> lGuards;
                            GetCreatureListWithEntryInGrid(lGuards, m_creature, NPC_Q_HONOR_GUARD, 30.0f);
                            for (std::list<Creature*>::iterator itr = lGuards.begin(); itr != lGuards.end(); ++itr)
                            {
                                lCloseGuardsGuids.push_back((*itr)->GetObjectGuid());
                                // i know i know .... :)
                                m_guardGuid = (*itr)->GetObjectGuid();
                                float x, y, z;
                                Unit* pTarget = NULL;
                                urand(0, 1) ? pTarget = ((Unit*)pAuric) : pTarget = ((Unit*)pPlayer);
                                pTarget->GetClosePoint(x, y, z, pTarget->GetObjectBoundingRadius(), 2.0f, urand(0, 5));
                                (*itr)->GetMotionMaster()->MovePoint(0, x, y, z);
                                (*itr)->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY1H);
                                (*itr)->SetWalk(false);
                            }
                            if (Creature* pGuard = m_creature->GetMap()->GetCreature(m_guardGuid))
                                DoScriptText(iQuelDalarText[5], pGuard);
                            m_uiEventTimer = 2000;
                        }
                        break;

                    case 6:
                        pRommath->SetFacingToObject(pPlayer);
                        DoCastSpellIfCan(pPlayer, SPELL_ICY_PRISON);
                        DoScriptText(iQuelDalarText[6], pRommath);
                        if (Creature* pGuard = m_creature->GetMap()->GetCreature(m_guardGuid))
                            DoScriptText(iQuelDalarText[7], pGuard, pPlayer);
                        m_uiEventTimer = 3000;
                        break;


                    case 7:
                        pTheron->GetMotionMaster()->MovePoint(0, fPosQuelDalar[1][0], fPosQuelDalar[1][1], fPosQuelDalar[1][2]);
                        for (GuidList::iterator itr = lCloseGuardsGuids.begin(); itr != lCloseGuardsGuids.end(); ++itr)
                            if (Creature* pGuard = m_creature->GetMap()->GetCreature(*itr))
                                pGuard->GetDistance(pAuric) > pGuard->GetDistance(pPlayer) ? pGuard->SetFacingToObject(pPlayer) : pGuard->SetFacingToObject(pAuric);

                        DoScriptText(iQuelDalarText[8], pAuric);
                        pAuric->SetFacingToObject(pRommath);
                        m_uiEventTimer = 5000;
                        break;

                    case 8:
                        DoScriptText(iQuelDalarText[9], pAuric);
                        m_uiEventTimer = 5000;
                        break;

                    case 9:
                        DoScriptText(iQuelDalarText[10], pRommath);
                        m_uiEventTimer = 5000;
                        break;

                    case 10:
                        DoScriptText(iQuelDalarText[11], pRommath);
                        pPlayer->RemoveAurasDueToSpell(SPELL_ICY_PRISON);
                        for (GuidList::iterator itr = lCloseGuardsGuids.begin(); itr != lCloseGuardsGuids.end(); ++itr)
                            if (Creature* pGuard = m_creature->GetMap()->GetCreature(*itr))
                            {
                                pGuard->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STAND);
                                pGuard->SetWalk(true);
                                float x, y, z;
                                pGuard->GetRespawnCoord(x, y, z);
                                pGuard->GetMotionMaster()->MovePoint(0, x, y, z);
                                
                            }

                        m_uiEventTimer = 5000;
                        break;

                    case 11:
                        DoScriptText(iQuelDalarText[12], pRommath, pPlayer);
                        pSword->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                        m_creature->RemoveAurasDueToSpell(SPELL_SUNWELL_LIGHTRAY);
                        if (Creature* pQuelDelar = m_creature->GetMap()->GetCreature(m_QuelDelarSpellTargetGuid))
                            pQuelDelar->ForcedDespawn();
                        m_uiEventTimer = 5000;
                        break;

                    case 12:
                        pAuric->SetFacingToObject(pPlayer);
                        DoScriptText(iQuelDalarText[13], pAuric, pPlayer);
                        m_uiEventTimer = 5000;
                        break;

                    case 13:
                        GoHomeCreatureURDrunk(pAuric);
                        GoHomeCreatureURDrunk(pRommath);
                        GoHomeCreatureURDrunk(pTheron);
                        Reset();
                        break;
                }
            }

            ++uiEventPhase;
        }
        else
            m_uiEventTimer -= uiDiff;

        if (!m_creature->getVictim() || !m_creature->SelectHostileTarget())
            return;
    }
};

CreatureAI* GetAI_npc_sunwell_bunny(Creature* pCreature)
{
    return new npc_sunwell_bunnyAI(pCreature);
}

void AddSC_sunwell_plateau()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_sunwell_bunny";
    pNewScript->GetAI = &GetAI_npc_sunwell_bunny;
    pNewScript->RegisterSelf();
}
