#include <float.h>

#define cartesian_pow powf
#define cartesian_abs fabsf
#define cartesian_sqrt sqrtf

namespace interpret {
    #define CART_MAX DBL_MAX
    typedef float cartesian;
}