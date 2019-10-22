if (NOT __post_build_INCLUDED)
  set (__post_build_INCLUDED ON)

  if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux" AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_custom_command (TARGET ${PROJECT_NAME}
      POST_BUILD
        COMMAND ${CMAKE_STRIP} ${PROJECT_NAME}
        WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
    )
  endif ()

endif ()
