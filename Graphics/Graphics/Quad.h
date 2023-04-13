#pragma once
#include "Entity.h"
class CQuad :
    public CEntity
{
public:
    CQuad(glm::vec3 _pos);
    virtual ~CQuad();
};

