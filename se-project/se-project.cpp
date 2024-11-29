#include <iostream>
#include "Business.h"
#include "Events/Event.h"
#include "Utils/UUID.h"
#include "Defs.h"
#include "Utils/Prompts.h"
#include <sstream>
#include "WeddingEventCenter.h"
#include "DisplayMannager.h"

using namespace WEP;

int main()
{
    WeddingEventCenter eventCenter = {};
    DisplayMannager display = DisplayMannager(eventCenter);
    display.run();
}