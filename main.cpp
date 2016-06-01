#include <iostream>
#include "screen.h"
#include "container.h"
#include "terminal.h"
#include "screenfield.h"

#include "event.h"
using namespace std;

int main() {
    cout << "Hello, World!" << endl;
    UI::Screen screen("holidayscreen");
    UI::terminal().root().addComponent(screen);
    UI::terminal().drawAll();
    screen.focus(screen.firstEditable());
    UI::terminal().root().focus(screen);
    UI::terminal().startMainLoop();
    return 0;
}
