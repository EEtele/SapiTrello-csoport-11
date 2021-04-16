#include "../include/instance.h"
#include "../include/terminal.h"

int main() {
    instanceLoad();

    terminalLoop();

    instanceWrite();
    return 0;
}
