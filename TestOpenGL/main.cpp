
#include "Appaction.hpp"
#include "00_draw_triangle.h"
#include "01_draw_texture.h"
#include "02_transformation.hpp"
#include "03_coordinateSystem.hpp"
#include "04_camera.hpp"
#include "05_camera_class.hpp"
#include "06_light.hpp"


int main() {
    Appaction *app = new Appaction();

    // draw_triangle(app->window);
    // draw_texture(app->window);
    // transformation(app->window);
    // coordinateSystem(app->window);
    // camera5(app->window);
    cameraClass(app->window);
    // light(app->window);

    return 0;
}
