#ifndef PROJECT_FORM
#define PROJECT_FORM

#include <form.h>

namespace net_spice{
    
    class ProjectForm{
    private:
        FIELD *field[4];
        FORM  *my_form;
        int ch;
    public:
        void DrawForm();
    };
    
}

#endif  // PROJECT_FORM