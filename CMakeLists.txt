cmake_minimum_required(VERSION 3.21)
project(AtlasTool
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependencias externas ---
include(FetchContent)

FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(stb)

FetchContent_Declare(
    rectpack2D
    GIT_REPOSITORY https://github.com/TeamHypersomnia/rectpack2D.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(rectpack2D)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG        v1.91.9
)
FetchContent_MakeAvailable(imgui)

# --- ImGui no tiene CMakeLists propio ---
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PUBLIC glfw)

# --- Tu ejecutable ---
set(SOURCES
    src/Atlastor_Tool.cpp
    src/AtlasPacker.cpp
    src/stb_image_impl.cpp
    src/AtlasRectPacker.cpp
)
set(HEADERS
    src/AtlasPacker.h
    src/AtlasRectPacker.h
    src/AtlasPackerTypes.h
)
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)
target_include_directories(${PROJECT_NAME} PRIVATE
    ${stb_SOURCE_DIR}
    ${rectpack2d_SOURCE_DIR}/src/rectpack2D
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    glfw
    opengl32
)