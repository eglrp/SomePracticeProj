import os # Operator System library
from PIL import Image # Pillow library

# Setting the para [USERS SETTING]
base_ratio = 0.8
base_length = 256
base_crop = base_ratio * base_length # 256 * 0.8 = 204.8 ~= 205
input_directory = "E:\\1-Office\\FUWF\\UCMerced_LandUse\\UCMerced_LandUse\\Images" # NOTICE: no \\
output_directory = "E:\\" # NOTICE: th suffix must be \\

# Define the function of rotate
def roatetImg(image, folder, part, base_name):
    # Create new folder
    new_fold_path = output_directory + "OUTPUT-IMAGE" + "\\" + folder
    os.makedirs(new_fold_path, exist_ok = True)
    output_base_name = new_fold_path + "\\" + base_name + "-" + part

    # Start rotate image
    image.save(output_base_name + "-0.tif") # Origin image
    image.rotate(270).save(output_base_name + "-90.tif") # rotate 90 deg
    image.rotate(180).save(output_base_name + "-180.tif") # rotate 180 deg
    image.rotate(90).save(output_base_name + "-270.tif")  # rotate 270 deg

# Create outputfile
os.makedirs(output_directory + "OUTPUT-IMAGE", exist_ok = True)
os.chdir(output_directory + "\\" + "OUTPUT-IMAGE")

# Loop the sub-directory
# [para1]: root_path: currenty path     
# [para2]: sub_directory_list: all sub-directory    
# [para3]: un_sub_directory_list: un-sub-directory
print("Start running...")
resize_image_txt = open(output_directory + "\\" + "OUTPUT-IMAGE" + "\\ImageResizeRecorder.txt", 'w')
resize_count = 0
for root_path, sub_directory_list, un_sub_directory_list in os.walk(input_directory):
    # Define the counter
    current_deal_count = 0
    total_deal_count = len(sub_directory_list)

    # Loop sub_directory_list
    for sub_directory in sub_directory_list:
        # Add count
        current_deal_count = current_deal_count + 1

        # Absolutely path
        subdir_abs_path = os.path.abspath(input_directory + "\\" + sub_directory)

        # Image list
        iamge_list = os.listdir(subdir_abs_path)
        
        # Start deal the image
        for image in iamge_list:
            # Open image
            image_abs_path = input_directory + "\\" + sub_directory
            im = Image.open(os.path.abspath(image_abs_path  + "\\" + image))
            image_size = im.size

            # Pass the image not satisfied teh condition
            if image_size[0] < base_length or image_size[1] < base_length:
                # count plus
                resize_count = resize_count + 1
                resize_image_txt.write(str(input_directory + "\\" + sub_directory + "\\" + image))
                resize_image_txt.write('\n')

                # Reset size
                # im.resize((base_length, base_length))

            # Crop one image to five sub-image
            crop_name_list = ['lt', 'rt', 'lb', 'rb', 'ce']
            crop_image_lt = im.crop((0, 0, base_crop, base_crop))
            crop_image_rt = im.crop((base_length - base_crop, 0, base_length, base_crop))
            crop_image_lb = im.crop((0, base_length - base_crop, base_crop, base_length))
            crop_image_rb = im.crop((base_length - base_crop, base_length - base_crop, base_length, base_length))
            crop_image_ce = im.crop(((base_length - base_crop) / 2, (base_length - base_crop) / 2,\
                    (base_length + base_crop) / 2, (base_length + base_crop) / 2))
            crop_list = [crop_image_lt, crop_image_rt, crop_image_lb, crop_image_rb, crop_image_ce]

            # Rotate the iamge   5 * 4
            loop_time = 0
            for crop_image in crop_list:
                roatetImg(crop_image, sub_directory, crop_name_list[loop_time], image[:-4])
                loop_time = loop_time + 1
        print(" [ " + str(current_deal_count) + " / " + str(total_deal_count) + " ] " + sub_directory + " finished!")
resize_image_txt.write("ERROR NUMBER: " + str(resize_count))
resize_image_txt.close()

print("Finished!")

