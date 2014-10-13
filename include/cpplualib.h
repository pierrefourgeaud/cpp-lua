#ifndef CPPLUA_CPPLUALIB_H
#define CPPLUA_CPPLUALIB_H

#if !defined(CPPLUA_API)

# if WINDOWS
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
