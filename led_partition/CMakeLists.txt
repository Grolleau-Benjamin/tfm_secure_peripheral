# Copyright (c) 2026 CATIE
# SPDX-License-Identifier: Apache-2.0

add_library(tfm_app_rot_partition_lp STATIC)

target_include_directories(tfm_app_rot_partition_lp
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${CMAKE_BINARY_DIR}/led_partition
)
target_include_directories(tfm_partitions
    INTERFACE
        ${CMAKE_BINARY_DIR}/led_partition
)

target_sources(tfm_app_rot_partition_lp
    PRIVATE
        led_partition.c
)

target_sources(tfm_app_rot_partition_lp
    PRIVATE
        ${CMAKE_BINARY_DIR}/led_partition/auto_generated/intermedia_tfm_led_partition.c
)
target_sources(tfm_partitions
    INTERFACE
        ${CMAKE_BINARY_DIR}/led_partition/auto_generated/load_info_tfm_led_partition.c
)

target_link_libraries(tfm_app_rot_partition_lp
    PRIVATE
        platform_s
        tfm_sprt
)

target_link_libraries(tfm_spm
    PRIVATE
        tfm_app_rot_partition_lp
)

target_link_libraries(tfm_partitions
    INTERFACE
        tfm_app_rot_partition_lp
)

target_compile_definitions(tfm_config
    INTERFACE
        TFM_PARTITION_LED_PARTITION
)
