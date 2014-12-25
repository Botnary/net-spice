#include <stdio.h>
#include <ncurses.h>
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
        waddstr(menubar,"ROJECTS");
        wmove(menubar,1,12);
        wattron(menubar,COLOR_PAIR(3));
        waddstr(menubar,"C");
        wbkgd(menubar,COLOR_PAIR(2));
        waddstr(menubar,"ONTACTS");
        wmove(menubar,1,23);
        wattron(menubar,COLOR_PAIR(3));
        waddstr(menubar,"R");
        wbkgd(menubar,COLOR_PAIR(2));
        waddstr(menubar,"EPORTS");
    };
    WINDOW **Gui::DrawProjectMenu(int start_col){
        WINDOW **items;
        items=(WINDOW **)malloc(9*sizeof(WINDOW *));
        items[0]=newwin(10,19,1,start_col);
        wbkgd(items[0],COLOR_PAIR(2));
        box(items[0],ACS_VLINE,ACS_HLINE);
        items[1]=subwin(items[0],1,17,2,start_col+1);
        wprintw(items[1],"NEW",1);
        items[2]=subwin(items[0],1,17,3,start_col+1);
        wprintw(items[2],"SEARCH",2);
        items[3]=subwin(items[0],1,17,4,start_col+1);
        wprintw(items[3],"LIST ALL",3);
        wbkgd(items[1],COLOR_PAIR(1));
        wrefresh(items[0]);
        return items;
    };
    WINDOW **Gui::DrawContactMenu(int start_col){
        WINDOW **items;
        items=(WINDOW **)malloc(9*sizeof(WINDOW *));
        items[0]=newwin(10,19,1,start_col);
        wbkgd(items[0],COLOR_PAIR(2));
        box(items[0],ACS_VLINE,ACS_HLINE);
        items[1]=subwin(items[0],1,17,2,start_col+1);
        wprintw(items[1],"NEW",1);
        items[2]=subwin(items[0],1,17,3,start_col+1);
        wprintw(items[2],"SEARCH",2);
        items[3]=subwin(items[0],1,17,4,start_col+1);
        wprintw(items[3],"LIST ALL",3);
        wbkgd(items[1],COLOR_PAIR(1));
        wrefresh(items[0]);
        return items;
    };
    WINDOW **Gui::DrawReportMenu(int start_col){
        WINDOW **items;
        items=(WINDOW **)malloc(9*sizeof(WINDOW *));
        items[0]=newwin(10,19,1,start_col);
        wbkgd(items[0],COLOR_PAIR(2));
        box(items[0],ACS_VLINE,ACS_HLINE);
        items[1]=subwin(items[0],1,17,2,start_col+1);
        wprintw(items[1],"NEW",1);
        items[2]=subwin(items[0],1,17,3,start_col+1);
        wprintw(items[2],"SEARCH",2);
        items[3]=subwin(items[0],1,17,4,start_col+1);
        wprintw(items[3],"LIST ALL",3);
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
                touchwin(stdscr);
                refresh();
                //items= this->DrawMenu(20-menu_start_col);
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
    void Gui::ProjectDropDownMenu(WINDOW *messagebar){
        int selected_item;
        WINDOW **menu_items;
        menu_items = this->DrawProjectMenu(0);
        selected_item = this->ScrollMenu(menu_items,8,10);
        this->DeleteMenu(menu_items,9);
        switch (selected_item) {
            case -1:
                wprintw(messagebar,"You haven't selected any item.");
                break;
            case 0:
                wprintw(messagebar,"NEW PROJECT.");
                break;
            case 1:
                wprintw(messagebar,"SEARCH FOR A PROJECT.",1);
                break;
            case 2:
                wprintw(messagebar,"LIST ALL PROJECTS.",2);
            default:
                break;
        }
        touchwin(stdscr);
        refresh();
    };
    void Gui::ContactDropDownMenu(WINDOW *messagebar){
        int selected_item;
        WINDOW **menu_items;
        menu_items = this->DrawContactMenu(10);
        selected_item = this->ScrollMenu(menu_items,8,10);
        this->DeleteMenu(menu_items,9);
        switch (selected_item) {
            case 0:
                wprintw(messagebar,"NEW CONTACT.");
                break;
            case 1:
                wprintw(messagebar,"SEARCH FOR A CONTACT.",1);
                break;
            case 2:
                wprintw(messagebar,"LIST ALL CONTACTS.",2);
            default:
                break;
        }
        touchwin(stdscr);
        refresh();
    };
    void Gui::ReportDropDownMenu(WINDOW *messagebar){
        int selected_item;
        WINDOW **menu_items;
        menu_items = this->DrawReportMenu(20);
        selected_item = this->ScrollMenu(menu_items,8,10);
        this->DeleteMenu(menu_items,9);
        switch (selected_item) {
            case 0:
                wprintw(messagebar,"NEW REPORT.");
                break;
            case 1:
                wprintw(messagebar,"SEARCH FOR A REPORT.",1);
                break;
            case 2:
                wprintw(messagebar,"LIST ALL REPORTS.",2);
            default:
                break;
        }
        touchwin(stdscr);
        refresh();
    };
    
    void Gui::InitNav(){
        int key;
        WINDOW *menubar,*messagebar;
        
        bkgd(COLOR_PAIR(1));
        menubar=subwin(stdscr,3,0,0,0);
        messagebar=subwin(stdscr,1,79,23,1);
        this->DrawMenuBar(menubar);
        move(4,1);
        printw("Press F1, F2 and F3 to open the menus. ");
        printw("ESC quits.");
        refresh();
        
        do {
            
            key=getch();
            werase(messagebar);
            wrefresh(messagebar);
            switch (key) {
                case KEY_F(1):
                    this->ProjectDropDownMenu(messagebar);
                    break;
                case KEY_F(2):
                    this->ContactDropDownMenu(messagebar);
                    break;
                case KEY_F(3):
                    this->ReportDropDownMenu(messagebar);
                    break;
                default:
                    break;
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
}