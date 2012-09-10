DELETE from creature_spell WHERE guid IN (24821, 24806, 24823 );
INSERT into creature_spell VALUES
(24821,44550,0,0,0,0),
(24806,44498,0,0,0,0),
(24823,44562,0,0,0,0);

UPDATE creature_template SET
minhealth=12300,
maxhealth=12300,
minlevel=70,
maxlevel=70,
armor=6740
WHERE entry IN (24821, 24806, 24823 );

-- quest collecting data
DELETE from creature_ai_scripts where creature_id=24820;
INSERT into creature_ai_scripts (`id`, `creature_id`, `event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`, `event_param1`,
`event_param2`, `event_param3`, `event_param4`,`action1_type`, `action1_param1` ,`action1_param2`, `action1_param3`,`action2_type`, `action2_param1`, `action2_param2`, `action2_param3`,`action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(2482001,24820,8,0,100,1,44550,-1,0,0,33,24820,6,0,0,0,0,0,0,0,0,0,'Collecting data quest credit');

UPDATE creature_template SET
AIName='EventAI'
WHERE entry=24820;

-- quest the bluff
DELETE from creature_ai_scripts where id=2471800;
INSERT into creature_ai_scripts (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,`action1_type`, `action1_param1`, `action1_param2`, `action1_param3`,`action2_type`, `action2_param1`, `action2_param2`, `action2_param3`,`action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
(2471800,24718,8,0,100,1,44562,-1,0,0,15,11491,6,0,0,0,0,0,0,0,0,0,'Lebronski kill credit');


UPDATE creature_template SET
AIName='',
ScriptName='npc_lebronski'
WHERE entry=24718;

-- rocket jumping
DELETE from spell_script_target where entry=44498;
INSERT into spell_script_target VALUES
(44498,0,186956);

UPDATE gameobject_template SET
ScriptName='go_walts_rune'
WHERE entry=186956;