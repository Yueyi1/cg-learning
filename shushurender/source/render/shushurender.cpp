#include "shushurender.h"
#include "tools/debug_tools.h"

ShushuRender::ShushuRender()
{
    init();
}

ShushuRender::~ShushuRender()
{
    cleanup();
}

void ShushuRender::init()
{
    DEBUG_PRINTF("enter ShushuRender::init()\n");
    

    mInitSuccess = true;
    DEBUG_PRINTF("ShushuRender::init() %i \n", mInitSuccess);
}

void ShushuRender::loop()
{
    
}

void ShushuRender::cleanup()
{
    DEBUG_PRINTF("enter ShushuRender::cleanup()\n");
}

void ShushuRender::Start()
{
    if (!mInitSuccess)
    {
        ERR_PRINT("ShushuRender::Start() : opg render is uninitlized.")
            return;
    }
    loop();
}

int main(int argc, char** argv)
{
    ShushuRender shushu;
    shushu.Start();
    return 0;
}