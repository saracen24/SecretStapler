cmake_minimum_required (VERSION 3.14 FATAL_ERROR)

project (secretstapler
  VERSION 0.0.1
  DESCRIPTION "AES-128/CBC/PKCS7 encryption."
  LANGUAGES CXX
)

add_executable (${PROJECT_NAME})

include ("cmake/compile_definitions.cmake")

include ("cmake/dependencies.cmake")

include ("cmake/sources.cmake")

include ("cmake/compile_options.cmake")

include ("cmake/iwyu.cmake")

set_target_properties (${PROJECT_NAME}
  PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    USE_FOLDERS ON
)

include ("cmake/post_build.cmake")
