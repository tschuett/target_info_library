
add_library(target_info_library
        library.cpp
        AArch64Linux.cpp
        AArch64LinuxTypebuilder.cpp
        Callwithlayoutandcode.cpp
        AArch32Linux.cpp
        AArch32LinuxTypeBuilder.cpp
        AArchLinuxStructBuilder.cpp
        X8664Linux.cpp
        X86LinuxTypeBuilder.cpp
        TypeBuilder.cpp
)

target_include_directories(target_info_library PRIVATE ../include)
