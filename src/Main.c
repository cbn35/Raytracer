/* Main file for recursive raytracer
 * CS430
 * Chance Nelsom
 */

#include <stdio.h>
#include <stdlib.h>
#include "../lib/PPM-Converter/src/PPM.h"
#include "CSV.h"
#include "Raytrace.h"

int main(int argc, char **argv) {
    // Check the program arguments
    if(argc != 5) {
        fprintf(stderr, "ERROR: invalid number of arguments\n");
        return 1;
    }

    if(atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
        fprintf(stderr, "ERROR: invalid width and height arguments\n");
        return 1;
    }

    FILE *test = fopen(argv[3], "r");
    if(test == NULL) {
        fprintf(stderr, "ERROR: config file could not be opeed\n");
        return 1;
    }
    else fclose(test);

    test = fopen(argv[4], "r");
    if(test != NULL) {
        fprintf(stderr, "ERROR: output file already exists\n");
        fclose(test);
        return 1;
    }

    double screenWidth = 0;
    double screenHeight = 0;
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    FILE *out = create_ppm_p6(argv[4], width, height, 255);
    Entity *entities = process_csv(fopen(argv[3], "r"));

    int numEntities = 0;
    while(entities[numEntities].id != -1) {
        if(entities[numEntities].id == 0) {
            screenWidth = entities[numEntities].attributes.dimensions[0];
            screenHeight = entities[numEntities].attributes.dimensions[1];
        }
        numEntities++;

    }  
 
    Color background;
    background.r = 0;
    background.g = 0;
    background.b = 0;
    Ray view;

    for(int row = 0; row < height; row++) {
        for(int column = 0; column < width; column++) {
            view.x0 = 0.00;
            view.y0 = 0.00;
            view.z0 = 0.00;
            view.x1 = view.x0 - (screenWidth / 2) + ((screenWidth / width) * column);
            view.y1 = view.y0 + (screenHeight / 2) - ((screenHeight / height) * row); 
            view.z1 = -1;

            Color color = shoot(view, entities, background, numEntities, 0);
            write_pixel((int) (color.r * 255.00), (int) (color.g * 255.00), (int) (color.b * 255.00), out);
        } 
    }
    free(entities);
    return 0;

}
