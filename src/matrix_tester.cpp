#include <string>
#include <fstream>
#include "Matrix.hpp"
#include "file_reading.hpp"
#include "matrix_tester.hpp"
#include "CacheManager.hpp"

void testing::matrix::add(CacheManager cache, const std::string& path, char* argv[]){
    Matrix matrix1(readTextFileContent(std::string(argv[3])));
    Matrix matrix2(readTextFileContent(std::string(argv[4])));
    matrix1 += matrix2;
    std::fstream toFile;
    toFile.open(std::string(argv[5]));
    writeFileContent(std::string(argv[5]), matrix1.toString());
    cache.insert(path, std::string(argv[5]));
}

void testing::matrix::multiply(CacheManager cache, const std::string& path, char* argv[]){
    Matrix matrix1(readTextFileContent(std::string(argv[3])));
    Matrix matrix2(readTextFileContent(std::string(argv[4])));
    matrix1 *= matrix2;
    std::fstream toFile;
    toFile.open(std::string(argv[5]));
    writeFileContent(std::string(argv[5]), matrix1.toString());
    cache.insert(path, std::string(argv[5]));
}