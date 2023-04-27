#pragma once
#include "Entity.h"
class CObjectSpaceCube :
    public CEntity
{
public:
    CObjectSpaceCube(glm::vec3 _pos);
    virtual ~CObjectSpaceCube();

    virtual bool Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    int m_Mode;
};

