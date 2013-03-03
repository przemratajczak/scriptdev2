/**************************** MaNGOS DB *******************************/
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

/**************************** ScriptDev2 *******************************/
DELETE FROM script_texts WHERE entry BETWEEN -1000802 AND -1000797;
INSERT INTO script_texts (entry,content_default,sound,TYPE,LANGUAGE,emote,COMMENT) VALUES
(-1000797,'%s squawks and heads toward Veil Shalas. Hurry and follow!',0,2,0,0,'skywing SAY_SKYWING_START'),
(-1000798,'%s pauses briefly before the tree and then heads inside.',0,2,0,0,'skywing SAY_SKYWING_TREE_DOWN'),
(-1000799,'%s seems to be looking for something. He wants you to follow.',0,2,0,0,'skywing SAY_SKYWING_TREE_UP'),
(-1000800,'%s flies to the platform below! You\'d better jump if you want to keep up. Hurry!',0,2,0,0,'skywing SAY_SKYWING_JUMP'),
(-1000801,'%s bellows a loud squawk!',0,2,0,0,'skywing SAY_SKYWING_SUMMON'),
(-1000802,'Free at last from that horrible curse! Thank you! Please send word to Rilak the Redeemed that I am okay. My mission lies in Skettis. Terokk must be defeated!',0,0,0,0,'skywing SAY_SKYWING_END');

