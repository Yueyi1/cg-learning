#ifndef SHUSHURENDER_H
#define SHUSHURENDER_H

#include "platform/platform.h"
#include "backend/graphics_backend.h"

#include <memory>

class ShushuRender
{
protected:
    // platform handler
    std::shared_ptr<platform::Platform> m_platform_inst;

    // graphics backend
    std::shared_ptr<GraphicsBackend> m_graphics_backend;


private:
    bool mInitSuccess = false;

    void init();
    void loop();
    void cleanup();

public:
    ShushuRender(/* args */);
    ~ShushuRender();
    void Start();
    void Stop();
};

#endif // SHUSHURENDER_H