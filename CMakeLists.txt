cmake_minimum_required(VERSION 3.23.2)

project(target_info_library)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-fproc-stat-report=abc)
add_link_options(-fproc-stat-report=abc)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#find_package(PkgConfig REQUIRED)
#find_package(libxml REQUIRED)

#find_package(LibXml2 REQUIRED)

add_subdirectory(lib)


add_executable(tester
        main.cpp
        )

target_include_directories(tester PRIVATE include)

llvm_map_components_to_libnames(llvm_libs support)

target_link_libraries(tester PRIVATE target_info_library ${llvm_libs})
