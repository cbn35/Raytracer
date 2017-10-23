/* Main file for recursive raytracer
 * CS430
 * Chance Nelsom
 */

typedef struct {
    int r;
    int g;
    int b;
} RGB;


RGB calc_lighting_for_pixel(Vector v)
