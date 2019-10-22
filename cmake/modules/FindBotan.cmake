# - FindBotan.cmake
# Find the Botan cryptographic library.
#
# This module defines the following variables:
#  Botan_FOUND - True if library and include directory are found
# If set to TRUE, the following are also defined:
#  Botan_INCLUDE_DIRS - The directory where to find the header file
#  Botan_LIBRARIES - Where to find the library file
#
# For conveniance, these variables are also set. They have the same values
# than the variables above. The user can thus choose his/her prefered way
# to write them.
#  Botan_INCLUDE_DIR
#  Botan_LIBRARY

find_path (Botan_INCLUDE_DIR
  NAMES "botan/botan.h"
  HINTS "${Botan_DIR}"
  PATH_SUFFIXES "include"
  DOC "The Botan include directory."
)

if (Botan_STATIC_LIB)
  find_library (Botan_LIBRARY
    NAMES "botan-static"
    HINTS "${Botan_DIR}"
    PATH_SUFFIXES "Release"
    DOC "The Botan library."
  )
else ()
  find_library (Botan_LIBRARY
    NAMES "botan"
    HINTS "${Botan_DIR}"
    PATH_SUFFIXES "Release"
    DOC "The Botan library."
  )
endif()

include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Botan DEFAULT_MSG
  Botan_INCLUDE_DIR Botan_LIBRARY
)
mark_as_advanced (Botan_INCLUDE_DIR Botan_LIBRARY)

set (Botan_INCLUDE_DIRS ${Botan_INCLUDE_DIR})
set (Botan_LIBRARIES ${Botan_LIBRARY})
