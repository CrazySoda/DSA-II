#include <stdio.h>

int main()
{   int n;
    printf("enter the nth term:");
    scanf("%d", &n);
    float term, degree;
    printf("enter the angle in degree:");
    scanf("%f", &degree);
    float x = degree * 3.1416/180;
    term = x;
    float sum = x;
    for(int i = 2; i <= 2*n; i = i+2){
        term = term * (-1)*x*x/(i*(i+1));
        sum = sum + term;

    }
    printf("the value of sin%.1f is %f\n", degree, sum);
    return 0;
}