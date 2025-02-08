#ifndef DEBUG_MESSAGE_H
#define DEBUG_MESSAGE_H

#include <iostream>
#include <windows.h>
#include <memory>

#ifdef _WIN32
typedef void *HANDLE;
typedef unsigned short WORD;

#define FOREGROUND_YELLOW    FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_PURPLE    FOREGROUND_RED | FOREGROUND_BLUE
#define FOREGROUND_CYAN      FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_WHITE     FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE

#ifdef DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#define ERR_PRINT(...)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        DebugMessage::Inst()->SetTextColor(FOREGROUND_RED);                                                                     \
        printf(__VA_ARGS__);                                                                                           \
        DebugMessage::Inst()->SetTextColor(FOREGROUND_WHITE);                                                                   \
    }                                                                                                                  \
    while (0);
#endif

class DebugMessage
{
private:
    HANDLE hConsole_;
    
    DebugMessage(const DebugMessage&) = delete;
    DebugMessage& operator=(const DebugMessage&) = delete;

public:
    DebugMessage();
    ~DebugMessage();

    void SetTextColor(WORD bit);

    static std::shared_ptr<DebugMessage> Inst()
    {
        static std::shared_ptr<DebugMessage> instance = std::make_shared<DebugMessage>();
        return instance;
    }
};

#endif

#endif // DEBUG_MESSAGE_H