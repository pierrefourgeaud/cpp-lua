#ifndef CPPLUA_CPPLUALIB_H
#if !defined(MIDDLEVR_API)

# if defined(CPPLUA_EXPORTS)
#  define CPPLUA_API __declspec(dllexport)
# else
#  define CPPLUA_API __declspec(dllimport) 
# endif
#endif

#endif // !CPPLUA_CPPLUALIB_H
