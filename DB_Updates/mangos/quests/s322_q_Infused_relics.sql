-- quest infused relics

DELETE from creature_ai_scripts where creature_id=24824
INSERT into creature_ai_scripts (`id`, `creature_id`, `event_type`, 
`event_param2`, `event_param3`, `event_param4`,`action1_type`, `action1_param1` ,`action1_param2`, `action1_param3`,`action2_type`, `action2_param1`, `action2_param2`, `action2_param3`,`action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(2482401,24824,8,0,100,1,44610,-1,0,0,33,24824,6,0,0,0,0,0,0,0,0,0,'infused relic quest credit');

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=24824;

DELETE from creature_spell WHERE guid=24825;
INSERT into creature_spell VALUES
(24825,44610,0,0,0,0),
(24825,44626,1,0,0,0),
(24825,44609,2,0,0,0);

UPDATE creature_template SET
minhealth=12300,
maxhealth=12300,
minlevel=70,
maxlevel=70,
armor=6740
WHERE entry=24825;

UPDATE creature_template SET
ScriptName='npc_walt'
WHERE entry=24807;

UPDATE gameobject_template SET
ScriptName='go_work_bench'
WHERE entry=186958;
