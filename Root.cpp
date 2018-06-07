//
// Created by vlad on 07.06.18.
//

#include "Root.h"

Root::Root(Image &image)
{
    fileStruct cur_file{};
    image.getFile().seekg(0, std::ios::beg);
    image.getFile().seekg(image.getCatalogStart());

    for (int i = 0; i < image.getBootData().rootEntries / 32; ++i)
    {
        image.getFile().read(reinterpret_cast<char *>(&cur_file), 32);
        rootFiles.emplace_back(cur_file);
    }
}

std::string Root::fileToStr(char *filename)
{
    std::string res;
    for (int i = 0; i < sizeof(filename); ++i)
    {
        res += filename[i];
    }
    return res;
}

int Root::find_file(std::string filename)
{
    if (filename.size() > 8)
        return -1;
    int i = 0;
    for (auto &item : rootFiles)
    {
        auto cur_filename = fileToStr(item.filename);
        boost::trim(cur_filename);
        if (cur_filename == filename)
        {
            return i;
        }
        ++i;
    }
    return -1;
}

Root::fileStruct Root::getFile(int id)
{
    return rootFiles[id];
}

void Root::describe_file(Root::fileStruct &file)
{
    std::string name = fileToStr(file.filename);
    boost::trim(name);
    std::cout << name << "." << fileToStr(file.ext) << std::endl;
    if (isDirectory(file)) std::cout << "It is a directory" << std::endl;
    else std::cout << "File size: " << file.file_size << std::endl;
    std::cout << "Modify date: " << file.modify_date << std::endl;
    std::cout << "Creation date: " << file.time_created<< std::endl;
    std::bitset<8> attr(file.attributes);
    std::cout << "Attributes: " << attr << std::endl;
    std::cout << "Starting cluster: " << file.starting_cluster << std::endl;
    
}

// 00010001
// 00000001

bool Root::isDirectory(Root::fileStruct &file)
{
    return (file.attributes >> 4 & 1);
}
