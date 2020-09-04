#pragma once

#include <cstdint>
#include<string>

#include "Matrix.h"
#include "ErrorCode.h"

class IMatrix {

public:
    /**
     * @brief create a new matrix from the given varoables.
     * 
     * @param height of the new matrix.
     * 
     * @param width of the new matrix.
     */
    IMatrix(std::uint32_t height, std::uint32_t width);
    
    /**
     * @brief copy constractor.
     * 
     * 
     */
    IMatrix(const IMatrix& other);
    IMatrix& operator=(const IMatrix& other);

    IMatrix(IMatrix&& other) noexcept = default;
    IMatrix& operator=(IMatrix&& other) = default;
    
	IMatrix(const std::string& s);
	std::string toString() const;

    /**
     * @brief 
     */
    IMatrix& operator+=(const IMatrix& other);
    IMatrix& operator-=(const IMatrix& other);
    IMatrix& operator*=(const IMatrix& other);
    IMatrix operator+(const IMatrix& other) const;
    IMatrix operator-(const IMatrix& other) const;
    IMatrix operator*(const IMatrix& other) const;
    friend IMatrix operator*(const double scalar, const IMatrix& matrix);
    double operator()(std::uint32_t rowInd, std::uint32_t colInd) const;
    void set(std::uint32_t rowInd, std::uint32_t colInd, double value);

    ~IMatrix();

    std::uint32_t getHeight() const;
    std::uint32_t getWidth() const;
private:
    PMatrix matrix;
};
