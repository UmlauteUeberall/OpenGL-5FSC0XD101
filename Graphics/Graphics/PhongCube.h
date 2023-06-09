#pragma once
#include "Entity.h"
class CPhongCube :
    public CEntity
{
public:
    CPhongCube(glm::vec3 _pos);
    virtual ~CPhongCube();

    virtual bool Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

protected:
    unsigned int m_mainTexture;
    unsigned int m_normalTexture;
};

