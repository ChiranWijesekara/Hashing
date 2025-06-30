#include <stdio.h>
#include <math.h>

double product(int k){
    double product = 1.0;
    for(int i=0;i<k;i++){
        product *= (365.0 - i) / 365.0;
    }
    return product;
}

void calculate(int k){
    double noSharedBirthday = product(k);
    double atLeastOneShared = 1.0 - noSharedBirthday;
    printf("Probability of at least one shared birthday: %.4lf\n",atLeastOneShared);
    return;
}

int main(){
    calculate(23);
    return 0;
    
}
