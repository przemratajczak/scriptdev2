DELETE FROM creature WHERE id IN (11480,11483);
SET @guid = 9000200;
INSERT INTO `creature`  (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`)  VALUES
(@guid,'11480','429','1','1','0','0','0.18435','277.584','-8.35593','3.03687','7200','0','0','7107','9476','0','0'),
(@guid+1,'11480','429','1','1','0','0','22.2903','268.93','-7.75637','5.61996','7200','0','0','7107','9476','0','0'),
(@guid+2,'11480','429','1','1','0','0','13.7393','290.024','-8.81422','1.43117','7200','0','0','7107','9476','0','0'),
(@guid+3,'11480','429','1','1','0','0','109.187','432.731','28.6844','2.93215','7200','0','0','7107','9476','0','0'),
(@guid+4,'11480','429','1','1','0','0','116.239','417.468','28.6844','4.41568','7200','0','0','7107','9476','0','0'),
(@guid+5,'11480','429','1','1','0','0','126.612','440.825','28.6844','1.18682','7200','0','0','7107','9476','0','0'),
(@guid+6,'11480','429','1','1','0','0','-79.4082','437.517','28.6859','5.61996','7200','0','0','7107','9476','0','0'),
(@guid+7,'11480','429','1','1','0','0','-86.4111','454.612','28.6864','1.18682','7200','0','0','7107','9476','0','0'),
(@guid+8,'11480','429','1','1','0','0','-98.4999','429.365','28.6854','4.20624','7200','0','0','7107','9476','0','0'),
(@guid+9,'11480','429','1','1','0','0','78.1069','724.323','-24.4956','4.67748','7200','0','0','7107','9476','0','0'),
(@guid+10,'11480','429','1','1','0','0','89.8462','745.194','-24.497','0.715585','7200','0','0','7107','9476','0','0'),
(@guid+11,'11480','429','1','1','0','0','64.6404','736.824','-24.497','3.33358','7200','0','0','7107','9476','0','0'),
(@guid+12,'11480','429','1','1','0','0','-154.641','721.118','-24.4952','4.64258','7200','0','0','7107','9476','0','0'),
(@guid+13,'11480','429','1','1','0','0','-142.956','743.886','-24.497','0.715585','7200','0','0','7107','9476','0','0'),
(@guid+14,'11480','429','1','1','0','0','-170.839','735.324','-24.497','3.14159','7200','0','0','7107','9476','0','0'),
(@guid+16,'11480','429','1','1','0','0','133.537','434.405','28.6844','0.471239','7200','0','0','7107','9476','0','0'),
(@guid+17,'11483','429','1','1','0','0','4.51283','268.919','-8.03384','3.83972','7200','0','0','6681','8964','0','0'),
(@guid+18,'11483','429','1','1','0','0','13.3353','265.504','-7.47873','4.85202','7200','0','0','6681','8964','0','0'),
(@guid+19,'11483','429','1','1','0','0','24.4087','277.987','-8.40844','6.0912','7200','0','0','6681','8964','0','0'),
(@guid+20,'11483','429','1','1','0','0','22.2632','286.032','-8.67728','0.855211','7200','0','0','6681','8964','0','0'),
(@guid+21,'11483','429','1','1','0','0','4.86775','286.17','-8.49644','2.51327','7200','0','0','6681','8964','0','0'),
(@guid+22,'11483','429','1','1','0','0','116.572','441.026','28.6844','1.90241','7200','0','0','6681','8964','0','0'),
(@guid+23,'11483','429','1','1','0','0','109.499','423.1','28.6844','3.31613','7200','0','0','6681','8964','0','0'),
(@guid+24,'11483','429','1','1','0','0','126.092','416.945','28.6844','4.99164','7200','0','0','6681','8964','0','0'),
(@guid+25,'11483','429','1','1','0','0','133.068','423.411','28.6844','5.93412','7200','0','0','6681','8964','0','0'),
(@guid+27,'11483','429','1','1','0','0','-86.7868','430.229','28.6855','4.83456','7200','0','0','6681','8964','0','0'),
(@guid+28,'11483','429','1','1','0','0','-79.6795','447.35','28.6859','0.401426','7200','0','0','6681','8964','0','0'),
(@guid+29,'11483','429','1','1','0','0','-97.6146','454.302','28.6873','2.21657','7200','0','0','6681','8964','0','0'),
(@guid+30,'11483','429','1','1','0','0','-104.249','447.252','28.6878','2.75762','7200','0','0','6681','8964','0','0'),
(@guid+31,'11483','429','1','1','0','0','-104.42','436.883','28.6865','3.36848','7200','0','0','6681','8964','0','0'),
(@guid+32,'11483','429','1','1','0','0','87.2501','727.643','-24.497','5.16617','7200','0','0','6681','8964','0','0'),
(@guid+33,'11483','429','1','1','0','0','91.785','737.786','-24.497','0','7200','0','0','6681','8964','0','0'),
(@guid+34,'11483','429','1','1','0','0','78.097','749.842','-24.497','1.41372','7200','0','0','6681','8964','0','0'),
(@guid+35,'11483','429','1','1','0','0','68.7335','747.766','-24.497','2.33874','7200','0','0','6681','8964','0','0'),
(@guid+36,'11483','429','1','1','0','0','68.4746','728.471','-24.4956','3.9619','7200','0','0','6681','8964','0','0'),
(@guid+37,'11483','429','1','1','0','0','-146.109','724.521','-24.4951','5.48033','7200','0','0','6681','8964','0','0'),
(@guid+38,'11483','429','1','1','0','0','-140.277','734.367','-24.4966','6.07375','7200','0','0','6681','8964','0','0'),
(@guid+39,'11483','429','1','1','0','0','-154.064','748.169','-24.497','1.50098','7200','0','0','6681','8964','0','0'),
(@guid+40,'11483','429','1','1','0','0','-165.33','746.258','-24.497','2.19912','7200','0','0','6681','8964','0','0'),
(@guid+41,'11483','429','1','1','0','0','-164.966','724.302','-24.4968','3.78736','7200','0','0','6681','8964','0','0');
