#include <string>
#include <stdint.h>
#include <bitset>
#include <math.h>

#include "MessageException.hpp"
#include "BMP.hpp"

//Added right now
#include "IMatrix.hpp"


// returns the part of 'str' starting at 'start' and with length of 'length'.
std::string read(const uint32_t start, const uint32_t length, const std::string& str) {
    std::string res;
    for (uint32_t i = start; i < start + length; ++i) {
        if (i >= str.length()) {
            break;
        }
        res.push_back(str.at(i));
    }
    return res;
}

// checks if the file starts with 'BM'.
bool checkStart(const std::string& bmpFile) {
    if (bmpFile.at(0) != 'B' || bmpFile.at(1) != 'M') { 
        return false;
    }
    return true;
}

// receives a string, where each char represent a byte, and returns the correct int.
// reads it in little endian.
uint32_t byteStringToInt(const std::string& str) {
    uint32_t res = 0;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        res <<= 8;
        res += (uint8_t)*it;
    }
    return res;
}

// does the opposite of byteStringToInt.
std::string intToByteString(uint32_t num, const uint32_t size) {
    std::string res;
    while (num > 0) {
        res.push_back(num & 0xFF);
        num >>= 8;
    }
    if (res.size() < size) {
        res.append(std::string(size - res.size(), 0));
    }
    return res;
}

BMP::BMP(const std::string& bmpFile) {
    uint32_t placeParsing = 0; // the position of parsing the string into BMP object.
    if (!checkStart(bmpFile)) {
        throw MessageException("file must start with BM");
    }

    placeParsing = 6;

    reservedAtStart = read(placeParsing, 4, bmpFile);

    placeParsing = 10;
    uint32_t pixelArrayOffset = byteStringToInt(read(placeParsing, 4, bmpFile)); // the offset of the pixel array.
    
    placeParsing = 14;

    // the size of the DIB header - must be 40.
    uint32_t dibSize = byteStringToInt(read(placeParsing, 4, bmpFile));
    if ( dibSize != 40) {
        throw MessageException("DIB header size must be 40");
    }
    placeParsing += 4;
    
    // the Width and the Height of the bitmap array.
    uint32_t bitmapWidth = byteStringToInt(read(placeParsing, 4, bmpFile));
    placeParsing += 4;
    uint32_t bitmapHeight = byteStringToInt(read(placeParsing, 4, bmpFile));

    bitmap = std::make_unique<IMatrix>(bitmapHeight, bitmapWidth);

    placeParsing = 26;

    // in this place there's a constant, which must be 1.
    uint32_t constant = byteStringToInt(read(placeParsing, 2, bmpFile)); 
    if (constant != 1) {
        
        throw MessageException("constant must be 1");
    }

    placeParsing = 28;

    // the number of bits saved for each pixel in the 
    this->bitsPerPixel = byteStringToInt(read(placeParsing, 2, bmpFile));

    // the resolution of the image.
    placeParsing = 38;
    this->horizontalResolution = byteStringToInt(read(placeParsing, 4, bmpFile));
    placeParsing += 4;
    this->verticalResolution = byteStringToInt(read(placeParsing, 4, bmpFile));
     

    placeParsing = 54;
    if (bitsPerPixel == 8) { // then color palette should appear.
        // the color palette size is at index 46 and takes 4 bytes.
        uint32_t colorPaletteSize = byteStringToInt(read(46, 4, bmpFile)); 
        if (colorPaletteSize == 0) {
            colorPaletteSize = 1 << bitsPerPixel;
        }
        
        colorPalette = std::make_unique<IMatrix>(1, colorPaletteSize);
        for (uint32_t i = 0; i < colorPaletteSize; ++i) {
            uint32_t rgbValue = byteStringToInt(read(placeParsing, 4, bmpFile));
            placeParsing += 4;
            colorPalette->set(0, i, (double) rgbValue);
        }
    }

    uint32_t paddingSize =  4 - ((bitsPerPixel / 8 * bitmapWidth) % 4); // the padding size in bytes.
    if (paddingSize == 4) {
        paddingSize = 0;
    }
    placeParsing = pixelArrayOffset;
    for (uint32_t i = 0; i < bitmapHeight; ++i) {
        for (uint32_t j = 0; j < bitmapWidth; ++j) {
            uint32_t value = byteStringToInt(read(placeParsing, bitsPerPixel / 8, bmpFile));
            bitmap->set(i, j,  value);
            placeParsing += bitsPerPixel / 8;
        }
        placeParsing += paddingSize;
    }
}


