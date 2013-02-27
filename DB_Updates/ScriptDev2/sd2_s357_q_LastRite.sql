/************* MaNGOS db ****************************/
UPDATE creature_template SET ScriptName = 'npc_thassarian' WHERE entry = 26170;

-- npc_thassarian
INSERT INTO creature (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)
VALUES ('850000','26170','571','1','1','0','613','3691.87','3576.49','473.322','6.06956','25','5','0','67270','0','0','2');

-- npc valanar
DELETE FROM creature WHERE id = 28189;

/************* SD2 db *******************************/
DELETE FROM script_texts WHERE entry BETWEEN -1534090 AND -1534070;
INSERT INTO script_texts (entry,TYPE,sound,COMMENT,content_default) VALUES
(-1534090,0,14211,'Prince Valanar says','My liege, the infiltration and control of the Alliance power structure by our cultists is well underway.'),
(-1534089,0,14756,'Image of the Lich King says','Your progress in this region has been impressive, Blood Prince. I am pleased...'),
(-1534088,0,14212,'Prince Valanar says','The power you\'ve bestowed upon me has allowed me great mental influence over human minds. I bear these offerings as proof of my progress.'),
-- Leryssa and General Arlos appear and walk toward Valanar and the Lich King. Thassarian runs forward.
(-1534087,1,14664,'Thassarian yells','Leryssa!'),
(-1534086,1,14665,'Thassarian yells','What have you done to my sister, you motherless elf scum!?'),
(-1534085,0,14757,'Image of the Lich King says','Now this is a surprise, Thassarian. I hadn\'t heard from Mograine or the other death knights for months. You\'ve come to rejoin the Scourge, I take it?'),
(-1534084,0,14666,'Thassarian says','I would sooner slit my own throat. You will pay for what you did to your own men, Arthas... for what you did to me! I swear it.'),
(-1534083,0,14213,'Prince Valanar says','Allow me to take care of the intruders, lord. I will feed their entrails to the maggots.'),
(-1534082,0,14758,'Image of the Lich King says','Do not fail me, San\'layn. Return to Icecrown with this fool\'s head or do not bother to return.'),
(-1534081,0,14214,'Prince Valanar says','Yes, my lord!'),
(-1534080,0,14196,'General Arlos says','What... what happened to me?'),
(-1534079,0,14197,'General Arlos says','Ugh! My head won\'t stop spinning...'),
(-1534078,1,14489,'Leryssa yells','Thassarian, you\'re alive!'),
(-1534077,0,14667,'Thassarian says','Leryssa... you... you\'re all right!'),
(-1534076,0,14490,'Leryssa says','I thought... I thought you were... dead.'),
(-1534075,0,14668,'Thassarian says','I cannot return home with you just yet, Leryssa. I am not quite done with the Scourge.'),
(-1534074,0,14491,'Leryssa says','Don\'t leave me again! You want to fight for your country, but they don\'t even want you! They sent you here to die!'),
(-1534073,0,14669,'Thassarian says','You might be right, sister. My obligations to my land and King have been fulfilled. But there is still something that I owe to myself.'),
(-1534072,0,14492,'Leryssa says','I know that look in your eye... I\'m not going to be able to talk you out of this. If you die on me again...'),
(-1534071,0,14670,'Thassarian says','Do not worry, Leryssa. I will come back to you when I\'m done. Nothing in the world will stop me from coming home to the only family that I have left.'),
(-1534070,0,0,'Prince Valanar says','Pitiful... just pitiful.');
