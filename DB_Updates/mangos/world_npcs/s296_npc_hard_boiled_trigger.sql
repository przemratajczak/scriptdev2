UPDATE  `creature_template` SET
ScriptName='npc_hard_boiled_trigger'
where entry=23837;

DELETE FROM creature WHERE id=23837;
INSERT INTO creature (id,map,spawnMask,phaseMask,modelid,equipment_id,position_x,position_y,position_z,orientation,spawntimesecs,spawndist,currentwaypoint,curhealth,curmana,DeathState,MovementType) VALUES 
(23837,1,1,1,0,0,-7319.51,-751.587,-272.306,1.18438,25,0,0,42,0,0,0),
(23837,1,1,1,0,0,-7295.59,-622.553,-271.46,1.3446,25,0,0,42,0,0,0),
(23837,1,1,1,0,0,-7246.32,-491.976,-267.547,1.14433,25,0,0,42,0,0,0),
(23837,1,1,1,0,0,-7156.65,-746.456,-272.017,5.8685,25,0,0,42,0,0,0),
(23837,1,1,1,0,0,-7364.06,-710.031,-272.306,4.38802,25,0,0,42,0,0,0);
