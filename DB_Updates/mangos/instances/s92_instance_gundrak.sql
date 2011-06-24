-- Instance Gundrak
-- Instance last changes: s92

UPDATE creature_template SET
ScriptName='mob_sladran_summon_target'
WHERE entry=29682;

UPDATE creature_template SET
ScriptName='boss_sladran'
WHERE entry=29304;

UPDATE creature_template SET
ScriptName='mob_sladran_constrictor'
WHERE entry=29713;

UPDATE creature_template SET
ScriptName='mob_sladran_snake_wrap'
WHERE entry=29742;

UPDATE creature_template SET
ScriptName='boss_colossus',
unit_flags = unit_flags&~33600
WHERE entry IN (29307, 31365);

UPDATE creature_template SET
ScriptName='boss_drakari_elemental'
WHERE entry=29573;

UPDATE creature_template SET
ScriptName='npc_living_mojo'
WHERE entry=29830;

UPDATE creature_template SET
ScriptName='boss_galdarah'
WHERE entry=29306;

UPDATE creature_template SET
ScriptName='boss_moorabi'
WHERE entry=29305;

UPDATE creature_template SET
ScriptName='boss_eck'
WHERE entry=29932;

UPDATE gameobject_template SET
ScriptName='go_gundrak_altar'
WHERE entry IN(192518,192519,192520);

UPDATE creature_template SET mechanic_immune_mask=mechanic_immune_mask|1|16|64|256|512|1024|2048|4096|8192|65536|131072|524288|8388608|536870912
WHERE entry IN (29304,29307,29573,29306,29305,31370,30530,31368,31365,31367,29932);
