#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include "MessageException.hpp"

/**
 * @brief Read the content of a file at path filePath.
 *
 * @param filePath The relative or absolute path to the file.
 * @return std::string File's content
 */
std::string readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);

  // The file is in a bad state.
  if (!in) {
      throw MessageException("Opening file failed");
  }

  // If Read the file to an std::ostringstream.
  std::ostringstream os;
  os << in.rdbuf();

  // If reading from the file failed
  if (!in) {
      throw MessageException("Reading from file failed");
  }

  in.close();

  return os.str();
}

/**
 * @brief Writes content to a file. If the file exists, removes
 *  previos content. Otherwise, creates a new file.
 *
 * @param filePath The relative or absolute path to the file.
 * @param content Content to write.
 */
void writeFileContent(const std::string& filePath, const std::string& content) {
  // Opens output-only file (ofstream) in binary mode, and truncates all
  //    existing content from the file.
  std::ofstream out(filePath, std::ios::binary | std::ios::trunc);

  // The file is in a bad state.
  if (!out) {
      throw MessageException("Opening file failed");
  }

  out.write(content.data(), static_cast<std::streamsize>(content.length()));
  if (!out) {
      throw MessageException("Writing to file failed");
  }

  out.close();
}