class uavMissionAccepted{
	author = "axeman";
	title = "UAV Mission Accepted";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 3;
	triggerDelay = 2;
	items[] = {"B_UavTerminal"};
	itemSpawn = 3;
	markerType = 0;
	markerRadius = 0;
	callEventBinTask = 0;
	diag1Condition = "true";
	dialogue1[] = {"The UAV terminal is at your feet, Equip it !","Pick up the terminal and equip yourself with it.","Grab the UAV terminal and put it in your GPS slot."};
	diagSquelch = 30;
	diag2Condition = "!('B_UavTerminal' in assignedItems player)";
	dialogue2[] = {"Hurry it up, pick up and equip the terminal.","Come on, Equip yourself with the terminal.","We don't have all day, get that terminal equipped."};
	abandonDist = 100;
	abandonTime = 240;
	failed[] = {"I guess you have better things to do.","Try again later.","You didn't pick up the terminal. Misison Failed !"};
	cleanUp = 0;
	completeCondition = "'B_UavTerminal' in assignedItems player";
	completed1[] = {"That's great, you have 30 seconds to find a safe position.","Find a hidden spot to operate from, take off in 30 seconds.","Find yourself a concealed position to work from, taking off in half a minute."};
	nextTask[] = {"doUAVSpawn"};
};
class doUAVSpawn{
	author = "axeman";
	title = "UAV Spawn";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 8;
	triggerDelay = 30;
	itemSpawn = 0;
	markerType = 0;
	markerRadius = 0;
	initcall = "axeUAV = objNull";
	callEventBinTask = 0;
	callEventCondition1 = "(diag_tickTime - EPOCH_task_startTime) > 6";
	callEventCALL1 = "_targetPos = (getPosATL player) findEmptyPosition [25,250,""I_UAV_01_F""];axeUAV = createVehicle[""I_UAV_01_F"", _targetPos, [], 10, ""CAN_COLLIDE""];_driver = (group player) createUnit[""I_UAV_AI"", position axeUAV, [], 0, ""CAN_COLLIDE""];_driver moveInAny axeUAV;";
	diag1Condition = "true";
	dialogue1[] = {"UAV is ready, get prepared !","Here it comes, connecting you now. 10 seconds..","Nice spot, connecting you to the UAV !"};
	diagSquelch = 60;
	failedCondition = "!('B_UavTerminal' in assignedItems player)";
	abandonDist = -1;
	abandonTime = 1200;
	failed[] = {"Lost it already.. Mission Over","Not a willing pilot eh ? Try again later.","Equipment Lost.. Mission Failed !"};
	cleanUp = 0;
	completeCondition = "!(isNull axeUAV)";
	nextTask[] = {"doUAVAttach"};
};
class doUAVAttach{
	author = "axeman";
	title = "UAV Spawn";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 16;
	triggerDelay = 6;
	itemSpawn = 0;
	markerType = 0;
	markerRadius = 0;
	initcall = "player connectTerminalToUAV axeUAV;player action [""SwitchToUAVDriver"", axeUAV];addToRemainsCollector[axeUAV];";
	callEventBinTask = 0;
	diag1Condition = "true";
	dialogue1[] = {"Woohoo, here we go.. Get it in the air.","Get it in the air, no time to waste","You are a natural kid. Let's fly."};
	diagSquelch = 60;
	failedCondition = "!('B_UavTerminal' in assignedItems player) || !(alive axeUAV)";
	abandonDist = -1;
	abandonTime = 1200;
	failed[] = {"Lost it already.. Mission Over","Not a natural pilot. Try again later.","Mission Failed !"};
	cleanUp = 0;
	completeCondition = "(getPosATL axeUAV select 2) > 10";
	completedCALL = "if(SunOrMoon < 1)then{player action [""lightOn"", axeUAV];};";
	nextTask[] = {"takeOffUAV"};
};
class takeOffUAV{
	author = "axeman";
	title = "Pilot the UAV";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 8;
	triggerDelay = 6;
	itemSpawn = 0;
	markerType = 0;
	markerRadius = 0;
	initcall = "axeUAVRndMission = floor random 2;";
	callEventBinTask = 1;
	callEventCondition1 = "(diag_tickTime - EPOCH_task_startTime > 30) && axeUAVRndMission == 0";
	callEventCondition2 = "(diag_tickTime - EPOCH_task_startTime > 30) && axeUAVRndMission == 1";
	callEventTask1 = "uavMission1";
	callEventTask2 = "uavMission2";
	diag1Condition = "alive axeUAV";
	dialogue1[] = {"Great start.. Lets take this thing for a ride.","We're off, get some practice, I am finding you a target.","Get clear of this area, I am calculating your target."};
	diagSquelch = 60;
	diag2Condition = "alive axeUAV";
	dialogue2[] = {"Keep it up, you are doing a great job.","Try and find some targets on your way.","Don't get shot down now !"};
	failedCondition = "!('B_UavTerminal' in assignedItems player) || !(alive axeUAV)";
	abandonDist = -1;
	abandonTime = 1280;
	failed[] = {"Oh dear, that didn't go well..","Try again later.","Misison Failed !"};
	cleanUp = 0;
	completeCondition = "false";
	completedCALL = "player connectTerminalToUAV objNull;";
	nextTask[] = {};
};
class uavMission1{
	author = "axeman";
	title = "Trader House Recon";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 16;
	triggerDelay = 8;
	items[] = {""};
	itemSpawn = 0;
	markerType = 2;
	markerRadius = 180;
	markerText = "Trader House Recon";
	initcall = "[] spawn {uavMission1Obj = selectRandom (nearestObjects [axeUAV,[""HOUSE""],2500]);EPOCH_taskMarkerPos = getPosATL uavMission1Obj;};";
	callEventBinTask = 0;
	diag1Condition = "true";
	dialogue1[] = {"I need some recon on a nearby house","We need intelligence on a potential trader location.","Help us gather intel on a trader house !"};
	diagSquelch = 60;
	diag2Condition = "EPOCH_taskMarkerPos distance axeUAV > 450";
	dialogue2[] = {"I have marked your map, it will be nearby.","Check you map, there is a marker near a safehouse","Search your map for the landing zone, near a traders safehouse."};
	diag3Condition = "EPOCH_taskMarkerPos distance axeUAV < 450";
	dialogue3[] = {"Land it nearby and switch off the engine.","You need to land by the house, quietly.","Drop the UAV in the marker, then keep quiet."};
	failedCondition = "!('B_UavTerminal' in assignedItems player) || !(alive axeUAV)";
	abandonDist = -1;
	abandonTime = 2200;
	failed[] = {"Oh dear, Mission Over !","Mission Failed !"};
	cleanUp = 1;
	completeCondition = "!(isengineOn axeUAV) && EPOCH_taskMarkerPos distance axeUAV < 275";
	reward[] = {"ItemGoldBar","ItemGoldBar"};
	completed1[] = {"Great work, here's your reward."};
	completedCALL = "player connectTerminalToUAV objNull;[(driver axeUAV)] joinSilent grpNull;";
};
class uavMission2{
	author = "axeman";
	title = "Deliver UAV To Trader";
	simpleTask = 0;
	taskLimit = 3;
	taskCheckTime = 16;
	triggerDelay = 8;
	itemSpawn = 0;
	markerType = 2;
	markerRadius = 220;
	markerText = "UAV Trader";
	initcall = "[] spawn {EPOCH_taskUAVTrader = selectRandom (player nearentities [[""C_Man_1""],10500] select {_x getVariable [""AI_SLOT"",-1] > -1 && player distance _x > 50});EPOCH_taskMarkerPos = getPosATL EPOCH_taskUAVTrader;};";
	callEventBinTask = 0;
	diag1Condition = "true";
	dialogue1[] = {"I need this UAV delivering to my buddy","Recon a rogue trader, land this near his location.","Land this UAV near the target trader."};
	diagSquelch = 60;
	diag2Condition = "EPOCH_taskMarkerPos distance axeUAV > 450";
	dialogue2[] = {"Check your map for his location, you will need to land nearby.","I have marked your map with his location.","Fly to the location marked on your map, then land."};
	diag3Condition = "EPOCH_taskMarkerPos distance axeUAV < 450";
	dialogue3[] = {"Get this thing down and the engine off.","Land in the zone and switch your engine off quickly.","Find a landing spot in the area and keep quiet."};
	failedCondition = "!('B_UavTerminal' in assignedItems player) || !(alive axeUAV)";
	abandonDist = -1;
	abandonTime = 2600;
	failed[] = {"Oh dear, Mission Over !","Mission Failed !"};
	cleanUp = 1;
	cleanUpCalls[] = {"player connectTerminalToUAV objNull"};
	completeCondition = "!(isengineOn axeUAV) && EPOCH_taskMarkerPos distance axeUAV < 275";
	reward[] = {"ItemGoldBar","ItemGoldBar"};
	completed1[] = {"Great work, here's your reward."};
	completedCALL = "player connectTerminalToUAV objNull;[(driver axeUAV)] joinSilent grpNull;";
};
