#include <stdio.h>
#include <curses.h>
#include <stdlib.h>

#include "gui.h"

namespace net_spice {

void Gui::Loop(){
	this->InitNav();
};

void Gui::DrawMenuBar(WINDOW *menubar){
	wmove(menubar,1,1);
	wattron(menubar,COLOR_PAIR(3));
	waddstr(menubar,"P");
	wbkgd(menubar,COLOR_PAIR(2));
	waddstr(menubar,"rojects");
	wmove(menubar,1,12);
	wattron(menubar,COLOR_PAIR(3));
	waddstr(menubar,"C");
	wbkgd(menubar,COLOR_PAIR(2));
	waddstr(menubar,"ontacts");
	wmove(menubar,1,23);
	wattron(menubar,COLOR_PAIR(3));
	waddstr(menubar,"R");
	wbkgd(menubar,COLOR_PAIR(2));
	waddstr(menubar,"eports");
};
WINDOW Gui::**DrawMenu(int start_col){
	WINDOW **items;
	items=(WINDOW **)malloc(9*sizeof(WINDOW *));
	items[0]=newwin(10,19,1,start_col);
	wbkgd(items[0],COLOR_PAIR(2));
	box(items[0],ACS_VLINE,ACS_HLINE);
	items[1]=subwin(items[0],1,17,2,start_col+1);
	wprintw(items[1],"Shailendra singh",1);
	items[2]=subwin(items[0],1,17,3,start_col+1);
	wprintw(items[2],"THIVNENT TECH",2);
	items[3]=subwin(items[0],1,17,4,start_col+1);
	wprintw(items[3],"THINCLIENT",3);
	items[4]=subwin(items[0],1,17,5,start_col+1);
	wprintw(items[4],"SOLARCOMPUTING",4);
	items[5]=subwin(items[0],1,17,6,start_col+1);
	wprintw(items[5],"TECHNOCRATS",5);
	items[6]=subwin(items[0],1,17,7,start_col+1);
	wprintw(items[6],"SENSORS",6);
	items[7]=subwin(items[0],1,17,8,start_col+1);
	wprintw(items[7],"NCURSESLIB",7);
	items[8]=subwin(items[0],1,17,9,start_col+1);
	wprintw(items[8],"GCC COMPILER",8);
	wbkgd(items[1],COLOR_PAIR(1));
	wrefresh(items[0]);
	return items;
};
int Gui::ScrollMenu(WINDOW **items,int count,int menu_start_col){
	int key;
	int selected=0;
	while (1) {
		key=getch();
		if (key==KEY_DOWN || key==KEY_UP) {
				wbkgd(items[selected+1],COLOR_PAIR(2));
				wnoutrefresh(items[selected+1]);
				if (key==KEY_DOWN) {
						selected=(selected+1) % count;
				} else {
						selected=(selected+count-1) % count;
				}
				wbkgd(items[selected+1],COLOR_PAIR(1));
				wnoutrefresh(items[selected+1]);
				doupdate();
		} else if (key==KEY_LEFT || key==KEY_RIGHT) {
				this->DeleteMenu(items,count+1);
				touchwin(stdscr);
				refresh();
				items= this->DrawMenu(20-menu_start_col);
				return this->ScrollMenu(items,20,20-menu_start_col);
		} else if (key==ESCAPE) {
				return -1;
		} else if (key==ENTER) {
				return selected;
		}
	}
};
void Gui::DeleteMenu(WINDOW **items,int count){
	int i;
	for (i=0;i<count;i++){
		delwin(items[i]);
	}
	free(items);
};
void Gui::InitNav(){
	int key;
    WINDOW *menubar,*messagebar;

    bkgd(COLOR_PAIR(1));
    menubar=subwin(stdscr,3,0,0,0);
    messagebar=subwin(stdscr,1,79,23,1);
    this->DrawMenuBar(menubar);
    move(4,1);
    printw("Press F1 or F2 to open the menus. ");
    printw("ESC quits.");
    refresh();

    do {
        int selected_item;
        WINDOW **menu_items;
        key=getch();
        werase(messagebar);
        wrefresh(messagebar);
        if (key==KEY_F(1)) {
            menu_items = this->DrawMenu(0);
            selected_item = this->ScrollMenu(menu_items,8,10);
            this->DeleteMenu(menu_items,9);
            if (selected_item<0){
                wprintw(messagebar,"You haven't selected any item.");
            }else if(selected_item==1){
                wprintw(messagebar,"You have selected menu SHAILENDRA SINGH.",1);
            }else if(selected_item==2){
                wprintw(messagebar,"You have selected menu THINVENT TECH.",2);
            }else if(selected_item==3){
                wprintw(messagebar,"You have selected menu THINCLIENT.",3);
            }else if(selected_item==4){
                wprintw(messagebar,"You have selected menu SOLAR COMPUTING",4);
            }else if(selected_item==5){
                wprintw(messagebar,"You have selected menu TECHNOCRATS.",5);
            }else if(selected_item==6){
                wprintw(messagebar,"You have selected menu SENSORS.",6);
            }else if(selected_item==7){
                wprintw(messagebar,"You have selected menu NCURSESLIB.",7);
            }else if(selected_item==8){
                wprintw(messagebar,"You have selected menu GCCCOMPILER.",8);
			}
            touchwin(stdscr);
            refresh();
        } 
	} while (key!=ESCAPE);

    delwin(menubar);
    delwin(messagebar);
    endwin();
};

Gui::Gui(){
	initscr();
	start_color();
	init_color(BACKGROUND, 181, 181, 181);
	init_pair(1,COLOR_WHITE, COLOR_BLUE);//text and background
	init_pair(2,COLOR_BLUE,COLOR_WHITE);//menu bar
	init_pair(3,COLOR_RED,COLOR_WHITE);
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
};

Gui::~Gui(){
	printf("Delete Gui ...\n");
}