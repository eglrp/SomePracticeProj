#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Author: Neverland_LY
# Date: 2018-11-24
# Version: v1.0
#
# Description:
#       1. Downloading the specified data from FTP: http://garner.ucsd.edu/pub
#       2. The specified data fild contains [ chan & bjfs & urum & lhaz & shao ]
#

# import the necessary library
import urllib.request, urllib, re
from urllib.request import urlretrieve
from bs4 import BeautifulSoup
from lxml import etree
import ftplib
import socket
import pdb
import requests
import os, sys

# define the HOST
HOST = 'garner.ucsd.edu'
# define the pub path
pub_path = '/pub/met'
# define the year list
year_list = ['2017'] # ['2017', '2016', ...]
# define data fild
data_fild_name = ['chan', 'bjfs', 'urum', 'lhaz', 'shao']
# define output path
output_path = "E:/xiaowei"


# download th file
def downloadByGroupYear(year):
    # ftp_year_path & local_year_path
    ftp_year_path = pub_path + '/' + year # /pub/met/2017
    # download th file
    local_year_path = output_path + '/' + year # E:/xiaowei/2017
    # create log file
    log_file = open(local_year_path + '/' + 'log' + str(year) + '.txt', 'w') # E:/xiaowei/2017/log2017.txt
    # statistics folders
    try:
        global f
        f.cwd(ftp_year_path)
    except ftplib.error_perm:
        print(' > ERROR: Cannot cd to "%s", program exited ... ' % ftp_year_path)
        log_file.close()
        f.quit()
        sys.exit(1) # ERROR #

    # calc days
    day_list = f.nlst()
    # counter
    count = 352
    for day in day_list:
        if int(day) < 352:
            continue
        try:
            f.cwd(ftp_year_path + '/' + day) # /pub/met/2017/001
        except ftplib.error_perm:
            print(' > ERROR: Cannot cd to "%s"' % (ftp_year_path + '/' + day))
            log_file.write('Folder: "%s"' % (ftp_year_path + '/' + day))
            log_file.write('\n')
            continue

        file_list = f.nlst()
        for file in file_list:
            file_front = file[0:4]
            if file_front in data_fild_name:
                try:
                    f.retrbinary('RETR %s' % file, open(local_year_path + '/' \
                        + file_front + '/' + file,'wb').write, 2048)
                    # print(' > Download "%s" successful ~ ' % (ftp_year_path + '/' + day + '/' + file))
                except ftplib.error_perm:
                    os.unlink(file)
                    log.write('File: "%s"' % (ftp_year_path + '/' + day + '/' + file))
                    log_file.write('\n')
        print(" > [ Day " + ('000' + str(count))[-3:] + " ] downloading finished ~" )
        count += 1
    f.quit()
    log_file.close()
    print(' > All task finished !')


# program entrance
if __name__ == '__main__':
    # Connect to the FTP
    try:
        print(' > Start to reach "%s" ...' % HOST)
        f = ftplib.FTP(HOST)
    except (socket.error, socket.gaierror) as e:
        print(' > ERROR: Cannot connect "%s" ! Time out !' % HOST)
        sys.exit(1)
    print(' > Connected to host "%s" successful ~' % HOST)

    # Login
    try:
        f.login("anonymous", "Neverland_LY@163.com")
    except ftplib.error_perm:
        print(' > ERROR: Cannot login anonymously !')
        f.quit()
        sys.exit(1)
    print(' > Logged in as "anonymous" ~')

    # check the path
    global sub_dir
    if not os.path.exists(output_path):
        os.makedirs(output_path)
        for item in data_fild_name:
            os.makedirs(output_path + '/' + item)

    # download the file by group
    for year in year_list:
        if not os.path.exists(output_path + '/' + year):
            os.makedirs(output_path + '/' + year)
            for item in data_fild_name:
                os.makedirs(output_path + '/' + year + '/' + item)
        print(" > Start downloading...")
        downloadByGroupYear(year)