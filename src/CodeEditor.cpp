#include "CodeEditor.h"

CodeEditor::CodeEditor(wxWindow *parent) : wxStyledTextCtrl(parent, wxID_ANY)
{
    SetupStyle();
    SetupSyntaxHighlighting();
}

void CodeEditor::UpdateMarginWidth()
{
    int charWidth = TextWidth(wxSTC_STYLE_LINENUMBER, "0");
    SetMarginWidth(0, charWidth * 4 + 4);
}

void CodeEditor::SetupStyle()
{
    SetUseTabs(true);
    SetTabWidth(4);
    SetBackSpaceUnIndents(true);

    SetIndentationGuides(wxSTC_IV_LOOKBOTH);
    StyleSetForeground(wxSTC_STYLE_INDENTGUIDE, wxColour(169, 169, 169));

    SetCaretLineVisible(true);
    SetCaretLineBackground(wxColour(230, 230, 250));

    SetEdgeMode(wxSTC_EDGE_LINE);
    SetEdgeColumn(80);

    SetMarginType(0, wxSTC_MARGIN_NUMBER);
}

void CodeEditor::SetupSyntaxHighlighting()
{
    SetLexer(wxSTC_LEX_CPP);

    StyleSetForeground(wxSTC_C_COMMENT, wxColour(0, 128, 0));
    StyleSetForeground(wxSTC_C_COMMENTLINE, wxColour(0, 128, 0));
    StyleSetForeground(wxSTC_C_COMMENTDOC, wxColour(0, 128, 0));
    StyleSetForeground(wxSTC_C_NUMBER, wxColour(128, 128, 0));
    StyleSetForeground(wxSTC_C_WORD, wxColour(0, 0, 205));
    StyleSetForeground(wxSTC_C_STRING, wxColour(128, 0, 128));
    StyleSetForeground(wxSTC_C_CHARACTER, wxColour(196, 98, 16));
    StyleSetForeground(wxSTC_C_PREPROCESSOR, wxColour(128, 117, 0));
    StyleSetForeground(wxSTC_C_OPERATOR, wxColour(165, 42, 42));

    SetKeyWords(
        0,
        "alignas alignof and and_eq asm auto bitand bitor bool break case catch char char16_t "
        "char32_t class compl const constexpr const_cast continue decltype default delete do "
        "double dynamic_cast else enum explicit export extern false float for friend goto if "
        "inline int long mutable namespace new noexcept not not_eq nullptr operator or or_eq "
        "private protected public register reinterpret_cast return short signed sizeof static "
        "static_assert static_cast struct switch template this thread_local throw true try typedef "
        "typeid typename union unsigned using virtual void volatile wchar_t while xor xor_eq");
}
