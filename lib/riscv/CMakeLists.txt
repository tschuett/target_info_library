add_library(target_info_library_riscv
        library.cpp
        riscv32linux.cpp
        riscv64linux.cpp
        RiscvTypeBuilder.cpp
)

target_include_directories(target_info_library_riscv PRIVATE ../../include)
