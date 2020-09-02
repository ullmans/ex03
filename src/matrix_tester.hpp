#pragma once

#include <string>

#include "CacheManager.hpp"

namespace testing {
namespace matrix {

void add(CacheManager cache, const std::string& path, char* argv[]);
void multiply(CacheManager cache, const std::string& path, char* argv[]);

}
}