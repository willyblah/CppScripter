#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <wx/stc/stc.h>
#include <wx/wx.h>

class CodeEditor : public wxStyledTextCtrl
{
public:
    explicit CodeEditor(wxWindow *parent);
};

#endif // CODEEDITOR_H
