-- ----------
-- Sindragosa
-- ----------

-- set to fly
UPDATE `creature_template` SET `InhabitType` = 7 WHERE `entry` IN (36853, 38265, 38266, 38267);
DELETE FROM `creature_template_addon` WHERE `entry` = 36853;
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `b2_0_sheath`, `b2_1_pvp_state`, `emote`, `moveflags`, `auras`)
VALUES (36853, 0, 50331648, 1, 0, 0, 1, '');

DELETE FROM `scripted_areatrigger` WHERE `entry` = 5604;
INSERT INTO `scripted_areatrigger` VALUES (5604, 'at_icecrown_citadel');
