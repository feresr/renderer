#pragma once

#include <glm/vec3.hpp>
#include <vector>
#include "glad/glad.h"

#include "string"
#include "fstream"
#include "sstream"
#include "iostream"

class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath,
           const char* fragmentPath,
           const char* geometryPath = nullptr
    ) {
        std::string vertexCode;
        std::string fragmentCode;
        std::string geometryCode;

        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        std::ifstream gShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try {
            //open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            if (geometryPath) gShaderFile.open(geometryPath);
            std::stringstream vShaderStream, fShaderStream, gShaderStream;
            //read files' buffer content into streams.
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();
            if (geometryPath) gShaderStream << gShaderFile.rdbuf();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
            if (geometryPath) geometryCode = gShaderStream.str();

            //close file handlers;
            vShaderFile.close();
            fShaderFile.close();
            if (geometryPath) gShaderFile.close();


            int vertex, fragment, geometry;
            int success;
            char infoLog[512];
            //Vertex shader
            //---------------
            vertex = glCreateShader(GL_VERTEX_SHADER);
            //The second argument specifies how many strings we’re passing as source code
            const char* v = vertexCode.c_str();
            glShaderSource(vertex, 1, &v, NULL);
            glCompileShader(vertex);
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            //Fragment shader
            //--------------
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            //The second argument specifies how many strings we’re passing as source code
            const char* f = fragmentCode.c_str();
            glShaderSource(fragment, 1, &f, NULL);
            glCompileShader(fragment);
            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }

            //Fragment shader
            //--------------
            if (geometryPath) {
                geometry = glCreateShader(GL_GEOMETRY_SHADER);
                //The second argument specifies how many strings we’re passing as source code
                const char* g = geometryCode.c_str();
                glShaderSource(geometry, 1, &g, NULL);
                glCompileShader(geometry);
                glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
                if (!success) {
                    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
                    std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;

                    GLint maxLength = 0;
                    glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &maxLength);

                    // The maxLength includes the NULL character
                    std::vector<GLchar> errorLog(maxLength);
                    glGetShaderInfoLog(geometry, maxLength, &maxLength, &errorLog[0]);
                    for (auto i : errorLog) std::cout << i << std::endl;
                    // Provide the infolog in whatever manor you deem best.
                    // Exit with failure.
                    glDeleteShader(geometry); // Don't leak the shader.
                    //return;
                }
            }


            //Program
            //-------
            ID = glCreateProgram();

            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            if (geometryPath) glAttachShader(ID, geometry);
            glLinkProgram(ID);

            glGetProgramiv(ID, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(ID, 512, NULL, infoLog);
                std::cout << "ERROR::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
            glUseProgram(ID);
            glDeleteShader(vertex);
            if (geometryPath) glDeleteShader(geometry);
            glDeleteShader(fragment);
        } catch (std::ifstream::failure& e) {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
        };
    }

    void use() const {
        glUseProgram(ID);
    }

    void setBool(const std::string& name, bool value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setInt(const std::string& name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string& name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setVec3(const std::string& name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    void setVec3(const std::string& name, glm::vec3& vec3) const {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), vec3.x, vec3.y,  vec3.z);
    }

    void setMatrix(const std::string& name, const float* mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, mat);
    }
};