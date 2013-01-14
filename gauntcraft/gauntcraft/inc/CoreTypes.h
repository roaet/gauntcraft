#ifndef class_sdlgauntcraft_coretypes
#define class_sdlgauntcraft_coretypes

#include "SDL/SDL.h"

#define CORE_ERR -1
#define CORE_SUCCESS 0

typedef uint32_t CORE_UINT32;
typedef int CORE_INT;
typedef unsigned int CORE_UINT;
typedef bool CORE_BOOL;
typedef float CORE_FLOAT;
typedef CORE_INT CORE_STATUS;
typedef CORE_INT CORE_BITMASK;

#define DIR_UP		0x0001
#define DIR_DOWN	0x0002
#define DIR_LEFT	0x0004
#define DIR_RIGHT	0x0008
#define DIR_ALL		0x000F

#define SPRITEIDLE -16
#define SPRITERANDOM -8

#endif // class_sdlgauntcraft_coretypes
