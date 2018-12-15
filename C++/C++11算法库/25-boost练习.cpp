#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <utility>

#include <iostream>

int main() {

    {
        boost::filesystem::recursive_directory_iterator itEnd;
        for(boost::filesystem::recursive_directory_iterator itor("E:\\TEST1"); itor != itEnd; ++itor) {

            /** Get absolute or relative path by inputy path */
            std::string str = itor->path().string();
            std::cout << str << std::endl;

            /** Different (boost::filesystem::patpath VS std::string) */
            boost::filesystem::path filePath(str);
            std::cout << filePath.filename() << std::endl;
            std::cout << filePath.filename().string() << std::endl;

            if(boost::filesystem::is_regular_file(filePath)) {
                std::cout << filePath.string() << "is regular file." << std::endl;

                /** Parent path */
                std::cout << "Parent path: " << filePath.parent_path() << std::endl;

                /** Stem */
                std::cout << filePath.stem() << std::endl;

                /** Extension */
                std::cout << filePath.extension() << std::endl;

                /** Size (Can not calculate folder's size) */
                std::cout << boost::filesystem::file_size((filePath)) << std::endl;

                /** Replace extension */
                boost::filesystem::path tmpPath = filePath;
                tmpPath.replace_extension(".zip");

                /** Create file */
                if(!boost::filesystem::exists(tmpPath)) {
                    boost::filesystem::create_directory(tmpPath);
                }

            }

            if(boost::filesystem::is_directory(filePath)) {
                std::cout << filePath.string() << "is directory." << std::endl;
            }

            if(boost::filesystem::is_symlink(filePath)) {
                std::cout << filePath.string() << "is symlink." << std::endl;
            }
        }
    }

    {
        /** Cancel file only */
        boost::filesystem::path tmp_file_path("E:\\TEST2\\1.txt");
        boost::filesystem::remove(tmp_file_path.string());

        /** Cancel file and folder */
        boost::filesystem::path tmp_folder_path("E:\\TEST2\\2");
        boost::filesystem::remove_all(tmp_folder_path.string());

        /** Rename */
        boost::filesystem::path srcPath("E:\\TEST2\\3.txt");
        boost::filesystem::path destPath("E:\\TEST2\\3.rename");
        boost::filesystem::rename(srcPath, destPath);

        /** Copy file */
        boost::filesystem::path copySrcFilePath("E:\\TEST2\\4.txt");
        boost::filesystem::path copyDestFilePath("F:\\444.txt");
        boost::filesystem::copy_file(copySrcFilePath, copyDestFilePath);

        /** Copy directory */
        boost::filesystem::path copySrcFolder("E:\\TEST2\\5");
        boost::filesystem::path copyDestFolder("F:\\");
        boost::filesystem::copy_directory(copySrcFolder, copyDestFolder);
    }
}