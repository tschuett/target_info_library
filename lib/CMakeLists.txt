
add_library(target_info_library
        library.cpp
        AArch64Linux.cpp
)

target_include_directories(target_info_library PRIVATE ../include)
