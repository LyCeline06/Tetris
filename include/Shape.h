#ifndef SHAPE_H
#define SHAPE_H
#include <SDL.h>

#include <iostream>
#include <cmath>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Shape{
	SDL_Color color;
    bool matrix[4][4];
    int size;
};

static const SDL_Color clear_grey = {127,127,127,255};
static const SDL_Color grey = {25,25,25,255};
static const SDL_Color black = {0,0,0,255};
static const SDL_Color green = {78,183,72,255};
static const SDL_Color blue = {43,172,226,255};
static const SDL_Color orange = {248,150,34,255};
static const SDL_Color purple = {146,43,140,255};
static const SDL_Color red = {238,39,51,255};
static const SDL_Color yellow = {253,225,0,255};
static const SDL_Color blue2 = {0,90,157,255};

static const Shape block[7] =
{
    {orange,
	{{0,0,1,0} // L BLOCK
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },3},
    {red,
	{{1,1,0,0} // Z BLOCK
    ,{0,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },3},
    {blue,{{1,1,1,1} // I BLOCK
    ,{0,0,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },4},
    {blue2,{{1,0,0,0} // J BLOCK
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },3},
    {yellow,{{1,1,0,0} // O BLOCK
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },2},
    {green,{{0,1,1,0} // S BLOCK
    ,{1,1,0,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },3},
    {purple,{{0,1,0,0} // T BLOCK
    ,{1,1,1,0}
    ,{0,0,0,0}
    ,{0,0,0,0}
    },3}
};
Shape transpose(Shape s);
Shape miror(Shape s);
Shape rotate(Shape s);


#endif
