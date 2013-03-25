/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
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
SDName: Boss_Ingvar
SD%Complete: 70%
SDComment: TODO: correct timers, spell 42912 requires proper position fix in core
SDCategory: Utgarde Keep
EndScriptData */

#include "precompiled.h"
#include "utgarde_keep.h"

enum
{
    SAY_AGGRO_FIRST             = -1574005,
    SAY_AGGRO_SECOND            = -1574006,
    SAY_DEATH_FIRST             = -1574007,
    SAY_DEATH_SECOND            = -1574008,
    SAY_KILL_FIRST              = -1574009,
    SAY_KILL_SECOND             = -1574010,
    EMOTE_ROAR                  = -1574022,
    SAY_ANNHYLDE_REZ            = -1574023,

    NPC_THROW_TARGET            = 23996,                    // the target, casting spell and target of moving dummy
    NPC_THROW_DUMMY             = 23997,                    // the axe, moving to target
    NPC_GROUND_VISUAL           = 24012,                    // has SPELL_SCOURGE_RES_BUBBLE aura

    //phase 1
    SPELL_CLEAVE                = 42724,

    SPELL_SMASH                 = 42669,
    SPELL_SMASH_H               = 59706,

    SPELL_ENRAGE                = 42705,
    SPELL_ENRAGE_H              = 59707,

    SPELL_STAGGERING_ROAR       = 42708,
    SPELL_STAGGERING_ROAR_H     = 59708,

    //phase 2
    SPELL_DARK_SMASH_H          = 42723,

    SPELL_DREADFUL_ROAR         = 42729,
    SPELL_DREADFUL_ROAR_H       = 59734,

    SPELL_WOE_STRIKE            = 42730,
    SPELL_WOE_STRIKE_H          = 59735,

    SPELL_SHADOW_AXE            = 42748,
    SPELL_SHADOW_AXE_PROC       = 42750,                    // triggers 42751
    SPELL_SHADOW_AXE_PROC_H     = 59719,                    // triggers 59720

    //ressurection sequenze
    SPELL_SUMMON_BANSHEE        = 42912,                    // summons Annhylde and sets a glow aura
    SPELL_FEIGN_DEATH           = 42795,
    SPELL_TRANSFORM             = 42796,
    SPELL_SCOURGE_RES_SUMMON    = 42863,                    // summones a dummy target
    SPELL_SCOURGE_RES_HEAL      = 42704,                    // heals max HP
    SPELL_SCOURGE_RES_BUBBLE    = 42862,                    // black bubble
    SPELL_SCOURGE_RES_CHANNEL   = 42857,                    // the whirl from annhylde
    SPELL_SELFROOT              = 42716,

    PH_B4_RESSURECTION          = 0,
    PH_RESSURECTION             = 1,
    PH_RESSURECTED              = 2
};

/*######
## boss_ingvar
######*/

