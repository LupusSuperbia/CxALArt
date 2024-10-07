#include <stdio.h>

int main() {
    // Usamos int por una sutil pero importante razón
    // El problema es destinguir el fin de la entrada
    // de los datos válidos, la solucion es que getchar
    // devuelve un valor distintivo cuando hay mas en la entrada
    // un valor que no puede ser confundido con ningun
    // otro caracter, este valor se llama EOF
    // por lo tanto no se usa char porque necesitamos que c
    // pueda mantener a EOF a demás de cualquier otro carácter
    // por lo tanto por esto se emplea int
    // EOF es un entero definido en stdio.h
    //
//     int c;
//     c = getchar();
//     while (c != EOF){
//         putchar(c);
//         c = getchar();
//     }
// }
//     int c;
//     // long son por lo menos de 32 bits
//     long nc;
//     nc = 0;
//     while (getchar() != EOF){
//         ++nc;
//         printf("%ld\n", nc);
//     }
// }
    // Un aspecto agradable acerca de los while y del for
    // es que hacen prueba al inicio del ciclo, antes de proceder
    // al cuerpo, los programas deben actuar en forma inteligente
    // cuando se les da una entrada de longitud cero
    //
    double nc;
    for(nc = 0; getchar() != EOF; ++nc)
    printf("%.0f\n", nc);

}
