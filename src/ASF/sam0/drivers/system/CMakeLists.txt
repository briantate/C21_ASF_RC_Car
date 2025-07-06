# src/ASF/sam0/drivers/system
add_subdirectory(clock)
add_subdirectory(interrupt)
add_subdirectory(pinmux)

target_sources( ${TARGET}
    PRIVATE
        system.c
)

target_include_directories( ${TARGET}
    PRIVATE
        clock
        interrupt
        pinmux
        power/power_sam_c
        reset/reset_sam_c
)