APPLE = 100  #global variable

def fun(a,b):
    c =a**b
    print("this is def fun(a,b)")
    print('the c is',c)


def sale_car(price,color='red',brand='carmy',is_second_hand=True):
    print('price',price,
          'color',color,
          'brand',brand,
          'is_second_hand',is_second_hand)

#sale_car(1000)

a = None

def fun():
    global a
    a= 20
    print("thisis fun()")
    return 100

print('a pass =' ,a)
print(fun())
print('a now =' ,a)

#print(a)  # print global variable in local space
