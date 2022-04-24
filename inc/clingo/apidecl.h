#ifndef CLINGO_APIDECL_H
#define CLINGO_APIDECL_H

#ifdef CLINGO_STATIC_DEFINE
#  define CLINGO_API
#  define CLINGO_NO_EXPORT
#else
#  ifdef _WIN32
#    ifndef CLINGO_API
#      ifdef clingo_EXPORTS
#        define CLINGO_API __declspec(dllexport)
#      else
#        define CLINGO_API __declspec(dllimport)
#      endif
#    endif
#  else
#    define CLINGO_API
#    define CLINGO_NO_EXPORT
#  endif
#
#  ifndef CLINGO_NO_EXPORT
#    define CLINGO_NO_EXPORT 
#  endif
#endif

#endif