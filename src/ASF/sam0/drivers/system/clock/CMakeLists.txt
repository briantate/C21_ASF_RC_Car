# src/ASF/sam0/drivers/system/clock
add_subdirectory(clock_samc20_c21)

target_include_directories( ${TARGET}
    PRIVATE
        clock_samc20_c21
)