cmake_minimum_required(VERSION 3.15...4.0.0)

include(FetchContent)
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
  GIT_TAG        v3.3.1
)
FetchContent_MakeAvailable(cxxopts)

project(file_sys LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(file_sys src/main.cpp src/file_sys.cpp)

target_link_libraries(file_sys PRIVATE cxxopts::cxxopts)