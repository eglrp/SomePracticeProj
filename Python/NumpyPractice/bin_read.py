import sys
import os
import struct
import random

path = "C:/Users/Never/Desktop/stud.txt"

infile=open(path,"rb")#以rb的方式打开二进制文件
s=struct.Struct('@II')#每次读int,int这样的两个整形结构。
count=0;
length_file=os.path.getsize(path)#二进制文件内容的长度。
print(length_file)
while count<length_file:
        src,dst=s.unpack(infile.read(8));
        count=count+8
        print(str(src)+"->"+str(dst)+":"+"\n")
print(count/8)
