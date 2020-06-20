
#include "Appaction.hpp"
#include "00_draw_triangle.h"
#include "01_draw_texture.h"
#include "02_transformation.hpp"
#include "03_coordinateSystem.hpp"
#include "04_camera.hpp"
#include "05_camera_class.hpp"
#include "06_light.hpp"
#include "07_baseLight.hpp"


int main() {
    // glm::vec3 a = glm::vec3(-0.5f, -0.5f, -0.5f);
    // glm::vec3 b = glm::vec3(0.5f, -0.5f, -0.5f);
    // glm::vec3 c = glm::vec3(0.5f, 0.5f, -0.5f);
    // // glm::vec3 norm = glm::cross(b - a, c - a);
    // glm::vec3 norm = glm::cross(a - b, c - a);
    // cout << norm.x << ", " << norm.y << ", " << norm.z << endl;


    Appaction *app = new Appaction();

    // draw_triangle(app->window);
    // draw_texture(app->window);
    // transformation(app->window);
    // coordinateSystem(app->window);
    // camera5(app->window);
    // cameraClass(app->window);
    // light(app->window);
    baseLight(app->window);

    return 0;
}
