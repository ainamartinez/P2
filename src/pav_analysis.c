#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    float pot = 1e-12; //Inicializamos esto porqué sino haremos el log de 0 y error
    for (unsigned int i = 0; i < N; i++)
    {
        pot += x[i]*x[i];
    }
    
    return 10*log10(pot/N);
}

float compute_am(const float *x, unsigned int N) {
    double am = 0;
    for (unsigned int i=0; i < N; i++) {
        am += fabs(x[i]);
    }
    return am/N;
}

int signo(float num) {
    if(num > 0) {
        return 1;
    } 

    if(num < 0) {
        return -1;
    }

    return 0;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float zcr = 0;
    for (unsigned int i=1; i < N; i++) {
        // Si la actual es 0, no hay cambio de signo --> entonces qué???
        // Tenemos que considerar cada vez que pasa de algo a 0 o de 0 a otra cosa
        zcr += ((signo((x[i])) != signo(x[i-1]))&&((signo(x[i]) && signo(x[i-1]))!=0)); //Comparem el resultat de la funció signo i descartem quan son 0.
    }

    /* OPCIÓ AMB IF
    for(unsigned int i = 1; i < N; i++) {
        if((x[i]<0 && x[i-1]>0)||(x[i]>0 && x[i-1]<0)){
            zcr ++;
        }
    }*/
    return (fm/2)*(zcr/(N-1));
}