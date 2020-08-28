#include <stdint.h>

#include "Matrix.h"
#include "ErrorCode.h"
#include "Matrix.hpp"
#include "MessageException.hpp"


Matrix::Matrix(uint32_t height, uint32_t width) {
    ErrorCode error = matrix_create(&matrix, height, width);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
}

Matrix::Matrix(const Matrix& other) {
    ErrorCode error = matrix_copy(&this->matrix, other.matrix);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
}

Matrix& Matrix::operator=(const Matrix& other) {
    matrix_destroy(this->matrix); // release the stored matrix.
    ErrorCode error = matrix_copy(&this->matrix, other.matrix);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return *this;
}
    
Matrix::~Matrix() {
    matrix_destroy(this->matrix);
}

uint32_t Matrix::getHeight() const {
    uint32_t result;
    ErrorCode error = matrix_getHeight(this->matrix, &result);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return result;
}

uint32_t Matrix::getWidth() const {
    uint32_t result;
    ErrorCode error = matrix_getWidth(this->matrix, &result);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    PMatrix temp;
    ErrorCode errorCreatingTempMatrix = matrix_create(&temp, this->getHeight(), this->getWidth());
    if (!error_isSuccess(errorCreatingTempMatrix)) {
        throw MessageException(error_getErrorMessage(errorCreatingTempMatrix));
    }
    
    ErrorCode errorCopyingMatrix = matrix_copy(&temp, this->matrix);
    if (!error_isSuccess(errorCopyingMatrix)) {
        throw MessageException(error_getErrorMessage(errorCopyingMatrix));
    }
    
    ErrorCode errorAddingTheMatrix = matrix_add(&this->matrix, temp, other.matrix);
    if (!error_isSuccess(errorAddingTheMatrix)) {
        throw MessageException(error_getErrorMessage(errorAddingTheMatrix));
    }

    matrix_destroy(temp);
    
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& other) {
    return *this += (-1.0 * other);
}

Matrix& Matrix::operator*=(const Matrix& other) {
    PMatrix temp;
    ErrorCode errorCreatingTempMatrix = matrix_create(&temp, this->getHeight(), this->getWidth());
    if (!error_isSuccess(errorCreatingTempMatrix)) {
        throw MessageException(error_getErrorMessage(errorCreatingTempMatrix));
    }
    
    ErrorCode errorCopyingMatrix = matrix_copy(&temp, this->matrix);
    if (!error_isSuccess(errorCopyingMatrix)) {
        throw MessageException(error_getErrorMessage(errorCopyingMatrix));
    }
    
    ErrorCode errorMultiplyTheMatrix = matrix_multiplyMatrices(&this->matrix, temp, other.matrix);
    if (!error_isSuccess(errorMultiplyTheMatrix)) {
        throw MessageException(error_getErrorMessage(errorMultiplyTheMatrix));
    }
    matrix_destroy(temp);
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    Matrix res = *this;
    res += other;
    return res;
}

Matrix Matrix::operator-(const Matrix& other) const {
    return *this + (-1.0 * other);
}

Matrix Matrix::operator*(const Matrix& other) const {
    Matrix res = *this;
    res *= other;
    return res;
}

double Matrix::operator()(uint32_t rowInd, uint32_t colInd) const {
    double result;
    ErrorCode errorAccessingMatrix = matrix_getValue(this->matrix, rowInd, colInd, &result);
    if (!error_isSuccess(errorAccessingMatrix)) {
        throw MessageException(error_getErrorMessage(errorAccessingMatrix));
    }
    return result;
}

void Matrix::set(uint32_t rowInd, uint32_t colInd, double value) {
    ErrorCode errorSettingValue = matrix_setValue(this->matrix, rowInd, colInd, value);
    if (!error_isSuccess(errorSettingValue)) {
        throw MessageException(error_getErrorMessage(errorSettingValue));
    }
}

Matrix operator*(const double scalar, const Matrix& matrix) {
    Matrix result = matrix;
    ErrorCode errorMultiplying = matrix_multiplyWithScalar(result.matrix, scalar);
    if (!error_isSuccess(errorMultiplying)) {
        throw MessageException(error_getErrorMessage(errorMultiplying));
    }
    return result;
    
}