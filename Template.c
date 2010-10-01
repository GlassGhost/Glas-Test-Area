/* Feature Test Switches */
#define _POSIX_SOURCE 0
/* System Headers */
#include <stdio.h>
#include "typenums.h"
/* Local Headers */
/* Macros */
/* File scope variables */
/* External variables */
/* External Functions */
/* Structures and unions */
/* Signal catching functions */
/* Functions */
void end(UInt16 rval){printf("\nPress enter to exit. . .\n");
	char end = '0'; scanf(&end); return rval; }
/* Main */
int main(){ SInt32 fahr, celsius, lower, upper, step;
	lower = -40; upper = 300; step = 10; /* step size */
	fahr = lower;
	while (fahr <= upper){
		celsius = 5 * (fahr-32) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + step; 
	}
end(0);}
