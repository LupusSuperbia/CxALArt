#include <stdio.h>
/* imprime la tabla Fahrenheit-Celsius
para fahr = 0, 20, ..., 300; versión de punto flotante */
#define LOWER 0 /* limite inferior de la tabla */
#define UPPER 300 /* limite superior de la tabla */
#define STEP 20 /* tamaño de incremento */
int main( ){
    int fahr;
    for(fahr = LOWER ; fahr <= UPPER; fahr = fahr + STEP){
        printf("%3d %6.lf \n", fahr, (5.0/9.0)*(fahr-32));
    }

}
