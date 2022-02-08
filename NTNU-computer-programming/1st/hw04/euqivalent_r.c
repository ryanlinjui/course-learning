#include <stdint.h>

double calculate(double r_value,int n_value){
    double r=r_value;
    r_value *= 2;
    for(int i=1;i<n_value;i++){
        r_value = (r_value*r)/(r_value + r)+r;
    }
    return r_value;
}