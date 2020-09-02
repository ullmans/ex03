#ifndef FILE_READING_H
#define FILE_READING_H

#include <string>

std::string readFileContent(const std::string& filePath);
void writeFileContent(const std::string& filePath, const std::string& content);

#endif