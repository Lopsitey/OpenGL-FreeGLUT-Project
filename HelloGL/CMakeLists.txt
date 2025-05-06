cmake_minimum_required(VERSION 3.10)
project(HelloGLcmake)

#Ensure it's 32-bit (x86)
set(CMAKE_GENERATOR_PLATFORM x86) 

#Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

add_executable(HelloGL main.cpp HelloGL.cpp)

#Add include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/FT
    ${CMAKE_SOURCE_DIR}/GL
)

#Add library directories
link_directories(
    ${CMAKE_SOURCE_DIR}/lib
)

#Add library dependencies
target_link_libraries(
    HelloGL
    freetype
    freeglut
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_UNICODE /DUNICODE /wd4996")
endif()