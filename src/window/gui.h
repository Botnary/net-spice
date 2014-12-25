#include <curses.h>

#ifndef WINDOW_GUI
#define WINDOW_GUI
#define ESC 0x1B
#define ENTER 10
#define ESCAPE 27
#define BACKGROUND 1


namespace net_spice{
    
    class Gui
    {
    private:
        void DrawMenuBar(WINDOW *menubar);
        WINDOW **DrawProjectMenu(int start_col);
        WINDOW **DrawContactMenu(int start_col);
        WINDOW **DrawReportMenu(int start_col);
        int ScrollMenu(WINDOW **items,int count,int menu_start_col);
        void DeleteMenu(WINDOW **items,int count);        
        void ProjectDropDownMenu(WINDOW *messagebar);
        void ContactDropDownMenu(WINDOW *messagebar);
        void ReportDropDownMenu(WINDOW *messagebar);
        void InitNav();
    public:
        void Loop();
        Gui();
        ~Gui();	
    };
    
}
#endif  // WINDOW_GUI