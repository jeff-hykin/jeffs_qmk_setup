#Description: Component osa_bm; user_visible: True
include_guard(GLOBAL)
message("component_osa_bm component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_os_abstraction_bm.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)

#OR Logic component
if(${MCUX_DEVICE} STREQUAL "RW612")
    include(component_osa_interface)
endif()
if(${MCUX_DEVICE} STREQUAL "RW610")
    include(component_osa_interface)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1166_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1052")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F12810")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV10Z1287")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT633S_cm33")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1064")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5526")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54607")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S016")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54606")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54616")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE15Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2B31A")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE16Z4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54016")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV11Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54018")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV31F51212")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE12Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54628")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5512")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F51212")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1173_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5516")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54605")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1051")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54618")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE13Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE14Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1021")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV10Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT555S_cm33")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54018M")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5514")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S16")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2B11A")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK02F12810")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1062")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE15Z4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm0plus")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L3A60_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1042")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1176_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1175_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S018M")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK22F25612")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKM35Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2B21A")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC51U68")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1061")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC5528")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1165_cm4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1165_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S66_cm33_core0")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV31F12810")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54S005")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE17Z7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1171_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S69_cm33_core0")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2A31A")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1024")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1011")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54005")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S28")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKE14Z4")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT533S_cm33")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S14")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV31F25612")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MKV30F12810")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC55S26")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "K32L2A41A")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "LPC54608")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT685S_cm33")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT595S_cm33")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1172_cm7")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MIMXRT1015")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK64F12")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK66F18")
    include(component_lists)
endif()
if(${MCUX_DEVICE} STREQUAL "MK28FA15")
    include(component_lists)
endif()
