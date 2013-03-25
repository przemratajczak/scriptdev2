-- dummy npcs used to handle black buble aura and shadow axe
UPDATE creature_template SET AIName = 'NullAI' WHERE entry IN (23997,24012);

UPDATE creature_template SET ScriptName = '' WHERE ScriptName = 'npc_annhylde';
