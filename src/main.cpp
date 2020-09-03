#include <string>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include "IMatrix.hpp"
#include "CacheManager.hpp"
#include "bmp_tester.hpp"
#include "matrix_tester.hpp"
#include "BMP.hpp"
#include "file_reading.hpp"
#include "MessageException.hpp"
#include "crc32.c"

void matrixArguments(CacheManager* cache, char* argv[]){
    //check if we have the action in the cache
    std::string key = "matrix_" + std::string(argv[2]) + '_' + std::string(argv[3]) + '_' + std::string(argv[4]);
    //1 -> if we have it
    if(cache->search(key)){
        cache->insert(key, std::string(argv[5]), cache->get(key));
    //0 -> if we do not have it
    } else {
        if(std::string(argv[2]).compare("add") == 0){
            //add the matrices
            testing::matrix::add(cache, key, argv);
        } else if(std::string(argv[2]).compare("multiply") == 0){
            //multiply the matrices
            testing::matrix::multiply(cache, key, argv);
        } else {
            throw MessageException("the argunments are not a valid command");
        }
    }
}

void imageArguments(CacheManager* cache, char* argv[]){
    //check if we have the action in the cache
    std:: string key = "image_" + std::string(argv[2]) + '_' + std::string(argv[3]);
    //1 -> if we have it
    if(cache->search(key)){
        cache->insert(key, std::string(argv[5]), cache->get(key));
    //0 -> if we dont have it
    } else {
        if(std::string(argv[2]).compare("rotate") == 0){
            //rotate the image
            testing::bmp::rotate_image(cache, key, argv);
        } else if(std::string(argv[2]).compare("convert") == 0){
            //convert the image
            testing::bmp::convert_to_grayscale(cache, key, argv);
        } else {
            throw MessageException("the argunments are not a valid command");
        }
    }
}

void hashArguments(CacheManager* cache, char* argv[]){
    if(std::string(argv[2]).compare("crc32") == 0){
        //calculate hash
        std::fstream in(std::string(argv[3]), std::ios::binary);
        if(!in){
            throw MessageException("could not open th egiven file");
        }
        std::vector<unsigned char> data((std::istream_iterator<unsigned char>(in)), 
                                        (std::istream_iterator<unsigned char>()));
        in.close();
        uint32_t fileHash =  calculate_crc32c(0, data.data(), data.size());
        if (std::string(argv[4]).compare("stdout")){
            std::cout << std::to_string(fileHash) << std::endl;
        } else {
            std::string key = "hash_crc32_" + std::string(argv[3]) + '_' + std::string(argv[4]);
            cache->insert(key, std::string(argv[4]), std::to_string(fileHash)); 
        }
    } else {
        throw MessageException("the argunments are not a valid command");
    }
}

void cacheArguments(CacheManager* cache, char* argv[]){
    if(std::string(argv[2]).compare("clear") == 0){
        cache->clear();
    } else if(std::string(argv[2]).compare("search") == 0){
        std::string key;
        if (std::string(argv[3]).compare("matrix") == 0) {
            key = "matrix_" + std::string(argv[4]) + '_' + std::string(argv[5]) + '_' + std::string(argv[6]);
        }
        else if (std::string(argv[3]).compare("image") == 0) {
            key = "image_" + std::string(argv[4]) + '_' + std::string(argv[5]);
        }
        else if (std::string(argv[3]).compare("crc32") == 0) {
            key = "hash_crc32_" + std::string(argv[4]);
        }

        if(cache->search(key)){
            std::cout << "result found in cache" << std::endl;
        }
    } else {
        throw MessageException("the argunments are not a valid command");
    }
}

int main(int argc, char* argv[]){
    argc += 1;

    CacheManager cache = CacheManager(100);   //what is the size?
    cache.loadCacheList();

    //for matrix
    if(std::string(argv[1]).compare("matrix") == 0){
        matrixArguments(&cache, argv);

    //for image (BMP)
    } else if(std::string(argv[1]).compare("image") == 0){
        imageArguments(&cache, argv);
    
    //for hash
    } else if(std::string(argv[1]).compare("hash") == 0){
        //hashArguments(&cache, argv);

    //for cache
    } else if(std::string(argv[1]).compare("cache") == 0){
        cacheArguments(&cache, argv);

    //not a valid command
    } else {
        throw MessageException("the argunments are not a valid command");
    }

    cache.saveCacheList();
}