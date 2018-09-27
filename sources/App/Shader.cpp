#include "Shader.hpp"
#include "Errors.hpp"
#include "Uniform.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

struct ShaderFile 
{
    std::string vertexSource;
    std::string fragmentSource;
};

Shader::Shader(const std::string& filename)
{
    ShaderFile shaderSource = ParseShaderFile(filename);
    m_RendererID = CreateShader(shaderSource.vertexSource, shaderSource.fragmentSource);
    GLCall(glUseProgram(m_RendererID));
}

Shader::Shader(const std::string& vertexFilename, const std::string& fragmentFilename)
{
    std::string vertexSource = ReadFile(vertexFilename);
    std::string fragmentSource = ReadFile(fragmentFilename);
    m_RendererID = CreateShader(vertexSource, fragmentSource);
    GLCall(glUseProgram(m_RendererID));
}

Shader::~Shader() 
{
    GLCall(glDeleteProgram(m_RendererID)); 
}

void Shader::AddUniform(const std::string& name, const Uniform *uniform)
{
    int location = GetUniformLocation(name);
    m_Uniforms.push_back(uniform);
    m_Locations.push_back(location);
}

void Shader::SetUniform(const std::string& name, const Uniform *uniform)
{
    int location = GetUniformLocation(name);
    uniform->Apply(location);
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
    for (unsigned int i = 0; i < m_Uniforms.size(); i++)
    {
        const Uniform *uniform = m_Uniforms.at(i);
        int location = m_Locations.at(i);
        uniform->Apply(location);
    }
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (m_LocationCache.find(name) != m_LocationCache.end())
        return m_LocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    m_LocationCache[name] = location;
    return location;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int shader = glCreateProgram();
    unsigned int vertexShaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    // attach and link shaders to shader program
    glAttachShader(shader, vertexShaderId);
    glAttachShader(shader, fragmentShaderId);
    glLinkProgram(shader);
    glValidateProgram(shader);
    // delete shader objects since compiled
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return shader;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) 
{
    unsigned int id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) 
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
ShaderFile Shader::ParseShaderFile(const std::string& filepath) 
{
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

std::string Shader::ReadFile(const std::string& filepath) 
{
    std::ifstream filestream(filepath);
    std::stringstream source;
    source << filestream.rdbuf();
    return source.str();
}