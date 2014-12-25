#include <form.h>
#include "project_form.h"

namespace net_spice{
    
    void ProjectForm::DrawForm(){
        /* Initialize few color pairs */
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_WHITE, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_BLACK);
        
        /* Initialize the fields */
        field[0] = new_field(1, 20, 4, 25, 0, 0);
        field[1] = new_field(1, 20, 6, 25, 0, 0);
        field[2] = new_field(1, 20, 8, 25, 0, 0);
        field[3] = NULL;
        
        /* Set field options */
        set_field_fore(field[0], COLOR_PAIR(2));/* Put the field with blue background */
        set_field_back(field[0], COLOR_PAIR(2));/* and white foreground (characters */
        
        set_field_fore(field[1], COLOR_PAIR(2));/* Put the field with blue background */
        set_field_back(field[1], COLOR_PAIR(2));/* and white foreground (characters */

        set_field_fore(field[2], COLOR_PAIR(2));/* Put the field with blue background */
        set_field_back(field[2], COLOR_PAIR(2));/* and white foreground (characters */

        /* are printed in white 	*/
        //field_opts_off(field[0], O_AUTOSKIP);  	/* Don't go to next field when this */
        /* Field is filled up 		*/
        //set_field_back(field[1], O_AUTOSKIP);
        //field_opts_off(field[1], O_AUTOSKIP);
        
        /* Create the form and post it */
        my_form = new_form(field);
        post_form(my_form);
        //refresh();
        
        set_current_field(my_form, field[0]); /* Set focus to the colored field */
        mvprintw(4, 12, "Name:");
        mvprintw(6, 12, "Date:");
        mvprintw(8, 12, "Description:");
        mvprintw(LINES - 2, 0, "Use UP, DOWN arrow keys to switch between fields");
        //refresh();
        
        /* Loop through to get user requests */
        while((ch = getch()) != KEY_F(1))
        {	switch(ch)
            {	case KEY_DOWN:
                    /* Go to next field */
                    form_driver(my_form, REQ_NEXT_FIELD);
                    /* Go to the end of the present buffer */
                    /* Leaves nicely at the last character */
                    form_driver(my_form, REQ_END_LINE);
                    break;
                case KEY_UP:
                    /* Go to previous field */
                    form_driver(my_form, REQ_PREV_FIELD);
                    form_driver(my_form, REQ_END_LINE);
                    break;
                default:
                    /* If this is a normal character, it gets */
                    /* Printed				  */
                    form_driver(my_form, ch);
                    break;
            }
        }
        
        /* Un post form and free the memory */
        unpost_form(my_form);
        free_form(my_form);
        free_field(field[0]);
        free_field(field[1]);
        free_field(field[2]);
        endwin();
    };
}