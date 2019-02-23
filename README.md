# karatsuba-
This is Karatsuba Multiplication of 64 digit multiplication


Implement the Karatsuba's algorithm for multiplying two large numbers. 
For e.g., for the following input numbers A and B of 64 digits each:
A: 3183659832789056157123231193065733348656398779138482079257996978
B: 9757530286603594664582342963198810930630352535413615256241340136
Our program must output the following 128 digit number:
31064657240682551391401291435398144167567639750649905625519442196152715900036240937706209178221640277395863167944384137758109008



ECS202: Data Structures and Algorithms
F
Due Feb 15, 11:59 PM
Assignment 2

Pawan Kumar Aurora
Jan 31 (Edited Feb 11)
Implement the Karatsuba's algorithm for multiplying two large numbers. 
For e.g., for the following input numbers A and B of 64 digits each:
A: 3183659832789056157123231193065733348656398779138482079257996978
B: 9757530286603594664582342963198810930630352535413615256241340136
Your program must output the following 128 digit number:
31064657240682551391401291435398144167567639750649905625519442196152715900036240937706209178221640277395863167944384137758109008

A write-up is enclosed. The write-up is also available at the link provided below.

Instructions:
1. You must implement using the C programming language.
2. You must submit a .c file containing your code.
3. The code must be well commented.
4. You must also submit a text file explaining your implementation in detail.
5. Your program must adhere to the following user interface:
Enter the number of digits:4
Enter the first 4-digit number:1234
Enter the second 4-digit number:5678
The product of the two numbers is:7006652

Link of Algorithm
https://courses.csail.mit.edu/6.006/spring11/exams/notes3-karatsuba


KARATSUBA ALGORITHM
An algorithm for multiplying two n-digit numbers that needs much fewer basic operations. It is named
after the Russian mathematician Anatolii Alexeevitch Karatsuba, who came up with its main idea
(published 1962 with Yu. Ofman1 ). It uses divide and conquer approach to multiply.


Description: In this assignment I have used Karatsuba Algorithm to compute the product of two numbers using three multiplication of no. half the size of the numbers  input. 


here's the pseudo code of algorithm from wikipedia:-
||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
procedure karatsuba(num1, num2)
  if (num1 < 10) or (num2 < 10)
    return num1*num2
  /* calculates the size of the numbers */
  m = min(size_base10(num1), size_base10(num2))
  m2 = floor(m/2)
  /*m2 = ceil(m/2) will also work */
  /* split the digit sequences in the middle */
  high1, low1 = split_at(num1, m2)
  high2, low2 = split_at(num2, m2)
  /* 3 calls made to numbers approximately half the size */
  z0 = karatsuba(low1, low2)
  z1 = karatsuba((low1 + high1), (low2 + high2))
  z2 = karatsuba(high1, high2)
  return (z2 * 10 ^ (m2 * 2)) + ((z1 - z2 - z0) * 10 ^ m2) + z0

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

pseudo code for main function from attched .c file:-
main()
1. int a[MAX], a[MAX],b[MAX], res[3 * MAX], size_of_a, size_of_b, d,i;
2. input 2 integers;

// let d be the smallest power of 2 greater than size_of_a and size_of_b and zero out the rest of a and b.
3. for(d= 1; d<i; d++);
4. for(i = size_of_a; i < d; i++) a[i] = 0;
5. for(i = size_of_b; i < d; i++) b[i] = 0;
6. multi(a, b, res, d);
 // compute product w/o regard to carry
7. carry(res, 2 * d);
 // now do any carrying when simple multiplication is used


--------------------------------------------------------------

pseudo code for multi function:--
multi()

1. int i, af, as, bf,bs,asum, bsum, x1, x2,x3;]
2. if(d <= limt) SimpleM(a, b, ret, d);
 //SimpleM is definded below this function

3.for (i; i <d/2; i++)
// compute asum and bsum
  4. asum[i] = as[i] + af[i];
  5.  bsum[i] = bs[i] + bf[i];

6. multi(af, bf, x1, d/2); //recurrence for first half elements
 7.   multi(as, bs, x2, d/2);
 8.   multi(asum, bsum, x3, d/2);
//do recursive calls (I have to be careful about the order,since the scratch space for the recursion on x1 includes the space used for x2 and x3)

9. for(i = 0; i < d; i++) x3[i] = x3[i] - x1[i] - x2[i];
  10.   for(i = 0; i < d; i++) ret[i + d/2] += x3[i]


--------------------------------------------------------------
pseudo code for SimpleM function:--

SimpleM(a, b ,ret, d) ////function multiplying number in usual way
1. int i, j;
2. for(i = 0; i < 2 * d; i++)ret[i] = 0;
3. for(i = 0; i < d; i++) 
4.   for(j = 0; j < d; j++)ret[i + j] += a[i] * b[j];


--------------------------------------------------------------
pseudo code for carry function:--
carry(a, d)
1. int c, i;
2. c =0;
3. for(i = 0; i < d; i++) 
4.	a[i] += c;
5.  if(a[i] < 0) 
6.	 c = -(-(a[i] + 1) / 10 + 1);
        
7.		else 
8.		c = a[i] / 10;
  
 9.       a[i] -= c * 10;
//condition when number of digits are greater than max_digit


--------------------------------------------------------------
pseudo code for getnum function:--
getnum(a, size_of_a)
  1. int c, i;
2. size_of_a = 0

3 while(1) {
 4. c = getchar();
  5. if(c == '\n' || c == EOF) break;
 6. if(*size_of_a >= MAX) {
 7.     fprintf(stderr, "using only first %d digits\n", MAX);
  8.    while(c != '\n' && c != EOF) c = getchar();
 9.  a[*size_of_a] = c - '0';
10.   ++(*size_of_a);
// reverse the number so that the 1's digit is first
 11.   for(i = 0; i * 2 < *size_of_a - 1; i++) 
 12.       c = a[i], a[i] = a[*size_of_a - i - 1];
13.	a[*size_of_a - i - 1] = c;
    


--------------------------------------------------------------
pseudo code for NumPrint function:--
NumPrint(a, d) ////funnction to print the numbers
1. int i;
2. for(i = d - 1; i > 0; i--) 
  3. if(a[i] != 0) break;
4.  for(; i >= 0; i--) 
5. printf("%d", a[i]);


