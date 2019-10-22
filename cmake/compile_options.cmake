if (NOT __compile_options_INCLUDED)
  set (__compile_options_INCLUDED ON)

  target_compile_options (${PROJECT_NAME}
    PRIVATE
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wall>
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-Wextra>
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic>
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pedantic-errors>
      $<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-pipe>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-c>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-O3>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-ftree-vectorize>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-march=native>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-mfpmath=sse>
      $<$<AND:$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>,$<CONFIG:Release>>:-funroll-loops>
      $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-fopt-info-loop-optimized>
      $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-ftree-loop-distribution>
      $<$<AND:$<CXX_COMPILER_ID:GNU>,$<CONFIG:Release>>:-ftree-vectorizer-verbose=3>
      $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/Zi>
      $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/MDd>
      $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/MD>
      $<$<CXX_COMPILER_ID:MSVC>:/Wall>
      $<$<CXX_COMPILER_ID:MSVC>:/EHsc>
      $<$<CXX_COMPILER_ID:MSVC>:/MP>
      $<$<CXX_COMPILER_ID:MSVC>:/Qpar>
      $<$<CXX_COMPILER_ID:MSVC>:/Qpar-report:2>
      $<$<CXX_COMPILER_ID:MSVC>:/Qvec-report:2>
      ${OpenMP_CXX_FLAGS}
  )

endif ()
