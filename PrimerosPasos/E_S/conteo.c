#include <stdio.h>
// Conteo espacio
int main(){
    int c, nc;
    nc = 0;
    while ((c = getchar())!= EOF) {
        if (c == '\t'){
            ++nc;

        }
    printf("%d\n", nc);
    }

}
