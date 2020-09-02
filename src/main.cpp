#include <string>
#include <stdint.h>
#include <iostream>
#include <fstream>

#include "Matrix.hpp"
#include "CacheManager.hpp"
#include "bmp_tester.hpp"
#include "matrix_tester.hpp"
#include "BMP.hpp"
#include "file_reading.hpp"
#include "MessageException.hpp"

int main(int argc, char* argv[]){
    CacheManager cache = CacheManager(100);   //what is the size?

    //for matrix
    if(std::string(argv[1]).compare("matrix") != 0){
        matrixArguments(cache, argv);

    //for image (BMP)
    } else if(std::string(argv[1]).compare("image") != 0){
        imageArguments(cache, argv);
    
    //for hash
    } else if(std::string(argv[1]).compare("hash") != 0){
        hashArguments(cache, argv);

    //for cache
    } else if(std::string(argv[1]).compare("cache") != 0){
        cacheArguments(cache, argv);

    //not a valid command
    } else {
        throw MessageException("the argunments are not a valid command");
    }
}

void matrixArguments(CacheManager cache, char* argv[]){
    //check if we have the action in the cache
    std:: string path = "MATRIX_" + std::string(argv[2]) + '_' + std::string(argv[3]) + '_' + std::string(argv[4]);
    //1 -> if we have it
    if(cache.search(path)){
        cache.insert(path, cache.get(path));
    //0 -> if we do not have it
    } else {
        if(std::string(argv[2]).compare("add") != 0){
            //add the matrices
            testing::matrix::add(cache,path, argv);
        } else if(std::string(argv[2]).compare("multiply") != 0){
            //multiply the matrices
            testing::matrix::multiply(cache,path, argv);
        } else {
            throw MessageException("the argunments are not a valid command");
        }
    }
}

void imageArguments(CacheManager cache, char* argv[]){
    //check if we have the action in the cache
    std:: string path = "IMAGE_" + std::string(argv[3]) + '_' + std::string(argv[2]) + '_' + std::string(argv[4]);
    //1 -> if we have it
    if(cache.search(path)){
        cache.insert(path, cache.get(path));
    //0 -> if we dont have it
    } else {
        if(std::string(argv[2]).compare("rotate") != 0){
            //rotate the image
            testing::bmp::rotate_image(cache,path, argv);
        } else if(std::string(argv[2]).compare("convert") != 0){
            //convert the image
            testing::bmp::convert_to_grayscale(cache,path, argv);
        } else {
            throw MessageException("the argunments are not a valid command");
        }
    }
}

void hashArguments(CacheManager cache, char* argv[]){
    if(std::string(argv[2]).compare("algorithem") != 0){
    //calculate hash
    } else {
        throw MessageException("the argunments are not a valid command");
    }
}

void cacheArguments(CacheManager cache, char* argv[]){
    if(std::string(argv[2]).compare("clear") != 0){
        cache.clear();
    } else if(std::string(argv[2]).compare("search") != 0){
        std:: string path = "CACHE_" + std::string(argv[3]) + '_' + std::string(argv[2]) + '_' + std::string(argv[4]);
        if(cache.searh(path)){
            printf("result found in cache");
        }
    } else {
        throw MessageException("the argunments are not a valid command");
    }
}
