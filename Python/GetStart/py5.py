
a_input = input('pls input a num: ')  # input

print(a_input)

#tuple  list

a_tuple = (1,2,3,4,5)
b_tuple = 1,2,3,4,5

a_list = [6,7,8,9,10]

#for i in a_list:
 #   print(content)

 
print(a_list[2])

a_list.append(1)
a_list.insert(1,0)  # location   value


a_list.remove(1)   #出去第一个出现的 1
a_list[-1]  #the last number
print(a_list[2:5])
print(a_list[2:])

a_list.index(5)   #返回  5 的索引
a_list.count(3)  #3 出现的次数
a_list.sort(reverse)   #加上 reverse 后变成从大到小排序

# 多维列表
multi_dimension_a =[[1,2,3],
                    [2,3,4],
                    [3,4,5]]

print(multi_dimension_a[2][2])
