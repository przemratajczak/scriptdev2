/********************************* MaNGOS DB **********************************************/

-- Set phasing for quest chain till Q:Journey To The Sunwell (A and H respectivly)
DELETE FROM spell_area WHERE spell = 59073 AND AREA = 4092;
INSERT INTO spell_area (spell,AREA,quest_start,quest_start_active,autocast) VALUES
(59073,4092,24522,0,1),
(59073,4092,24562,0,1);

-- NPC_THALORIEN_DAWNSEEKER_CORPSE - ToDo: Yellow Aura
UPDATE creature SET phasemask = 2 WHERE id = 37552;

-- NPC_THALORIEN_DAWNSEEKER
UPDATE creature_template SET npcflag = 0, ScriptName = 'npc_thalorien_dawnseeker' WHERE entry = 37205;
-- NPC_MORLEN_COLDGRIP
UPDATE creature_template SET AIName = 'EventAI' WHERE entry = 37542;

-- change org. YTDB? script with summoning NPC_THALORIEN_DAWNSEEKER
DELETE FROM dbscripts_on_gossip WHERE id = 37552;
INSERT INTO dbscripts_on_gossip (id,command,datalong,datalong2,X,Y,z,o,comments) VALUES
(37552,10,37205,360000,11793,-7072,26,5.9,'Summon Thalorien Dawnseeker'),
(37552,18,0,0,0,0,0,0,'Despawn Thalorien Dawnseeker corpse');
UPDATE creature SET Spawntimesecs = 240 WHERE id = 37552;

-- NPC_MORLEN_COLDGRIP on a Deathcharger
DELETE FROM creature_template_addon WHERE entry = 37542;
INSERT INTO creature_template_addon (entry,mount,b2_0_sheath) VALUES
(37542,25280,1);

DELETE FROM creature_ai_scripts WHERE creature_id = 37542;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('3754201','37542','0','0','100','1','1000','5000','10000','20000','11','50688','0','0','0','0','0','0','0','0','0','0','Morlen Coldgrip - Plague Strike');

/********************************* Scriptdev2 **********************************************/
DELETE FROM script_texts WHERE entry BETWEEN -1574964 AND -1574950;
INSERT INTO `script_texts` (`entry`,`comment`,`content_default`,`sound`,`type`, `emote`) VALUES
-- A host of ten sunwell defenders and the ghost of Thalorien Dawnseeker appear to relive his last moments.
(-1574950,"Thalorien Dawnseeker says","We must defend the Sunwell from the enemy at all costs.",16769,0,0),
(-1574951,"Thalorien Dawnseeker says","I am ordering you to withdraw to the Sunwell proper to help prepare the defenses.",16770,0,0),
(-1574952,"Thalorien Dawnseeker says","I will make my stand here and buy you as much time as I am able. Use it well and make our prince proud.",16771,0,0),
(-1574953,"Thalorien Dawnseeker says","It has been a great honor to fight beside you in defense of our land and our people.",16772,0,0),
-- The host departs and Thalorien notices the player.
(-1574954,"Thalorien Dawnseeker says","You, stranger... you are not one of my soldiers. Will you stay and stand with me to face the enemy?",16773,0,0),
-- Morlen Coldgrip appears
(-1574955,"Thalorien Dawnseeker yells","Listen well, Scourge defilers. None of you will reach the Sunwell so long as I stand!",16774,0,0),
(-1574956,"Morlen Coldgrip yells","You will fall as your lands and your city have before you. My lord will win a great victory here, and none will remember your name!",0,1,0),
(-1574957,"Morlen Coldgrip yells","Forward!",0,0,0),
-- 5 Scourge Zombies attack
(-1574958,"Morlen Coldgrip yells","Ghouls, slay this pathetic high elf!",0,1,0),
-- 5 Ghoul Invaders attack
(-1574959,"Morlen Coldgrip yells","You will fall before the might of the Scourge. Crypt raiders, attack!",0,1,0),
-- 3 Crypt Raiders attack
(-1574960,"Morlen Coldgrip yells","I shall kill you myself!",0,1,0),
-- Morlen Coldgrip joins the fight
-- On victory:
(-1574961,"Thalorien Dawnseeker says","I... I wasn't meant to survive this attack.",16775,0,1),
(-1574962,"Thalorien Dawnseeker says","Why has this happened? Why have you come here?",16776,0,1),
(-1574963,"Thalorien Dawnseeker says","It's Quel'Delar! You possess the sword!",16775,0,1),
(-1574964,"Thalorien Dawnseeker says","I don't know how, but the blade has chosen you to be its new wielder. Take it with my blessing, and wield it against the Scourge as I once did.",16778,0,1);
-- Thalorien's ghost fades.
