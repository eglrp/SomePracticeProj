while True:
    a= int(input("---> "))
    if a==2:
        continue
    else:
        break

print("EXIT")

try:
    file = open('eee.txt' ,'r')
except Exception as e:
    print(e)
    print('No such file or directory: eee.txt')


a = [1,2,3]
b= [4,5,6]

zip(a,b)
list(zip(a,b))
for i, j in zip(a,b):
    print(i + j)

list(zip(a,a,b))
for i, j,k in zip(a, a, b):
    print(i + j)



def fun1(x,y):
    print(x+y)

fun2 = lambda x ,y : x + y


fun1(1,2)
print(fun2(1,2))


map(fun1, [1], [2])
print(list(map(fun1, [1], [2])))

print(list(map(fun1, [1,3], [2,5])))



