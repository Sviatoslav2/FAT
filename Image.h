//
// Created by vlad on 30.05.18.
//

#ifndef FSE_IMAGE_H
#define FSE_IMAGE_H


#include <cstdint>
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;

class Image
{

private:

#pragma pack(push, 1)
    struct bootData
    {
        char text_identifier_OS[3];
        char machine_instruction[8];
        u_int16_t bytesPerSector;
        u_int8_t sectorPerCluster;
        u_int16_t reservedSectors;
        u_int8_t numberOfFATS;
        u_int16_t rootEntries;
        u_int16_t diskBlocks;
        u_int8_t mediaDescriptor;
        u_int16_t sectorsPerFAT;
        u_int16_t SectorPerTrack;
        u_int16_t Heads;
        char HiddenSectors[4];
        char BigTotalSectors[4];
        u_int16_t PhysicalDiscNumbers;
        u_int8_t CurrentHead;
        char VolumeSerialNumber[4];
        char VolumeLabel[11];
        char SystemID[8];
        char LoaderCodeArea[448];
        u_int8_t signature;
    };
#pragma pack(pop)


//    struct boot
//    {
//        std::pair<int, int> text_identifier_OS = std::make_pair(0, 3);
//        std::pair<int, int> machine_instruction = std::make_pair(3, 8);
//        std::pair<int, int> BytesPerSector = std::make_pair(11, 2);
//        std::pair<int, int> sectorPerCluster = std::make_pair(13, 1);
//        std::pair<int, int> ReservedSector = std::make_pair(14, 2);
//        std::pair<int, int> NumberOfFAts = std::make_pair(16, 1);
//        std::pair<int, int> rootEntries = std::make_pair(17, 2);
//        std::pair<int, int> MediaDescriptor = std::make_pair(21, 1);
//        std::pair<int, int> SectorPerFat = std::make_pair(22, 2);
//        std::pair<int, int> SectorPerTrack = std::make_pair(24, 2);
//        std::pair<int, int> Heads = std::make_pair(26, 2);
//        std::pair<int, int> HiddenSectors = std::make_pair(28, 4);
//        std::pair<int, int> BigTotalSectors = std::make_pair(32, 4);
//        std::pair<int, int> PhysicalDiscNumbers = std::make_pair(36, 1);
//        std::pair<int, int> CurrentHead = std::make_pair(37, 1);
//        std::pair<int, int> signature = std::make_pair(38, 1);
//        std::pair<int, int> VolumeSerialNumber = std::make_pair(39, 4);
//        std::pair<int, int> VolumeLabel = std::make_pair(43, 11);
//        std::pair<int, int> SystemID = std::make_pair(54, 8);
//        std::pair<int, int> LoaderCodeArea = std::make_pair(62, 448);
//        std::pair<int, int> BootSignature = std::make_pair(510, 2);
//    };

    struct file_locations
    {
        std::pair<int, int> NameOfFile = std::make_pair(0, 8);
        std::pair<int, int> TypeOfFile = std::make_pair(8, 3);
        std::pair<int, int> Reserv = std::make_pair(12, 1);
        std::pair<int, int> TimeOfBornInSeconds = std::make_pair(13, 1);
        std::pair<int, int> TimeOfBorn = std::make_pair(14, 2);
        std::pair<int, int> DataOfBorn = std::make_pair(16, 2);
        std::pair<int, int> DataLstCal = std::make_pair(18, 2);
        std::pair<int, int> H_Word = std::make_pair(20, 2);
        std::pair<int, int> TimeLastT = std::make_pair(22, 2);
        std::pair<int, int> DataLastT = std::make_pair(24, 2);
        std::pair<int, int> l_word = std::make_pair(26, 2);
        std::pair<int, int> size = std::make_pair(24, 4);
    };

    void readImage();

    void setCatalogStart();

private:
    std::ifstream file;
public:
    std::ifstream &getFile();
    bootData &getBootData();

private:
    std::vector<uint8_t> imageData;
    size_t catalogStart;
    bootData bootSectorData;
    size_t baseByte = 17 * 512;


    uint32_t from_disk_to_mem32(uint32_t x);

    uint16_t from_disk_to_mem16(uint16_t x);

public:

    size_t getCatalogStart() const;

    uint16_t getTableData(u_int16_t offset, u_int8_t length);

    explicit Image(std::string filename);
};


#endif //FSE_IMAGE_H
