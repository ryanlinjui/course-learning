#include <math.h>
#include <stdio.h>
#define _USE_MATH_DEFINES

static double x_1=0,y_1=0,x_2=0,y_2=0,x_3=0,y_3=0;
static int check_set1=0,check_set2=0,check_set3=0;

int is_triangle(){
    if( 
        !(check_set1&check_set2&check_set3) || (
        (((x_1==x_2)&&(x_2==x_3))||((y_1==y_2)&&(y_2==y_3))) || // 3 points on same line. 
        (((x_1==x_2)&&(y_1==y_2))||((x_2==x_3)&&(y_2==y_3))||((x_1==x_3)&&(y_1==y_3))) // Any 2 points is same coordinate. 
        )
    ){
        return 0;
    }
    else{
        return 1;
    }
}

int set_1_point( double x, double y){
    double xx = x_1;
    double yy = y_1;
    x_1=x; y_1=y;    
    if(is_triangle()||check_set1==0){
        check_set1|=1;
        return 1;
    }
    else{     
        x_1 = xx;
        y_1 = yy;
        return 0;
    }

}
int set_2_point( double x, double y){
    double xx = x_2;
    double yy = y_2;
    x_2=x;y_2=y;
    if(is_triangle()||check_set2==0){
        check_set2|=1;
        return 1;
    }
    else{
        x_2 = xx;
        y_2 = yy;
        return 0;
    }
}
int set_3_point( double x, double y){
    double xx = x_3;
    double yy = y_3;
    x_3=x;y_3=y;
    if(is_triangle()||check_set3==0){
        check_set3|=1;
        return 1;
    }
    else{
        x_3=xx;
        y_3=yy;
        return 0;
    }
}

// Check if the current setting is a valid triangle.
// Yes: return 1; No: return 0
int check( void ){ 
    printf("%lf %lf %lf %lf %lf %lf\n",x_1,y_1,x_2,y_2,x_3,y_3);
    if(is_triangle()){
        return 1;
    }
    else{
        return 0;
    }
}

// Return the perimeter of the triangle.
// If the current setting is not a triangle , return < 0
double get_perimeter( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return s1+s2+s3;
    }
    else{
        return -1;
    }
}

// Return the area of the triangle.
// If the current setting is not a triangle , return < 0
double get_area( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        double s = (s1+s2+s3)/2;
        return sqrt(s*(s-s1)*(s-s2)*(s-s3));
    }
    else{
        return -1;
    }
}

// Get the degrees (0-360) of three angles
// If the current setting is not a triangle , return < 0
double get_1_degree( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return (acos((s1*s1+s2*s2-s3*s3)/(2*s1*s2))/M_PI)*180;
    }
    else{
        return -1;
    }
}
double get_2_degree( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return (acos((s3*s3+s1*s1-s2*s2)/(2*s3*s1))/M_PI)*180;
    }
    else{
        return -1;
    }
}
double get_3_degree( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return (acos((s2*s2+s3*s3-s1*s1)/(2*s2*s3))/M_PI)*180;
    }
    else{
        return -1;
    }
}


// Inscribed circle and Circumscribed circle of the triangle.
// If the current setting is not a triangle , the area functions return < 0
// and the center functions return 0.
double get_inscribed_center_x( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return (s1*x_1+s2*x_2+s3*x_3)/(s1+s2+s3);
    }
    else{
        return -1;
    }
}
double get_inscribed_center_y( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        return (s1*y_1+s2*y_2+s3*y_3)/(s1+s2+s3);
    }
    else{
        return -1;
    }
}
double get_inscribed_center_area( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        double r = (s1+s2-s3)/2;
        return r*(r+s3);
    }
    else{
        return -1;
    }
}
double get_circumscribed_center_x( void ){
    if(is_triangle()){
        double a1 = 2*(x_2-x_1);
        double b1 = 2*(y_2-y_1);
        double c1 = (x_2*x_2)+(y_2*y_2)-(x_1*x_1)-(y_1*y_1);
        double a2 = 2*(x_3-x_2);
        double b2 = 2*(y_3-y_2);
        double c2 = (x_3*x_3)+(y_3*y_3)-(x_2*x_2)-(y_2*y_2);
        return ((c1*b2)-(c2*b1))/((c1*b2)-(c2*b1));
    }
    else{
        return -1;
    }
}
double get_circumscribed_center_y( void ){
    if(is_triangle()){
        double a1 = 2*(x_2-x_1);
        double b1 = 2*(y_2-y_1);
        double c1 = (x_2*x_2)+(y_2*y_2)-(x_1*x_1)-(y_1*y_1);
        double a2 = 2*(x_3-x_2);
        double b2 = 2*(y_3-y_2);
        double c2 = (x_3*x_3)+(y_3*y_3)-(x_2*x_2)-(y_2*y_2);
        return ((a1*c2)-(a2*c1))/((a1*b2)-(a2*b1));
    }
    else{
        return -1;
    }
}
double get_circumscribed_center_area( void ){
    if(is_triangle()){
        double s1 = sqrt(pow(x_1-x_2,2)+pow(y_1-y_2,2));
        double s2 = sqrt(pow(x_1-x_3,2)+pow(y_1-y_3,2));
        double s3 = sqrt(pow(x_2-x_3,2)+pow(y_2-y_3,2));
        double s1_degree = acos((s1*s1+s2*s2-s3*s3)/(2*s1*s2));
        double r = (s1/sin(s1_degree))/2;
        return (s1*s2*s3)/(4*r);
    }
    else{
        return -1;
    }
}