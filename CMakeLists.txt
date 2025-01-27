cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 23)
project(cpp VERSION 0.1.0)

# Add all provided files to the executable
file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(
    ${PROJECT_NAME} 
    ${SRC_FILES}
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE src)

