/**********************************License(s)***********************************
Copyright © 2010 Roy Pfund.                                 All rights reserved.
Use of this source code is governed by a  BSD-style License(the "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
******************************LIBRARY DESCRIPTION*******************************
This header makes sure that the following static types are provided:
intN_t = N bit two’s complement signed integer type, (should be multiple of 8)
uintN_t = N bit unsigned integer type, (should be multiple of 8)
floatN_t = N bit IEE754 binary float, (MUST be multiple of 32 OR equal to 16)
decimalN_t = N bit IEE754 decimal float, (MUST be multiple of 32)

And SHALL depecrate the following incomplete chart:
    bits    unsigned-integer    signed-integer      IEE754-binary-float
    8       ??unsigned char??   ??signed char??     ??
    16      unsigned short      short               ??half
    32      unsigned            int                 float
    64      unsigned long       long                double
    128     ??                  ??                  ??Quad
**********************************DEPENDENCIES**********************************
stdint.h
***********************************Revisions************************************
(UTC 2010)-v0.01-1Mohs-GlassGhost File created more emphasis  on  Documentation,
than on the actual library at this time.
*********************************System Headers********************************/
#include <stdint.h>
/********************************Local Headers*********************************/
/************************************Macros************************************/
typedef float float32_t;
typedef double float64_t;
/*!***************************Structures and Unions*****************************
=====uintN_t(N bit unsigned integer type)=====
====intN_t(N bit two’s complement signed integer type)====
====floatN_t(IEE754 binary float)====
ALL uppercase variables WILL; denote the number of bits in their respective lowercase variables.\\
Interchange format Encoding of s(sign), e(exponent), and  x(mantissa):
if $N \text{ mod } 32 \neq 0$ or if $N \neq 16$; N is invalid.\\
$n$ = Value of some float$N$\_t representation; given $s$(sign), $e$(exponent), and $x$(mantissa). For $n_p$; $p=0$ at it's msb and decrements 1 traveling right to it's lsb $n_{N-1}$\\
if $2-2^{E-1}=e_\text{min} \leq e \leq e_\text{max}=2^{E-1}-1$; $n=2^{e}sx$\\
if $e > e_\text{max}=2^{E-1}-1$ and $x=1$; $n=s\times \infty$\\
if $e > e_\text{max}=2^{E-1}-1$ and $x\neq 1$; $n$ is qNaN or sNaN\\
if $e < e_\text{min}=2-2^{E-1}$ and $x=1$; $n=s\times 0$\\
if $e < e_\text{min}=2-2^{E-1}$ and $x\neq 1$;\\
Except for when \{$N=16$, $E=5$; $N=32$, $E=8$\}; $\forall N\neq (16\text{ or }32), E=\text{round}(4{\log}_{2}(N))-13$.\\$\forall N, S=1$; $\forall N, X=N-E-1$.
$$e =  1-\left(2^{E-1} \right)+\sum_{p=1}^{E}n_p 2^{E-p}$$
$$s=(-1)^{n_0}; x=1+\sum_{p=-1}^{-X}n_{(E-p+1)} 2^p$$

    e.g. float32_t π=0x40490FDB
       msb  lsb msb                 lsb
    ┌─┬────────┬───────────────────────┐
    │s│   e    │           x           │
    │1│   1    │       1.921FB6        │
    │0│10000000│10010010000111111011011│
    └─┴────────┴───────────────────────┘
LSB least significant bit
MSB most significant bit
NaN not a number
qNaN    quiet NaN
sNaN    signaling NaN
====??rating??====
Mohs hardness   Mineral     Absolute hardness
10  Diamond (C)                     1600
9   Corundum (Al2O3)                400
8   Topaz (Al2SiO4(OH–,F–)2)        200
7   Quartz (SiO2)                   100
6   Orthoclase Feldspar (KAlSi3O8)  72
5   Apatite (Ca5(PO4)3(OH–,Cl–,F–))   48
4   Fluorite (CaF2)                 21
3   Calcite (CaCO3)                 9
2   Gypsum (CaSO4·2H2O)                3
1   Talc (Mg3Si4O10(OH)2)           1
All minerals listed can be ground into a powder(with enough force of course).
*/
/**********************************Variables***********************************/
/*****************************Feature Test Switches****************************/
//#define _POSIX_SOURCE 1
/*****************************File scope variables*****************************/
/******************************External variables******************************/
/**********************************Functions***********************************/

//void print_hex( uint64_t num ){
///*!Input(s)     : an unsigned integer
//PreCondition(s) :
//Description     : prints the hex value of the unsigned integer "num"
//If you can count to 8 you can count in hex; numbers 8-F are identical to 0-7 except the MSB, so when your confused just think 000-111!
//PostCondition(s):
//Output(s)       : none
//*/  const char hex[16] = "0123456789ABCDEF";// hex[16] = "F";
///*  for (int16_t i=sizeof(num)*2;i>0;{i--; rol(num, 4);})
//        printf("%c", hex[num % 16]);
//*/
//    //char hex[16] = "0123456789ABCDE"; hex[16] = "F";
//    char test[16] = "0000000000000000";
//    for(int16_t i=0; num>0; num /= 16){
//        test[i] = hex[(num % 16)];
//        i++;
//    }
//    for(int16_t i=15; i>=0; i--) printf("%c", test[i]);
//    printf("\n");
//}//_____________________________________________________________________________

/*
unsigned int rotateleft4(uint64_t data){
    uint64_t carry;
    carry = data & 0x0FFFFFFFFFFFFFFF;
    data  = data << 4;
    if (carry) data += carry;
    return data;
}*/

//uint64_t rotateleft4(uint64_t data){
///*!Input(s)       : an unsigned integer "data"
//PreCondition(s) :
//Description       : rotates data 4 bit to the left
//PostCondition(s):
//Output(s)     : none
//*/
//  uint64_t carry;
//  carry = data & 0x0FFFFFFFFFFFFFFF;
//  data  = data << 4;
//  if (carry) data += carry;
//  return data;
//}//_____________________________________________________________________________

/******************************External Functions******************************/
/***************************Signal catching functions**************************/
