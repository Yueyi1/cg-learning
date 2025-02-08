#ifndef GRAPHICS_BACKEND_H
#define GRAPHICS_BACKEND_H

#define USING_OPENGL

#ifdef USING_OPENGL
#include "render/backend/opengl/opengl_handler.h"
#include "glad/glad.h"
#endif // USING_OPENGL

class GraphicsBackend
{
private:
	//GraphicHanlder mHandler;
#ifdef USING_OPENGL
	
#endif // USING_OPENGL

public:
	GraphicsBackend();
	~GraphicsBackend();

};

GraphicsBackend::GraphicsBackend()
{
}

GraphicsBackend::~GraphicsBackend()
{
}

#endif // GRAPHICS_BACKEND_H