#coding:utf-8
#ftp演示，首先要在本机或远程服务器开启ftp功能
import sys,os,ftplib,socket
print("=====================FTP客户端=====================");

# HOST = '192.168.8.102'  #FTP主机
HOST = 'http://garner.ucsd.edu/pub'  #FTP主机
user = "anonymous"
password = "Neverland_LY@163.com"
buffer_size = 8192

#连接登陆
def connect():
    try:
        ftp = ftplib.FTP(HOST)
        ftp.login()#登录，参数user，password，acct均是可选参数，
        #f.login(user, password)
        return ftp
    except (socket.error,socket.gaierror):
        print("FTP登陆失败，请检查主机号、用户名、密码是否正确")
        sys.exit(0)
    print('已连接到： "%s"' % HOST)

#中断并退出
def disconnect(ftp):
    ftp.quit()  #FTP.close()：单方面的关闭掉连接。FTP.quit():发送QUIT命令给服务器并关闭掉连接

#上传文件
def upload(ftp, filepath):
    f = open(filepath, "rb")
    file_name = os.path.split(filepath)[-1]
    try:
        ftp.storbinary('STOR %s'%file_name, f, buffer_size)
        print('成功上传文件： "%s"' % file_name)
    except ftplib.error_perm:
        return False
    return True

#下载文件
def download(ftp, filename):
    f = open(filename,"wb").write
    try:
        ftp.retrbinary("RETR %s"%filename, f, buffer_size)
        print('成功下载文件： "%s"' % filename)
    except ftplib.error_perm:
        return False
    return True

#获取目录下文件或文件夹想详细信息
def listinfo(ftp):
    ftp.dir()


#查找是否存在指定文件
def find(ftp,filename):
    ftp_f_list = ftp.nlst()  #获取目录下文件、文件夹列表
    if filename in ftp_f_list:
        return True
    else:
        return False

def main():
    ftp = connect()                  #连接登陆ftp
    # dirpath = 'lp'                   #目录，不能使用lp/lp1这种多级创建，而且要保证你的ftp目录，右键属性不能是只读的
    # try: ftp.mkd(dirpath)                 #新建远程目录
    # except ftplib.error_perm:
    #     print("目录已经存在或无法创建")
    # try:ftp.cwd(dirpath)             #重定向到指定路径
    # except ftplib.error_perm:
    #     print('不可以进入目录："%s"' % dirpath)
    # print(ftp.pwd())                        #返回当前所在位置
    # try: ftp.mkd("dir1")                  #在当前路径下创建dir1文件夹
    # except ftplib.error_perm:
    #     print("目录已经存在或无法创建")
    # upload(ftp,"D:/test.txt")       #上传本地文件
    # filename="test1.txt"
    # ftp.rename("test.txt", filename) #文件改名
    # if os.path.exists(filename):   #判断本地文件是否存在
    #     os.unlink(filename)    #如果存在就删除
    # download(ftp,filename)        #下载ftp文件
    # listinfo(ftp)                   #打印目录下每个文件或文件夹的详细信息
    files = ftp.nlst()              #获取路径下文件或文件夹列表
    print(files)


    # ftp.delete(filename)              #删除远程文件
    # ftp.rmd("dir1")                  #删除远程目录
    ftp.quit()  #退出

if __name__ == '__main__':
    main()





# # def download(url, savepath='./'):
# #     """
# #     download file from internet
# #     :param url: path to download from
# #     :param savepath: path to save files
# #     :return: None
# #     """
# #     def reporthook(a, b, c):
# #         """
# #         显示下载进度
# #         :param a: 已经下载的数据块
# #         :param b: 数据块的大小
# #         :param c: 远程文件大小
# #         :return: None
# #         """
# #         print("\rdownloading: %5.1f%%" % (a * b * 100.0 / c), end="")

# #     filename = os.path.basename(url)
# #     # 判断文件是否存在，如果不存在则下载
# #     if not os.path.isfile(os.path.join(savepath, filename)):
# #         print('Downloading data from %s' % url)
# #         urlretrieve(url, os.path.join(savepath, filename), reporthook=reporthook)
# #         print('\nDownload finished!')
# #     else:
# #         print('File already exsits!')

# #     # 获取文件大小
# #     filesize = os.path.getsize(os.path.join(savepath, filename))
# #     # 文件大小默认以Bytes计， 转换为Mb
# #     print('File size = %.2f Mb' % (filesize/1024/1024))

