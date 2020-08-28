#pragma once

#include <stdint.h>
#include <memory>
#include <string>
#include "Matrix.hpp"


class BMP {
    std::unique_ptr<Matrix> bitmap;
    std::unique_ptr<Matrix> colorPalette;
    std::string reservedAtStart;
    uint32_t bitsPerPixel;
    uint32_t horizontalResolution;
    uint32_t verticalResolution;
    
public:
    /**
     * @brief constractor- create a new BMP from the given ref to string.
     * read the string according to the BMP format and save the information.
     * 
     * @param string& - a ref to the file (a binary string).
     */
    BMP(const std::string&);

    /**
     * rotate the BMP 90 degrees.
     */
    void rotate();

    /**
     * make a new picture that look like the original, expect that this is a gray one.
     */
    void toGrayscale();

    /**
     * @brief make a sring from a BMP object, according to the BMP format.
     * 
     * @return a binary std::string that has the file's content (binary).
     */
    std::string  toString();
};