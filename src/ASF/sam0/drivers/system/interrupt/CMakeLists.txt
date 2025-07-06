# src/ASF/sam0/drivers/system/interrupt

target_sources( ${TARGET}
    PRIVATE
        system_interrupt.c
)

target_include_directories( ${TARGET}
    PRIVATE
        system_interrupt_samc20_c21
)