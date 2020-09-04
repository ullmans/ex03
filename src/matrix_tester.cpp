#include <string>
#include <iostream>
#include <fstream>
#include "IMatrix.hpp"
#include "file_reading.hpp"
#include "matrix_tester.hpp"
#include "CacheManager.hpp"


void insertResultIMatrixToCache(CacheManager* cache, const std::string& key, char* argv[], const IMatrix& result) {
    std::string matrix1_string = result.toString();

    std::cout << matrix1_string << std::endl; 

    if (!std::string(argv[5]).compare("stdout") == 0) {
        std::cout << matrix1_string << std::endl;
    }
    else {
        cache->insert(key, std::string(argv[5]), matrix1_string);
    }
}

void testing::matrix::add(CacheManager* cache, const std::string& key, char* argv[]){
    IMatrix matrix1(readFileContent(std::string(argv[3])));
    IMatrix matrix2(readFileContent(std::string(argv[4])));
    matrix1 += matrix2;
    insertResultIMatrixToCache(cache, key, argv, matrix1);
}

void testing::matrix::multiply(CacheManager* cache, const std::string& key, char* argv[]) {
    IMatrix matrix1(readFileContent(std::string(argv[3])));
    IMatrix matrix2(readFileContent(std::string(argv[4])));
    matrix1 *= matrix2;
    insertResultIMatrixToCache(cache, key, argv, matrix1);
}