struct MANGOS_DLL_DECL boss_ingvarAI : public ScriptedAI
{
    boss_ingvarAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_utgarde_keep*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();
    }

    instance_utgarde_keep* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiPhase;
    uint32 m_uiSubevent;

    uint32 m_uiCleaveTimer;
    uint32 m_uiSmashTimer;
    uint32 m_uiStaggeringRoarTimer;
    uint32 m_uiEnrageTimer;
    uint32 m_uiEventTimer;

    void Reset()
    {
        m_uiPhase = 0;
        m_uiSubevent = 0;

        m_uiEventTimer = 5000;
        m_uiCleaveTimer = urand(5000, 7000);
        m_uiSmashTimer = urand(8000, 15000);
        m_uiStaggeringRoarTimer = urand(10000, 25000);
        m_uiEnrageTimer = 30000;
    }

    void JustReachedHome()
    {
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->UpdateEntry(NPC_INGVAR);
        SetCombatMovement(true);
    }

    void Aggro(Unit* pWho)
    {
        // don't yell for her
        if (pWho->GetEntry() == NPC_ANNHYLDE || m_uiPhase)
            return;

        // ToDo: it shouldn't yell this aggro text after removing the feign death aura
        DoScriptText(SAY_AGGRO_FIRST, m_creature);
    }

    void DamageTaken(Unit* pDealer, uint32& uiDamage)
    {
        if (m_uiPhase == PH_B4_RESSURECTION && uiDamage >= m_creature->GetHealth())
        {
            uiDamage = 0;
            DoScriptText(SAY_DEATH_FIRST, m_creature);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            DoCastSpellIfCan(m_creature, SPELL_FEIGN_DEATH);
            ++m_uiPhase;
        }
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_TRANSFORM)
            m_creature->UpdateEntry(pSpell->GetEffectMiscValue(EFFECT_INDEX_0));
    }

    void JustSummoned(Creature* pSummoned)
    {
        switch (pSummoned->GetEntry())
        {
            case NPC_THROW_DUMMY:
                // ToDo: should this move to the target?
                pSummoned->CastSpell(pSummoned, m_bIsRegularMode ? SPELL_SHADOW_AXE_PROC : SPELL_SHADOW_AXE_PROC_H, true);
                pSummoned->setFaction(m_creature->getFaction());
                pSummoned->GetMotionMaster()->MoveRandom(20.0f);
                pSummoned->ForcedDespawn(10000);
                break;

            case NPC_GROUND_VISUAL:
                pSummoned->SetFactionTemporary(35);
                pSummoned->GetMotionMaster()->MoveChase(m_creature);
                pSummoned->CastSpell(pSummoned, SPELL_SCOURGE_RES_BUBBLE, false);
                pSummoned->ForcedDespawn(5000);
                break;

            case NPC_ANNHYLDE:
                pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                break;
        }
    }

    void JustDied(Unit* pKiller)
    {
        DoScriptText(!m_uiPhase ? SAY_DEATH_FIRST : SAY_DEATH_SECOND, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(!m_uiPhase ? SAY_KILL_FIRST : SAY_KILL_SECOND, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if (m_uiPhase == PH_RESSURECTION)
        {
            if (m_uiEventTimer < uiDiff)
            {
                switch(m_uiSubevent)
                {
                    case 0:
                        float x, y, z;
                        m_creature->GetClosePoint(x, y, z, m_creature->GetObjectBoundingRadius(), 0.0f, M_PI_F, m_creature);
                        //  hackzzzzz - Summon Banshee cannot be propper casted with visuals while feiging death
                        //m_creature->CastSpell(x, y, (z + 15), SPELL_SUMMON_BANSHEE, false, NULL, NULL, m_creature->GetObjectGuid());
                        m_creature->_AddAura(SPELL_SUMMON_BANSHEE, 5000);
                        if (Creature* pAnnhylde = m_creature->SummonCreature(NPC_ANNHYLDE, x, y, z+15, m_creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 25000))
                            pAnnhylde->SetLevitate(true, m_creature->GetPositionZ() + 15);
                        break;

                    case 1:
                        if (Creature* pAnnhylde = m_pInstance->GetSingleCreatureFromStorage(NPC_ANNHYLDE))
                        {
                            DoScriptText(SAY_ANNHYLDE_REZ, pAnnhylde);
                            pAnnhylde->CastSpell(m_creature, SPELL_SCOURGE_RES_CHANNEL, false);
                        }
                        break;

                    case 2:
                        DoCastSpellIfCan(m_creature, SPELL_SCOURGE_RES_SUMMON, CAST_TRIGGERED);
                        m_creature->RemoveAurasDueToSpell(SPELL_SUMMON_BANSHEE);
                        break;

                    case 3:
                        if (Creature* pAnnhylde = m_pInstance->GetSingleCreatureFromStorage(NPC_ANNHYLDE))
                            pAnnhylde->CastSpell(m_creature, SPELL_SCOURGE_RES_SUMMON, false);
                        break;

                    case 4:
                        SetCombatMovement(false);
                        DoCastSpellIfCan(m_creature, SPELL_SELFROOT, CAST_TRIGGERED);
                        m_creature->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
                        m_creature->HandleEmote(EMOTE_ONESHOT_EMERGE);
                        DoCastSpellIfCan(m_creature, SPELL_SCOURGE_RES_HEAL, CAST_TRIGGERED);
                        break;

                    case 5:
                        SetCombatMovement(true);
                        DoCastSpellIfCan(m_creature, SPELL_TRANSFORM, CAST_TRIGGERED);
                        m_creature->RemoveAurasDueToSpell(SPELL_SELFROOT);
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        DoScriptText(SAY_AGGRO_SECOND, m_creature);
                        ++m_uiPhase;
                        break;
                }
                m_uiEventTimer = 3500;
                ++m_uiSubevent;
            }
            else
                 m_uiEventTimer -= uiDiff;
        }


        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        switch(m_uiPhase)
        {
            case PH_B4_RESSURECTION:
                if (m_uiCleaveTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE) == CAST_OK)
                        m_uiCleaveTimer = urand(2500, 7000);
                }
                else
                    m_uiCleaveTimer -= uiDiff;

                if (m_uiSmashTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_SMASH : SPELL_SMASH_H) == CAST_OK)
                        m_uiSmashTimer = urand(8000, 15000);
                }
                else
                    m_uiSmashTimer -= uiDiff;

                if (m_uiStaggeringRoarTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_STAGGERING_ROAR : SPELL_STAGGERING_ROAR_H) == CAST_OK)
                    {
                        DoScriptText(EMOTE_ROAR, m_creature);
                        m_uiStaggeringRoarTimer = urand(15000, 30000);
                    }
                }
                else
                    m_uiStaggeringRoarTimer -= uiDiff;

                if (m_uiEnrageTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_ENRAGE : SPELL_ENRAGE_H) == CAST_OK)
                        m_uiEnrageTimer = urand(10000, 20000);
                }
                else
                    m_uiEnrageTimer -= uiDiff;

                DoMeleeAttackIfReady();
                break;

            case PH_RESSURECTED:

                if (m_uiCleaveTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature->getVictim(), m_bIsRegularMode? SPELL_WOE_STRIKE : SPELL_WOE_STRIKE_H) == CAST_OK)
                        m_uiCleaveTimer = urand(2500, 7000);
                }
                else
                    m_uiCleaveTimer -= uiDiff;

                if (m_uiSmashTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_DARK_SMASH_H) == CAST_OK)
                        m_uiSmashTimer = urand(8000, 15000);
                }
                else
                    m_uiSmashTimer -= uiDiff;

                if (m_uiStaggeringRoarTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, m_bIsRegularMode ? SPELL_DREADFUL_ROAR : SPELL_DREADFUL_ROAR_H) == CAST_OK)
                    {
                        DoScriptText(EMOTE_ROAR, m_creature);
                        m_uiStaggeringRoarTimer = urand(15000, 30000);
                    }
                }
                else
                    m_uiStaggeringRoarTimer -= uiDiff;

                if (m_uiEnrageTimer < uiDiff)
                {
                    if (DoCastSpellIfCan(m_creature, SPELL_SHADOW_AXE) == CAST_OK)
                        m_uiEnrageTimer = urand(10000, 20000);
                }
                else
                    m_uiEnrageTimer -= uiDiff;

                DoMeleeAttackIfReady();
                break;
        }
    }
};

CreatureAI* GetAI_boss_ingvar(Creature* pCreature)
{
    return new boss_ingvarAI(pCreature);
}

void AddSC_boss_ingvar()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_ingvar";
    pNewScript->GetAI = &GetAI_boss_ingvar;
    pNewScript->RegisterSelf();
}
