print("One dimensional array")

array = { "Lua", "Tutorial" }

for i = 0, 2 do
  print(array[i])
end

print("Two dimensional array")
-- Multidimensional array

mul_array = {}

for i = 1, 3 do
  mul_array[i] = {}
  for j = 1, 3 do
    mul_array[i][j] = i * j
    print(mul_array[i][j])
  end
end
