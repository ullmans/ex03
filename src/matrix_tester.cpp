#include <string>
#include <fstream>
#include "IMatrix.hpp"
#include "file_reading.hpp"
#include "matrix_tester.hpp"
#include "CacheManager.hpp"

void testing::matrix::add(CacheManager* cache, const std::string& key, char* argv[]){
    IMatrix matrix1(readFileContent(std::string(argv[3])));
    IMatrix matrix2(readFileContent(std::string(argv[4])));
    matrix1 += matrix2;
    cache->insert(key, std::string(argv[5]), matrix1.toString());
}

void testing::matrix::multiply(CacheManager* cache, const std::string& key, char* argv[]){
    IMatrix matrix1(readFileContent(std::string(argv[3])));
    IMatrix matrix2(readFileContent(std::string(argv[4])));
    matrix1 *= matrix2;
    cache->insert(key, std::string(argv[5]), matrix1.toString());
}