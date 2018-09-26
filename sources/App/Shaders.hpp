#pragma once

#include <iostream>

struct ShaderFile {
    std::string vertex;
    std::string fragment;
};

unsigned int createProgram(const std::string& vertexShader, const std::string& fragmentShader);
unsigned int compileShader(unsigned int type, const std::string& source);
struct ShaderFile parseShaderFile(const std::string& filepath); 

