# Config
cmake_minimum_required(VERSION 3.26)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
project( OpenCVExercises )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
# Opdrachten
add_executable( Exercise2_1 src/Exercise2_1.cpp )
target_link_libraries( Exercise2_1 ${OpenCV_LIBS} )
add_executable( Exercise2_2 src/Exercise2_2.cpp )
target_link_libraries( Exercise2_2 ${OpenCV_LIBS} )
add_executable( Exercise2_3 src/Exercise2_3.cpp )
target_link_libraries( Exercise2_3 ${OpenCV_LIBS} )