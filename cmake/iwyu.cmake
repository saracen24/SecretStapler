if (NOT __iwyu_INCLUDED)
  set (__iwyu_INCLUDED ON)

  find_program (IWYU_PATH
    NAMES "include-what-you-use" "iwyu"
  )

  if (NOT IWYU_PATH)
    message (WARNING "Could not find the program include-what-you-use.")
    return ()
  endif ()

  set (IWYU_COMMAND "${IWYU_PATH}"
    -Xiwyu any
    -Xiwyu iwyu
    -Xiwyu args
    -Xiwyu cxx17ns
    $<$<CXX_COMPILER_ID:MSVC>:--driver-mode=cl>
  )

  set_property (TARGET ${PROJECT_NAME}
    PROPERTY
      CXX_INCLUDE_WHAT_YOU_USE "${IWYU_COMMAND}"
  )

endif ()
