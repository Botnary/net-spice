#include "./src/window/gui.h"

int main()
{
   net_spice::Gui *gui = new net_spice::Gui();
   gui->Loop();
   delete gui;
   return 0;
}