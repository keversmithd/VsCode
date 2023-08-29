#ifndef WINDOW_STATS_H
#define WINDOW_STATS_H

#include "NGL.h"
#include "GLFW/glfw3.h"


struct WindowStats
{
    float wx;
    float wy;

    float vx;
    float vy;
};

WindowStats GlobalWindowStats;

#endif