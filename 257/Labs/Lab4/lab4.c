#include <stdio.h>

const int M = 3;
const int N = 4;

void print1DArray(int arr[N]){
    int i;
    for(i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
}

void print2DArray(int arr[M][N]){
    int i, j;
    for(i = 0; i < M; i++){
        for(j = 0; j < N; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    // Task 1
    int x = 5;
    printf("Variable x is located at %p\n", &x);
    int *p = NULL;
    p = &x;
    printf("Pointer value of p is %p\n", p);
    printf("Dereferenced value of p is %d, and x = %d\n\n", *p, x);

    // Task 2
    int a = 42;
    int b = 7;
    int c = 999;
    int *t = &a;
    int *u = NULL;
    printf("%d %d\n", a, *t);
    c = b;
    u = t;
    printf("%d %d\n", c, *u);
    a = 8;
    b = 8;
    printf("%d %d %d %d\n", b, c, *t, *u);
    *t = 123;
    printf("%d %d %d %d %d\n", a, b, c, *t, *u);

    t = &c;
    *t = 555;
    printf("%d %d %d %d %d\n", a, b, c, *t, *u);
    c = 100;
    printf("%d %d %d %d %d\n", a, b, c, *t, *u);
    int **v = &t;
    printf("%d\n", **v);

    printf("sizeof(char): %lu\n", sizeof(char));     // 1
    printf("sizeof(42): %lu\n", sizeof(42));         // 4
    printf("sizeof(float): %lu\n", sizeof(float));   // 4
    printf("sizeof(double): %lu\n", sizeof(double)); // 8
    printf("sizeof(NULL): %lu\n", sizeof(NULL));     // 8

    // Task 3
    printf("sizeof(int): %lu\n", sizeof(int));     // 4
    printf("sizeof(3.14): %lu\n\n", sizeof(3.14)); // 8

    int d[3] = {1, 2, 3};
    printf("sizeof(d) = %lu\n", sizeof(d));

    printf("The array starts at %p\n", d);
    printf("The first element is %d\n", *d);
    printf("The second element is %d\n", *(d + 1));
    printf("The third element is %d\n", *(d + 2));

    for (int i = 0; i < 3; i++)
    {
        printf("Element: %d\n", d[i]);
    }

    for (int *w = d; w < (d + 3); w++)
    {
        printf("Element: %d\n", *w);
    }

    int data[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
    printf("\naddress of first element of row 0 is %p\n", *(data + 0) + 0);
    printf("value of first element of row 0 is %d\n\n", **(data + 0) + 0);

    int column = sizeof(data[0]) / sizeof(int);
    int total = sizeof(data)/sizeof(int);
    int row = total/column; 

    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < column; j++){
            printf("%p ", &data[row][column]);
        }
        printf("\n");
    }

    int oneDArr[] = {1, 2, 3, 4};

    printf("\n");
    print1DArray(oneDArr);
    printf("\n\n");
    print2DArray(data);

    return 0;
}


