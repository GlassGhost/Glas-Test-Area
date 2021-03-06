/**********************************License(s)***********************************
Copyright © 2010, 2011 Roy Pfund.                           All rights reserved.
Use of this source code is governed by a  BSD-style License(the "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
******************************LIBRARY DESCRIPTION*******************************
This header SHALL make sure that the following static types are provided:
intN_t = N bit two’s complement signed integer type, (should be multiple of 8)
uintN_t = N bit unsigned integer type, (should be multiple of 8)
floatN_t = N bit IEE754 binary float, (MUST be multiple of 32 OR equal to 16)
decimalN_t = N bit IEE754 decimal float, (MUST be multiple of 32)

And SHALL undefine AND depecrate the following incomplete chart:
    bits    unsigned-integer    signed-integer      IEE754-binary-float
    8       ??unsigned char??   ??signed char??     XXXXXX
    16      unsigned short      short               ??half
    32      unsigned            int                 float
    64      unsigned long       long                double
    128     ????????            ?????               ??Quad

and shall also define the functions:
shr(), shl(), ror(), rol()
described in further detail in the Functions section
***********************************Revisions************************************
(2010-Nov-17 00:00 UTC)-v0.01-1Mohs-GlassGhost File created. More emphasis is on
Documentation, than on the actual library at this time.
**********************************DEPENDENCIES*********************************/
#include <stdint.h>
#include "stdops.h"
/************************************Macros************************************/
typedef float float32_t;
typedef double float64_t;
/*!***************************Structures and Unions*****************************
ALL uppercase variables WILL; denote the number  of  bits  in  their  respective
lowercase variables.
Word-the bit length for an instrucition on a certain architecture
LSB-least significant bit
MSB-most significant bit
NaN-not a number
qNaN-quiet NaN
sNaN-signaling NaN

               =======uintN_t(N bit unsigned integer type)=======
If $N \mod 8 ≠ 0$; N is invalid. $n$ = value of some  uint$N$_t  representation.
$radix=2$ and $p=N-1$ at the MSB, and decrements 1 traveling right  towards  the
LSB($p=0$). uint$N$_t can represent all ℕatural numbers from 0 to $2^{N}-1$
$$n =  \sum_{p=0}^{N-1}n_p 2^{p}$$

        =======intN_t(N bit two’s complement signed integer type)=======
If $N \mod 8 ≠ 0$; N is invalid. Identical to the uint$N$_t type, except if $n ≥
2^{N-1};n=1+n-2^{N}$. $n$ = value of some int$N$_t representation. $radix=2$ and
$p=N-1$ at the MSB, and decrements 1 traveling right towards the LSB($p=0$).  An
N-bit int$N$_t can represent every integer in the range $-2^{N-1} … +2^{N-1}-1$
$$n = (1-2^{N})n_{N-1}+\sum_{p=0}^{N-2}n_p 2^{p}$$

               =======floatN_t(N bit IEE754 binary float)=======
If $N \mod 32 ≠ 0$ or if $N ≠ 16$; N is invalid.  Interchange format Encoding of
float$N$_t, where $n$ = value of some float$N$_t representation;given $s$(sign),
$e$(exponent), and $x$(mantissa). For $n_p$; $p=0$ at  it's  msb  and decrements
1 traveling right to it's lsb $n_{N-1}$
Except for when \{$N=16$, $E=5$; $N=32$, $E=8$\};
$∀ N≠(16\text{ or }32), E=\text{round}(4{\log}_{2}(N))-13$.
$∀ N: S=1\text{ AND } X=N-E-1$.
$$e =  1-\left(2^{E-1} \right)+\sum_{p=1}^{E}n_p 2^{E-p}$$
$$s=(-1)^{n_0}; x=\sum_{p=-1}^{-X}n_{(E-p+1)} 2^p$$
if $2-2^{E-1}=e_\text{min} ≤ e ≤ e_\text{max}=2^{E-1}-1$; $n=s(x+1)2^{e}$
if $e < e_\text{min}=2-2^{E-1}$; $n=sx2^{e+1}$
if $e > e_\text{max}=2^{E-1}-1$ and $x=0$; $n=s×∞$
if $e > e_\text{max}=2^{E-1}-1$ and $x≠0$; $n$ is qNaN or sNaN

              =======decimalN_t(N bit IEE754 decimal float)=======
Who cares?
                             =======Examples=======
           0xC248=49736        0xC248=-15799      0xC248=-3.140625≈-π
        ┌───(uint16_t)───┐  ┌─┬─(int16_t)─────┐  ┌─┬─ (float16_t)───┐
        │       n        │  │ │      n        │  │s│  e  │    x     │
        │1100001001001000│  │1│100001001001000│  │1│10000│1001001000│
        └────────────────┘  └─┴───────────────┘  └─┴─────┴──────────┘
         msb          lsb      msb         lsb     msb lsb msb    lsb
***********************************Functions************************************
shr(shift right), shl(shift left), ror(rotate right), rol(rotate left)
            =======Redundant Operations for large Word sizes=======
When rotating multiple times only the last $log_{2}{N}$ bits are pertinent since
rotating a uintN_t N(equal to $2^{log_{2}{N}}$) times would not do anything.  So
any compiler should typecast the num_rotates of a uintN_t to a  uint$log_2(N)$_t
when $N > word length$

Since Shifting a uintN_t N(equal to $2^{log_{2}{N}}$) times or more will  return
0. when N > word length for num_rotates if any bit above  $log_{2}{N}$  for  the
num is set it should go ahead and just return 0.
*/

#ifdef __cplusplus
/*! rotates "num" right "num_rotates" times
*/template <typename uintN_t>
uintN_t ror(uintN_t num, uintN_t num_rotates){
    num_rotates = (uint$log(2,sizeof(num)*8)$_t)num_rotates;//avoid redundant rotates.
    return (num << ((sizeof(num)*8)-num_rotates)) bitor (num >> num_rotates);
};/*__________________________________________________________________________*/

/*! rotates "num" left "num_rotates" times
*/template <typename uintN_t>
uintN_t rol(uintN_t num, uintN_t num_rotates){
    num_rotates = (uint(log(2,sizeof(num)*8))_t)num_rotates;//avoid redundant rotates.
    return (num >> ((sizeof(num)*8)-num_rotates)) bitor (num << num_rotates);
};/*__________________________________________________________________________*/

/*! shifts "num" right "num_rotates" times
*/template <typename uintN_t>
uintN_t shr(uintN_t &num, uintN_t &num_rotates){
    if (num_rotates ≥ (sizeof(num)*8)) return 0;//avoid redundant shifts.
    return num >> num_rotates;
};/*__________________________________________________________________________*/

/*! shifts "num" left "num_rotates" times
*/template <typename uintN_t>
uintN_t shl(uintN_t &num, uintN_t &num_rotates){
    if (num_rotates ≥ (sizeof(num)*8)) return 0;//avoid redundant shifts.
    return num << num_rotates;
};/*__________________________________________________________________________*/

/*! converts unsigned integer "num" into a hex string
*/template <typename uintN_t>
uint8_t [sizeof(uintN_t)*2] uint_to_hex( uintN_t num ){
    uint8_t HEX[16] = "0123456789ABCDE"; HEX[16] = "F";
//  const char HEX[16] = "0123456789ABCDEF";
    uint8_t string_hex[sizeof(num)*2];
    for(int16_t i=sizeof(num)*2; i!=0; {i--; num = rol(num, 4);}){
        string_hex[i] = HEX[(num % 16)];
    }
    return string_hex[];
};/*__________________________________________________________________________*/
#endif
