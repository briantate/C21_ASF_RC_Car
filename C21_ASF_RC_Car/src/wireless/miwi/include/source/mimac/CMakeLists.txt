# src/ASF/thirdparty/wireless/miwi/source/mimac
add_subdirectory(phy/at86rf212b)

target_sources( ${TARGET}
    PRIVATE
        mimac_at86rf.c
)

target_include_directories( ${TARGET}
    PRIVATE
        phy
)