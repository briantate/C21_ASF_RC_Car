# src/ASF/common
add_subdirectory(utils)

target_include_directories( ${TARGET}
    PRIVATE
        utils
        boards
        services/serial
)