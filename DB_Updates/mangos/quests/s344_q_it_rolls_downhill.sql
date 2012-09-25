UPDATE creature_template SET
AIName='',
ScriptName='npc_blight_geist'
WHERE entry=28750;

DELETE from creature_spell where guid=28750 AND spell=52245;
INSERT into creature_spell VALUES
(28750,52245,0,0,0,0);