cmake_minimum_required(VERSION 3.11)

project(Live CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

set(HPP setting.h point.h board.h frame.h game.h)
set(CPP setting.cpp point.cpp board.cpp frame.cpp game.cpp)

add_subdirectory(SDL-release-2.0.10)
add_executable(live WIN32 main.cpp ${HPP} ${CPP})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT live)

target_link_libraries(live SDL2 SDL2main)
target_include_directories(live PUBLIC SDL-release-2.0.10/include)


