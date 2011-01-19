/**********************************License(s)***********************************
Copyright © 2010, 2011 Roy Pfund.                           All rights reserved.
Use of this source code is governed by a  BSD-style License(the "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
*************************************Inputs*************************************
accepts a command line arg "-of_test"
*********************************Pre-Conditions*********************************
none
******************************PROGRAM DESCRIPTION*******************************
A generic C++ template with command line arguments.                 tab=4 spaces

compile with: any ISO/IEC-14882 or C++2003 compliant compiler
*********************************Post-Conditions********************************
none
*************************************Output*************************************
prints my own version of "Hello World"
***********************************Revisions************************************
(UTC Year-Month-Day Hour:Minute:second)-v0.01-File created
*********************************System Headers********************************/
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
//#include <numeric_limits>
/********************************Local Headers*********************************/
#include "stdmath_t.h"
/************************************Macros************************************/
#define of_test_arg_bool ((std::bitset<sizeof(*Flags_Ptr)*8>)*Flags_Ptr)[0]
/*****************************Structures and Unions****************************/
/**********************************Variables***********************************/
uint16_t* Flags_Ptr = new uint16_t(0);
/*****************************Feature Test Switches****************************/
/*hopefully someday I will be able to define this with 1*/
//#define _POSIX_SOURCE 1
of_test_arg_bool = 1;
/*****************************File scope variables*****************************/
/******************************External variables******************************/
/**********************************Functions***********************************/

void of_test(){
/*!Input(s)     :
PreCondition(s) :
Description     :tests ofstream
PostCondition(s):
Output(s)       :a file in the directory of the executable
*/  std::ofstream txtout("./txtout.txt", std::ios::app);
    txtout << "ALL YOUR BASE ARE BELONG TO US!\n";
    txtout.close();
}//_____________________________________________________________________________

/******************************External Functions******************************/
/***************************Signal catching functions**************************/

int main(int argc, char *argv[]){/*MAIN logic**********************************/
    if(argv[0] == "-"){/*Command line args------------------------------------*/
        std::string *arg = new std::string(argv[--argc]);
        //insert new aruments after this line.
        //a standard boolean command line arg
        if((*arg).find("-of_test") != -1) of_test_arg_bool = 1;
        /*add here your unique code to input any data into the program before
        the object at address "arg" is deleted when it falls out of scope*/
    }/*End of Command line args-----------------------------------------------*/
    //a example action for a command line argument boolean flag
    if (of_test_arg_bool == 1) of_test();
    std::cout << "Good Morning, Dave.\n";
/*system("pause");/*keeps Microsoft command prompt from going bananas*/return 0;
}/**********************************End MAIN***********************************/
