#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Author: Neverland_LY
# Date: 2018-11-28
# Version: v3.0
#
# Description:
#       1. Downloading the specified data from FTP: http://garner.ucsd.edu/pub
#       2. The specified data fild contains [ chan & bjfs & urum & lhaz & shao ]
#

# import the necessary library
import urllib.request, urllib, re
from urllib.request import urlretrieve
import ftplib
import socket
import pdb
import requests
import os, sys

# define the HOST
HOST = 'ftp.aiub.unibe.ch'
# define the pub path
pub_path = '/CODE'
# define the year list
year_list = ['2017', '2018'] # ['2017', '2016', ...]
# define output path
output_path = "F:/xiaowei"


# download th file
def downloadByGroupYear(year):
    # ftp_year_path & local_year_path
    ftp_year_path = pub_path + '/' + year  # /CODE/2017
    # download th file
    local_year_path = os.path.join(output_path,year) # E:/xiaowei/2017
    # statistics folders
    try:
        global f
        f.cwd(ftp_year_path)
    except ftplib.error_perm:
        print(' > ERROR: Cannot cd to "%s", program exited ... ' % ftp_year_path)
        log_file.close()
        f.quit()
        sys.exit(1) # ERROR #

    # file list
    file_list = f.nlst()
    download_num = 1
    for file in file_list:
        file_front = file[-5:-2]
        if file_front == "ION":
            try:
                f.retrbinary('RETR %s' % file, open(local_year_path + '/' + file,'wb').write)
                print(" > No." + year + " - " + str(download_num) + " : " + \
                    ftp_year_path + "/" + file + " downloaded successful ~")
            except ftplib.error_perm:
                os.unlink(file)
                print(" > File " + ftp_year_path + "/" + file + " downloaded failed !")
        download_num = download_num + 1
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
        f.login()
    except ftplib.error_perm:
        print(' > ERROR: Cannot login anonymously !')
        f.quit()
        sys.exit(1)
    print(' > Logged in as "anonymous" ~')

    # download the file by group
    for year in year_list:
        if not os.path.exists(os.path.join(output_path, year)):
            os.makedirs(os.path.join(output_path, year))
        print(" > Start downloading year " + year + " ...")
        downloadByGroupYear(year)
        f.quit()