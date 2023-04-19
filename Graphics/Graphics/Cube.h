#pragma once
#include "Entity.h"
class CCube :
    public CEntity
{
public:
    CCube(glm::vec3 _pos);
    virtual ~CCube();

    unsigned int m_texture1;
    unsigned int m_texture2;

    virtual void Render() override;
};

