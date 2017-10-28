/* CSV Parsing library for a raycaster
 * CS-430
 * Chance Nelson
 */

#ifndef H_CSV
#define H_CSV

#define BUFFER_SIZE 255

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Raytrace.h"
#include "CSV.c"

Entity* process_csv(FILE *file);  // Process a full CSV file
Entity  parse_line(char *line);   // Parse a line of a CSV file

#endif
