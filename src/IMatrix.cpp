#include <cstdint>
#include <algorithm>
#include "ErrorCode.h"
#include "Matrix.h"
#include "IMatrix.hpp"
#include "MessageException.hpp"


IMatrix::IMatrix(std::uint32_t height, std::uint32_t width) {
    ErrorCode error = matrix_create(&matrix, height, width);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
}

IMatrix::IMatrix(const IMatrix& other) {
    ErrorCode error = matrix_copy(&(this->matrix), other.matrix);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
}

IMatrix& IMatrix::operator=(const IMatrix& other) {
    matrix_destroy(this->matrix); // release the stored matrix.
    ErrorCode error = matrix_copy(&this->matrix, other.matrix);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return *this;
}
    
IMatrix::~IMatrix() {
    matrix_destroy(this->matrix);
}

IMatrix::IMatrix(const std::string& s) {
    
	const std::uint32_t height = static_cast<uint32_t>(std::count(s.begin(), s.end(), '\n') + 1);
    const std::uint32_t width = static_cast<uint32_t>(std::count(s.begin(), s.begin() + s.find_first_of('\n'), ',') + 1);
	ErrorCode error = matrix_create(&matrix, height, width);
	if (!error_isSuccess(error)) {
		throw MessageException(error_getErrorMessage(error));
	}
	std::uint32_t rowIndex = 0;
	std::uint32_t colIndex = 0;
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

std::string IMatrix::toString() const {
	const std::uint32_t height = getHeight();
	const std::uint32_t width = getWidth();
	std::string matString;
	for (std::uint32_t i = 0; i < height; i++) {
		for (std::uint32_t j = 0; j < width; j++) {
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

std::uint32_t IMatrix::getHeight() const {
    std::uint32_t result;
    ErrorCode error = matrix_getHeight(this->matrix, &result);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return result;
}

std::uint32_t IMatrix::getWidth() const {
    std::uint32_t result;
    ErrorCode error = matrix_getWidth(this->matrix, &result);
    if (!error_isSuccess(error)) {
        throw MessageException(error_getErrorMessage(error));
    }
    return result;
}

IMatrix& IMatrix::operator+=(const IMatrix& other) {
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

IMatrix& IMatrix::operator-=(const IMatrix& other) {
    return *this += (-1.0 * other);
}

IMatrix& IMatrix::operator*=(const IMatrix& other) {
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

IMatrix IMatrix::operator+(const IMatrix& other) const {
    IMatrix res = *this;
    res += other;
    return res;
}

IMatrix IMatrix::operator-(const IMatrix& other) const {
    return *this + (-1.0 * other);
}

IMatrix IMatrix::operator*(const IMatrix& other) const {
    IMatrix res = *this;
    res *= other;
    return res;
}

double IMatrix::operator()(std::uint32_t rowInd, std::uint32_t colInd) const {
    double result;
    ErrorCode errorAccessingMatrix = matrix_getValue(this->matrix, rowInd, colInd, &result);
    if (!error_isSuccess(errorAccessingMatrix)) {
        throw MessageException(error_getErrorMessage(errorAccessingMatrix));
    }
    return result;
}

void IMatrix::set(std::uint32_t rowInd, std::uint32_t colInd, double value) {
    ErrorCode errorSettingValue = matrix_setValue(this->matrix, rowInd, colInd, value);
    if (!error_isSuccess(errorSettingValue)) {
        throw MessageException(error_getErrorMessage(errorSettingValue));
    }
}

IMatrix operator*(const double scalar, const IMatrix& matrix) {
    IMatrix result = matrix;
    ErrorCode errorMultiplying = matrix_multiplyWithScalar(result.matrix, scalar);
    if (!error_isSuccess(errorMultiplying)) {
        throw MessageException(error_getErrorMessage(errorMultiplying));
    }
    return result;
    
}