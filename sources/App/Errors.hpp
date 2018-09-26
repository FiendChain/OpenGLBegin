#pragma once
#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(func) GLClearErrors();\
    func;\
    ASSERT(GLCheckErrors(#func, __FILE__, __LINE__))

void GLClearErrors();
bool GLCheckErrors(const char *funcName, const char *file, int line);