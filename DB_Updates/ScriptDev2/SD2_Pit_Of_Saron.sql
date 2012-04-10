-- Intro
DELETE FROM `script_texts` WHERE `entry` IN (-1658070, -1658071, -1658072, -1658073, -1658074, -1658075, -1658076, -1658077, -1658078, -1658080, -1658081);
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658070, "Intruders have entered the master's domain. Signal the alarms!", 0, 1, 0, 0, 'Tyrranus SAY_TYRANNUS_1');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658071, "Hrmph, fodder. Not even fit to labor in the quarry. Relish these final moments for soon you will be nothing more than mindless undead.", 0, 1, 0, 0, 'Tyrranus SAY_TYRANNUS_2');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658072, "Heroes of the Alliance, attack!", 16626, 1, 0, 0, 'Jaina SAY_JAINA_1');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658073, "You last waking memory will be of agonizing pain.", 0, 1, 0, 0, 'Tyrranus SAY_TYRANNUS_3');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658074, "NO! YOU MONSTER!", 16627, 1, 0, 0, 'Jaina SAY_JAINA_2');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658075, "Minions, destroy these interlopers!", 0, 1, 0, 0, 'Tyrranus SAY_TYRANNUS_4');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658076, "I do what I must. Please forgive me, noble soldiers.!", 16628, 0, 0, 0, 'Jaina SAY_JAINA_3');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658077, "You will have to make your way across this quarry on your own.!", 16629, 0, 0, 0, 'Jaina SAY_JAINA_4');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658078, "Free any Alliance slaves that you come across. We will most certainly need their assistance in battling Tyrannus. I will gather reinforcements and join you on the other side of the quarry.!", 16630, 0, 0, 0, 'Jaina SAY_JAINA_5');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658080, "Free any Horde slaves that you come across. We will most certainly need their assistance in battling Tyrannus. I will gather reinforcements and join you on the other side of the quarry.!", 17048, 0, 0, 0, 'Sylvanas SAY_SYLVANAS_2');
INSERT INTO `script_texts` (`entry`, `content_default`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(-1658081, "Soldiers of the Horde, attack!!", 17045, 0, 0, 0, 'Sylvanas SAY_SYLVANAS_2');


-- krick and ick outro
DELETE from script_texts WHERE entry BETWEEN -1658044 AND -1658035;
INSERT into script_texts (entry,content_default,type,comment) VALUES
(-1658035,'Wait! Stop! Don\'t kill me, please! I\'ll tell you everything!' , 1 , 'SAY_OUTRO_KRICK_1'),
(-1658036,' I\'m not so naive as to believe your appeal for clemency, but I will listen.' , 1 ,  'SAY_OUTRO_JAINA_1'),
(-1658037,'What you seek is in the master\'s lair, but you must destroy Tyrannus to gain entry. Within the Halls of Reflection you will find Frostmourne. It... it holds the truth.',1, 'SAY_OUTRO_KRICK_2'),
(-1658038,'Frostmourne lies unguarded? Impossible!',1, 'SAY_OUTRO_JAINA_2'),
(-1658039,' I swear it is true! Please, don\'t kill me!!',1, 'SAY_OUTRO_KRICK_3'),
(-1658040,'Worthless gnat! Death is all that awaits you!',1, 'SAY_OUTRO_TYRAN_1'),
(-1658041,'Urg... no!!',1, 'SAY_OUTRO_KRICK_4'),
(-1658042,'Do not think that I shall permit you entry into my master\'s sanctum so easily. Pursue me if you dare.',1,'SAY_OUTRO_TYRAN_2'),
(-1658043, 'What a cruel end. Come, heroes. We must see if the gnome\'s story is true. If we can separate Arthas from Frostmourne, we might have a chance at stopping him.' ,1, 'SAY_OUTRO_JAINA_3'),
(-1658044, 'Your pursuit shall be in vain, adventurers, for the Lich King has placed an army of undead at my command! Behold!.',1, 'SAY_OUTRO_TYRAN_3');
