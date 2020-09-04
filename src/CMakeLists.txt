cmake_minimum_required(VERSION 3.0.0)
project(ex3 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# add the .cpp files of the project
add_executable(ex3.out BMP.cpp bmp_tester.cpp CacheManager.cpp file_reading.cpp main.cpp IMatrix.cpp matrix_tester.cpp MessageException.cpp)

# add the library
target_link_libraries(ex3.out matrix)

# add the folders of the .h files (to be able to include them)
# target_include_directories(ex3.out PUBLIC
#                             ${CMAKE_SOURCE_DIR}/bmp
#                             ${CMAKE_SOURCE_DIR}/cache
#                             ${CMAKE_SOURCE_DIR}/exceptions
#                             ${CMAKE_SOURCE_DIR}/hash
#                             ${CMAKE_SOURCE_DIR}/matrix
#                             ${CMAKE_SOURCE_DIR}/paths
#                             )

# make the cache directory
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/cache)

# include the src directory
target_link_directories(ex3.out PUBLIC ${PROJECT_SOURCE_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

