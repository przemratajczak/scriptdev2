UPDATE creature_template SET ScriptName = '' WHERE entry IN (17900,17901);
DELETE FROM conditions WHERE condition_entry IN (1594,1595,1596,491,1590,1591,1592,818,819,820);
INSERT INTO `conditions` (`condition_entry`, `type`, `value1`, `value2`)  VALUES('491','5','942','7'),
('818','5','942','4'),
('819','5','942','5'),
('820','5','942','6'),
('1590','30','942','4'),
('1591','30','942','5'),
('1592','30','942','6'),
('1594','-1','818','1590'),
('1595','-1','819','1591'),
('1596','-1','820','1592');

DELETE FROM gossip_menu_option WHERE menu_id IN (7559,7560);

INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `action_script_id`, `box_coded`, `box_money`, `box_text`,  `condition_id`) VALUES('7559','0','0','Grant me your mark, wise ancient.','1','1','-1','0','7559','0','0',NULL,'1594'),
('7559','1','0','Grant me your mark, wise ancient.','1','1','-1','0','50010','0','0',NULL,'1595'),
('7559','2','0','Grant me your mark, wise ancient.','1','1','-1','0','50011','0','0',NULL,'1596'),
('7559','3','0','Grant me your mark, wise ancient.','1','1','-1','0','50012','0','0',NULL,'491'),
('7560','0','0','Grant me your mark, mighty ancient.','1','1','-1','0','7560','0','0',NULL,'1594'),
('7560','1','0','Grant me your mark, mighty ancient.','1','1','-1','0','50005','0','0',NULL,'1595'),
('7560','2','0','Grant me your mark, mighty ancient.','1','1','-1','0','50006','0','0',NULL,'1596'),
('7560','3','0','Grant me your mark, mighty ancient.','1','1','-1','0','50007','0','0',NULL,'491');
