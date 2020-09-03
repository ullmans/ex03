#include <string>
#include <fstream>
#include "BMP.hpp"
#include "file_reading.hpp"
#include "bmp_tester.hpp"
#include "CacheManager.hpp"

void testing::bmp::rotate_image(CacheManager* cache, const std::string& key, char* argv[]) {
    BMP bmpFile = BMP(readFileContent(std::string(argv[3])));
    bmpFile.rotate();
    cache->insert(key, std::string(argv[4]), bmpFile.toString());
}

void testing::bmp::convert_to_grayscale(CacheManager* cache, const std::string& key, char* argv[]) {
    BMP bmpFile = BMP(readFileContent(std::string(argv[3])));
    bmpFile.toGrayscale();
    cache->insert(key, std::string(argv[4]), bmpFile.toString());
}