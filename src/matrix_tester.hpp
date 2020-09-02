#pragma once

#include <string>

namespace testing {
namespace matrix {

void testing::matrix::add(CacheManager cache, const std::string& path, char* argv[]);
void testing::matrix::multiply(CacheManager cache, const std::string& path, char* argv[]);

}
}