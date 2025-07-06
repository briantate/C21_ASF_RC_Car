# src/ASF/sam0/utils
add_subdirectory(cmsis/samc21/source)
add_subdirectory(stdio)
add_subdirectory(syscalls/gcc)

target_include_directories( ${TARGET}
    PRIVATE
        header_files
        preprocessor
        cmsis/samc21/include
        cmsis/samc21/include/component
        cmsis/samc21/include/instance
        cmsis/samc21/include/pio
        cmsis/samc21/source
)