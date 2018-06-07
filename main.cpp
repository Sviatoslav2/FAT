#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <sstream>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "Image.h"
#include "Root.h"

#pragma pack(push, 1)
struct file_struct
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

using std::cout;
using std::endl;
using std::string;

string cool_func(char *source)
{
    string s;
    for (int i = 0; i < sizeof(source); ++i)
    {
        s += source[i];
    }
    return s;
}

int main(int argc, char *argv[])
{
    std::string filename = "../hd0.img";
    Image mainImage = Image(filename);

    std::cout << "Bytes per sector: " << mainImage.getBootData().bytesPerSector << std::endl;
    std::cout << "Sectors per claster: " << (int) mainImage.getBootData().sectorPerCluster << std::endl;
    std::cout << "# of FATs: " << (int) mainImage.getBootData().numberOfFATS << std::endl;
    std::cout << "FAT size: " << mainImage.getBootData().sectorsPerFAT << std::endl;
    std::cout << "Root directory entires: " << mainImage.getBootData().rootEntries / 32 << ". Its size: "
              << mainImage.getBootData().rootEntries << std::endl;
    std::cout << "Reserved Sectors: " << mainImage.getBootData().reservedSectors << std::endl;
    std::cout << "Signature: " << (int) mainImage.getBootData().signature << std::endl;
    std::cout << "----------------" << std::endl;

    Root root = Root(mainImage);

    std::string needed = argv[1];
    auto res = root.find_file(needed);

    if (res == -1)
    {
        std::cout << "File not found" << std::endl;
    } else
    {
        std::cout << "File found" << std::endl;
    }

    auto file = root.getFile(res);
    root.describe_file(file);
}
