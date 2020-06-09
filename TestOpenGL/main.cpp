
#include <string>

#include "Appaction.hpp"
#include "00_draw_triangle.h"
#include "01_draw_texture.h"
#include "02_transformation.hpp"
#include "03_coordinateSystem.hpp"
#include "04_camera.hpp"

int main() {
    Appaction *app = new Appaction();

    // draw_triangle(app->window);
    // draw_texture(app->window);
    // transformation(app->window);
    // coordinateSystem(app->window);
    camera(app->window);
    return 0;
}
