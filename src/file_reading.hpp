#pragma once

#include <string>


std::string readFileContent(const std::string& filePath);
std::string readTextFileContent(const std::string& filePath);
void writeFileContent(const std::string& filePath, const std::string& content);