std::string BMP::toString() {
    std::string str;
    
    // we starts after the size of the file.
    // we'll add 'BM' and the size of the file at the end.
    str.append(reservedAtStart);

    uint32_t offset = 54;
    if (bitsPerPixel == 8) {
        offset += 4 * this->colorPalette->getWidth(); // each RGB in the color palette takes 4 bytes.
    }
    str.append(intToByteString(offset, 4));

    str.append(intToByteString(40, 4));
    str.append(intToByteString(this->bitmap->getWidth(), 4));
    str.append(intToByteString(this->bitmap->getHeight(), 4));
    str.append(intToByteString(1, 2));
    str.append(intToByteString(bitsPerPixel, 2));
    str.append(intToByteString(0, 4));
    str.append(intToByteString((bitsPerPixel / 8) * this->bitmap->getWidth() * this->bitmap->getHeight(), 4));
    str.append(intToByteString(horizontalResolution, 4));
    str.append(intToByteString(verticalResolution, 4));
    
    if (bitsPerPixel == 8) {
        uint32_t colorPaletteSize = this->colorPalette->getWidth();
        if (colorPaletteSize == (uint32_t) 1 << bitsPerPixel) {
            str.append(intToByteString(0, 4));
        } else {
            str.append(intToByteString(colorPaletteSize, 4));
        }
    } else {
        str.append(intToByteString(0, 4));
    }
    str.append(intToByteString(0, 4));

    if (bitsPerPixel == 8) {
        for (uint32_t i = 0; i < this->colorPalette->getWidth(); ++i) {
            uint32_t value = (uint32_t) (*(this->colorPalette))(0, i);
            str.append(intToByteString(value, 4));
        }
    }

    uint32_t bytesInRow = bitmap->getWidth() * (bitsPerPixel / 8);
    uint32_t paddingSize = 4-(bytesInRow % 4); // in bytes.
    if (paddingSize == 4) {
        paddingSize =0;
    }
    std::string paddingString(paddingSize, 0); // the padding string - just zeros.

    for (uint32_t i = 0; i < this->bitmap->getHeight(); ++i) {
        for (uint32_t j = 0; j < this->bitmap->getWidth(); ++j) {
            uint32_t value = (uint32_t)(*(this->bitmap))(i, j);
            str.append(intToByteString(value, bitsPerPixel / 8));
            
        }
        str.append(paddingString);
    }

    uint32_t size = 2 + 4 + (uint32_t) str.size();
    std::string res;
    res.push_back('B');
    res.push_back('M');
    res.append(intToByteString(size, 4));
    res.append(str);
    return res;
}


void BMP::rotate() {
    IMatrix bitmapCopy = *(this->bitmap);
    uint32_t newHeight = (this->bitmap)->getWidth();
    uint32_t newWidth = (this->bitmap)->getHeight();
    this->bitmap = std::make_unique<IMatrix>(newHeight, newWidth);

    for (uint32_t i = 0; i < newHeight; ++i) {
        for (uint32_t j = 0; j < newWidth; ++j) {
            (this->bitmap)->set(i, j, bitmapCopy(j, i));
        }
    } // now the matrix is a transpose of what it was.

    // reverse each column.
    for (uint32_t i = 0; i < newHeight / 2; ++i) {
        for (uint32_t j = 0; j < newWidth; ++j) {
            double value1 = (*(this->bitmap))(i, j);
            double value2 = (*(this->bitmap))(newHeight - 1 - i, j);
            (this->bitmap)->set(i, j, value2);
            (this->bitmap)->set(newHeight -1 - i, j, value1);
        }
    }

    // replace vertical resolution and horizontal resolution
    uint32_t temp = this->verticalResolution;
    this->verticalResolution = this->horizontalResolution;
    this->horizontalResolution = temp;
}

uint32_t rgbToGrayscale(uint32_t rgb, bool isFourByte) {
    uint8_t r, g, b;
    if (isFourByte) {
        rgb >>= 8;
    }
    b = rgb & 0xFF;
    rgb >>= 8;
    g = rgb & 0xFF;
    rgb >>= 8;
    r = rgb & 0xFF;

    uint8_t value = (uint8_t) round(0.2126*r + 0.7152*g + 0.0722*b);
    uint32_t res = value << 16 | value << 8 | value;
    if (isFourByte) {
        res <<= 8;
    }
    return res;
}

void BMP::toGrayscale() {
    if (bitsPerPixel == 8) {
        for (uint32_t i = 0; i < this->colorPalette->getWidth(); ++i) {
            uint32_t value = (uint32_t)(*(this->colorPalette))(0, i);
            uint32_t newVal = rgbToGrayscale(value, true);
            this->colorPalette->set(0, i, (double)newVal);
        }
    } else {
        for (uint32_t i = 0; i < this->bitmap->getHeight(); ++i) {
            for (uint32_t j = 0; j < this->bitmap->getWidth(); ++j) {
                uint32_t value = (uint32_t)(*(this->bitmap))(i, j);
                uint32_t newVal = rgbToGrayscale(value, false);
                this->bitmap->set(i, j, (double)newVal);
            }
        }
    }
}