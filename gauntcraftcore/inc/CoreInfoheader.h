#ifndef gauntcraft_coreinfoheader
#define gauntcraft_coreinfoheader

#include <glog/logging.h>
#include <cstring>
#include <stdio.h>

const int MaxInfoLength = 256;
const int MaxInfoDepth = 64;

static int g_infoStackDepth = 0;
static char g_infoStack[MaxInfoDepth][MaxInfoLength + 1];
void push_info_stack(const char * string);
void pop_info_stack();

class InfoPushPopHelper
{
public:
    InfoPushPopHelper( const char * string )
    {
        push_info_stack( string );
    }

    ~InfoPushPopHelper()
    {
        pop_info_stack();
    }
};
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define CORELOG( format, ... )                                     \
    char buffer[MaxInfoLength+1];                               \
    _snprintf( buffer, MaxInfoLength+1, format, __VA_ARGS__ );   \
    InfoPushPopHelper infoPushPop( buffer );
#else
#define CORELOG( format, ... )                                     \
    char buffer[MaxInfoLength+1];                               \
	snprintf( buffer, MaxInfoLength+1, format, ##__VA_ARGS__ );   \
    InfoPushPopHelper infoPushPop( buffer );
#endif
#endif