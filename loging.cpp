#include "loging.h"

bool Loging::ENABLE_RED_LOG = true;
bool Loging::ENABLE_WHITE_LOG = true;
bool Loging::ENABLE_MAGENTA_LOG = true;
bool Loging::ENABLE_GREEN_LOG = true;
bool Loging::ENABLE_BLUE_LOG = true;
bool Loging::ENABLE_YELLOW_LOG = true;
bool Loging::ENABLE_CYAN_LOG = true;

void Loging::disableLogs()
{
    Loging::ENABLE_RED_LOG = false;
    Loging::ENABLE_WHITE_LOG = false;
    Loging::ENABLE_MAGENTA_LOG = false;
    Loging::ENABLE_GREEN_LOG = false;
    Loging::ENABLE_BLUE_LOG = false;
    Loging::ENABLE_YELLOW_LOG = false;
    Loging::ENABLE_CYAN_LOG = false;

}

void Loging::enableLogs()
{
    Loging::ENABLE_RED_LOG = true;
    Loging::ENABLE_WHITE_LOG = true;
    Loging::ENABLE_MAGENTA_LOG = true;
    Loging::ENABLE_GREEN_LOG = true;
    Loging::ENABLE_BLUE_LOG = true;
    Loging::ENABLE_YELLOW_LOG = true;
    Loging::ENABLE_CYAN_LOG = true;
}
