print("SM Script Start!!")  

menuEvent = {}
gameStartEvent = {}
finishEvent = {}
restartEvent = {}

function menuEvent.action()
	print("LUA menuEvent action! ")
end
function gameStartEvent.action()
	print("LUA gameStartEvent action! ")
end
function finishEvent.action()
	print("LUA finishEvent action! ")
end
function restartEvent.action()
	print("LUA restartEvent action! ")
end
--/////////////////////////////////

gameIntroState = {}
menuState = {}
gameLoopState = {}
finishGameState = {}

function gameIntroState.onEntry(sm)
	print("LUA gameIntroState onEntry! ")
	print(tostring(sm))
print("type is "..tolua.type(sm))

    pl_window:createWindow("Test1", 1280, 800, 0);
	
	local context = getContext()
	gameIntroState.scene = Scene:new(context)
	gameIntroState.scene:initialize()
	gameIntroState.scene:load("E:/code/ElfClion/ElfBox/res/GameIntro.tmx")	
	gameIntroState.scene:startToDraw()

	gameIntroState.counter = 0
end
function gameIntroState.onUpdate(sm, timeStep)
    --print("LUA gameIntroState onUpdate! ")
	gameIntroState.counter = gameIntroState.counter + (1000 * timeStep);
	if (gameIntroState.counter > 1000) then
		local e = StateEvent:new("menuEvent")
		pl_stateMachine:prcessEvent(e)
	end
	
	gameIntroState.scene:update(timeStep)
end
function gameIntroState.onExit(sm)
	print("LUA gameIntroState onExit! ")
	pl_renderDevice:clearDrawable()
end

--/////////////////////////////////
function menuState.onEntry(sm)
	print("LUA menuState onEntry! ")
	
	local context = getContext()
	menuState.scene = Scene:new(context)
	menuState.scene:initialize()
	menuState.scene:load("E:/code/ElfClion/ElfBox/res/map.tmx")
	menuState.scene:startToDraw()
end
function menuState.onUpdate(sm, timeStep)
	--print("LUA menuState onUpdate!11111 ")
	--local eOff = StateEvent:new("turnOffEvent")
    --stateMachine:prcessEvent(eOff)
	--print("LUA menuState onUpdate!22222 ")
	menuState.scene:update(timeStep)
end
function menuState.onExit(sm)
	print("LUA menuState onExit! ")
end

--/////////////////////////////////
function gameLoopState.onEntry(sm)
	print("LUA gameLoopState onEntry! ")
end
function gameLoopState.onUpdate(timeStep, sm)
	print("LUA gameLoopState onUpdate!1111 ")
	--local eOn = StateEvent:new("turnOnEvent")
    --stateMachine:prcessEvent(eOn)
	print("LUA gameLoopState onUpdate!2222 ")
end
function gameLoopState.onExit(sm)
	print("LUA gameLoopState onExit! ")
end

--/////////////////////////////////
function finishGameState.onEntry(sm)
	print("LUA finishGameState onEntry! ")
end
function finishGameState.onUpdate(timeStep, sm)
	print("LUA finishGameState onUpdate!1111 ")
	--local eOn = StateEvent:new("turnOnEvent")
    --stateMachine:prcessEvent(eOn)
	print("LUA finishGameState onUpdate!2222 ")
end
function finishGameState.onExit(sm)
	print("LUA finishGameState onExit! ")
end

print("SM Script END!!")