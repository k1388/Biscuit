#pragma once
#include "Glad/glad.h"

namespace Biscuit
{
    class Shader
    {
    public:
        /// <summary>
        /// 生成、加载并尝试编译、链接着色器
        /// </summary>
        /// <param name="vertexSrc">顶点着色器源码</param>
        /// <param name="fragmentSrc">片段着色器源码</param>
        Shader(const char* vertexSrc,const char* fragmentSrc);
        

        /// <summary>
        /// 生成并加载一个默认的着色器
        /// </summary>
        Shader();

        /// <summary>
        /// 获得着色器程序句柄
        /// </summary>
        /// <returns>着色器程序句柄</returns>
        inline unsigned int GetShaderProgram() const
        {
            return m_ShaderProgram;
        }

        inline void SetUniform1i(const std::string& name, int value) const
        {
            glUniform1i(glGetUniformLocation(m_ShaderProgram, name.c_str()), value);
        }
        inline void SetUniform2i(const std::string& name, int value1, int value2) const
        {
            glUniform2i(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2);
        }
        inline void SetUniform3i(const std::string& name, int value1, int value2, int value3) const
        {
            glUniform3i(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2, value3);
        }
        inline void SetUniform4i(const std::string& name, int value1, int value2, int value3, int value4) const
        {
            glUniform4i(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2, value3, value4);
        }
        inline void SetUniform1f(const std::string& name, float value) const
        {
            glUniform1f(glGetUniformLocation(m_ShaderProgram, name.c_str()), value);
        }
        inline void SetUniform2f(const std::string& name, float value1, float value2) const
        {
            glUniform2f(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2);
        }
        inline void SetUniform3f(const std::string& name, float value1, float value2, float value3) const
        {
            glUniform3f(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2, value3);
        }
        inline void SetUniform4f(const std::string& name, float value1, float value2, float value3, float value4) const
        {
            glUniform4f(glGetUniformLocation(m_ShaderProgram, name.c_str()), value1, value2, value3, value4);
        }

        
        private:
            unsigned int m_ShaderProgram;
    };
}
