if (NOT __dependencies_INCLUDED)
  set (__dependencies_INCLUDED ON)

  list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
  set (3RDPARTY_DIR "${PROJECT_SOURCE_DIR}/3rdparty" CACHE PATH "3rdparty directory.")

  # Threads
  set (CMAKE_THREAD_PREFER_PTHREAD ON)
  set (THREADS_PREFER_PTHREAD_FLAG ON)
  find_package (Threads REQUIRED)
  
  # OpenMP
  find_package (OpenMP REQUIRED)

  # jarro2783/cxxopts
  set (CXXOPTS_BUILD_EXAMPLES OFF CACHE BOOL "Set to ON to build examples.")
  set (CXXOPTS_BUILD_TESTS OFF CACHE BOOL "Set to ON to build tests.")
  add_subdirectory ("${3RDPARTY_DIR}/jarro2783/cxxopts")

  # randombit/botan
  set (Botan_DIR "${3RDPARTY_DIR}/randombit/botan/build" CACHE PATH "Botan build directory.")
  set (Botan_STATIC_LIB OFF CACHE BOOL "Link static library.")
  find_package (Botan REQUIRED)

  target_include_directories (${PROJECT_NAME}
    PRIVATE
      "${PROJECT_SOURCE_DIR}"
      "${PROJECT_SOURCE_DIR}/src"
      "${PROJECT_BINARY_DIR}"
      "${3RDPARTY_DIR}"
      "${3RDPARTY_DIR}/${CMAKE_SYSTEM_NAME}"
      "${Botan_INCLUDE_DIR}"
  )

  target_link_libraries (${PROJECT_NAME}
    PRIVATE
      Threads::Threads
      OpenMP::OpenMP_CXX
      cxxopts
      ${Botan_LIBRARY}
      $<$<PLATFORM_ID:Linux>:stdc++fs>
  )

endif ()
