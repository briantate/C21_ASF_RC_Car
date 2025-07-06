# src/
add_subdirectory(ASF)
# add_subdirectory(config)
add_subdirectory(wireless)

target_include_directories( ${TARGET}
    PRIVATE
        config
)

target_sources( ${TARGET}
    PRIVATE
        analog.c
        DebugConsole.c
        hbridge.c
        joystick.c
        main.c
        motor.c
        network_management.c
        remoteControl.c
        remoteTimer.c
        rf_transceiver.c
        UserIO.c
)