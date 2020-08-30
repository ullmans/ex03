#include <string>
#include <stdint.h>

#include "Matrix.hpp"
#include "CacheManager.hpp"
#include "bmp_tester.hpp"
#include "BMP.hpp"

int main(uint32_t argc, char* argv[]){
    if(argv[1] == "matrix"){
        if(argv[2] == "add"){

        } else if(argv[2] == "multiply"){

        } else {
            //throw exception
        }

    } else if(argv[1] == "image"){
        if(argv[2] == "rotate"){

        } else if(argv[2] == "convert"){

        } else {
            //throw exception
        }

    } else if(argv[1] == "hash"){
        if(argv[2] == "algorithem"){
        
        } else {
            //throw exception
        }

    } else if(argv[1] == "cache"){
        if(argv[2] == "clear"){
            //need to add a clear function to cacheManager
        } else if(argv[2] == "search"){
            
        }

    } else {
        //throw exception
    }
}
