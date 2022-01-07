# Compiler-Optionen
set( CMAKE_C_COMPILER "/usr/bin/clang" )
add_definitions(
   -O0
   -g3
   -std=c11
   -Wall
   -Wconversion # Warn for implicit conversions that may alter a value.
   -Werror
   -c
   -fmessage-length=0
)
