# src/ASF/thirdparty/CMSIS/Lib/GCC

# target_link_libraries(${TARGET}
#     PRIVATE
#         libarm_cortexM0l_math.a
# )
target_sources( ${TARGET}
    PRIVATE
        libarm_cortexM0l_math.a
)