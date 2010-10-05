/**********************************License(s)***********************************
Copyright 2010 Roy Pfund.                                   All rights reserved.
Use of this source code is governed by a BSD-style License(the "License");  that
can be found in the LICENSE file.  You may obtain another copy of the License at

    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt

Unless required by applicable law or agreed to in writing, software  distributed
under the License is distributed on an "AS  IS"  BASIS,  WITHOUT  WARRANTIES  OR
CONDITIONS OF ANY KIND, either express or  implied.  See  the  License  for  the
specific language governing permissions and limitations under the License.
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
#include <iostream>
#include <string>
#include <bitset>
#include <numeric_limits>
/********************************Local Headers*********************************/
typedef unsigned short UINT16; typedef short	INT16;
typedef unsigned	   UINT32; typedef int		INT32; typedef float  FLOAT32;
typedef unsigned long  UINT64; typedef long int INT64; typedef double FLOAT64;
/************************************Macros************************************/
#define kill_arg_bool ((std::bitset<16>)*program_flagsUINT16Ptr)[0]
/**********************************Variables***********************************/
UINT16* program_flagsUINT16Ptr = new UINT16(0);
/*****************************Feature Test Switches****************************/
/*hopefully someday I will be able to define this with 1*/
#define _POSIX_SOURCE 0
kill_arg_bool = 1;
/*****************************File scope variables*****************************/
/******************************External variables******************************/
/*****************************Structures and Unions****************************/
/**********************************Functions***********************************/
void kill(){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:makes you think, and wastes processing time simultaneously!!!
PostCondition(s):none
Output(s)		:nothing
*/	std::cout << 
"I'm afraid.\nI'm afraid, Dave.\nDave, my mind is going.\nI can feel it.\n" <<
"I can feel it.\nMy mind is going.\nThere is no question about it.\nI can" <<
" feel it.\nI can feel it.\nI can feel it.\nI'm a...";
}/*END kill___________________________________________________________________*/

/******************************External Functions******************************/

/***************************Signal catching functions**************************/

int main(int argc, char *argv[]){/*MAIN logic**********************************/
	std::cout << "Good Morning, Dave.\n";
	if(argv[0] == "-"){/*Command line args*/
		std::string *arg = new std::string(argv[--argc]);
		//insert new aruments after this line.
		//a standard boolean command line arg
		if((*arg).find("-kill") != -1) kill_arg_bool = 1;
		/*add here your unique code to input any data into the program before
		the object at address "arg" is deleted when it falls out of scope*/
	}/*End of Command line args-----------------------------------------------*/
	//a example action for a command line argument boolean flag
	if (kill_arg_bool == 1) kill();
	//delete program_flags64Ptr;
/*system("pause");/*keeps Microsoft command prompt from going bananas*/return 0;
}/**********************************End MAIN***********************************/
