def multiplier1():
    return [ lambda x : i * x for i in range(4) ]

def multiplier2():
    return [ lambda x, i = i : i * x for i in range(4) ]

def multiplier3():
    for i in range(4):
        yield lambda x : i * x

if __name__ == '__main__':
    print([m(2) for m in multiplier1()])
    print([m(2) for m in multiplier2()])
    print([m(2) for m in multiplier3()])