DELETE FROM script_waypoint WHERE entry=22424;
INSERT INTO script_waypoint VALUES
(22424, 1, -3620.54, 4164.57, 1.81, 0, 'SKYWING_START'),
(22424, 2, -3624.78, 4149.65, 7.44, 0, ''),
(22424, 3, -3630.30, 4124.84, 21.28, 0, ''),
(22424, 4, -3629.14, 4093.65, 44.35, 0, ''),
(22424, 5, -3626.34, 4080.29, 52.39, 0, ''),
(22424, 6, -3619.35, 4063.86, 60.86, 3000, 'SAY_SKYWING_TREE_DOWN'),
(22424, 7, -3615.09, 4054.17, 62.46, 0, ''),
(22424, 8, -3611.39, 4046.60, 65.07, 0, ''),
(22424, 9, -3606.68, 4040.50, 66.00, 0, ''),
(22424, 10, -3600.88, 4038.69, 67.14, 0, ''),
(22424, 11, -3597.88, 4033.84, 68.53, 0, ''),
(22424, 12, -3602.19, 4027.89, 69.36, 0, ''),
(22424, 13, -3609.85, 4028.37, 70.78, 0, ''),
(22424, 14, -3613.01, 4031.10, 72.14, 0, ''),
(22424, 15, -3613.18, 4035.63, 73.52, 0, ''),
(22424, 16, -3609.84, 4039.73, 75.25, 0, ''),
(22424, 17, -3604.55, 4040.12, 77.01, 0, ''),
(22424, 18, -3600.61, 4036.03, 78.84, 0, ''),
(22424, 19, -3602.63, 4029.99, 81.01, 0, ''),
(22424, 20, -3608.87, 4028.64, 83.27, 0, ''),
(22424, 21, -3612.53, 4032.74, 85.24, 0, ''),
(22424, 22, -3611.08, 4038.13, 87.31, 0, ''),
(22424, 23, -3605.09, 4039.35, 89.55, 0, ''),
(22424, 24, -3601.87, 4035.44, 91.64, 0, ''),
(22424, 25, -3603.08, 4030.58, 93.66, 0, ''),
(22424, 26, -3608.47, 4029.23, 95.91, 0, ''),
(22424, 27, -3611.68, 4033.35, 98.09, 0, ''),
(22424, 28, -3609.51, 4038.25, 100.45, 0, ''),
(22424, 29, -3604.54, 4038.01, 102.72, 0, ''),
(22424, 30, -3602.40, 4033.48, 105.12, 0, ''),
(22424, 31, -3606.17, 4029.69, 107.63, 0, ''),
(22424, 32, -3609.93, 4031.26, 109.53, 0, ''),
(22424, 33, -3609.38, 4035.86, 110.67, 0, ''),
(22424, 34, -3603.58, 4043.03, 112.89, 0, ''),
(22424, 35, -3600.99, 4046.49, 111.81, 0, ''),
(22424, 36, -3602.32, 4051.77, 111.81, 3000, 'SAY_SKYWING_TREE_UP'),
(22424, 37, -3609.55, 4055.95, 112.00, 0, ''),
(22424, 38, -3620.93, 4043.77, 111.99, 0, ''),
(22424, 39, -3622.44, 4038.95, 111.99, 0, ''),
(22424, 40, -3621.64, 4025.39, 111.99, 0, ''),
(22424, 41, -3609.62, 4015.20, 111.99, 0, ''),
(22424, 42, -3598.37, 4017.72, 111.99, 0, ''),
(22424, 43, -3590.21, 4026.62, 111.99, 0, ''),
(22424, 44, -3586.55, 4034.13, 112.00, 0, ''),
(22424, 45, -3580.39, 4033.46, 112.00, 0, ''),
(22424, 46, -3568.83, 4032.53, 107.16, 0, ''),
(22424, 47, -3554.81, 4031.23, 105.31, 0, ''),
(22424, 48, -3544.39, 4030.10, 106.58, 0, ''),
(22424, 49, -3531.91, 4029.25, 111.70, 0, ''),
(22424, 50, -3523.50, 4030.24, 112.47, 0, ''),
(22424, 51, -3517.48, 4037.42, 112.66, 0, ''),
(22424, 52, -3510.40, 4040.77, 112.92, 0, ''),
(22424, 53, -3503.83, 4041.35, 113.17, 0, ''),
(22424, 54, -3498.31, 4040.65, 113.11, 0, ''),
(22424, 55, -3494.05, 4031.67, 113.11, 0, ''),
(22424, 56, -3487.71, 4025.58, 113.12, 0, ''),
(22424, 57, -3500.42, 4012.93, 113.11, 0, ''),
(22424, 58, -3510.86, 4010.15, 113.10, 0, ''),
(22424, 59, -3518.07, 4008.62, 112.97, 0, ''),
(22424, 60, -3524.74, 4014.55, 112.41, 2000, 'SAY_SKYWING_JUMP'),
(22424, 61, -3537.81, 4008.59, 92.53, 0, ''),
(22424, 62, -3546.25, 4008.81, 92.79, 0, ''),
(22424, 63, -3552.07, 4006.48, 92.84, 0, ''),
(22424, 64, -3556.29, 4000.14, 92.92, 0, ''),
(22424, 65, -3556.16, 3991.24, 92.92, 0, ''),
(22424, 66, -3551.48, 3984.28, 92.91, 0, ''),
(22424, 67, -3542.90, 3981.64, 92.91, 0, ''),
(22424, 68, -3534.82, 3983.98, 92.92, 0, ''),
(22424, 69, -3530.58, 3989.91, 92.85, 0, ''),
(22424, 70, -3529.85, 3998.77, 92.59, 0, ''),
(22424, 71, -3534.15, 4008.45, 92.34, 0, ''),
(22424, 72, -3532.87, 4012.97, 91.64, 0, ''),
(22424, 73, -3530.57, 4023.42, 86.82, 0, ''),
(22424, 74, -3528.24, 4033.91, 85.69, 0, ''),
(22424, 75, -3526.22, 4043.75, 87.26, 0, ''),
(22424, 76, -3523.84, 4054.29, 92.42, 0, ''),
(22424, 77, -3522.44, 4059.06, 92.92, 0, ''),
(22424, 78, -3514.26, 4060.72, 92.92, 0, ''),
(22424, 79, -3507.76, 4065.21, 92.92, 0, ''),
(22424, 80, -3503.24, 4076.63, 92.92, 0, 'SAY_SKYWING_SUMMON'),
(22424, 81, -3504.23, 4080.47, 92.92, 7000, 'SPELL_TRANSFORM'),
(22424, 82, -3504.23, 4080.47, 92.92, 20000, 'SAY_SKYWING_END');

