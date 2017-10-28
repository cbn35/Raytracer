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


