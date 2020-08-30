#include <stdint.h>
#include <algorithm>
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

std::string** turnStringTo2dArray(const std::string & s, const char row_delim, const char col_delim) {
	const uint32_t height = std::count(s.begin(), s.end(), row_delim);
	uint32_t pos = 0;
	std::string token;
	while ((pos = s.find(row_delim)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());       //there is an error here -what is "delmeter"?
	}
}

Matrix::Matrix(const std::string& s) {
	const uint32_t height = std::count(s.begin(), s.end(), '\n') + 1;
	//const uint32_t width = s.find('\n');
    const uint32_t width = std::count(s.begin(), s.find('\n'), ',') + 1;
	ErrorCode error = matrix_create(&matrix, height, width);
	if (!error_isSuccess(error)) {
		throw MessageException(error_getErrorMessage(error));
	}
	uint32_t rowIndex = 0;
	uint32_t colIndex = 0;
	std::string temp;
	for (auto it = s.begin(); it != s.end(); ++it) {
		if (*it != ',' && *it != '\n') {
			temp += *it;
			continue;
		}
		set(rowIndex, colIndex, std::stod(temp));
		temp.clear();
		if (*it == ',') {
			colIndex++;
		}
		else if (*it == '\n') {
			rowIndex++;
			colIndex = 0;
		}
	}
}

std::string Matrix::toString() const {
	const uint32_t height = getHeight();
	const uint32_t width = getWidth();
	std::string matString;
	for (uint32_t i = 0; i < height; i++) {
		for (uint32_t j = 0; j < width; j++) {
			matString += std::to_string(operator()(i, j));
			if (j < width - 1) {
				matString += ",";
			}
		}
		if (i < height - 1) {
			matString += "\n";
		}
	}
	return matString;
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