#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <errno.h>
#include <math.h>

#include "common/math/vec4.h"
#include "common/typedefs.h"
#include "display/display.h"

#include <GLFW/glfw3.h>

#define TO_U32_PIXEL(x, y, z, w) (\
(((int)(x)&0xff) << 24) | \
(((int)(y)&0xff) << 16) | \
(((int)(z)&0xff) << 8) | \
(((int)(w)&0xff)))

typedef struct 
{
    u32 *fb;
    usize w, h;
}
app_state;

typedef struct 
{
    vec4 o;
    vec4 d;
    float t;
}
ray;

ray new_ray(vec4 o, vec4 d, float t)
{
    return (ray){o, d, t};
}

vec4 ray_hit_point(ray r)
{   
    return vec4_add(r.o, vec4_muls(r.d, r.t));
}

void image(u32 *p_color, u32 x, u32 y, u32 w, u32 h)
{
    float u = x / (float)w;
    float v = y / (float)h;
    
    *p_color = TO_U32_PIXEL(u*255.99f, v*255.99f, 0, 255);
}

void render_scene(app_state *p_state)
{
    for (u32 i = 0; i < p_state->w*p_state->h; i++)
    {
        u32 y = p_state->h - (i / p_state->w);
        u32 x = i % p_state->w;

        u32 c = 0;
        image(&c, x, y, p_state->w, p_state->h);
        p_state->fb[i] = c;
    }
}

u8 create_app_state(app_state *p_state, usize w, usize h)
{
    p_state->fb = alloc(u32, w*h);
    if (p_state->fb == NULL)
    {
        LOG_ERROR("failed to allocate memory for framebuffer: %s\n", strerror(errno));
        return SR_ERROR_UNKNOWN;
    }

    p_state->w = w;
    p_state->h = h;

    return SR_SUCCESS;
}

void destroy_app_state(app_state *p_state)
{
    if (p_state->fb != NULL)
        free(p_state->fb);
}

u8 file_exists(const char *p_filename)
{
    FILE *fp = fopen(p_filename, "r");
    u8 result = (fp != NULL);

    if (result)
        fclose(fp);

    return result;
}

u8 write_to_ppm(app_state *p_state, const char *p_filepath)
{
    // Overwrite file if it exists
    if (file_exists(p_filepath))
        remove(p_filepath);

    FILE *fp = fopen(p_filepath, "w");
    if (fp == NULL)
    {
        LOG_ERROR("failed to open file '%s' for reading: %s\n", p_filepath, strerror(errno));
        return SR_ERROR_UNKNOWN;
    }

    // Print header
    fprintf(
        fp, 
        "P3\n#%s\n%d %d\n256\n", 
        "simdray_out",
        (int)p_state->w,
        (int)p_state->h
    );

    // Print pixels
    for (usize i = 0; i < p_state->w*p_state->h; i++)
    {
        fprintf(
            fp, 
            "%d, %d, %d\n", 
            (p_state->fb[i] & 0xFF000000) >> 24,
            (p_state->fb[i] & 0xFF0000) >> 16,
            (p_state->fb[i] & 0xFF00) >> 8
        );
    }

    fclose(fp);

    return SR_SUCCESS;
}

int main(int argc, char** argv)
{
    app_window w;
    app_state state;
    u8 result = SR_ERROR_UNKNOWN;

    // Create app state
    result = create_app_state(&state, 1280, 720);
    CHECK_ERROR(result, "failed to create app state");

    // Create window
    result = create_app_window(1280, 720, "the cum", &w);
    CHECK_ERROR(result, "failed to create window");

    render_scene(&state);

    // Print to PPM (temporary)
    result = write_to_ppm(&state, "./out.ppm");
    CHECK_ERROR(result, "failed to write image");

    // Destroy app state
    destroy_app_state(&state);

    return 0;    
}