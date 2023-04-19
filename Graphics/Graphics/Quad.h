#pragma once
#include "Entity.h"
class CQuad :
    public CEntity
{
public:
    CQuad(glm::vec3 _pos);
    virtual ~CQuad();

    unsigned int m_texture1;
    unsigned int m_texture2;

    virtual void Render() override;
};

