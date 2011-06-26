-- last update s104
-- Chaos Rift
UPDATE creature_template SET
ScriptName = '',
AIName = 'EventAI'
WHERE entry = 26918;
DELETE FROM creature_ai_scripts WHERE creature_id = 26918;
INSERT INTO  `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('2691801','26918','4','0','100','2','0','0','0','0','11','47687','0','2','21','0','0','0','0','0','0','0','Chaotic Rift - Aura Normal'),
('2691802','26918','4','0','100','4','0','0','0','0','11','47733','0','2','21','0','0','0','0','0','0','0','Chaotic Rift - Aura Heroic'),
('2691803','26918','11','0','100','2','0','0','0','0','11','47732','0','2','0','0','0','0','0','0','0','0','Chaotic Rift - Aura Summon Normal'),
('2691804','26918','11','0','100','4','0','0','0','0','11','47742','0','2','0','0','0','0','0','0','0','0','Chaotic Rift - Aura Summon Heroic');
