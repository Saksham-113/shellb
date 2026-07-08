#include <cstdlib>
#include "shellbStart.h"
#include "shellbLoop.h"

int main() {
    //The config files (if any) are here
    shellb_start();

    //The shell loop
    shellb_loop();

    //Cleaning up / Shutdown
    // end_shellb();
    
    return EXIT_SUCCESS;
}
