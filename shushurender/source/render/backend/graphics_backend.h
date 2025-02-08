#ifndef GRAPHICS_BACKEND_H
#define GRAPHICS_BACKEND_H

#define USING_OPENGL

#if defined(USING_OPENGL)
#include "render/backend/opengl/opengl_handler.h"
#elif defined(USING_VULKAN)
#include "render/backend/vulkan/vulkan_handler.h"
#elif defined(USING_SHUSHUGL)
#include "render/backend/shushugl/shushugl_handler.h"
#else
#define PLATFORM "Unknown"
#endif


class GLHandler
{
public:
	GLHandler();
	~GLHandler();

private:

};

class GraphicsBackend
{
private:
	GLHandler mHandler;

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