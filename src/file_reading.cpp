#include <fstream>
#include <iterator>
#include <string>
#include "iostream"
#include <sstream>

/**
 * @brief Read the content of a file at path filePath.
 *
 * @param filePath The relative or absolute path to the file.
 * @return std::string File's content
 */
std::string readFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream) in binary mode.
  std::ifstream in(filePath, std::ios::binary);
  std::ostringstream os;
  os << in.rdbuf();
  return os.str();
}

std::string readTextFileContent(const std::string& filePath) {
  // Opens input-only file (ifstream).
  std::ifstream in(filePath, std::ios::in);
  std::ostringstream os;
  os << in.rdbuf();
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
	  
  }

  out.write(content.data(), static_cast<std::streamsize>(content.length()));
  if (!out) {
  }
}

