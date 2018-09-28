#include "App/App.hpp"
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    App main_app(640, 480);
    main_app.Run();

    return EXIT_SUCCESS;
}