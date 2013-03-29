/************************** MaNGOS DB *************************/
UPDATE creature_template SET ScriptName = "npc_hor_altar_bunny" WHERE entry = 37704;
UPDATE creature_template SET ScriptName = "" WHERE entry = 37158;
DELETE FROM creature WHERE id = 37158;

/************************** ScriptDev2 *************************/
DELETE FROM script_texts WHERE entry BETWEEN -1574947 AND -1574940;
INSERT INTO script_texts (entry,COMMENT,content_default,TYPE,sound) VALUES
-- Upon entering Sword's Rest in the Halls of Reflection and approaching Frostmourne while under Quel'Delar's Compulsion:
(-1574940,"Uther the Lightbringer yells","Halt! Do not carry that blade any further!",1,16675),
(-1574941,"Quel'Delar","Quel'Delar leaps to life in the presence of Frostmourne!",3,0),
(-1574942,"Uther the Lightbringer yells","Do you realize what you've done?",1,16676),
(-1574943,"Quel'Delar","Quel'Delar prepares to attack!",3,0),
-- After defeating the sword:
(-1574944,"Uther the Lightbringer says","You have forged this blade from saronite, the very blood of an old god. The power of the Lich King calls to this weapon.",0,16677),
(-1574945,"Uther the Lightbringer says","Each moment you tarry here Quel'Delar drinks in the evil of this place.",0,16678),
(-1574946,"Uther the Lightbringer says","There is only one way to cleanse the sword. Make haste for the Sunwell and immerse the blade in its waters.",0,16679),
(-1574947,"Uther the Lightbringer says","I can resist Frostmourne's call no more...",0,16680);
-- Uther fades away
