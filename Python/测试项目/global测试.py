#Python中的变量：全局变量和局部变量

#在很多语言中，在声明全局变量的时候，都喜欢把全局变量的名称定义为大写

#定义学生人数为100
STUDENT_NUMBER = 1111111
#学校名称
SCHOOL_NAME = '1111111111'

"""\
    获取全局变量：学生人数STUDENT_NUMBER的值
"""
def getStudentNumber():
    return STUDENT_NUMBER
"""\
    重置全局变量：学生人数STUDENT_NUMBER值
"""
def setStudentNumber(num):
    # global STUDENT_NUMBER
    STUDENT_NUMBER = num
"""\
    获取全局变量：学校名称SCHOOL_NAME的值
"""
def getSchoolName():
    return SCHOOL_NAME
"""\
    重置全局变量：学校名称SCHOOL_NAME值
"""
def setSchoolName(name):
    global SCHOOL_NAME
    SCHOOL_NAME = name

def changeValue():
    name = '666666'
    number = 666666
    print('全局变量STUDENT_NUMBER = ' , getStudentNumber())
    print('全局变量SCHOOL_NAME = ' , getSchoolName())
    print('#######################################')
    print('局部变量namber = ' , number)
    print('局部变量name = ' , name)
    print('#######################################')
    print('改变全局变量值...')
    print('#######################################')
    setStudentNumber(number)
    setSchoolName(name)
    print('全局变量STUDENT_NUMBER = ' , getStudentNumber())
    print('全局变量SCHOOL_NAME = ' , getSchoolName())

if __name__ == '__main__':
    changeValue()