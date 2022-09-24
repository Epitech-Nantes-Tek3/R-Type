# Script that sets the COMPILER_TYPE variable according to the current variable
#
# Possible values:
# "msvc" (windows-only)
# "gcc" (linux, mingw not supported yet)


if (CMAKE_COMPILER_IS_GNUCXX)
  set(COMPILER_TYPE "gcc")
elseif (MSVC)
  set(COMPILER_TYPE "msvc")
else ()
  set(COMPILER_TYPE "unknown")
  message(WARNING "Unknown compiler type, compilation may not work as expected")
endif()
