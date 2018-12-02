char_list = [1,1,2,3,4,4,4,5,6,6,7]

sentence = "Welcome to China"

print(set(char_list))
print(set(sentence))  #不能在  set  里传列表

unique_char = set(char_list)
unique_char.add('x')
print(unique_char)

unique_char.add('2')
print(unique_char)

#unique_char.clear()
#print(unique_char)

unique_char.remove('x')
print(unique_char)

unique_char.discard('z')  #  Z 不存在
print(unique_char)

set1 = unique_char
set2 = {'a',1,2}

print(set1.difference(set2))   # set1 - set2
print(set1.intersection(set2))   # set1 交集 set2





