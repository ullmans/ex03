#include <fstream>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include "MessageException.hpp"

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