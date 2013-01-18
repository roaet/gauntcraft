#include <glog/logging.h>
const char MaxInfoLength = 256;
const char MaxInfoDepth = 64;

static int g_infoStackDepth = 0;
static char g_infoStack[MaxInfoDepth][MaxInfoLength + 1];

void push_info_stack( const char * string )
{
    CHECK( g_infoStackDepth < MaxInfoDepth ) << "Max recursion depth";
    strncpy( &g_infoStack[g_infoStackDepth][0], string, MaxInfoLength );
    g_infoStack[g_infoStackDepth][MaxInfoLength] = '\0';
    g_infoStackDepth++;
}

void pop_info_stack()
{
    CHECK( g_infoStackDepth > 0 ) << "Min recursion depth";
    g_infoStack[g_infoStackDepth][0] = '\0';
    g_infoStackDepth--;
}

class InfoPushPopHelper
{
    InfoPushPopHelper( const char * string )
    {
        push_info_stack( string );
    }

    ~InfoPushPopHelper()
    {
        pop_info_stack();
    }
};

#define COREINFO( format, ... )                                     \
    char buffer[MaxInfoLength+1];                               \
    snprintf( buffer, MaxInfoLength+1, format, __VA_ARGS__ );   \
    InfoPushPopHelper infoPushPop( buffer );