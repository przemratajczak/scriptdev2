-- spring rabbit spawns
DELETE FROM creature WHERE id=32791;
INSERT INTO creature (id,map,spawnMask,phaseMask,modelid,equipment_id,position_x,position_y,position_z,orientation,spawntimesecs,spawndist,currentwaypoint,curhealth,curmana,DeathState,MovementType) VALUES 
(32791,1,1,1,0,0,9859.54,957.579,1306.07,2.61846,25,0,0,1,0,0,0),
(32791,0,1,1,0,0,-9454.95,69.1646,56.3616,3.26447,25,0,0,1,0,0,0),
(32791,0,1,1,0,0,-5600.49,-486.163,397.127,5.42818,25,0,0,1,0,0,0),
(32791,530,1,1,0,0,-4190.85,-12516.5,44.5276,1.34225,25,0,0,1,0,0,0),
(32791,0,1,1,0,0,2264.98,289.393,34.2846,0.99998,25,0,0,1,0,0,0),
(32791,1,1,1,0,0,326.81,-4706.65,15.3665,4.16414,25,0,0,1,0,0,0),
(32791,1,1,1,0,0,-2251.99,-394.01,-9.42446,2.10942,25,0,0,1,0,0,0),
(32791,530,1,1,0,0,9512.4,-6819.91,16.4902,2.29466,25,0,0,1,0,0,0);


UPDATE `creature_template` SET `ScriptName`='npc_spring_rabbit' WHERE `entry`=32791;