# src/ASF
add_subdirectory(thirdparty)
add_subdirectory(sam0)
add_subdirectory(common)
add_subdirectory(common2)

target_include_directories( ${TARGET}
    PRIVATE
        sam0
)