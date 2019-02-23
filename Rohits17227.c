/*
Assignment 2- ECS

Name: Rohit Saini
Roll no. 17227


with help of: Keshav bihani 17123


*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX 256  //number of elements in array
#define limt 4  //when number of digits afe less than 'cutoff' program uses usual multipliaction method
int main() 
{

    int a[MAX]; // first multiplicand
    int b[MAX]; // second multiplicand
    int res[3 * MAX]; // result
    int size_of_a; // length of a
    int size_of_b; // length of b
    int d; // maximum length
    int i; // counter

	printf("Enter the first number:");
	getNum(a, &size_of_a);
    printf("\nEnter the second number:");
    getNum(b, &size_of_b);



    // let d be the smallest power of 2 greater than size_of_a and size_of_b,
    // and zero out the rest of a and b.
    i = (size_of_a > size_of_b) ? size_of_a : size_of_b;
    for(d = 1; d < i; d ++);  
    for(i = size_of_a; i < d; i++) a[i] = 0;
    for(i = size_of_b; i < d; i++) b[i] = 0;

    {
    multi(a, b, res, d); // compute product w/o regard to carry
    carry(res, 2 * d); // now do any carrying when simple multiplication is used
    }

    printf("\nThe product of the two numbers is:");
    NumPrint(res, 2 * d);
    
}


void multi(int *a, int *b, int *ret, int d) 
{

    int i;
    int *af = &a[0]; // 1st half of a
    int *as = &a[d/2]; // 2nd half of a
    int *bf = &b[0]; // 1st half of b
    int *bs = &b[d/2]; // 2nd half of b
    int *asum = &ret[d * 5]; // sum of a's halves
    int *bsum = &ret[d * 5 + d/2]; // sum of b's halves
    int *x1 = &ret[d * 0]; // af*bf's location
    int *x2 = &ret[d * 1]; // as*bs's location
    int *x3 = &ret[d * 2]; // asum*bsum's location
    
    if(d <= limt) 
	{
        SimpleM(a, b, ret, d);
        return;
    }

    // compute asum and bsum
    for(i = 0; i < d / 2; i++) 
	{
        asum[i] = as[i] + af[i];
        bsum[i] = bs[i] + bf[i];
    }

    // do recursive calls (I have to be careful about the order,
    // since the scratch space for the recursion on x1 includes
    // the space used for x2 and x3)
    multi(af, bf, x1, d/2);
    multi(as, bs, x2, d/2);
    multi(asum, bsum, x3, d/2);

    // combine recursive steps
    for(i = 0; i < d; i++) x3[i] = x3[i] - x1[i] - x2[i];
    for(i = 0; i < d; i++) ret[i + d/2] += x3[i];
}

void carry(int *a, int d);
void SimpleM(int *a, int *b, int *ret, int d);
void getNum(int *a, int *d_a);
void NumPrint(int *a, int d);

void SimpleM(int *a, int *b, int *ret, int d)   //function multiplying number in usual way
{
    int i, j;	

    for(i = 0; i < 2 * d; i++) 
	ret[i] = 0;
	
    for(i = 0; i < d; i++) 
	{
    for(j = 0; j < d; j++) 
	ret[i + j] += a[i] * b[j];
    }
}

void carry(int *a, int d)
{
    int c;
    int i;

    c = 0;
    for(i = 0; i < d; i++) 
	{
        a[i] += c;
        if(a[i] < 0) 
		{
            c = -(-(a[i] + 1) / 10 + 1);
        }
		else 
		{
            c = a[i] / 10;
        }
        a[i] -= c * 10;
    }
   				//condition when number of digits are greater than max_digit.
}

void getNum(int *a, int *size_of_a) //simple function to take input in the array from the user and returing the size of the array if needed.
{				
    int c;
    int i;

    *size_of_a = 0;
    while(1) {
        c = getchar();
        if(c == '\n' || c == EOF) break;
        if(*size_of_a >= MAX) {
            fprintf(stderr, "using only first %d digits\n", MAX);
            while(c != '\n' && c != EOF) c = getchar();
        }
        a[*size_of_a] = c - '0';
        ++(*size_of_a);
    }
    // reverse the number so that the 1's digit is first
    for(i = 0; i * 2 < *size_of_a - 1; i++) {
        c = a[i], a[i] = a[*size_of_a - i - 1], a[*size_of_a - i - 1] = c;
    }
}

void NumPrint(int *a, int d) //funnction to print the numbers
{					
    int i;
    for(i = d - 1; i > 0; i--) if(a[i] != 0) break;
    for(; i >= 0; i--) printf("%d", a[i]);
}
