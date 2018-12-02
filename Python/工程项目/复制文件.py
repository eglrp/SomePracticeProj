import os
import os.path
import shutil

def copyFiles(sourceDir, targetDir):
    for root_path, sub_directory_list, un_sub_directory_list in os.walk(sourceDir):
        for file in un_sub_directory_list:
            if file.find(".las") > 0:
                src_file = os.path.join(sourceDir, file[0:-4], file)
                dst_file = os.path.join(targetDir, file)
                open(dst_file, "wb").write(open(src_file, "rb").read())


if __name__ == '__main__':
    copyFiles("G:/Xian_ShiFan_20180416/project_ssf/Productions/pix_3/Data", "E:/pix3-total" )