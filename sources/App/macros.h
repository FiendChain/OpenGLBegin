#ifndef _MACRO_H_
#define _MACRO_H_

#define ASSERT(x) if(!x) __builtin_trap();
#define GLCall(func) GLClearErrors();\
    func;\
    ASSERT(GLCheckErrors(#func, __FILE__, __LINE__))

#endif