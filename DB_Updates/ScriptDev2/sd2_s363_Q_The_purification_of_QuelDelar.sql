-- Quel'Dalar spawn
DELETE FROM gameobject WHERE id IN (
300249,  -- hacky sunwell focus
201794,  -- Quel'Delar
201797);  -- Portal to Dalaran

INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('72796','201794','580','1','2','1691.69','618.096','30.4546','1.06446','0','0','0.507455','0.861678','-25','100','1'),
('599999','201797','580','1','2','1655.17','654.746','28.0502','5.55766','0','0','0.354861','-0.934919','25','255','1'),
('599998','300249','580','1','2','1697.78','628.615','27.5664','3.17441','0','0','0.999865','-0.0164058','25','255','1');

UPDATE gameobject_template SET flags = 0 WHERE entry = 201794;

DELETE FROM creature WHERE id IN (
38047, -- Blood Elf Pilgrim
36991, -- Sunwell Guardian
38052, -- Liadrin
37781, -- Sunwell Honor Guard
37763, -- Rommath
37764, -- Theron
37765, -- Auric
38056, -- Galiros
37000) ORDER BY guid,id; -- Sunwell visual bunny

INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
('9000101','38047','580','1','2','0','0','1721.61','630.401','28.5311','3.30556','25','0','0','1','0','0','0'),
('9000102','38047','580','1','2','0','0','1720.63','630.952','28.4303','3.55688','25','0','0','1','0','0','0'),
('9000103','38047','580','1','2','0','0','1721.05','632.615','28.5352','3.17989','25','0','0','1','0','0','0'),
('9000104','38047','580','1','2','0','0','1720.81','629.09','28.4554','3.0503','25','0','0','1','0','0','0'),
('9000105','38047','580','1','2','0','0','1720.68','626.748','28.4518','2.87751','25','0','0','1','0','0','0'),
('9000106','38047','580','1','2','0','0','1722.91','626.145','28.2761','2.94035','25','0','0','1','0','0','0'),
('9000107','38047','580','1','2','0','0','1722.57','631.079','28.2991','3.42337','25','0','0','1','0','0','0'),
('9000108','38047','580','1','2','0','0','1721.99','627.466','28.5332','3.14848','25','0','0','1','0','0','0'),
('9000109','38047','580','1','2','0','0','1721.32','625.256','28.5738','2.90893','25','0','0','1','0','0','0'),
('9000110','38047','580','1','2','0','0','1721.91','628.677','28.5338','3.06601','25','0','0','1','0','0','0'),
('9000112','38047','580','1','2','0','0','1681.24','628.755','27.6643','0.000467','25','0','0','1','0','0','0'),
('9000113','38047','580','1','2','0','0','1712.51','617.948','27.5815','2.52644','25','0','0','1','0','0','0'),
('9000114','38047','580','1','2','0','0','1706.46','612.97','27.5613','2.15102','25','0','0','1','0','0','0'),
('9000115','38047','580','1','2','0','0','1707.64','613.113','27.6534','1.79367','25','0','0','1','0','0','0'),
('9000116','38047','580','1','2','0','0','1715.9','628.819','27.5439','3.21524','25','0','0','1','0','0','0'),
('9000117','38047','580','1','2','0','0','1697.23','645.214','27.587','5.16302','25','0','0','1','0','0','0'),
('9000118','38047','580','1','2','0','0','1684.66','638.459','27.733','5.57535','25','0','0','1','0','0','0'),
('9000119','38047','580','1','2','0','0','1680.97','633.973','27.8796','6.05052','25','0','0','1','0','0','0'),
('9000120','37763','580','1','2','0','0','1664.15','638.689','28.0503','5.72144','25','0','0','1117800','63100','0','0'),
('9000121','37764','580','1','2','0','0','1665.03','641.375','28.0503','5.52116','25','0','0','5578000','127740','0','0'),
('9000122','37781','580','1','2','0','0','1788.1','678.585','71.2402','3.58516','25','0','0','37800','0','0','0'),
('9000123','37781','580','1','2','0','0','1764.88','662.995','71.2402','0.502474','25','0','0','37800','0','0','0'),
('9000124','37781','580','1','2','0','0','1768.8','651.43','71.2402','0.262927','25','0','0','37800','0','0','0'),
('9000125','37781','580','1','2','0','0','1776.36','647.937','71.2483','1.83373','25','0','0','37800','0','0','0'),
('9000126','37781','580','1','2','0','0','1783.29','653.179','71.2479','2.11647','25','0','0','37800','0','0','0'),
('9000127','37781','580','1','2','0','0','1789.56','657.405','71.248','1.81802','25','0','0','37800','0','0','0'),
('9000128','37781','580','1','2','0','0','1794.15','660.965','71.2442','1.93975','25','0','0','37800','0','0','0'),
('9000129','37781','580','1','2','0','0','1850.66','606.202','71.348','2.54451','25','0','0','37800','0','0','0'),
('9000130','37781','580','1','2','0','0','1842.55','595.526','71.3444','2.41492','25','0','0','37800','0','0','0'),
('9000131','37781','580','1','2','0','0','1793.1','668','71.2402','3.71868','25','0','0','37800','0','0','0'),
('9000132','37781','580','1','2','0','0','1776.23','628.955','71.2434','0.160822','25','0','0','37800','0','0','0'),
('9000133','37781','580','1','2','0','0','1805.48','651.509','71.2604','3.7226','25','0','0','37800','0','0','0'),
('9000134','37781','580','1','2','0','0','1772.03','695.032','71.2402','3.86398','25','0','0','37800','0','0','0'),
('9000135','37781','580','1','2','0','0','1751.88','683.106','71.2403','0.498543','25','0','0','37800','0','0','0'),
('9000136','37781','580','1','2','0','0','1755.33','708.176','71.2403','3.84434','25','0','0','37800','0','0','0'),
('9000137','37781','580','1','2','0','0','1728.78','698.637','71.2403','1.20147','25','0','0','37800','0','0','0'),
('9000138','37781','580','1','2','0','0','1732.5','717.096','71.2403','4.39018','25','0','0','37800','0','0','0'),
('9000139','38056','580','1','2','0','0','1663.21','636.039','28.0503','5.42017','25','0','0','1','0','0','0'),
('9000140','37781','580','1','2','0','0','1652.86','651.055','28.0512','5.86438','25','0','0','37800','0','0','0'),
('9000141','37781','580','1','2','0','0','1656.86','657.706','28.0505','5.70338','25','0','0','37800','0','0','0'),
('9000142','37781','580','1','2','0','0','1670.33','633.458','28.0503','5.88564','25','0','0','37800','0','0','0'),
('9000143','37781','580','1','2','0','0','1671.83','638.736','28.0503','5.866','25','0','0','37800','0','0','0'),
('9000144','37781','580','1','2','0','0','1680.03','606.098','28.0502','1.02245','25','0','0','37800','0','0','0'),
('9000145','37781','580','1','2','0','0','1683.77','604.276','28.0502','0.928201','25','0','0','37800','0','0','0'),
('9000146','38052','580','1','2','0','0','1716.5','632.353','27.7478','5.79606','25','0','0','1','0','0','0'),
('9000147','37000','580','1','2','0','0','1698.65','628.499','27.6179','0.302208','25','0','0','1','0','0','0'),
('9000148','37765','580','1','2','0','0','1686.09','602.996','28.1002','1.06011','25','0','0','9215','0','0','0'),
('9000149','36991','580','1','2','0','0','1623.19','612.56','33.3712','1.80546','25','0','0','18430','0','0','0'),
('9000150','36991','580','1','2','0','0','1651.65','640.577','28.1503','5.9877','25','0','0','18430','0','0','0'),
('9000151','36991','580','1','2','0','0','1681.74','676.065','28.1002','4.86851','25','0','0','18430','0','0','0'),
('9000152','36991','580','1','2','0','0','1646.8','611.88','30.6566','0.525261','25','0','0','18430','0','0','0'),
('9000153','36991','580','1','2','0','0','1658.12','594.204','30.6539','0.650926','25','0','0','18430','0','0','0'),
('9000154','36991','580','1','2','0','0','1676.72','581.12','31.1066','1.02006','25','0','0','18430','0','0','0'),
('9000155','36991','580','1','2','0','0','1694.82','577.46','30.638','2.05286','25','0','0','18430','0','0','0'),
('9000156','36991','580','1','2','0','0','1708.7','583.686','28.1002','1.81724','25','0','0','18430','0','0','0'),
('9000157','36991','580','1','2','0','0','1743.17','611.001','28.1002','2.67332','25','0','0','18430','0','0','0');

