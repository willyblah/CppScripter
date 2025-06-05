#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <wx/stc/stc.h>
#include <wx/wx.h>

class CodeEditor : public wxStyledTextCtrl
{
public:
    explicit CodeEditor(wxWindow *parent);

    void UpdateMarginWidth();

private:
    void SetupStyle();
    void SetupSyntaxHighlighting();
};

#endif // CODEEDITOR_H
