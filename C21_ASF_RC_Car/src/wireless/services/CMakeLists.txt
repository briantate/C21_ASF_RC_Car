# src/ASF/thirdparty/wireless
add_subdirectory(common_hw_timer/sam0/)
add_subdirectory(nvm/sam0)
add_subdirectory(sal/at86rf2xx/src)
add_subdirectory(trx_access)

target_include_directories( ${TARGET}
    PRIVATE
        common_hw_timer
        common_hw_timer/sam0
        nvm
        sal/inc
        trx_access
)