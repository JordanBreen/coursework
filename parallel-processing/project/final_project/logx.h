// Logarithm Macros: //
#include <math.h>
#ifndef LOGX_H
#define LOGX_H
// Log base x operations ////////////////////////
#define logx(b, a)       (log(a)/log(b))
#define logx_ceil(b, a)  ((int)ceil(logx(b, a)))
#define logx_floor(b, a) ((int)floor(logx(b, a)))
// Log base 2 operations ////////////////////////
#define log2(a)          (log(a)/log(2))
#define log2_ceil(a)     ((int)ceil(log2(a)))
#define log2_floor(a)    ((int)floor(log2(a)))
// Log base 10 operations ///////////////////////
#define log10(a)         (log(a)/log(10))
#define log10_ceil(a)    ((int)ceil(log10(a)))
#define log10_floor(a)   ((int)floor(log10(a)))
#endif
