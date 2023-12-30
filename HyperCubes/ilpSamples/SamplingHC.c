#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef exp
#define exp 2
#endif
#define n 1 << exp


void bfs(unsigned int i, unsigned int* v) {

    unsigned int queue[n];
    v[i] = 0;
    unsigned int size = 1;
    unsigned int last = 0;
    queue[last] = i;

    while(last < n) {

        unsigned int node = queue[last];
        ++last;

        for (unsigned int k = 0; k < exp; ++k) {

            unsigned int j = node ^ (1 << k);

            if (v[j] == n) {
                queue[size] = j;
                ++size;
                v[j] = v[node] + 1;
            }
        } 
    }

}




int main(int argc, char** argv) {

    unsigned int *v = (unsigned int *) malloc((1 << (exp + exp)) * sizeof(unsigned int));

    #pragma omp parallel
    #pragma omp single
    #pragma omp taskloop nogroup
    for (unsigned int i = 0; i < n; ++i) {
        unsigned int col = i << exp;
        for (unsigned int j = 0; j < n; ++j) v[col + j] = n;
        bfs(i,&v[col]);
    }

    printf("Minimize\n");

    printf("x0");
    for (unsigned int i = 1; i < n; ++i) printf(" + x%u", i);
    printf("\n");

    printf("Subject To\n");
    for (unsigned int i = 0; i < n; ++i) {

        for (unsigned int j = i + 1; j < n; ++j) {

            int b = 0;
            int col_i = i << exp;
            int col_j = j << exp;

            for (unsigned int k = 0; k < n; ++k) {

                if (v[col_i + k] != v[col_j + k]) {

                    if (!b) {
                        printf("x%u", k);
                        b = 1;
                    }
                    else printf(" + x%u",k);
                }
            }

            printf(" >= 1 \n");
        }
    }



    printf("Binary\n");
    printf("x0");
    for (unsigned int i = 1; i < n; ++i) printf(" x%u", i);
    printf("\n");
    printf("End\n");

    free(v);
}
