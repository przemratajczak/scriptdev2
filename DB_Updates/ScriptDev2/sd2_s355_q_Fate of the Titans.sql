DELETE FROM script_texts WHERE entry BETWEEN -1799118 AND -1799100;
INSERT INTO script_texts (entry, content_default, comment) VALUES
(-1799100, 'Temple of Invention analysis commencing.', 'Temple of Invention 0'),
(-1799101, 'Temple of Invention verified to be in-tact.', 'Temple of Invention 0'),
(-1799102, 'Mechanical servants appear to have turned against each other. Several attendants have been piled together in an unorganized manner.', 'Temple of Invention 0'),
(-1799103, 'Remaining mechagnome guardians corrupted by unknown source.', 'Temple of Invention 0'),
(-1799104, 'Watcher Mimir verified to no longer be present. Analysis complete.', 'Temple of Invention 0'),

(-1799105, 'Temple of Winter analysis commencing.', 'Temple of Winter 0'),
(-1799106, 'Temple of Winter verified to be in-tact.', 'Temple of Winter 0'),
(-1799107, 'Temple guardians verified to be deceased. Sulfurous odor suggests that death resulted from a fire-base entity.', 'Temple of Winter 0'),
(-1799108, 'Previously established cold weather patterns at the temple have ceased.', 'Temple of Winter 0'),
(-1799109, 'Watcher Hodir verified to no longer be present. Analysis complete.', 'Temple of Winter 0'),

(-1799110, 'Temple of Life analysis commencing.', 'Temple of Life 0'),
(-1799111, 'Temple of Life verified to be damaged beyond repair.', 'Temple of Life 0'),
(-1799112, 'Evidence indicates a significant battle. The opponent of Watcher Freya estimated to be of similar size and strength to Watcher Freya.', 'Temple of Life 0'),
(-1799113, 'Temple guardians are no longer present. Plant forms associated with temple are deceased.', 'Temple of Life 0'),
(-1799114, 'Watcher Freya verified to no longer be present. Analysis complete.', 'Temple of Life 0'),

(-1799115, 'Temple of Order analysis commencing.', 'Temple of Order 0'),
(-1799116, 'Temple of Order verified to be in-tact.', 'Temple of Order 0'),
(-1799117, 'No indications of struggle are present. No guardians are present.', 'Temple of Order 0'),
(-1799118, 'Watcher Tyr verified to no longer be present. Analysis complete.', 'Temple of Order 0');

UPDATE creature_template SET ScriptName = 'npc_mobile_databank' WHERE entry = 30313;
