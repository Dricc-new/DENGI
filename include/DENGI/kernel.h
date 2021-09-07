#ifdef DENGI_STATIC
#  define DENGIDEF
#  define DENGIDEFI
#else
#  ifdef DENGI_BUILD
#    define DENGIDEF __declspec(dllexport)
#  else
#    define DENGIDEF __declspec(dllimport)
#  endif
#endif
