#ifndef GUISHADER_H_INCLUDED
#define GUISHADER_H_INCLUDED

#include"Light.h"
#include"shader.h"
#include"string"


class GuiShader : public Shader
{
public:
    GuiShader(const std::string fileName) : Shader(fileName , false)
    {
    }
    void UpdateGUI(glm::vec3 pos , glm::vec3 scale)
    {
        glm::mat4 posMat = glm::translate(pos);
        glm::mat4 scaleMat = glm::scale(scale);
        glm::mat4 model = posMat*scaleMat;

    glUniformMatrix4fv(m_uniforms["Model"], 1, GL_FALSE, &model[0][0]);
        //setUniformMatrix4f("Model" , &model[0][0]);
    }
};

#endif // GUISHADER_H_INCLUDED
