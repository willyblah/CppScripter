#include "App.h"
#include "MainFrame.h"

bool App::OnInit()
{
    auto mainFrame = new MainFrame("CppScripter");
    mainFrame->Show();
    return true;
}
