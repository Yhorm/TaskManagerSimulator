# Versão mínima do CMake
cmake_minimum_required(VERSION 3.15)

# Nome do seu projeto
project(TaskManagerSimulator LANGUAGES C CXX)

# Use o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)


# --- GLAD (OpenGL Loader) ---
# Adiciona o GLAD como uma biblioteca
add_library(glad STATIC 
    libraries/glad/glad.c
)
target_include_directories(glad PUBLIC 
    libraries/glad # Para encontrar glad.h
)

# --- GLFW (Windowing) ---
# Baixa e configura o GLFW automaticamente
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.3.8 # Use uma tag de release estável
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

# --- Dear ImGui ---
# Adiciona o ImGui como uma biblioteca
add_library(imgui STATIC
    libraries/imgui/imgui.cpp
    libraries/imgui/imgui_draw.cpp
    libraries/imgui/imgui_tables.cpp
    libraries/imgui/imgui_widgets.cpp
    libraries/imgui/imgui_demo.cpp 
    # Backend
    libraries/imgui/backends/imgui_impl_glfw.cpp
    libraries/imgui/backends/imgui_impl_opengl3.cpp
)
# Informa ao CMake onde encontrar os headers do ImGui
target_include_directories(imgui PUBLIC 
    libraries/imgui
    libraries/imgui/backends
)

find_package(OpenGL REQUIRED)


file(GLOB SOURCES "source/*.cpp")
add_executable(TMSIM
    ${SOURCES}
)

target_include_directories(TMSIM PUBLIC 
    headers
)


target_link_libraries(imgui PUBLIC 
    glfw        # Dependência do ImGui (backend)
    glad        # Dependência do ImGui (backend)
    OpenGL::GL  # Dependência do ImGui (backend)
)

target_link_libraries(TMSIM PUBLIC 
    imgui      
)

if(APPLE)
    set_target_properties(TMSIM PROPERTIES
        MACOSX_BUNDLE ON
    )
endif()