#ifndef class_sdlgauntcraft_coretypes
#define class_sdlgauntcraft_coretypes

#include "SDL.h"

#define CORE_ERR -1
#define CORE_SUCCESS 0

typedef uint32_t CORE_UINT32;
typedef int CORE_INT;
typedef unsigned int CORE_UINT;
typedef bool CORE_BOOL;
typedef float CORE_FLOAT;
typedef CORE_INT CORE_STATUS;
typedef CORE_INT CORE_BITMASK;

#define DIR_UP 1
#define DIR_DOWN 2
#define DIR_LEFT 4
#define DIR_RIGHT 8
#define DIR_ALL 15

#define SPRITEIDLE -16
#define SPRITERANDOM -8

#endif // class_sdlgauntcraft_coretypes
