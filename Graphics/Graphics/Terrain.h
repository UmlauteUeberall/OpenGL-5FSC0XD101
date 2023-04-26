#pragma once
#include "Entity.h"
class CTerrain :
    public CEntity
{
public:
    CTerrain(glm::vec3 _pos, int _widthSegments, int _depthSegments);
    virtual ~CTerrain();

    virtual bool Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

protected:
    unsigned int m_mainTexture;
    unsigned int m_heightMap;
};

