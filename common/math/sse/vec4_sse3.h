#pragma once
#include "../../typedefs.h"
#include <immintrin.h>

typedef __m128 vec4;
typedef vec4 mat4[4];

// https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction
__m128 _mm_fast_hadd_sse3(__m128 v)
{
    __m128 shuf = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2,3,0,1));
    __m128 sums = _mm_add_ps(v, shuf);
    shuf = _mm_movehl_ps(shuf, sums);
    return _mm_add_ss(sums, shuf);
}

vec4 new_vec4_sse3(float x, float y, float z, float w){return _mm_set_ps(x, y, z, w);}
vec4 new_vec4_array_sse3(float *a){return _mm_load_ps(a);}
vec4 new_vec4_scalar_sse3(float s){return _mm_set1_ps(s);}

vec4 vec4_add_sse3(vec4 a, vec4 b){return _mm_add_ps(a,b);}
vec4 vec4_sub_sse3(vec4 a, vec4 b){return _mm_sub_ps(a,b);}
vec4 vec4_mul_sse3(vec4 a, vec4 b){return _mm_mul_ps(a,b);}
vec4 vec4_div_sse3(vec4 a, vec4 b){return _mm_div_ps(a,b);}

vec4 vec4_adds_sse3(vec4 a, float s){return _mm_add_ps(a,_mm_set1_ps(s));}
vec4 vec4_subs_sse3(vec4 a, float s){return _mm_sub_ps(a,_mm_set1_ps(s));}
vec4 vec4_muls_sse3(vec4 a, float s){return _mm_mul_ps(a,_mm_set1_ps(s));}
vec4 vec4_divs_sse3(vec4 a, float s){return _mm_div_ps(a,_mm_set1_ps(s));}

float vec4_dot_sse3(vec4 a, vec4 b)
{
    return _mm_cvtss_f32(
        _mm_fast_hadd_sse3(_mm_mul_ps(a, b))
    );
}

vec4 vec4_cross_sse3(vec4 a, vec4 b)
{
    return _mm_sub_ps(
        _mm_mul_ps(
            _mm_shuffle_ps(a,a,_MM_SHUFFLE(3,0,2,1)), 
            _mm_shuffle_ps(b,b,_MM_SHUFFLE(3,1,0,2))
        ), 
        _mm_mul_ps(
            _mm_shuffle_ps(a,a,_MM_SHUFFLE(3,1,0,2)),
            _mm_shuffle_ps(b,b,_MM_SHUFFLE(3,0,2,1))
        )
    );
}

float vec4_dot2_sse3(vec4 v)
{
    return _mm_cvtss_f32(
        _mm_fast_hadd_sse3(_mm_mul_ps(v, v))
    );
}

float vec4_length_sse3(vec4 v)
{
    return _mm_cvtss_f32(_mm_rsqrt_ss(
        _mm_fast_hadd_sse3(_mm_mul_ps(v, v))
    ));
}

vec4 vec4_normalize_sse3(vec4 v)
{
    vec4 norm = _mm_rsqrt_ss(_mm_fast_hadd_sse3(_mm_mul_ps(v, v)));
    norm = _mm_shuffle_ps(norm, norm, _MM_SHUFFLE(0,0,0,0));

    return _mm_mul_ps(v, norm);
}

float vec4_getc_sse3(vec4 v, u8 c)
{
    float out[4] = {0};
    _mm_store_ps(out, v);

    return out[c & 3];
}

vec4 vec4_setc_sse3(vec4 v, float f, u8 c)
{
    float out[4] = {0};
    _mm_store_ps(out,v);
    out[c & 3] = c;

    return _mm_load_ps(out);
}