print("While loop")
while_index = 0

while(while_index < 20)
do
    print("While",while_index)
    while_index= while_index + 1
end

print("For loop")
for i = 15, 1, -1
do
    print("For", i)
end

print("Repeat loop")
repeat_index = 10
repeat
    print("Repeat",repeat_index)
    repeat_index = repeat_index-1
until(repeat_index == 0)

print("Nested loop")
for i = 0, 3, 1
do
    for j = 0,3,1
    do
        print("Nested",i,j)
    end
end