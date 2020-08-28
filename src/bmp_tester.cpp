#include <string>
#include "BMP.hpp"
#include "file_reading.hpp"
#include "bmp_tester.hpp"

void testing::bmp::rotate_image(const std::string& imagePath, const std::string& outputPath) {
    BMP bmpFile(readFileContent(imagePath));
    bmpFile.rotate();
    writeFileContent(outputPath, bmpFile.toString());
}

void testing::bmp::convert_to_grayscale(const std::string& imagePath, const std::string& outputPath) {
    BMP bmpFile(readFileContent(imagePath));
    bmpFile.toGrayscale();
    writeFileContent(outputPath, bmpFile.toString());
}