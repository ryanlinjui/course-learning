#pragma once

// Setup three points for a triangle.
// Success: return 1; Fail: return 0
int set_1_point( double x, double y);
int set_2_point( double x, double y);
int set_3_point( double x, double y);

// Check if the current setting is a valid triangle.
// Yes: return 1; No: return 0
int check( void );

// Return the perimeter of the triangle.
// If the current setting is not a triangle , return < 0
double get_perimeter( void );

// Return the area of the triangle.
// If the current setting is not a triangle , return < 0
double get_area( void );

// Get the degrees (0-360) of three angles
// If the current setting is not a triangle , return < 0
double get_1_degree( void );
double get_2_degree( void );
double get_3_degree( void );


// Inscribed circle and Circumscribed circle of the triangle.
// If the current setting is not a triangle , the area functions return < 0
// and the center functions return 0.
double get_inscribed_center_x( void );
double get_inscribed_center_y( void );
double get_inscribed_center_area( void );
double get_circumscribed_center_x( void );
double get_circumscribed_center_y( void );
double get_circumscribed_center_area( void );