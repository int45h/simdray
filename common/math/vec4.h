#include "sse/vec4_sse3.h"

#define new_vec4(x,y,z,w)\
    new_vec4_sse3(x,y,z,w)

#define new_vec4_array(a)\
    new_vec4_array_sse3(a)

#define new_vec4_scalar(s)\
    new_vec4_scalar_sse3(s)

#define vec4_add(a,b) vec4_add_sse3(a,b)
#define vec4_sub(a,b) vec4_sub_sse3(a,b)
#define vec4_mul(a,b) vec4_mul_sse3(a,b)
#define vec4_div(a,b) vec4_div_sse3(a,b)
#define vec4_adds(a,b) vec4_adds_sse3(a,b)
#define vec4_subs(a,b) vec4_subs_sse3(a,b)
#define vec4_muls(a,b) vec4_muls_sse3(a,b)
#define vec4_divs(a,b) vec4_divs_sse3(a,b)

#define vec4_dot(a,b) vec4_dot_sse3(a,b)
#define vec4_cross(a,b) vec4_cross_sse3(a,b)

#define vec4_dot2(a,b) vec4_dot2_sse3(a)
#define vec4_length(a) vec4_length_sse3(a)
#define vec4_normalize(a) vec4_normalize_sse3(a)

#define vec4_getc(v,c) vec4_getc_sse3(v,c)
#define vec4_setc(v,f,c) vec4_setc_sse3(v,f,c)
#define vec4_lerp(a,b,t) vec4_lerp_sse3(a,b,t)