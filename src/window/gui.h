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
	WINDOW **DrawMenu(int start_col);
	int ScrollMenu(WINDOW **items,int count,int menu_start_col);
	void DeleteMenu(WINDOW **items,int count);
	void InitNav();
public:
	void Loop();
	Gui();
	~Gui();	
};

}
#endif  // WINDOW_GUI