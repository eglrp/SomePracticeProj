#  字典

d = {'apple':1, 'pear':2, 'orange':3}
d2 = {1:'a', 2:'b'}

print(d['apple'])

#print(d2['a'])   #err

del d['pear']  #删除元素
print(d)

d['grape'] = 20
print(d)

#字典立面继续添加字典
f = {'apple':[1,2,3], 'pear':{1:3, 2:'a'}}
print(f['pear'][2])
