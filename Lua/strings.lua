string1 = 'Lua'
print("\"string1\" is", string1)

string2 = "Tutorial"
print("string2 is", string2)

string3 = [["Lua Tutorial"]]
print("string3 is ", string3)

test_string = "This is a test Lua string"
print(string.upper(test_string))
print(string.lower(test_string))
print(string.gsub(test_string, "i", "!"))
print(string.find(test_string, "test"))
print(string.reverse(test_string))
print(string.format("Test of %s", test_string))
print(string.char(77))
print(string.byte(test_string))
-- Third character
print(string.byte(test_string, 3))
-- First character from last
print(string.byte(test_string, -1))

print(test_string.." "..test_string)
print("Len is", string.len(test_string))
print(string.rep(test_string, 5))