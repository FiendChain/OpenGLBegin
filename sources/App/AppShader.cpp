#include "App.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace app;

unsigned int App::createProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int programId = glCreateProgram();
    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
    // attach and link shaders to program
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    glValidateProgram(programId);
    // delete shader descriptor? files since already 
    // compiled and attached to program
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
}

unsigned int App::compileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    // https://youtu.be/71BLZwRGUJE?t=8m35s
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // glShaderiv => i = integer, v = vector
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) // error is GL_FALSE
    {   
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)calloc(length, sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cerr << 
            "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
            " shader!" << std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id);
        free(message);
        return 0;
    }

    return id;
}

// parse the shader file
struct ShaderFile App::parseShaderFile(const std::string& filepath) {
    // keep track of shader type
    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };
    std::ifstream filestream(filepath);
    std::string buffer;
    std::stringstream shader[2];
    ShaderType scanmode = ShaderType::NONE;
    while (getline(filestream, buffer)) {
        if (buffer.find("#shader") != std::string::npos) 
        {
            if (buffer.find("vertex") != std::string::npos) 
            {
                scanmode = ShaderType::VERTEX;
            } 
            else if (buffer.find("fragment") != std::string::npos) 
            {
                scanmode = ShaderType::FRAGMENT;
            }
        } 
        else if (buffer.find("#endshader") != std::string::npos) 
        {
            scanmode = ShaderType::NONE;
        } 
        else if (scanmode != ShaderType::NONE) 
        {
            shader[(int)scanmode] << buffer << std::endl;
        }
    }
    return {shader[0].str(), shader[1].str()};
}