C/C++ Source Code | Sample Input | Sample Output

int TC, a, b;   //  |     3         | 3
scanf("%d", &TC); // number of test cases | 1 2 | 12
while (TC--) { // shortcut to repeat until 0 | 5 7 | 9
scanf("%d %d", &a, &b); // compute answer | 6 3 |--------------
printf("%d\n", a + b); } // on the fly |--------------|

int a, b; // | 1 2 | 3
// stop when both integers are 0 | 5 7 | 12
while (scanf("%d %d", &a, &b), (a || b)) // | 6 3 | 9
printf("%d\n", a + b); // | 0 0



int a, b; // | 1 2 | 3
// scanf returns the number of items read | 5 7 | 12
while (scanf("%d %d", &a, &b) == 2) // | 6 3 | 9
// or you can check for EOF, i.e. |--------------|--------------
// while (scanf("%d %d", &a, &b) != EOF) | |
printf("%d\n", a + b);


int a, b, c = 1; // | 1 2 | Case 1: 3
while (scanf("%d %d", &a, &b) != EOF) // | 5 7 |
// notice the two ‘\n’ | 6 3 | Case 2: 12
printf("Case %d: %d\n\n", c++, a + b);


int a, b, c = 1;
while (scanf("%d %d", &a, &b) != EOF) { // | 5 7 |
if (c > 1) printf("\n"); // 2nd/more cases | 6 3 | Case 2: 12
printf("Case %d: %d\n", c++, a + b); }