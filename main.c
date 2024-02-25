#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <math.h>

#include <immintrin.h>
#include "common/typedefs.h"
#include "display/display.h"

#include <GLFW/glfw3.h>

typedef struct 
{
    
}
app_state;

void render_scene()
{

}

int main()
{
    app_window w;
    u8 result = SR_ERROR_UNKNOWN;

    result = create_app_window(1280, 720, "the cum", &w);
    CHECK_ERROR(result, "failed to create window");

    return 0;    
}