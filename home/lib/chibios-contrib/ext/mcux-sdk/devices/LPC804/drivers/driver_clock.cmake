#Description: Clock Driver; user_visible: True
include_guard(GLOBAL)
message("driver_clock component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_clock.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_power_no_lib)
include(driver_rom_api)
