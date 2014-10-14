#ifndef CPPLUA_CPPLUALIB_H
#define CPPLUA_CPPLUALIB_H

#if !defined(CPPLUA_API)

# ifndef ISWINDOWS
#  if defined(_WIN32) || defined(_WIN64) || \
	  defined(__WIN32__) || defined(__TOS_WIN__) || \
	  defined(__WINDOWS__)
#   define ISWINDOWS
#  endif
# endif // !ISWINDOWS

# if defined(ISWINDOWS)
#  if defined(CPPLUA_EXPORTS)
#   define CPPLUA_API __declspec(dllexport)
#  else
#   define CPPLUA_API __declspec(dllimport) 
#  endif
# else
#  define CPPLUA_API
# endif

#endif // !define(CPPLUA_API)

#endif // !CPPLUA_CPPLUALIB_H
