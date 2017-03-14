print("Hello Lua!!")  

t = {}

function t.test1(mode)
	print("Hello! " .. mode)
end

function testfunc(param1, param2)

print("Hello Lua function!!" .. param1 .. " " .. param2)  
end


--local contextVar = elfbox.common.Context:new()
--contextVar.addComponent("dasd")
--local yuu = contextVar.getComponent("dasd")


print("!!!!!!!!stateMachine!!!!!!!")
pl_stateMachine:load("E:/code/ElfClion/ElfBox/res/MainStateMachine.xml")
pl_stateMachine:start()

local e = StateEvent:new("startEvent")
pl_stateMachine:prcessEvent(e)

pl_stateMachine:update(1.0)
pl_stateMachine:update(1.0)
--local eOn = StateEvent:new("turnOnEvent")
--stateMachine:prcessEvent(eOn)

--local eOff = StateEvent:new("turnOffEvent")
--stateMachine:prcessEvent(eOff)
print("!!!!!!!!stateMachine!!!!!!!")



print("TEST END!!!")