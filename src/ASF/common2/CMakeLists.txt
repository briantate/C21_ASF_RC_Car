# src/ASF/common2
add_subdirectory(boards/user_board)
add_subdirectory(services/delay)

target_include_directories( ${TARGET}
    PRIVATE
        boards/user_board
        services/delay
)