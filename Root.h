//
// Created by vlad on 07.06.18.
//

#ifndef FSE_ROOT_H
#define FSE_ROOT_H


#include <vector>
#include <fstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <bitset>

#include "Image.h"

class Root
{
private:
#pragma pack(push, 1)
    struct fileStruct
    {
        char filename[8];
        char ext[3];
        u_int8_t attributes;
        char reserved[10];
        u_int16_t time_created;
        u_int16_t modify_date;
        u_int16_t starting_cluster;
        u_int32_t file_size;
    };
#pragma pack(pop)

    std::vector<fileStruct> rootFiles;
    std::string fileToStr(char *filename);

public:
    explicit Root(Image &image);

    int find_file(std::string filename);

    fileStruct getFile(int id);

    void describe_file(fileStruct &file);

    bool isDirectory(fileStruct &file);

};


#endif //FSE_ROOT_H
