#include "App/App.hpp"
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    app::App main_app = app::App();
    main_app.run();

    return EXIT_SUCCESS;
}