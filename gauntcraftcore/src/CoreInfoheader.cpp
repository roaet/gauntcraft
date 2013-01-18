#include "../inc/CoreInfoheader.h"
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