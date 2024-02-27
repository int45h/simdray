#pragma once

#include "../typedefs.h"
#include <math.h>

float maxf(float a, float b){ return (a>b)?a:b; }
float minf(float a, float b){ return (a<b)?a:b; }
float clampf(float x, float l, float u){return minf(maxf(x,l),u);}
float lerpf(float a, float b, float f){return a+f*(b-a);}