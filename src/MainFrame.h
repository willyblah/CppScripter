#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
    explicit MainFrame(const wxString& title);

private:
    // ---- IDs for menus ----

    enum IDs
    {
        ID_LOWEST = 99,

        ID_OUTPUT,
        ID_COMPILE,
        ID_RUN
    };

    // ---- UI-related methods ----

    void SetupMenus();
};

#endif // MAINFRAME_H
