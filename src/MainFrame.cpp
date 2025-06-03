#include "MainFrame.h"

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupMenus();
    CreateControls();
}

void MainFrame::SetupMenus()
{
    auto *menuBar = new wxMenuBar;

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

void MainFrame::CreateControls()
{
    auto mainSizer = new wxBoxSizer(wxVERTICAL);

    m_splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);

    m_editor = new CodeEditor(m_splitter);

    m_outputPanel = new wxPanel(m_splitter);
    auto outputSizer = new wxBoxSizer(wxVERTICAL);

    auto outputCtrlSizer = new wxBoxSizer(wxHORIZONTAL);

    auto outputLabel = new wxStaticText(m_outputPanel, wxID_ANY, "Output");
    m_closeOutputButton = new wxButton(m_outputPanel, wxID_ANY, "Close");

    outputCtrlSizer->Add(outputLabel, 0, wxALIGN_CENTER_VERTICAL);
    outputCtrlSizer->AddStretchSpacer();
    outputCtrlSizer->Add(m_closeOutputButton);

    m_outputArea = new wxTextCtrl(m_outputPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE | wxTE_READONLY);

    outputSizer->Add(outputCtrlSizer, 0, wxEXPAND);
    outputSizer->Add(m_outputArea, 1, wxEXPAND);

    m_outputPanel->SetSizer(outputSizer);

    // Hide the output panel on startup.
    m_splitter->Initialize(m_editor);
    m_outputPanel->Hide(); // Ensure that the output panel is completely invisible

    mainSizer->Add(m_splitter, 1, wxEXPAND | wxALL, 4);

    SetSizer(mainSizer);

    // Change the window's background color to match the color of the editor and wxWidgets panels.
    auto bgColor = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
    SetBackgroundColour(bgColor);

    SetClientSize(1280, 720);
    SetMinClientSize(wxSize(800, 600));
}
