# Compiler-Optionen
set( CMAKE_C_COMPILER "/usr/bin/clang" )
add_definitions(
   -O0
   -g3
   -std=c11
   -Wall
   -Wabsolute-value
   -Werror=absolute-value
   -Waddress-of-temporary
   -Werror=address-of-temporary
   -Wconversion # Warn for implicit conversions that may alter a value.
   -Werror=conversion
   -c
   -fmessage-length=0
)
