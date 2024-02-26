#pragma once
#include "../common/typedefs.h"
#include <GLFW/glfw3.h>

typedef struct 
{
    char title[128];
    usize w;
    usize h;

    GLFWwindow *window;
}
app_window;

u8 init_app_renderer()
{
    if (glfwInit() != GLFW_TRUE)
        return SR_ERROR_UNKNOWN;

    return SR_SUCCESS;
}

void destroy_app_renderer()
{
    
}

u8 create_app_window(usize w, usize h, const char *p_title, app_window *p_window)
{
    sr_copy(char, p_window->title, p_title, MIN(strlen(p_title), 128));
    p_window->w = w;
    p_window->h = h;

    p_window->window = glfwCreateWindow(w, h, p_window->title, NULL, NULL);
    if (p_window == NULL)
    {
        LOG_ERROR("failed to init GLFW");
        return SR_ERROR_UNKNOWN;
    }

    return SR_SUCCESS;
}

void destroy_app_window(app_window *p_window)
{
    if (p_window->window != NULL)
        glfwDestroyWindow(p_window->window);
}