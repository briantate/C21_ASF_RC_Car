# src/ASF/thirdparty
add_subdirectory(CMSIS/Lib/GCC)

target_include_directories( ${TARGET}
    PRIVATE
        CMSIS/Include
)