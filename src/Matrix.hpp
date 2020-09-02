#pragma once

#include <cstdint>
#include<string>

#include "Matrix.h"
#include "ErrorCode.h"

class Matrix {

public:
    /**
     * @brief create a new matrix from the given varoables.
     * 
     * @param height of the new matrix.
     * 
     * @param width of the new matrix.
     */
    Matrix(std::uint32_t height, std::uint32_t width);
    
    /**
     * @brief copy constractor.
     * 
     * 
     */
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);

    Matrix(Matrix&& other) noexcept = default;
    Matrix& operator=(Matrix&& other) = default;
    
	Matrix(const std::string& s);
	std::string toString() const;

    /**
     * @brief 
     */
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    friend Matrix operator*(const double scalar, const Matrix& matrix);
    double operator()(std::uint32_t rowInd, std::uint32_t colInd) const;
    void set(std::uint32_t rowInd, std::uint32_t colInd, double value);

    ~Matrix();

    std::uint32_t getHeight() const;
    std::uint32_t getWidth() const;
private:
    PMatrix matrix;
};
