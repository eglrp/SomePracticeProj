import copy


a=[1,2,3]
b =a    #指向同一块内存

print(id(a))

print(id(b))

print(id(b) == id(b))

c = copy.copy(a)    #浅拷贝 shallow copy
print(id(a) == id(c))

e = [1, 2, [3, 4]]
f = copy.copy(e)
print(id(e) == id(f))
print(id(e[2]) == id(f[2]))

g = copy.deepcopy(e)
print(id(e) == id(g))
print(id(e[2]) == id(g[2]))



