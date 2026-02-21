cmake_minimum_required(VERSION 3.21)

project(AtlasTool
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/Atlastor_Tool.cpp
    src/AtlasPacker.cpp
    src/stb_image_impl.cpp
    src/AtlasRectPacker.cpp
)

set(HEADERS
  "src/AtlasPacker.h"
   "src/AtlasRectPacker.h"
    "src/AtlasPackerTypes.h"
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME} PRIVATE external/stb)
target_include_directories(${PROJECT_NAME} PRIVATE external/rectpack2D)