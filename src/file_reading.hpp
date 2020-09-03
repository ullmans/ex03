#ifndef FILE_READING_H
#define FILE_READING_H

#include <string>

/**
 * @brief Read the content of a file at path filePath.
 *
 * @param filePath The relative or absolute path to the file.
 * @return std::string File's content
 */
std::string readFileContent(const std::string& filePath);

/**
 * @brief Writes content to a file. If the file exists, removes
 *  previos content. Otherwise, creates a new file.
 *
 * @param filePath The relative or absolute path to the file.
 * @param content Content to write.
 */
void writeFileContent(const std::string& filePath, const std::string& content);

#endif