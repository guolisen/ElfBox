print("SM Script Start!!")  

startEvent = {}
turnOnEvent = {}
turnOffEvent = {}

function startEvent.action()
	print("LUA startEvent action! ")
end
function turnOnEvent.action()
	print("LUA turnOnEvent action! ")
end
function turnOffEvent.action()
	print("LUA turnOffEvent action! ")
end

--/////////////////////////////////
stateStart = {}
stateOn = {}
stateOff = {}

function stateStart.onEntry()
	print("LUA stateStart onEntry! ")
end
function stateStart.onUpdate()
	print("LUA stateStart onUpdate! ")
end
function stateStart.onExit()
	print("LUA stateStart onExit! ")
end

--/////////////////////////////////
function stateOn.onEntry()
	print("LUA stateOn onEntry! ")

end
function stateOn.onUpdate()
	print("LUA stateOn onUpdate!11111 ")
	local eOff = StateEvent:new("turnOffEvent")
    stateMachine:prcessEvent(eOff)
	print("LUA stateOn onUpdate!22222 ")
end
function stateOn.onExit()
	print("LUA stateOn onExit! ")
end

--/////////////////////////////////
function stateOff.onEntry()
	print("LUA stateOff onEntry! ")
end
function stateOff.onUpdate()
	print("LUA stateOff onUpdate!1111 ")
	local eOn = StateEvent:new("turnOnEvent")
    stateMachine:prcessEvent(eOn)
	print("LUA stateOff onUpdate!2222 ")
end
function stateOff.onExit()
	print("LUA stateOff onExit! ")
end

print("SM Script END!!")