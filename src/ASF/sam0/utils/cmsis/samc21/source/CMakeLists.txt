# src/ASF/sam0/utils/cmsis/samr30/source
add_subdirectory(gcc)

target_sources( ${TARGET}
    PRIVATE
        system_samc21.c
)