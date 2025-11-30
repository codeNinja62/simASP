cmake_minimum_required(VERSION 3.10)
project(SparseFlowSimulator)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(src)

# Source files
set(SOURCES
    src/main.cpp
    src/core/SparseFlowCore.cpp
    src/hardware/RegisterFile.cpp
    src/hardware/Memory.cpp
    src/hardware/BranchPredictor.cpp
    src/hardware/Cache.cpp
    src/utils/Loader.cpp
    src/utils/Stats.cpp
)

# Executable
add_executable(simulator ${SOURCES})
