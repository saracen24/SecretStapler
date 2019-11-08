if (NOT __sources_INCLUDED)
  set (__sources_INCLUDED ON)

  set (SOURCE_FILES
    "src/main.cpp"
    "src/secretstapler.cpp"
    "src/secretstapler.hpp"
  )

  if ("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set (PLATFORM_DEPENDENT_SOURCE_FILES
    )
  elseif ("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set (PLATFORM_DEPENDENT_SOURCE_FILES
    )
  endif ()

  set (OTHER_FILES
  )

  source_group (TREE ${PROJECT_SOURCE_DIR}
    FILES
      ${SOURCE_FILES}
      ${PLATFORM_DEPENDENT_SOURCE_FILES}
      ${OTHER_FILES}
  )

  target_sources (${PROJECT_NAME}
    PRIVATE
      ${SOURCE_FILES}
      ${PLATFORM_DEPENDENT_SOURCE_FILES}
      ${OTHER_FILES}
  )

endif ()
