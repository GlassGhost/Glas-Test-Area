/**********************************License(s)***********************************
Copyright 2010 Roy Pfund.                                   All rights reserved.
Use of this source code is governed by a BSD-style License(the  "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
*************************************Inputs*************************************
accepts a command line arg "-kill"
*********************************Pre-Conditions*********************************
none
******************************PROGRAM DESCRIPTION*******************************
A generic "main class" C++ template with command line arguments.	tab=4 spaces
It uses a single bit to store booleans through the use of macros and typecasting
with the standard library "bitset"

compile with: any ISO/IEC-14882 or C++2003 compliant compiler
*********************************Post-Conditions********************************
none
*************************************Output*************************************
prints my own version of "Hello World"
***********************************Revisions************************************
(insert date & time)-v0.01-File created
*********************************System Headers********************************/
#include <stdio.h>
#include "typenums.h"
/* Feature Test Switches */
#define _POSIX_SOURCE 0
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
