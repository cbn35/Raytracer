/* Implementation of CSV.h
 * For CS430, Raytracer
 * Chance Nelson
 */

Entity parse_line(char *line) {
    char entityType[BUFFER_SIZE];
    char attribute0Name[BUFFER_SIZE];
    char attribute0Data[BUFFER_SIZE];
    char attribute1Name[BUFFER_SIZE];
    char attribute1Data[BUFFER_SIZE];
    char attribute2Name[BUFFER_SIZE];
    char attribute2Data[BUFFER_SIZE];

    Entity entity;
    sscanf(line, "%[^,]", entityType);

    if(strcmp(entityType, "camera") == 0) {        
        entity.id = 0;

        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] %[^,] %*[^ ] %[^:] %*[^ ] %[^,]",
                     attribute0Name, attribute0Data,
                     attribute1Name, attribute1Data);

        if(strcmp(attribute0Name, "width") == 0) {
            entity.attributes.dimensions[0] = atof(attribute0Data);    
        } else if(strcmp(attribute0Name, "height") == 0) {
            entity.attributes.dimensions[1] = atof(attribute0Data);
        }

        if(strcmp(attribute1Name, "width") == 0) {
            entity.attributes.dimensions[0] = atof(attribute1Data);    
        } else if(strcmp(attribute1Name, "height") == 0) {
            entity.attributes.dimensions[1] = atof(attribute1Data);
        }
    } else if(strcmp(entityType, "sphere") == 0) {
        entity.id = 1;

        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] %[^\n]",
                     attribute0Name, attribute0Data, attribute1Name, attribute1Data, attribute2Name, attribute2Data);

        if(strcmp(attribute0Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute0Data);
        } else if(strcmp(attribute0Name, "position") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute0Name, "color") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

        if(strcmp(attribute1Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute1Data);
        } else if(strcmp(attribute1Name, "position") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z); 
        } else if(strcmp(attribute1Name, "color") == 0) {
            sscanf(attribute1Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }
       
        if(strcmp(attribute2Name, "radius") == 0) {
            entity.attributes.radius = atof(attribute2Data);
        } else if(strcmp(attribute2Name, "position") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute2Name, "color") == 0) {
            sscanf(attribute2Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

    } else if(strcmp(entityType, "plane") == 0) {
        entity.id = 2;

        sscanf(line, "%*[^,] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]] %*[^ ] %[^:] %*[^ ] [%[^]]",
                     attribute0Name, attribute0Data, attribute1Name, attribute1Data, attribute2Name, attribute2Data);

        if(strcmp(attribute0Name, "normal") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.attributes.normal.x, 
                                                    &entity.attributes.normal.y,
                                                    &entity.attributes.normal.z);
        } else if(strcmp(attribute0Name, "position") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.x, &entity.y, &entity.z);
        } else if(strcmp(attribute0Name, "color") == 0) {
            sscanf(attribute0Data, "%lf, %lf, %lf", &entity.color.r,
                                                    &entity.color.g,
                                                    &entity.color.b);
        }

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
