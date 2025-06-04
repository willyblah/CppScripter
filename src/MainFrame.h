#ifndef MAINFRAME_H
#define MAINFRAME_H

#include "CodeEditor.h"

#include <wx/splitter.h>
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    explicit MainFrame(const wxString &title);

private:
    // ---- IDs for menus ----

    enum IDs
    {
        ID_LOWEST = 99,

        ID_OUTPUT,
        ID_COMPILE,
        ID_RUN
    };

    // ---- Controls ----

    wxSplitterWindow *m_splitter;
    CodeEditor *m_editor;
    wxPanel *m_outputPanel;
    wxButton *m_closeOutputButton;
    wxTextCtrl *m_outputArea;

    // ---- UI-related methods ----

    void SetupMenus();
    void CreateControls();
    void BindEventHandlers();

    // ---- Event handlers ----

    void OnClose(wxCloseEvent &event);

    // ---- Other methods ----

    void LoadSettings();
    void SaveSettings();
};

#endif // MAINFRAME_H
