
#ifndef SS_CFG_H_INCLUDED
#define SS_CFG_H_INCLUDED

#ifndef SS_DEBUG
# ifdef _DEBUG
#  define SS_DEBUG 1
# else
#  define SS_DEBUG 0
# endif
#endif



/* SDL */
#define NO_STDIO_REDIRECT


#endif /* SS_CFG_H_INCLUDED */
