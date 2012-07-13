-- last update s310
-- ---------------------Achievements ------------------------------
-- Oculus
DELETE FROM `achievement_criteria_requirement` where `criteria_id` IN(203,204,205,206);
INSERT INTO `achievement_criteria_requirement` VALUES(203,12,0,0),(204,12,0,0),(205,12,0,0),(206,12,0,0);

-- Oculus (heroic)
DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` IN(6859,6860,6861,6862);
INSERT INTO `achievement_criteria_requirement` VALUES(6859,12,1,0),(6860,12,1,0),(6861,12,1,0),(6862,12,1,0);

-- Make It Count + Expirienced Drake Rider
DELETE FROM `achievement_criteria_requirement` WHERE `criteria_id` IN(7145,7178,7179,7177);
INSERT INTO `achievement_criteria_requirement` VALUES(7145,12,1,0),(7178,12,1,0),(7179,12,1,0),(7177,12,1,0);