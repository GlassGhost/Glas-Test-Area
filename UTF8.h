/**********************************License(s)***********************************
Copyright © 2010, 2011 Roy Pfund.                           All rights reserved.
Use of this source code is governed by a  BSD-style License(the "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
******************************LIBRARY DESCRIPTION*******************************
reads or prints to the UTF8 encoding according to:
http://tools.ietf.org/html/rfc3629
***********************************Revisions************************************
(2011-Feb-17 00:00 UTC)-v0.01-1Mohs-GlassGhost File created. More emphasis is on
Documentation, than on the actual library at this time.
(2011-Mar-17 00:00 UTC)-v0.02-1Mohs-earlier overlong detection.
**********************************DEPENDENCIES**********************************
must have getbyte() and putbyte() functions available
*********************************System Headers********************************/
#include "stdata.h"
/************************************Macros************************************/
/*!***************************Structures and Unions*****************************
uint21_t the full length of a char
uint8_t an octet

Char. number range  |        UTF-8 octet sequence
   (hexadecimal)    |              (binary)
--------------------+---------------------------------------------
0000 0000-0000 007F | 0xxxxxxx
0000 0080-0000 07FF | 110xxxxx 10xxxxxx
0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

Acceptable bytes | how to get corresponding pertinent bits
-----------------+------------------------------------------------
0xxxxxxx < 0x80; | 0xxxxxxx = 0xxxxxxx;//1 byte sequence
10xxxxxx < 0xC0; | 00xxxxxx = 10xxxxxx bitand 0x3F;//continuing byte sequence
110xxxxx < 0xE0; | 000xxxxx = 110xxxxx bitand 0x1F;//2 byte sequence
1110xxxx < 0xF0; | 0000xxxx = 1110xxxx bitand 0x0F;//3 byte sequence
11110xxx < 0xF8; | 00000xxx = 11110xxx bitand 0x07;//4 byte sequence

***********************************Functions***********************************/
/*!Input(s)     :
PreCondition(s) : the next 1-4 bytes taken from the getbyte() function are a valid RFC3629 sequence. or getbyte() returns EOF.
Description     : calls getbyte() 1-4 times reading thechar from utf8
PostCondition(s):
Output(s)       : a UTF8 char, error, or eof.
*/uint21_t GetUTF8Char(){
    uint21_t thechar = 0; uint8_t CurrentOctet = getbyte();
    if (CurrentOctet < 0x80){//1 byte sequence
        return (uint21_t)CurrentOctet;
    }else if (CurrentOctet < 0xC2){ return error; //invalid byte sequence
    }else if (CurrentOctet < 0xE0){//2 byte sequence
        thechar = (uint21_t)CurrentOctet bitand 0x1F;
        ReadContinuingOctet(thechar, CurrentOctet);
        return thechar;
    }else if (CurrentOctet < 0xF0){//3 byte sequence
        thechar = (uint21_t)CurrentOctet bitand 0x0F;
        ReadContinuingOctet(thechar, CurrentOctet);
        if (thechar < 0x20)return error;//if thechar < (0x800 >> 6) overlong
        ReadContinuingOctet(thechar, CurrentOctet);
        return thechar;
    }else if (CurrentOctet < 0xF8){//4 byte sequence
        thechar = (uint21_t)CurrentOctet bitand 0x07;
        ReadContinuingOctet(thechar, CurrentOctet);
        ReadContinuingOctet(thechar, CurrentOctet);
        if (thechar < 0x40)return error;//if thechar < (0x10000 >> 6) overlong
        ReadContinuingOctet(thechar, CurrentOctet);
        if (thechar < 0x110000) return thechar; else return error;
    }else return error;
}/*___________________________________________________________________________*/

/*! appends the next 6 bits from the next octet to thechar or throws error.
*/inline void ReadContinuingOctet(uint21_t thechar, uint8_t CurrentOctet){
    CurrentOctet = getbyte();//getbyte() should be throwing error or eof
    if ((CurrentOctet bitand 0xC0)≠0x80) return error;//not a continuation byte
    thechar = (thechar << 6) bitor (uint21_t)(CurrentOctet bitand 0x3F);
}/*___________________________________________________________________________*/

/*!Input(s)     : a 21 bit unicode char < 0x110000
PreCondition(s) : memory not full
Description     : calls putbyte() 1-4 times writing thechar in utf8
PostCondition(s): thechar is the same as it's original state
Output(s)       : none
*/void PutUTF8Char(uint21_t thechar){
    if (thechar < 0x80){//1 byte sequence
        putbyte((uint8_t)thechar);
    }else if (thechar < 0x800){//2 byte sequence
        thechar = ror(thechar, 6); putbyte((uint8_t)thechar bitor 0xC0);
        writeContinuingOctet(thechar);
    }else if (thechar < 0x10000){//3 byte sequence
        thechar = ror(thechar, 12); putbyte((uint8_t)thechar bitor 0xE0);
        writeContinuingOctet(thechar);
        writeContinuingOctet(thechar);
    }else if (thechar < 0x110000){//4 byte sequence
        thechar = ror(thechar, 18);
        putbyte(((uint8_t)thechar bitand 0x07) bitor 0xF0);
        writeContinuingOctet(thechar);
        writeContinuingOctet(thechar);
        writeContinuingOctet(thechar);
    }else return error;
}/*___________________________________________________________________________*/

/*!Input(s)     :
PreCondition(s) : memory not full
Description     :
PostCondition(s):
Output(s)       :
*/inline void writeContinuingOctet(uint21_t thechar){
    thechar = rol(thechar, 6);
    putbyte(((uint8_t)thechar bitand 0x3F) bitor 0x80);
}/*___________________________________________________________________________*/
