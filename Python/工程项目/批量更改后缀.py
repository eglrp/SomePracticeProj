#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Author: Neverland_LY
# Date: 2018-11-27
# Version: v5.0
#
# Description:
#       1. rename the file suffix
#

import os

input_directory = "E:\\xiaowei"
output_directory = "E:\\xiaowei\\modify"

def modifyAllFile(input_path, suffix):
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
    for root_path, sub_directory_list, file_list in os.walk(input_path):
        for file in file_list:
            old_name = root_path + "\\" + file
            new_name = output_directory + "\\" + os.path.splitext(file)[0]  + suffix
            os.rename(old_name, new_name)

if __name__ == '__main__':
    modifyAllFile(input_directory, ".txt")