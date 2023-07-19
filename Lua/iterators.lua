array = {"Lua", "Tutorial"}

for key,value in ipairs(array)
do
    print(key, value)
end

print("Stateless iterators")

function square_stateless(iteratorMaxCount, currentNumber)
    if currentNumber < iteratorMaxCount
    then
        currentNumber = currentNumber + 1
        return currentNumber, currentNumber*currentNumber
    end
end

function squares_stateless(iteratorMaxCount)
    return square_stateless,iteratorMaxCount,0
end

for i, n in square_stateless,3,0
do 
    print(i, n)
end

for i, n in squares_stateless(3)
do
    print(i,n)
end

print("Stateful iterators")

function element_iterator(collection)
    local index = 0
    local count = #collection
    
    -- The closure function is returned 
    return function()
        index = index + 1
        if index <= count
        then
            return collection[index]
        end
    end
end

for element in element_iterator(array)
do
    print(element)
end