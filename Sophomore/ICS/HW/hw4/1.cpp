#include <stdio.h>
int overflow(void);
int one = 1;
int overflow() {
char buf[4];
int val, i = 0;
while (scanf("%x", &val) != EOF) buf[i++] = (char)val;
return 15213;
}
int main() {
int val = overflow();
val += one;
if (val != 15213)
printf("Boom!\n");
else
printf("????\n");
return 0;
}
