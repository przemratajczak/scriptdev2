/********************** MaNGOS DB **********************/
-- set injured matriarch as spell_click creature, no other flags needed
UPDATE creature_template SET npcflag = 16777216 WHERE entry = 29563;

DELETE FROM npc_spellclick_spells WHERE npc_entry = 29563;
INSERT INTO npc_spellclick_spells (npc_entry, spell_id, quest_start,quest_start_active,quest_end,cast_flags) VALUES
(29563, 56795, 12983, 1, 12983, 1)

/********************** ScriptDev2 DB ******************/
DELETE FROM script_waypoint WHERE entry = 30468;
INSERT INTO script_waypoint (entry,pointid,location_x,location_y,location_z) VALUES
('30468','0','7334.74','-2058.52','764.333'),
('30468','1','7334.86','-2065.04','765.365'),
('30468','2','7335.02','-2072.04','766.731'),
('30468','3','7335.04','-2079.03','768.892'),
('30468','4','7332.9','-2089.59','771.294'),
('30468','5','7328.07','-2095.41','772.91'),
('30468','6','7321.58','-2099.79','774.279'),
('30468','7','7315.23','-2102.73','774.086'),
('30468','8','7305.5','-2106.68','774.285'),
('30468','9','7299.04','-2109.38','774.743'),
('30468','10','7288.22','-2112.47','775.561'),
('30468','11','7277.72','-2112.46','775.286'),
('30468','12','7270.75','-2112.86','776.136'),
('30468','13','7264.1','-2113.17','777.783'),
('30468','14','7259.55','-2113.94','778.21'),
('30468','15','7254.83','-2118.1','779.079'),
('30468','16','7247.43','-2121.99','778.397'),
('30468','17','7240.69','-2120.09','777.672'),
('30468','18','7233.96','-2118.19','777.462'),
('30468','19','7227.23','-2116.28','777.435'),
('30468','20','7220.43','-2114.61','775.961'),
('30468','21','7211.59','-2112.48','772.363'),
('30468','22','7207.52','-2110.78','770.346'),
('30468','32','7174.01','-2125.34','763.095'),
('30468','31','7179.74','-2121.31','763.052'),
('30468','30','7188.36','-2115.32','764.041'),
('30468','29','7193.18','-2111.46','765.82'),
('30468','28','7202.61','-2110.35','768.329'),
('30468','33','7164.92','-2130.41','762.092'),
('30468','34','7158.27','-2132.59','762.436'),
('30468','35','7147.44','-2135.21','761.771'),
('30468','36','7140.03','-2133.2','761.473'),
('30468','37','7133.5','-2128.27','761.208'),
('30468','38','7128','-2121.96','760.829'),
('30468','39','7121.96','-2113.37','760.841'),
('30468','40','7117.1','-2104.16','761.668'),
('30468','41','7115.47','-2096.43','762.171'),
('30468','42','7113.93','-2086.06','763.396'),
('30468','43','7111.41','-2075.87','764.836'),
('30468','44','7109.69','-2069.08','765.387'),
('30468','45','7105.48','-2055.73','765.738'),
('30468','46','7103.32','-2049.08','766.431'),
('30468','47','7099.93','-2039.14','766.693'),
('30468','48','7096.54','-2029.2','766.816'),
('30468','49','7093.15','-2019.27','767.254'),
('30468','50','7089.76','-2009.33','768.299'),
('30468','51','7086.37','-1999.39','768.575'),
('30468','52','7084.11','-1992.77','768.305'),
('30468','53','7080.68','-1982.85','768.105'),
('30468','54','7076.94','-1973.04','767.945'),
('30468','55','7074.65','-1966.43','768.541'),
('30468','56','7071.25','-1956.5','769.523'),
('30468','57','7069.23','-1949.79','771.125'),
('30468','58','7066.61','-1939.63','773.907'),
('30468','59','7065.22','-1932.78','775.71'),
('30468','60','7063.43','-1923.61','779.061'),
('30468','61','7064.23','-1912.95','783.636'),
('30468','62','7068.28','-1908.46','785.152'),
('30468','63','7074','-1904.43','786.075'),
('30468','64','7081.45','-1899.03','787.038'),
('30468','65','7085.27','-1892.66','788.053'),
('30468','66','7083.72','-1887.55','789.304'),
('30468','67','7079.68','-1884.75','790.617'),
('30468','68','7072.76','-1883.71','791.949'),
('30468','69','7065.76','-1883.98','793.362'),
('30468','70','7058.77','-1884.25','795.137'),
('30468','71','7051.77','-1884.52','796.531'),
('30468','72','7042.47','-1884.39','797.421'),
('30468','73','7036.21','-1882.73','798.967'),
('30468','74','7030.35','-1878.46','801.207'),
('30468','75','7026.67','-1870.72','804.448'),
('30468','76','7026.08','-1867.28','806.235'),
('30468','77','7025.14','-1860.35','810.398'),
('30468','78','7024.48','-1853.38','814.409'),
('30468','79','7024.47','-1849.88','816.222'),
('30468','80','7022.6','-1840.53','819.664'),
('30468','81','7020.43','-1835.25','820.541'),
('30468','82','7018.46','-1828.53','820.684'),
('30468','83','7016.74','-1821.75','820.67'),
('30468','84','7015.37','-1814.88','820.669'),
('30468','85','7014.28','-1807.97','820.669'),
('30468','86','7013.19','-1801.05','820.669'),
('30468','87','7011.76','-1794.2','820.679'),
('30468','88','7010.05','-1787.78','820.851'),
('30468','89','7010.47','-1780.79','820.264'),
('30468','90','7011.27','-1770.32','819.717'),
('30468','91','7012.37','-1763.41','819.523'),
('30468','92','7013.47','-1756.5','819.302'),
('30468','93','7014.43','-1749.57','819.471'),
('30468','94','7015.4','-1742.63','819.911'),
('30468','95','7016.06','-1736.6','819.737'),
('30468','96','7015.2','-1728.44','819.831'),
('30468','97','7012.33','-1723.67','819.797'),
('30468','98','7005.31','-1720.17','819.923'),
('30468','99','7001.94','-1719.9','820.009'),
('30468','119','6821.63','-1702.9','820.619'),
('30468','118','6831.72','-1703.44','820.731'),
('30468','117','6839.92','-1701.35','820.659'),
('30468','116','6849.41','-1696.86','820.206'),
('30468','115','6858.9','-1692.35','820.234'),
('30468','114','6865.34','-1689.64','820.251'),
('30468','113','6874.18','-1687.6','820.318'),
('30468','112','6883.46','-1687.26','820.43'),
('30468','111','6893.27','-1690.24','820.466'),
('30468','110','6902.42','-1695.38','820.641'),
('30468','109','6910.83','-1701.67','820.612'),
('30468','108','6919.22','-1707.98','820.621'),
('30468','107','6927.6','-1714.3','820.69'),
('30468','106','6935.45','-1718.47','820.591'),
('30468','105','6945.46','-1721.65','820.568'),
('30468','104','6955.04','-1723.59','820.6'),
('30468','103','6966.05','-1724.61','820.644'),
('30468','102','6974.29','-1724.01','820.682'),
('30468','101','6984.68','-1722.48','820.752'),
('30468','100','6995.43','-1721.06','820.197');