DELETE FROM spell_target_position WHERE id = 70746;
INSERT INTO spell_target_position (id, target_map,target_position_x, target_position_y,target_position_z,target_orientation) VALUES
(70746,580,1771,676.5,71.2,2.25);

-- Quel'Delar Phase Shift
DELETE FROM spell_area WHERE spell = 70193 AND AREA = 4075;
INSERT INTO spell_area (spell,AREA,quest_start,quest_start_active,quest_end,autocast) VALUES
(70193,4075,24553,1,24553,1),
(70193,4075,24564,1,24564,1),
(70193,4075,24594,1,24594,1),
(70193,4075,24595,1,24595,1),
(70193,4075,24596,1,24596,1),
(70193,4075,24598,1,24598,1);

UPDATE creature_template SET Scale = 10, ScriptName = "npc_sunwell_bunny" WHERE entry = 37000;

DELETE FROM spell_script_target WHERE entry IN (70466,70477,70548);
INSERT INTO spell_script_target (entry,TYPE,targetentry) VALUES
(70466,1,37745), -- SPELL_SUNWELL_LIGHTRAY AURA - target on Quel'Delar spelltarget bunny
(70477,1,37000), -- Cleanse Quel'Delar - target on Sunwell Vis Bunny
(70548,1,37000); -- Cleanse Quel'Delar - target on Sunwell Vis Bunny

