# src/
add_subdirectory(ASF)
add_subdirectory(network)
# add_subdirectory(config)
# add_subdirectory(wireless)

target_include_directories( ${TARGET}
    PRIVATE
        config
        network
)

target_sources( ${TARGET}
    PRIVATE
        debug_interface.c
        hbridge.c
        joystick.c
        main.c
        motor.c
        remoteControl.c
        rf_transceiver.c
        UserIO.c
)