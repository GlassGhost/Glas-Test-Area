/**********************************License(s)***********************************
Copyright (c) 2010, Roy Pfund.                              All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice,  this
    list of conditions and the following disclaimer.
 2. Redistributions in binary form  must reproduce  the above  copyright notice,
    this  list of conditions  and  the following disclaimer in the documentation
    and/or other materials provided with the distribution.
 3. Neither the name of the Copyright Holders  nor the names of its Contributors
    may  be  used  to endorse  or  promote products  derived from  this software
    without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"  AND
ANY EXPRESS OR IMPLIED WARRANTIES,  INCLUDING,  BUT NOT LIMITED TO,  THE IMPLIED
WARRANTIES  OF  MERCHANTABILITY  AND  FITNESS  FOR  A  PARTICULAR  PURPOSE   ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNERS OR CONTRIBUTORS BE LIABLE FOR
ANY  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;LOSS
OF USE, DATA,  OR PROFITS;  OR BUSINESS INTERRUPTION)  HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY,  WHETHER IN CONTRACT, STRICT LIABILITY,  OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE)   ARISING IN ANY WAY  OUT OF THE USE OF  THIS SOFTWARE,
EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                - 3 Clause BSD
*****************************STRUCTURE DESCRIPTIONS*****************************
<vector> onedimensional array of T §16.3

<list> doubly linked list of T §17.2.2 - use a xor linked list

<deque or deck> doubleended queue of T §17.2.3 pronounced "deck"
The deck data type: a dynamically growing xor-linked-list. "tunable" in the fact
that you can optionally set it to place variable in groups of a certain length
of bytes in praise of less waste of memory for pointers. has an overhead of up to (2 times the byte length specified - 2 times actual size of data structure in
the deck)
	<stack> stack of T §17.3.1		equivalent to a deck without the push_bottom and pop_bottom - to be impelemented as a small amount of memory can be gained.
	<queue> queue of T §17.3.2		equivalent to a deck without the push_top and pop_bottom - not be implemented as no performance or memory is gained by losing the specificied functionality

<map> associative array of T §17.4.1
<set> set of T §17.4.3
<bitset> array of booleans §17.5.3 - for the purpose of addressing single bits
of a data structure. best to just use type casting with this rather than actual
instantiation. example:
	#define help_arg_bool ((std::bitset<64>)*program_flagsUINT64Ptr)[0]
	UINT64* program_flagsUINT64Ptr = new UINT64(0);
	if (help_arg_bool == 1) std::cout << "Command line args are:\n\t-help\n";	
***********************************Revisions************************************
(5-11-2010 14:00)-v0.01-began deck structure
******************************Feature Test Switches****************************/
#define _POSIX_SOURCE 0
/************************************Macros************************************/
typedef unsigned short UINT16; typedef short	INT16;
typedef unsigned	   UINT32; typedef int		INT32;
typedef unsigned long  UINT64; typedef long int INT64;
/*********************************STRUCTURES***********************************/

template <typename Object> deck{/*------Don't deal from the botom of the deck*/
private:
	UINT16 Sector_Size = 512;
	UINT16 Sector_Obj_Capacity, Sector_ObjPtr_Capacity;
	UINT32 Deck_Size = 0;
	struct position{Object* ArrayPtr;	UINT16 ArrayOffset, Offset;};
	position top, bottom;
protected:
public:
	void push(Object){/*-------------------adds an item to the top of the deck*/
		if (Deck_Size == 0){
			ObjectPtr[x] = new Object[Sector_Obj_Capacity];
		}
		Deck_Size++;
	}/*---------------------------------------------------------------END push*/

	Object pop(){/*----------------returns the item off of the top of the deck*/
		Deck_Size--;
	}/*----------------------------------------------------------------END pop*/

	void enqueue(Object){/*-------------adds an item to the bottom of the deck*/
		Deck_Size++;
	}/*------------------------------------------------------------END enqueue*/

	Object pop_bottom(){/*------returns the item off of the bottom of the deck*/
		Deck_Size--;
	}/*---------------------------------------------------------END pop_bottom*/

	 deck(){/*------------------------------------------------deck constructor*/
		Sector_Obj_Capacity = Sector_Size/sizeof(Object);//determines how many objects can fit in a sector
		Sector_ObjPtr_Capacity = Sector_Size/sizeof(Object*);//determines how many object can fit in a sector
		Top.ArrayPtr = new Object* ObjectPtr[Sector_ObjPtr_Capacity];
		Top.ArrayOffset = (Sector_ObjPtr_Capacity / 2)++;
		Top.Offset = (Sector_Obj_Capacity / 2)++;
		Bottom = Top;
	}

	Object exchange(UINT32 x, Object instance){/*replaces instance x with new instance*/
		if (Deck_Size == 0 or x >= Deck_Size){
			throw exception ;
		}
		Deck_Size++;
	}/*---------------------------------------------------------------END constructor*/

	void shift_up(){/*--------------------------------------------------------*/
		enqueue(pop());
	}/*END shift_up-----------------------------------------------------------*/

	void shift_down(){/*------------------------------------------------------*/
		push(pop_bottom());
	}/*END shift_down---------------------------------------------------------*/

	UINT32 size(){/*----------------------------------------------------------*/
		return(deck_size);
	}/*END shift_down---------------------------------------------------------*/
};/*---------------------------------------------------------------END of deck*/

/*UNLESS NOTED OHERWISE: ALL INFORMATION PROVIDED INCLUDING COMMENTARY, OPINION,
FILES, DRAWINGS, DIAGNOSTICS, LISTS, AND OTHER DOCUMENTS (TOGETHER AND
SEPARATELY, “MATERIALS”) ARE BEING PROVIDED “AS IS.” THE COPYRIGHT HOLDERS AND CONTRIBUTORS MAKE NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR ANY PARTICULAR PURPOSE.*/

/*Marcelo's answer is correct;the 1st declaration is an array of the struct "emp" whereas, the 2nd is an array of pointers to "emp" structs.

there are good applications of both instances:
Because of the way data buses are; It is best to use a an array of structs, to take out new chunks or sectors of memory, but only when needed(an array of pointers to the first element in each sector).Then use pointer arithmetic to access the pointers to the sectors, then pointer arithmetic again to access elements of each sector.

well the only thing left to decide is sector size and pointer array size, and allow the data structure to grow dynamically. this depends on your target machine's ram sector size or maybe even it's hard disk sector size if you are going to be opening, and editing the files a lot.

now remember you want to think in hex;NEVER declare ANY structure that doesn't use some power of 2 added to some power of 2 bytes. Doesn't matter if it's 32 or 4096

    struct emp{char first_name[24]; //makes the struct take precisely 64bytes
               char last_name[24];
               char key[16];       };

Example: NEVER make a stack OR a queue; make a double ended queue or dequeue

    x :
    dfd==1fl;j
*/
