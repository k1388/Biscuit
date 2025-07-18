#include "pch.h"
#include "Shader.h"
namespace Biscuit
{
    Shader::Shader(const char* vertexSrc,const char* fragmentSrc)
    {
        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSrc, NULL);
        glCompileShader(vertexShader);
        int verSuccess;
        char verInfoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &verSuccess);
        if (!verSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, verInfoLog);
            BC_ERROR("Error compiling vertex shader:{0}", verInfoLog);
            return;
        }
        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
        glCompileShader(fragmentShader);
        int fragSuccess;
        char fragInfolog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &fragSuccess);
        if (!fragSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, fragInfolog);
            BC_ERROR("Error compiling fragment shader:{0}", fragInfolog);
            return;
        }

        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        char infoLog[512];
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            BC_ERROR("Error shader linking:{0}", infoLog);
            return;
        }
        m_ShaderProgram = shaderProgram;
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::Shader()
    {
         const char* vertexSrc = R"(
                #version 330 core
                layout (location = 0) in vec3 aPos;
                void main()
                {
                    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                }
            )";

            unsigned int vertexShader;
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexSrc, NULL);
            glCompileShader(vertexShader);
            int verSuccess;
            char verInfoLog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &verSuccess);
            if (!verSuccess)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, verInfoLog);
                BC_ERROR("Error compiling vertex shader:{0}", verInfoLog);
                return;
            }

            const char* fragmentSrc = R"(
                #version 330 core
                out vec4 color;
                void main()
                {
                    color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
                }
            )";
            unsigned int fragmentShader;
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentSrc, NULL);
            glCompileShader(fragmentShader);
            int fragSuccess;
            char fragInfolog[512];
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &fragSuccess);
            if (!fragSuccess)
            {
                glGetShaderInfoLog(vertexShader, 512, NULL, fragInfolog);
                BC_ERROR("Error compiling fragment shader:{0}", fragInfolog);
                return;
            }

            unsigned int shaderProgram;
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);

            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                BC_ERROR("Error shader linking:{0}", infoLog);
                return;
            }
            m_ShaderProgram = shaderProgram;
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
    }
}
