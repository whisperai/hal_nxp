if(CONFIG_HAS_MCUX OR CONFIG_HAS_IMX_HAL)
  zephyr_library_named(__modules__hal__nxp)
endif()

add_subdirectory_ifdef(
  CONFIG_HAS_MCUX
  mcux
  )

add_subdirectory_ifdef(
  CONFIG_HAS_IMX_HAL
  imx
  )
