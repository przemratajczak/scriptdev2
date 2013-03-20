UPDATE creature_template SET ainame = 'EventAI' WHERE entry = 37094;
DELETE FROM creature_ai_scripts WHERE creature_id = 37094;
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES
('3709401','37094','8','0','100','6','6922','-1','0','0','11','69956','6','1','0','0','0','0','0','0','0','0','Return Tempered Blade (Quest: 24476,24560)');
