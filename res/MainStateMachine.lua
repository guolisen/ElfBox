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

function gameIntroState.onEntry()
	print("LUA gameIntroState onEntry! ")
    pl_window:createWindow("Test1", 1024, 768, 0);
	
	local context = getContext()
	print(tostring(context))
	print("type is "..tolua.type(context))
	
	gameIntroState.scene = Scene:new(context)
	gameIntroState.scene:initialize()
	gameIntroState.scene:load("E:/code/s/map/T22.tmx")
	gameIntroState.scene:update(0.0)
end
function gameIntroState.onUpdate()
    --print("LUA gameIntroState onUpdate! ")
end
function gameIntroState.onExit()
	print("LUA gameIntroState onExit! ")
end

--/////////////////////////////////
function menuState.onEntry()
	print("LUA menuState onEntry! ")
end
function menuState.onUpdate()
	print("LUA menuState onUpdate!11111 ")
	--local eOff = StateEvent:new("turnOffEvent")
    --stateMachine:prcessEvent(eOff)
	print("LUA menuState onUpdate!22222 ")
end
function menuState.onExit()
	print("LUA menuState onExit! ")
end

--/////////////////////////////////
function gameLoopState.onEntry()
	print("LUA gameLoopState onEntry! ")
end
function gameLoopState.onUpdate()
	print("LUA gameLoopState onUpdate!1111 ")
	--local eOn = StateEvent:new("turnOnEvent")
    --stateMachine:prcessEvent(eOn)
	print("LUA gameLoopState onUpdate!2222 ")
end
function gameLoopState.onExit()
	print("LUA gameLoopState onExit! ")
end

--/////////////////////////////////
function finishGameState.onEntry()
	print("LUA finishGameState onEntry! ")
end
function finishGameState.onUpdate()
	print("LUA finishGameState onUpdate!1111 ")
	--local eOn = StateEvent:new("turnOnEvent")
    --stateMachine:prcessEvent(eOn)
	print("LUA finishGameState onUpdate!2222 ")
end
function finishGameState.onExit()
	print("LUA finishGameState onExit! ")
end

print("SM Script END!!")