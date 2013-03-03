UPDATE creature_template SET ScriptName = '', AIName = 'EventAI' WHERE entry IN (22307,22095);
DELETE FROM creature_ai_scripts WHERE creature_id IN (22307,22095);
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('2230701','22307','0','0','100','1','5000','9000','32000','38000','11','15548','1','0','0','0','0','0','0','0','0','0','Rotting Forest-Rager - Cast Thunderclap'),
('2230702','22307','6','0','100','0','0','0','0','0','11','39130','0','7','0','0','0','0','0','0','0','0','Rotting Forest-Rager - Summon Wood Mites on Death'),
('2209501','22095','0','0','100','1','15000','20000','32000','38000','11','39000','0','0','0','0','0','0','0','0','0','0','Infested Root-Walker - Cast Regrowth'),
('2209502','22095','6','0','100','0','0','0','0','0','11','39130','0','7','0','0','0','0','0','0','0','0','Infested Root-Walker - Summon Wood Mites on Death');

INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `condition_id`) VALUES
('7732','0','0','I have been sent by Sal\'salabim to collect a debt that you owe. Pay up or I\'m going to have to hurt you.','1','1','7731','0','0','0','0',NULL,'875');

UPDATE creature_template SET ScriptName = '', AIName = 'EventAI' WHERE entry IN (18588);
DELETE FROM gossip_menu_option WHERE menu_id = 7732;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `condition_id`) VALUES
('7732','0','0','I have been sent by Sal\'salabim to collect a debt that you owe. Pay up or I\'m going to have to hurt you.','1','1','7731','0','0','0','0',NULL,'875');
DELETE FROM conditions WHERE condition_entry = 875;
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value2`) VALUES('875','9','10009','0');

DELETE FROM creature_ai_scripts WHERE creature_id IN (18588);
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('1858801','18588','0','0','100','1','2000','2000','30000','30000','11','6726','1','0','0','0','0','0','0','0','0','0','Floon - Cast Silence'),
('1858802','18588','0','0','100','1','4000','4000','5000','7000','11','9672','1','0','0','0','0','0','0','0','0','0','Floon - Cast Frostbolt'),
('1858803','18588','0','0','100','1','9000','9000','20000','20000','11','11831','0','0','0','0','0','0','0','0','0','0','Floon - Cast Frost Nova');

DELETE FROM gossip_menu_option WHERE menu_id = 8719;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `condition_id`) VALUES
('8719','0','0','Absolutely!  Send me to the Skyguard Outpost.','1','1','-1','0','8719','0','0',NULL,'441');
DELETE FROM conditions WHERE condition_entry = 441;
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value2`) VALUES('441','5','1031','5');

UPDATE creature_template SET ScriptName = '' WHERE entry IN (19679);
DELETE FROM gossip_menu_option WHERE menu_id = 8021;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `condition_id`) VALUES
('8021','0','1','Show me what you have for sale, \"Slim.\"','3','128','0','0','0','0','0',NULL,'1567');
DELETE FROM conditions WHERE condition_entry = 1567;
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value2`) VALUES('1567','5','933','4');

UPDATE creature_template SET ScriptName = 'npc_skywing' WHERE entry = 22424;
DELETE FROM quest_template WHERE entry = 10898;
INSERT INTO `quest_template` (`entry`, `Method`, `ZoneOrSort`, `MinLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`, `RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`, `QuestFlags`, `SpecialFlags`, `CharTitleId`, `PlayersSlain`, `BonusTalents`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `RewXPId`, `SrcItemId`, `SrcItemCount`, `SrcSpell`, `Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `CompletedText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemId5`, `ReqItemId6`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`, `ReqItemCount5`, `ReqItemCount6`, `ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`, `ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`, `ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`, `RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`, `RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`, `RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`, `RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValueId1`, `RewRepValueId2`, `RewRepValueId3`, `RewRepValueId4`, `RewRepValueId5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`, `RewHonorAddition`, `RewHonorMultiplier`, `RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`) VALUES
('10898','2','3519','63','65','1','0','0','0','0','0','0','0','0','0','0','2','0','138','2','','0','0','0','0','0','0','6','0','0','0','Skywing','Skywing flutters around you.$b$bYou get the feeling he wants you to follow him.','Escort Skywing and report to Rilak the Redeemed in Shattrath City.','Alas, poor Skywing was under the dreaded curse of Luanga the Imprisoner!$B$BSkywing traveled to Veil Shalas to attempt to sway others in seeing the way of the Light. They didn\'t take lightly to his actions, especially sitting on the doorstep of Skettis.$B$BLuanga was one of Terokk\'s most feared agents. You have done well by freeing Skywing! I thank you.','What brings you here?','Escort Skywing','Return to Rilak the Redeemed in the Lower City section of Shattrath City.',NULL,NULL,NULL,NULL,'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','31766','31765','31764','0','0','0','1','1','1','0','0','0','31760','0','0','0','1','0','0','0','1011','0','0','0','0','6','0','0','0','0','0','0','0','0','0','0','0','66000','8400','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','396','396','396','0','0','0','0','0','0','0');

DELETE FROM creature WHERE guid = 80999;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
('80999','22424','530','1','1','0','0','-3605.72','4175.58','-0.031817','2.90906','300','0','0','5715','0','0','0');

DELETE FROM gossip_menu_option WHERE menu_id = 8687;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`, `condition_id`) VALUES
('8687','0','0','<Call forth Terrok.>','1','1','-1','0','8687','0','0',NULL,'527');
DELETE FROM dbscripts_on_gossip WHERE id = 8687;
INSERT INTO `dbscripts_on_gossip` (`id`, `delay`, `command`, `datalong`, `datalong2`, `buddy_entry`, `search_radius`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES
('8687','0','15','41004','0','0','0','4','3','185928','0','0','0','0','0','0','');
DELETE FROM conditions WHERE condition_entry = 527;
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value2`) VALUES('527','2','32720','1');

DELETE FROM spell_script_target WHERE entry = 41004;
INSERT INTO `spell_script_target` (`entry`, `type`, `targetEntry`, `inverseEffectMask`) VALUES('41004','0','185928','0');
