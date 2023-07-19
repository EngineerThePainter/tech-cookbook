local function max(num1, num2)
    if (num1 > num2) then
        return num1
    else
        return num2
    end
end

print("max(4,5)", max(4,5))
print("max(5,4)", max(5,4))

local my_print = function(param)
    print("my_print",param)
end

local function add(num1, num2, printingFunction)
    printingFunction(num1+num2)
    return num1+num2
end

print("add(1,2,my_print)",add(1, 2, my_print))
print("add(1,2,print)",add(1, 2, print))

local function average(...)
    result = 0
    local arg = {...}
    for i,v in ipairs(arg) do
        result = result + v
    end
    return result/#arg
end

print("The average is", average(1,2,3,4,5))