# # if __name__ == '__main__':
# #     # 以下载cifar-10数据集为例
# #     # url = "https://www.cs.toronto.edu/~kriz/cifar-10-python.tar.gz"
# #     url = "ftp://garner.ucsd.edu/pub/met/2017/001/ac200010.17m.Z"
# #     download(url, savepath='./')


# # url = 'http://garner.ucsd.edu/pub/met/2017/001/'
# # url = 'http://www.cnblogs.com/hhh5460/p/5044038.html'
# # url = 'https://www.baidu.com/s?wd=%E5%8A%A8%E7%89%A9&rsv_spt=1&rsv_iqid=0x8aae4a9300009342&issp=1&f=8&rsv_bp=0&rsv_idx=2&ie=utf-8&tn=baiduhome_pg&rsv_enter=1&rsv_sug2=0&inputT=5104&rsv_sug4=6277'
# # r = requests.get(url)
# # r.encoding = 'gb2312'
# #


# # html="""
# # <html><head><title>The Dormouse's story</title></head>
# # <body>
# # <p class="title" name="dromouse"><b>The Dormouse's story</b></p>
# # <p class="story">Once upon a time there were three little sisters; and their names were
# # <a href="http://example.com/elsie" class="sister" id="xiaodeng"><!-- Elsie --></a>,
# # <a href="http://example.com/lacie" class="sister" id="link2">Lacie</a> and
# # <a href="http://example.com/tillie" class="sister" id="link3">Tillie</a>;
# # <a href="http://example.com/lacie" class="sister" id="xiaodeng">Lacie</a>
# # and they lived at the bottom of a well.</p>
# # <p class="story">...</p>
# # """

# # soup = BeautifulSoup(html, 'html.parser')   #文档对象

# # 利用 BeautifulSoup4 （DOM树）
# # soup = BeautifulSoup(r.text,'lxml')
# # for k in soup.find_all('a'):
# # #     link = a['href']
# # #     print(link)
# #     print(k)
# #     print(k)
# #     print(k['class']) # 查a标签的class属性
# #     print(k['id']) # 查a标签的id值
# #     print(k['href']) # 查a标签的href值
# #     print(k.string) # 查a标签的string


# # 利用 lxml.etree （XPath）
# # tree = etree.HTML(r.text)
# # for k in tree.xpath("//@href"):
# #     print(k)
# #     print(k)
# #     print(k['class']) # 查a标签的class属性
# #     print(k['id']) # 查a标签的id值
# #     print(k['href']) # 查a标签的href值
# #     print(k.string) # 查a标签的string
# #
# #

# # 如果是网址，可以用这个办法来读取网页
# html_doc = "ftp://garner.ucsd.edu/pub/met/2017/001/"
# req = urllib.request.Request(html_doc)
# webpage = urllib.request.urlopen(req)
# html = webpage.read()


# # url = "ftp://garner.ucsd.edu/pub/met/2017/001/"
# # html = urllib.request.urlopen(url)
# soup = BeautifulSoup(html, 'html.parser')
# t1 = soup.find_all('a')
# href_list = []
# for t2 in t1:
#     t3 = t2.get('href')
#     href_list.append(t3)

# for item in href_list:
#     print(item)


# ############################################################

# # #1. 确定好要爬取的入口链接
# # # url = "http://blog.csdn.net"
# # url = "ftp://garner.ucsd.edu/pub/met/2017/001/"
# # # 2.根据需求构建好链接提取的正则表达式
# # pattern1 = '<.*?(href=".*?").*?'
# # #3.模拟成浏览器并爬取对应的网页 谷歌浏览器
# # headers = {'User-Agent', 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.110 Safari/537.36'}
# # opener = urllib.request.build_opener()
# # opener.addheaders = [headers]
# # data = opener.open(url).read().decode('utf8')
# # # 4.根据2中规则提取出该网页中包含的链接
# # content_href = re.findall(pattern1,data,re.I)
# # # print(content_href)
# # # 5.过滤掉重复的链接
# # #    # 列表转集合(去重) list1 = [6, 7, 7, 8, 8, 9] set(list1) {6, 7, 8, 9}
# # set1 = set(content_href)
# # # 6.后续操作，比如打印出来或者保存到文件中。
# # # file_new = "E:\\爬虫\\href.txt"
# # # with open(file_new,'w') as f:
# # #     for i in set1:
# # #         f.write(i)
# # #         f.write("\n")
# # # f.close()
# # #
# # for i in set1:
# #     print(i)

# # print('已经生成文件')