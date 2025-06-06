#include "MainFrame.h"

#include <wx/config.h>

MainFrame::MainFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetupMenus();
    CreateControls();
    BindEventHandlers();
    LoadSettings();
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

    m_splitter =
        new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);

    m_editor = new CodeEditor(m_splitter);

    m_outputPanel = new wxPanel(m_splitter);
    auto outputSizer = new wxBoxSizer(wxVERTICAL);

    auto outputCtrlSizer = new wxBoxSizer(wxHORIZONTAL);

    auto outputLabel = new wxStaticText(m_outputPanel, wxID_ANY, "Output");
    m_closeOutputButton = new wxButton(m_outputPanel, wxID_ANY, "Close");

    outputCtrlSizer->Add(outputLabel, 0, wxALIGN_CENTER_VERTICAL);
    outputCtrlSizer->AddStretchSpacer();
    outputCtrlSizer->Add(m_closeOutputButton);

    m_outputArea = new wxTextCtrl(m_outputPanel, wxID_ANY, wxEmptyString, wxDefaultPosition,
                                  wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

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

    SetMinClientSize(wxSize(800, 600));
}

void MainFrame::BindEventHandlers()
{
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->Undo(); }, wxID_UNDO);
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->Redo(); }, wxID_REDO);
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->Cut(); }, wxID_CUT);
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->Copy(); }, wxID_COPY);
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->Paste(); }, wxID_PASTE);
    Bind(wxEVT_MENU, [this](wxCommandEvent &) { m_editor->SelectAll(); }, wxID_SELECTALL);

    Bind(wxEVT_UPDATE_UI, &MainFrame::OnUpdateUI, this);

    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

void MainFrame::OnUpdateUI(wxUpdateUIEvent &event)
{
    wxMenuBar* menuBar = GetMenuBar();

    menuBar->Enable(wxID_UNDO, m_editor->CanUndo());
    menuBar->Enable(wxID_REDO, m_editor->CanRedo());
    menuBar->Enable(wxID_CUT, m_editor->CanCut());
    menuBar->Enable(wxID_COPY, m_editor->CanCopy());
    menuBar->Enable(wxID_PASTE, m_editor->CanPaste());
}

void MainFrame::OnClose(wxCloseEvent &event)
{
    SaveSettings();
    event.Skip();
}

void MainFrame::LoadSettings()
{
    wxConfigBase *config = wxConfig::Get();

    int x = config->ReadLong("/Window/X", -1);
    int y = config->ReadLong("/Window/Y", -1);
    int w = config->ReadLong("/Window/Width", 1280);
    int h = config->ReadLong("/Window/Height", 720);

    if (x != -1 && y != -1)
        SetPosition(wxPoint(x, y));
    SetSize(w, h);

    if (bool maximized = config->ReadBool("/Window/Maximized", false))
        Maximize();

    wxString editorFontDesc;
    if (config->Read("/Editor/Font", &editorFontDesc))
    {
        wxFont editorFont;
        editorFont.SetNativeFontInfo(editorFontDesc);
        m_editor->StyleSetFont(wxSTC_STYLE_DEFAULT, editorFont);
        m_editor->StyleSetFont(wxSTC_STYLE_LINENUMBER, editorFont);
    }
    else
    {
        wxFont editorFont(wxFontInfo(10).FaceName("Consolas"));
        m_editor->StyleSetFont(wxSTC_STYLE_DEFAULT, editorFont);
        m_editor->StyleSetFont(wxSTC_STYLE_LINENUMBER, editorFont);
    }
    m_editor->UpdateMarginWidth();
}

void MainFrame::SaveSettings()
{
    wxConfigBase *config = wxConfig::Get();

    if (!IsMaximized())
    {
        const wxRect rect = GetRect();
        config->Write("/Window/X", static_cast<long>(rect.x));
        config->Write("/Window/Y", static_cast<long>(rect.y));
        config->Write("/Window/Width", static_cast<long>(rect.width));
        config->Write("/Window/Height", static_cast<long>(rect.height));
    }

    config->Write("/Window/Maximized", IsMaximized());

    wxFont editorFont = m_editor->StyleGetFont(wxSTC_STYLE_DEFAULT);
    config->Write("/Editor/Font", editorFont.GetNativeFontInfoDesc());

    config->Flush();
}
