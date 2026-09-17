#include "directstate.h"

extern void* APIENTRY_GL4ES gl4es_GetProcAddress(const char* name);
extern void APIENTRY_GL4ES glEnableClientStateiEXT(GLenum array, GLuint index);
extern void APIENTRY_GL4ES glDisableClientStateiEXT(GLenum array, GLuint index);

/** Require the public exports and lookup targets without creating a GL context. */
int main(void)
{
    void (APIENTRY_GL4ES *volatile publicEnable)(GLenum, GLuint) = glEnableClientStateiEXT;
    void (APIENTRY_GL4ES *volatile publicDisable)(GLenum, GLuint) = glDisableClientStateiEXT;
    if (!publicEnable || !publicDisable)
        return 3;
    // Pull gl_lookup.o out of the static archive and require both alias definitions.
    // No graphics context is needed to verify procedure addresses.
    if (gl4es_GetProcAddress("glEnableClientStatei") != (void*)gl4es_glEnableClientStatei
        || gl4es_GetProcAddress("glDisableClientStatei") != (void*)gl4es_glDisableClientStatei
        || gl4es_GetProcAddress("glEnableClientStateiEXT") != (void*)gl4es_glEnableClientStatei
        || gl4es_GetProcAddress("glDisableClientStateiEXT") != (void*)gl4es_glDisableClientStatei)
        return 1;
#if !defined(__APPLE__)
    if (publicEnable != gl4es_glEnableClientStateIndexed
        || publicDisable != gl4es_glDisableClientStateIndexed)
        return 2;
#endif
    return 0;
}
