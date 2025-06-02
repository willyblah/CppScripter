#ifndef APP_H
#define APP_H

#include <wx/app.h>

class App : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(App);

#endif //APP_H
