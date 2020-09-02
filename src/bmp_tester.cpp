#include <string>
#include <fstream>
#include "BMP.hpp"
#include "file_reading.hpp"
#include "bmp_tester.hpp"
#include "CacheManager.hpp"

void testing::bmp::rotate_image(CacheManager cache, const std::string& path, char* argv[]) {
    BMP bmpFile(readFileContent(cache.get(path)));
    bmpFile.rotate();
    writeFileContent(std::string(argv[5]), bmpFile.toString());
    cache.insert(path, std::string(argv[5]));
}

void testing::bmp::convert_to_grayscale(CacheManager cache, const std::string& path, char* argv[]) {
    BMP bmpFile(readFileContent(cache.get(path)));
    bmpFile.toGrayscale();
    writeFileContent(std::string(argv[5]), bmpFile.toString());
    cache.insert(path, std::string(argv[5]));
}