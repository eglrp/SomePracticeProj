import os, smtplib

# smtpObj = smtplib.SMTP('smtp.163.com', 25)
# print(smtpObj.ehlo())

# smtpObj.starttls()
# smtpObj.login('neverland_ly@163.com','liuyu.netease')
# smtpObj.sendmail('neverland_ly@163.com',
# 	'fwfchangan@163.com',
# 	'Subject:\nThis message from python.' )
# smtpObj.quit()

# print('发送完成')


# coding:utf-8
# import smtplib
# from email.mime.text import MIMEText  # 引入smtplib和MIMEText
 
# host = 'smtp.163.com'  # 设置发件服务器地址
# port = 25  # 设置发件服务器端口号。注意，这里有SSL和非SSL两种形式
# sender = '13669195936@163.com'  # 设置发件邮箱，一定要自己注册的邮箱
# pwd = 'liuyu.netease'  # 设置发件邮箱的密码，等会登陆会用到
# receiver = 'fwfchangan@163.com' # 设置邮件接收人，可以是扣扣邮箱
# body = '<h1>Hi</h1><p>test</p>' # 设置邮件正文，这里是支持HTML的
 
# msg = MIMEText(body, 'html') # 设置正文为符合邮件格式的HTML内容
# msg['subject'] = 'Hello world' # 设置邮件标题
# msg['from'] = sender  # 设置发送人
# msg['to'] = receiver  # 设置接收人
 
# try:
# 	s = smtplib.SMTP(host, port)  # 注意！如果是使用SSL端口，这里就要改为SMTP_SSL
# 	s.login(sender, pwd)  # 登陆邮箱
# 	s.sendmail(sender, receiver, msg.as_string())  # 发送邮件！
# 	print('Done')
# except smtplib.SMTPException:
# 	print('Error')


# --------------------------------------------------

#!/usr/bin/python
#coding=utf8
#Name:  py_sendattach.py        
#Purpose:       send ptp data to antifraud
#Author:        yangshuqiang
 
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart 
import smtplib
import os,sys
 
mail_host = 'smtp.163.com'
mail_from = 'neverland_ly@163.com'
mail_pass = 'liuyu.netease'

def addAttch(to_list, subject, content, path):
        msg = MIMEMultipart('related') ##采用related定义内嵌资源的邮件体
        msgtext = MIMEText(content,_subtype='plain',_charset='utf-8') ##_subtype有plain,html等格式，避免使用错误
 
        msg.attach(msgtext)
 
        os.chdir(path)  
        dir = os.getcwd()
        
        for fn in os.listdir(dir): ##返回字符串文件名   
                print(fn)
                #attach = MIMEText(open(fn,'rb').read()) 
                #attach["Content-Type"] = 'application/octet-stream'
                #attach["Content-Disposition"] = 'attachment; filename='+fn
                #msg.attach(attach)
        msg['Subject'] = subject
        msg['From'] = mail_from
        msg['To'] = to_list
        return msg
 
def sendMail(msg):
        try:
                server = smtplib.SMTP()
                server.connect(mail_host, 25)
                server.starttls()
                server.login(mail_from, mail_pass)      
                server.sendmail(mail_from, msg['To'], msg.as_string())  
                server.quit() ##断开smtp连接
                print("邮件发送成功")
        except Exception as e:
                print("失败"+str(e))
 
if __name__=='__main__':
        msg = addAttch('1019436173@qq.com', '11', '222', 'E:\\Temp')
        sendMail(msg)
 
 
 
 
 
