#!/usr/bin/env python
# -*- coding: utf-8 -*-

# COMMENT
#

input_file = "E:\\xiaowei" # the file to be processed
output_name = "Result_LY.xlsx" # output name

import openpyxl, os

def cancelCol():
    for root_path, sub_directory_list, file_list in os.walk(input_file):
        for file in file_list:
            print(root_path + "\\" + file)
    # define output file
    # result_wb = openpyxl.Workbook()
    # result_sheet = result_wb.active

if __name__ == '__main__':
    cancelCol()