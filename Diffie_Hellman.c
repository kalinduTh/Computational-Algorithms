//Diffie - Hellman key exchange algorithm

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//To check if the number is a prime number
int isPrime(int number){
    if(number<2) return 0;
    int limit = (int)sqrt(number);
    for(int i = 2; i <= limit; i++){
        if(number % i == 0) return 0;
    }
    return 1;
}

//Generating the p(divisor) and g(base)
int generate_Public_Agreement(){

    int num = 0;
    do{
        num = rand() % 90 + 10;
    }while(!isPrime(num));

    return num;
}


//modular exponentiation - binary exponentiation
int key_cal(int base, int key, int divisor){
    int result = 1;
    base = base % divisor;
    while(key > 0){
        if(key % 2 == 1){
            result = (result * base) % divisor; 
        }
        key = key / 2;
        base = (base * base) % divisor;
    }

    return result;
}

int main(){
    srand(time(NULL));
    //clock_t start, end;
    //double cpu_time_used;

    //initializing base and divisor
    int p = generate_Public_Agreement();
    int g = generate_Public_Agreement();

    //Private Keys
    int a = rand() % (p+2) + 2;     //Alice's Private key
    int b = rand() % (p+2) + 2;     //Bob's private key

    //Public keys
    int A = key_cal(g, a, p);   //Alice's public key A = g^b (mod p)
    int B = key_cal(g, b, p);   //Bob's public key B = g^a (mod p)

    //Shared secret keys
    int Sa = key_cal(B, a, p);  //Alice Computes the Secret key Sa = B^a (mod p)
    int Sb = key_cal(A, b, p);  //Bob Computes the Secret key Sb = A^b (mod p)

    //Print.....
    printf("\nPuBlic Agreement;\n Public divisor: %d\n Public base: %d\n\n", p, g);
    printf("Private keys;\n Alice's Private key: %d\n Bob's Private key: %d\n\n", a, b);
    printf("Public keys;\n Alice's Public key: %d\n Bob's Public key: %d\n\n", A, B);
    printf("Shared Secret key;\n Alice's Shared Secret key: %d\n Bob's Shared Secret key: %d\n\n", Sa, Sb);

    if(Sa != Sb){
        printf("\nERROR!!! Shared Sectre keys do not match! :`(\n\n");
        return 1;
    }
    
    printf("\nSuccessfully calculated the Shared Sectre key! :D\n\n");  
    return 0;
}