DELETE FROM dbscripts_on_event WHERE id = 22833;
INSERT INTO dbscripts_on_event (id,command,datalong,datalong2,comments) VALUES
(22833,9,72796,360,"Tainted Quel'Delar - respawn QuelDalar");

DELETE FROM script_texts WHERE entry BETWEEN -1574998 AND -1574970;
INSERT INTO script_texts (entry,COMMENT,content_default,TYPE,emote) VALUES
-- Randomly, Liadrin makes a statement to some gathered Pilgrims:
("-1574970","Lady Liadrin says","My brothers and sisters, words cannot describe what I felt upon seeing the Sunwell rekindled.",0,1),
("-1574971","Lady Liadrin says","In that moment, the Light revealed to me the truth of the terrible things I had done.",0,1),
("-1574972","Lady Liadrin says","Our people had walked a dark path and mine was among the darkest of them all.",0,1),
("-1574973","Lady Liadrin says","But the Light showed me that I was not lost. It helped me to find the strength to survive in spite of all that had happened and all the evil I had wrought.",0,1),
("-1574974","Lady Liadrin says","It is a strength that we sin'dorei all share. It is a strength we will need to free ourselves of the addiction ravaging our people.",0,1),
("-1574975","Lady Liadrin says","It will be the most difficult battle we have ever faced, but our resolve and the power of the Sunwell will sustain us until we have been restored to our greatness.",0,1),
("-1574976","Blood Elf Pilgrim says","Well said, my lady. We sin'dorei will be free and we shall be great again.",0,1),
-- Upon Enetring Room
("-1574977","Chamberlain Galiros yells","My lords and ladies, I present $N, bearer of Quel'Delar.",1,1),
-- Upon throwing in the sword on the southeast side of the Sunwell
("-1574978","Sunwell Honor Guard says","Can that really be Quel\'Delar?",0,1),
("-1574979","Lor\'themar Theron says","We shall see.",0,1),
("-1574980","Grand Magister Rommath says","Look at it, Lor'themar. It is certainly Quel'Delar.",0,1),
# NON-BLOOD ELVES LINE#
("-1574981","Lor'themar Theron says","So it is. You have my thanks, $N, for restoring Quel'Delar to its rightful owners.",0,1),
-- Theron walks up to the blade and grabs it","He is thrown across the room by the blade, knocking him to roughly half-health
("-1574982","Sunwell Honor Guard yells","My Lord Regent! What have they done to you?",1,1),
-- Rommath freezes the player in an Icy Prison and guards approach from all directions
("-1574983","Grand Magister Rommath says","What is the meaning of this treachery?",0,1),
("-1574984","Sunwell Honor Guard yell","Drop your weapon and surrender, traitor!",1,1),
("-1574985","Captain Auric Sunchaser says","This is not my doing, Rommath. There is no treachery here.",0,1),
("-1574986","Captain Auric Sunchaser says","Call off your men. Lor'themar's own foolishness caused his injuries. Quel'Delar is not chosen; it chooses its master.",0,1),
("-1574987","Grand Magister Rommath says","It seems the captain is correct. Quel'Delar is not to be ours after all.",0,1),
("-1574988","Grand Magister Rommath says","Guards, return to your posts.",0,1),
-- The Icy Prison fades
("-1574989","Grand Magister Rommath says","You will have what you have come for, $N. Take the sword and begone. And you, Auric, have a care for what you say in this sacred place.",0,1),
("-1574990","Captain Auric Sunchaser says","Carry the sword back to Dalaran through that portal, $N. You have done what many quel'dorei have dreamt of for years. Quel'Delar has been restored at last.",0,1),
# BLOOD ELVES LINE#
("-1574991","Lor'themar Theron says","It is indeed Quel'Delar. I had not thought I'd live to see the day when Thalorien Dawnseeker's legendary sword would be restored to us.",0,1),
("-1574992","Lor'themar Theron says","You are a hero and an inspiration to the sin'dorei, $N, a symbol of our endurance in the face of tragedy and treachery.",0,2),
("-1574993","Grand Magister Rommath says","The regent speaks truly, %N. Thalorien's sacrifice could not prevent the fall of this very Sunwell.",0,1),
("-1574994","Grand Magister Rommath says","When you found the sword, it was broken and abandoned, much like Silvermoon after Kael'thas's betrayal.",0,1),
("-1574995","Grand Magister Rommath says","Let Quel'delar be a sign that we will never give up, that we will face any enemy without fear.",0,1),
("-1574996","Captain Auric Sunchaser says","Quel'delar is not held in high esteem by the sin'dorei alone. It holds a place in the heart of all children of Silvermoon.",0,1),
("-1574997","Captain Auric Sunchaser says","This blade has been returned to us for a reason, my lords. Now is the time to rally behind the bearer of Quel'delar and avenge the destruction of Silvermoon and the Sunwell.",0,1),
("-1574998","Grand Magister Rommath says","Reclaim the sword, $N, and bear it through the portal to Dalaran. Archmage Aethas Sunreaver will be waiting to congratulate you.",0,1);
