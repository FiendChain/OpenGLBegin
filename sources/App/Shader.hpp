#pragma once
#include "Uniform.hpp"
#include <string>
#include <unordered_map>
#include <memory>
 
class Shader
{
    private:
        unsigned int m_RendererID;
        std::vector<std::shared_ptr<Uniform>> m_Uniforms;
        std::vector<int> m_Locations;
        std::unordered_map<std::string, int> m_LocationCache;
    public:
        Shader(const std::string& filename);
        Shader(const std::string& vertexFilename, const std::string&fragmentFilename);
        ~Shader();
        void AddUniform(const std::string& name, std::shared_ptr<Uniform> uniform);
        void SetUniform(const std::string& name, std::shared_ptr<Uniform> uniform);
        void Bind() const;
        void Unbind() const;
        inline const std::vector<std::shared_ptr<Uniform>>& GetUniforms() const {return m_Uniforms; };
    private:
        int GetUniformLocation(const std::string& name);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        struct ShaderFile ParseShaderFile(const std::string& filepath); 
        std::string ReadFile(const std::string& filepath); 
};



