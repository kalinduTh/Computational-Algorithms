#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//To check whether the generated number is a prime number
int isPrime(int number){
    if(number<2) return 0;

    int limit = (int)sqrt(number);
    for(int i = 2; i <= limit; i++){
        if(number % i == 0) return 0;
    }
    return 1;
}

//Generating the p(modulus) and g(base)
int generate_Public_Agreement(){

    int num = 0;

    do{
        num = rand() % 90 + 10;
    }while(!isPrime(num));

    return num;
}


int Alice(int base, int modulus){
    //generating Alice's private key
    int a = rand() % 8 + 2;
    printf("Alice's Private key: %d\n", a);

    //generating Alice's Public Key
    int AP_Key = (int) pow(base, a) % modulus;
    printf("Alice's Public Key: %d\n", AP_Key);

    int bp_key = Bob(AP_Key);

    return AP_Key;
}

int Bob(int ap_key){
    //Generating Bob's private key
    int b = rand() % 8 + 2;
    printf("Bob's Private key: %d\n", b);

    int base = generate_Public_Agreement();
    int modulus = generate_Public_Agreement();
    //Generating public key
    int BP_Key = (int) pow(base, b) % modulus;
    printf("Bob's Public Key: %d\n", BP_Key);

    int ap_key = Alice(base, modulus);

    return BP_Key;
}


int main(){

    clock_t start, end;
    double cpu_time_used;

    srand(time(NULL));

    start = clock();
    int p = generate_Public_Agreement();
    end = clock();
    int g = generate_Public_Agreement();

    printf("\nP: %d\nG: %d\n\n", p, g);



    printf("\n");
    
    //printf("generatePrime() took %f seconds\n", ((double)(end - start)));
    
    return 0;
}