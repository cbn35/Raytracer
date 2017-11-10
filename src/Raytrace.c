/* Implementation of methods from Raytrace.h
 * CS430
 * Chance Nelson
 */

double dot_product(Vector a, Vector b) {
    /* Get the dot product of a and b
     * Args:
     *      a (3DVector): Vector A
     *      b (3DVector): Vector B
     * Returns (double): Dot product fo A and B
     */
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector vector_sub(Vector a, Vector b) {
        /* Get the cross product of a and b
     * Args:
     *      a (3DVector): Vector A
     *      b (3DVector): Vector B
     *      c (3DVector): Will contain cross product of A and B
     * Returns: Cross product will be stored in c
     */
    Vector c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

double* check_intersect(Ray v, Entity entity) {
    /* Check if a ray intersects a given entity
     * Args:
     *      v (Ray): Ray to check for intersects
     *      entity (Entity): Entity to check for intersect
     * Returns (double*): 4-long double array of the structure [x, y, z, t] if
     *                    there is an intersect, otherwise a NULL pointer.
     */
    if(entity.id == 1) {  // Check intersect with sphere
        /* Ray Sphere Intersect:
         * cx, cy, cz               = sphere coordinates
         * x0, y0, z0 -> x1, y1, z1 = ray
         * a    = x1^2 + y1^2 + z1^2
         * b    = 2 * (x1 * (x0 - cx) + y1 * (y0 - cy) + z1 * (z0 - cz))
         * c    = (x0 - cx)^2 + (y0 - cy)^2 + (z0 - cz)^2 - r^2
         * disc = b^2 - 4 * a * c
         * t    = (-b +- sqrt(disc)) / 2 * a
         */
        double a = pow(v.x1, 2) + pow(v.y1, 2) + pow(v.z1, 2);
        double b = 2 * (v.x1 * (v.x0 - entity.x) + v.y1 * (v.y0 - entity.y) + v.z1 * (v.z0 - entity.z));
        double c = pow(v.x0 - entity.x, 2) + pow(v.y0 - entity.y, 2) + pow(v.z0 - entity.z, 2) - pow(entity.attributes.radius, 2);

        double disc = pow(b, 2) - 4 * a * c;
        if(disc < 0) {
            return NULL;
        } else {
            double t = (-b - sqrt(disc)) / (2 * a);
            double t2 = (-b + sqrt(disc)) / (2 * a);
            if(t2 < t || t <= 0) t = t2;

            double *intersect = malloc(sizeof(double) * 4);
            intersect[0] = v.x0 + v.x1 * t;
            intersect[1] = v.y0 + v.y1 * t;
            intersect[2] = v.z0 + v.y1 * t;
            intersect[3] = t;
            return intersect;
        }

    } else if(entity.id == 2) {  // check intersect with plane
        /* Ray Plane Intersect:
         * x0, y0, z0 -> x1, y1, z1    = ray
         * 0 = A*x + B*y + C*z + D     = plane equation
         * <A, B, C>                   = plane normal
         * D                           = distance from plane to origin
         * D  = -1(Ax + By + Cz)
         * v0 = (A*x1 + B*y1 + C*z1)
         * vD = -(A*x0 + B*y0 + C*z0 + D) 
         */
        Vector coords;
        coords.x = entity.x;
        coords.y = entity.y;
        coords.z = entity.z;

        Vector eyes;
        eyes.x = v.x0;
        eyes.y = v.y0;
        eyes.z = v.z0;

        Vector screen;
        screen.x = v.x1;
        screen.y = v.y1;
        screen.z = v.z1;

        double t = -1 * dot_product(entity.attributes.normal, (vector_sub(eyes, coords))) / dot_product(entity.attributes.normal, screen); 
       
        if(t <= 0) return NULL;  // The plane is behind the ray, no intersect
        
        double *intersect = malloc(sizeof(double) * 4);
        intersect[0] = v.x0 + (v.x1 * t);
        intersect[1] = v.y0 + (v.y1 * t);
        intersect[2] = v.z0 + (v.y1 * t);
        intersect[3] = t;
        return intersect;


    } else {  // If the ID isn't for a shape, skip it
        return NULL;
    }
}

double angular_attenuation(double theta, Vector light, Vector intersect) {
    if(theta == 0) return 1.0;

    double attenuation = vector_dot(intersect, light);
    if(abs(attenuation) > theta) return 0;
    else return pow(attenuation, FRAD_FACTOR);
}

double radial_attenuation(Vector light, Vector intersect, a0, a1, a2) {
    double distance = sqrt(pow(light.x - intersect.x, 2) +
                           pow(light.y - intersect.y, 2) +
                           pow(ligt.z - intersect.z, 2));

    return 1 / (a2 * pow(distance, 2) + a1 * pow(distance, 2). a1);
}

Color shoot(Ray v, Entity *entities, Color background, int entitiesLen, int phong) {
    /* Calculate the color of a returning ray
     * r (Ray)            : ray to check
     * entities (Entity *): array of entities in the scene
     * entitiesLen (int)  : length of the array of entities
     * phong (int)        : flag for use of phong model (True = 1)
     */
    Color pixColor = background;
    double t = INFINITY;
    double *intersect;
    Entity intersectedEntity;

    // When not called to use phong shading, simply check for intersections
    if(phong != 1) {
        for(int i = 0; i < entitiesLen; i++) {
            intersect = check_intersect(v, entities[i]);
    
            if(intersect == NULL) continue;

            if(intersect[3] < t) {
                t = intersect[3];
                free(intersect);
                intersectedEntity = entities[i];
            } 
        }

        pixColor.r = intersectedEntity.color.r;
        pixColor.g = intersectedEntity.color.g;
        pixColor.b = intersectedEntity.color.b;
    }

    // Compute attenuation factors for lights and use the Illumination model
    if(phong == 1) {
        for(int i = 0; i < entitiesLen; i++) {
            intersect = check_intersect(v, entities[i]);
    
            if(intersect == NULL) continue;

            if(intersect[3] < t) {
                t = intersect[3];
                free(intersect);
                intersectedEntity = entities[i];
            } 
        }

        // Loop through the lights in the scene and calculate attenuation factors
        for(int i = 0; i < entitiesLen; i++) {
            if(entities[i].id != 3) continue;  // Skip non-light entities

            // build a ray between the intersect and the light
            Ray ray;
            ray.x0 = intersect[0];
            ray.y0 = intersect[1];
            ray.z0 = intersect[2];
            ray.x1 = entities[i].x;
            ray.y1 = entities[i].y;
            ray.z1 = entities[i].z;
            
            // check if the light is behind any objects
            double *rayIntersect;
            for(int j = 0; j < entitiesLen; j++) {
                rayIntersect = check_intersect(ray, entities[i]);
                if(rayIntersect != NULL) break;
            }

            if(rayIntersect != NULL) continue;

            // Declare fAng, fRad, theta, and a0-a2
            double fAng, fRad;
            double theta = entities[i].attributes.radials[0];
            double a0 = entities[i].attributes.radials[1];
            double a1 = entities[i].attributes.radials[2];
            double a2 = entities[i].attributes.radials[3];

            // Find the angular attenuation
            fAng = angular_attenuation(theta, entities[i].x, entities[i].y,
                                       entities[i].z, entities[i].direction,
                                       intersect[0], intersect[1], intersect[2]);

            // Find the radial attenuation
            fRad = radial_attenuation(entities[i].x, entities[i].y, entities[i].z,
                                      intersect[0], intersect[1], intersect[2],
                                      a0, a1, a2);

            pixColor.r += fRad * fAng * (fRad + fAng);
            pixColor.g += fRad * fAng * (fRad + fAng);
            pixColor.b += fRad * fAng * (fRad + fAng);
        }

        // Add ambient and emitted light
        pixColor += ambient;
        pixColor += emitted
    }

    return pixColor;
}
