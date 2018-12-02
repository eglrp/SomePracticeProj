#read and write file

text = "This is my first test.\nThis is my second line."

#print(text)

my_file = open('C:/Users/Never/Desktop/myfile.txt','w')
my_file.write(text)
my_file.close()

append_text = "\n\nThis                 is append text"

my_file = open('C:/Users/Never/Desktop/myfile.txt','a') #append
my_file.write(append_text)
my_file.close()

file = open('C:/Users/Never/Desktop/myfile.txt','r')
content = file.readlines()  # VS. readline VS. readlines VS. read
print(content)
file.close()
