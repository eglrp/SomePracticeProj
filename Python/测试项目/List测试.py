def extendList1(val, list = []):
    list.append(val)
    return list

def extendList2(val, list = None):
    if list is None:
        list = []
    list.append(val)
    return list

if __name__ == '__main__':
    '''
    list1 = extendList1(10)
    list2 = extendList1(123, [])
    list3 = extendList1('a')
    '''
    list1 = extendList2(10)
    list2 = extendList2(123, [])
    list3 = extendList2('a')

    print(list1)
    print(list2)
    print(list3)

