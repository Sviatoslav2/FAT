#include "Image.h"

uint16_t Image::getTableData(u_int16_t offset, u_int8_t length)
{
    return *reinterpret_cast<uint16_t *>(imageData.data() + baseByte + offset);
}

void Image::readImage()
{
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    file.seekg(0, std::ios::beg);
    imageData.resize(size + 1);
    file.read(reinterpret_cast<char *>(imageData.data()), size);
}

Image::Image(std::string filename)
{
    file.open(filename.c_str(), std::ios::binary);
    file.seekg(baseByte);
    file.read(reinterpret_cast<char *>(&bootSectorData), 512);
//    file.seekg(0, std::ios::beg);
    readImage();
    setCatalogStart();
}

void Image::setCatalogStart()
{
    catalogStart =
            bootSectorData.bytesPerSector * bootSectorData.reservedSectors +
            bootSectorData.numberOfFATS * bootSectorData.sectorsPerFAT *
            bootSectorData.bytesPerSector + baseByte;
}

size_t Image::getCatalogStart() const
{
    return catalogStart;
}

uint16_t Image::from_disk_to_mem16(uint16_t x)
{
    uint16_t y = ((x & 0xFF00 >> 8) << 8) | (x >> 8 & 0xFF);
    return y;
}

uint32_t Image::from_disk_to_mem32(uint32_t x)
{
    uint8_t *sa = reinterpret_cast<uint8_t *>(&x);
    uint32_t res = 0;
    uint8_t *sb = reinterpret_cast<uint8_t *>(&res);
    for (int i = 0; i < 4; ++i)
        sb[i] = sa[4 - i - 1];
    return res;
}

std::ifstream &Image::getFile()
{
    return file;
}

Image::bootData &Image::getBootData()
{
    return bootSectorData;
}
