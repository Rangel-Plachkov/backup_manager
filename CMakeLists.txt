cmake_minimum_required(VERSION 3.16)
project(Backup_Manager)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        include
        external
)

find_package(ZLIB REQUIRED)
target_link_libraries(${PROJECT_NAME}
        pthread
        ZLIB::ZLIB
)

