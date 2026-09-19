# 1. Enforce a minimum version of CMake so features don't break
cmake_minimum_required(VERSION 3.10)

# 2. Name your project and state that we are writing C++
project(TestProject VERSION 1.0 LANGUAGES CXX)

# 3. Generate a compilation database (this is what gives Kate/clangd its autocompletion smarts)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 4. Lock in modern C++ features (C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find all .cpp files inside the src/ directory and its subdirectories.
# The CONFIGURE_DEPENDS flag forces CMake to notice when you create a new file.
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

# 2. Tell the compiler to compile main.cpp and everything it found in src/
add_executable(App main.cpp ${SRC_FILES})

# 3. Tell CMake that any #include can start looking from the "src" folder
target_include_directories(App PRIVATE src)
