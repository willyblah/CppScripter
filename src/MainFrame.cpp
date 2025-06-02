#include "MainFrame.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupMenus();
}

void MainFrame::SetupMenus()
{
    auto* menuBar = new wxMenuBar;

    auto fileMenu = new wxMenu;
    fileMenu->Append(wxID_NEW);
    fileMenu->Append(wxID_OPEN);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_SAVE);
    fileMenu->Append(wxID_SAVEAS);
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "&Quit\tCtrl+Q");

    auto editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO);
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT);
    editMenu->Append(wxID_COPY);
    editMenu->Append(wxID_PASTE);
    editMenu->AppendSeparator();
    editMenu->Append(wxID_SELECTALL);

    auto viewMenu = new wxMenu;
    viewMenu->AppendCheckItem(ID_OUTPUT, "&Output\tCtrl+Alt+O");

    auto executeMenu = new wxMenu;
    executeMenu->Append(ID_COMPILE, "&Compile\tCtrl+B");
    executeMenu->Append(ID_RUN, "&Run...\tCtrl+R");

    auto helpMenu = new wxMenu;
    helpMenu->Append(wxID_ABOUT, "&About...");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(editMenu, "&Edit");
    menuBar->Append(viewMenu, "&View");
    menuBar->Append(executeMenu, "E&xecute");
    menuBar->Append(helpMenu, "Help");

    SetMenuBar(menuBar);
}
