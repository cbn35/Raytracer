/* Implementation of CSV.h
 * For CS430, Raytracer
 * Chance Nelson
 */

Entity parse_line(char *line) {
    /* Parse a line from a CSV file
     * 
     * Args:
     *      line (char*): null-terminated string from a CSV file
     * Returns (Entity): Entity struct with the neede data
     */
    char entityType[BUFFER_SIZE];      // Allocate some space for each possible
    char attribute0Name[BUFFER_SIZE];  // attribute name and it's data
    char attribute0Data[BUFFER_SIZE];
    char attribute1Name[BUFFER_SIZE];
    char attribute1Data[BUFFER_SIZE];
    char attribute2Name[BUFFER_SIZE];
    char attribute2Data[BUFFER_SIZE];

    Entity entity;                      // Initialize the returning entity
    
    sscanf(line, "%[^,]", entityType);  // Run through the line until the
                                        // first comma, and put the string
                                        // into entityType

    // Parse through with the expected structure of a camera
    if(strcmp(entityType, "camera") == 0) {        
        entity.id = 0;

        // Parse through the line, with exprect structure:
        //      "[type], [attr0]: [data0], [attr1]: [data1]"
        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] %[^,] %*[^ ] %[^:] %*[^ ] %[^,]",
                     attribute0Name, attribute0Data,
                     attribute1Name, attribute1Data);

        // If attribute0Name is "width", set the camera width
        if(strcmp(attribute0Name, "width") == 0) {
            entity.attributes.dimensions[0] = atof(attribute0Data);
        // Otherwise set the camera height    
        } else if(strcmp(attribute0Name, "height") == 0) {
            entity.attributes.dimensions[1] = atof(attribute0Data);
        }

        // If attribute1Name is "height", set the camera height
        if(strcmp(attribute1Name, "width") == 0) {
            entity.attributes.dimensions[0] = atof(attribute1Data);
        // Otherwise set the camera width    
        } else if(strcmp(attribute1Name, "height") == 0) {
            entity.attributes.dimensions[1] = atof(attribute1Data);
        }
    // Parse through the expected structure of a sphere
    } else if(strcmp(entityType, "sphere") == 0) {
        entity.id = 1;

        // Parse through the line, with expected structure:
        //      "[type], [attr0]: [[data0]], [attr1]: [[data1]], [attr2]: [data2]"
        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] %[^\n]",
                     attribute0Name, attribute0Data, attribute1Name, attribute1Data, attribute2Name, attribute2Data);

        // If attribute0Name is "radius", set the sphere radius
        if(strcmp(attribute0Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute0Data);
        // Otherwise attempt parsing of "position"
        } else if(strcmp(attribute0Name, "position") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        // Otherwise attempt parsing of "color"
        } else if(strcmp(attribute0Name, "color") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

        // Do the same deal for attribute1Name/Data
        if(strcmp(attribute1Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute1Data);
        } else if(strcmp(attribute1Name, "position") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z); 
        } else if(strcmp(attribute1Name, "color") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

        // Do the same deal for attribute2Name/Data
        if(strcmp(attribute2Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute2Data);
        } else if(strcmp(attribute2Name, "position") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute2Name, "color") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }
    // Parse through the expected structure of a Plane
    } else if(strcmp(entityType, "plane") == 0) {
        entity.id = 2;

        // Parse through the line, with expected structure:
        //      "[type], [attr0]: [[data0]], [attr1]: [[data1]], [attr2]: [[data2]]"
        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]]",
                     attribute0Name, attribute0Data, attribute1Name, attribute1Data, attribute2Name, attribute2Data);

        // If attribute0Name is "normal", set the normal vector
        if(strcmp(attribute0Name, "normal") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.attributes.normal.x, 
                                                    &entity.attributes.normal.y,
                                                    &entity.attributes.normal.z);
        // Otherwise, set the position vector
        } else if(strcmp(attribute0Name, "position") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        // Otherwise, set the color
        } else if(strcmp(attribute0Name, "color") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

        // Do the same deal for attribute1Name/Data
        if(strcmp(attribute1Name, "normal") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.attributes.normal.x, 
                                                    &entity.attributes.normal.y,
                                                    &entity.attributes.normal.z);
        } else if(strcmp(attribute1Name, "position") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute1Name, "color") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

        // Do the same deal for attribute2Name/Data
        if(strcmp(attribute2Name, "normal") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.attributes.normal.x, 
                                                    &entity.attributes.normal.y,
                                                    &entity.attributes.normal.z);
        } else if(strcmp(attribute2Name, "position") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute2Name, "color") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        } 
    }
    return entity;

}
