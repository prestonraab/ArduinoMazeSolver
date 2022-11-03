cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(ImageMazeSolver)

add_subdirectory(/Users/prestonraab/Downloads/oiio-master/src/include /bin)

add_executable(ImageMazeSolver main.cpp)

install(TARGETS ImageMazeSolver DESTINATION bin)


include_directories(/Users/prestonraab/Downloads/oiio-master/src/include/OpenImageIO PUBLIC)

target_link_libraries(ImageMazeSolver OpenImageIO)
