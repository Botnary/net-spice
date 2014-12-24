#include <curses.h>

#ifndef WINDOW_GUI
#define WINDOW_GUI
#define ESC 0x1B

namespace net_spice{

class Gui
{
private:
	void init_curses();
	void draw_menubar(WINDOW *menubar);
	WINDOW **draw_menu(int start_col);
	int scroll_menu(WINDOW **items,int count,int menu_start_col);
	void delete_menu(WINDOW **items,int count);
	void ini_nav();
public:
	void Loop();
	Gui();
	~Gui();	
};

}
#endif  // WINDOW_GUI