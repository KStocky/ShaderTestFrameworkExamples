cmake_minimum_required(VERSION 3.25)

project(
    ShaderTestingFrameworkExamples 
    VERSION 0.1.0 
    DESCRIPTION "A project for showing how to use Shader Test Framework"
    LANGUAGES CXX )

# Enables running tests via CTest
enable_testing()

# Set the C++ standard. Shader Test Framework currently requires C++23
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

# Set the target name
set(TARGET_NAME Catch2ExampleTests)

# SHADER_SOURCES contains the relative paths to shader files
# We use this list to add the files to the visual studio solution
set(SHADER_SOURCES
    shader/ShaderHeader.hlsli
    shader/ShaderTest.hlsl 
)

# SOURCES is the list of c++ source files in the project
set(SOURCES
    test/Catch2Tests.cpp
)

# SHADER_SOURCE_DIR is the directory of where the shaders exist in the project
# SHADER_SOURCE_REL_DIR is the directory that we want the shader files to be
# copied to after the build relative to the generated exe
set(SHADER_SOURCE_REL_DIR "Shader")
set(SHADER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shader)

# Adding our target as an executable
add_executable(${TARGET_NAME})

# Add our list of sources to the target
target_sources(${TARGET_NAME} PRIVATE ${SHADER_SOURCES})
target_sources(${TARGET_NAME} PRIVATE ${SOURCES})

# Exclude shader files from the build. If this is not enabled VS will compile
# the shaders as part of the build. STF has it's own compilation pipeline so this
# is not something we want.
set_source_files_properties(${SHADER_SOURCES} PROPERTIES VS_SETTINGS "ExcludedFromBuild=true")

# Ensures that when we running the project in VS, that we give it the same
# working directory as we would have if we ran the executable without VS
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:${TARGET_NAME}>" )

# source_group sets up the Visual Studio filter heirarchy
# This just makes sure that the generated solution has the source files
# organised in some way.
source_group(TREE ${SHADER_SOURCE_DIR} PREFIX "ShaderSources" FILES ${SHADER_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCES})

# Including the FetchContent library to grab ShaderTestFramework
include(FetchContent)

FetchContent_Declare(
        stf
        GIT_REPOSITORY https://github.com/KStocky/ShaderTestFramework
        GIT_TAG main
    )

FetchContent_MakeAvailable(stf)

# Add STFs cmake library to our list of include paths so that we can use the
# cmake libraries that it provides
# *_SOURCE_DIR is created during FetchContent which is where stf_SOURCE_DIR
# comes from
list(APPEND CMAKE_MODULE_PATH ${stf_SOURCE_DIR}/cmake)

#include STF library to do the following actions
include(AssetDependencyManagement)
include(STF)

# initialize asset dependency for this target
asset_dependency_init(${TARGET_NAME})

# add the shader source directory to the list of folders that should be copied
# to a location relative to the generated exe during the build
target_add_asset_directory(${TARGET_NAME} ${SHADER_SOURCE_DIR} "/${SHADER_SOURCE_REL_DIR}")

# Finally add STF and catch2 to the project
add_stf_with_catch2(${TARGET_NAME})