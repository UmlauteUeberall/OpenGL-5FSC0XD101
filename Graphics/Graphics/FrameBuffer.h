#pragma once
#include "Shader.h"
#include "Vertex.h"

class CFrameBuffer
{
public:
	CFrameBuffer();
	virtual ~CFrameBuffer();

	bool Initialize();
	void RenderFirst();
	void RenderSecond();
	void CleanUp();

private:
	unsigned int m_framebuffer;
	unsigned int m_textureColorBuffer;
	CShader* m_frameBufferShader;

	unsigned int m_VBO = 0;
	unsigned int m_VAO = 0;
};

