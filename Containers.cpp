/**********************************License(s)***********************************
Copyright 2010 Roy Pfund.                                   All rights reserved.
Use of this source code is governed by a BSD-style License(the  "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
*****************************STRUCTURE DESCRIPTIONS*****************************
<vector> onedimensional array of T §16.3

<list> doubly linked list of T §17.2.2 - use a xor linked list

<deque or deck> doubleended queue of T §17.2.3 pronounced "deck"
The deck data type: a dynamically growing xor-linked-list. "tunable" in the fact
that you can optionally set it to place variable in groups of a certain length
of bytes in praise of less waste of memory for pointers. has an overhead of up to (2 times the byte length specified - 2 times actual size of data structure in
the deck)
    <stack> stack of T §17.3.1     equivalent to a deck without the push_bottom and pop_bottom - to be impelemented as a small amount of memory can be gained.
    <queue> queue of T §17.3.2     equivalent to a deck without the push_top and pop_bottom - not be implemented as no performance or memory is gained by losing the specificied functionality

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
/*********************************STRUCTURES***********************************/

template <typename Object> deck{/*------Don't deal from the botom of the deck*/
private:
    UINT16 Sector_Size = 512;
    UINT16 Sector_Obj_Capacity, Sector_ObjPtr_Capacity;
    UINT32 Deck_Size = 0;
    struct position{Object* ArrayPtr;   UINT16 ArrayOffset, Offset;};
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
        Sector_ObjPtr_Capacity = Sector_Size/sizeof(Object*);//determines how many object ptrs can fit in a sector
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

/*UNLESS NOTED OHERWISE: ALL INFORMATION PROVIDED INCLUDING COMMENTARY, OPINION, FILES, DRAWINGS, DIAGNOSTICS, LISTS, AND OTHER DOCUMENTS (TOGETHER AND SEPARATELY, “MATERIALS”) ARE BEING PROVIDED “AS IS.” THE COPYRIGHT HOLDERS AND CONTRIBUTORS MAKE NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR ANY PARTICULAR PURPOSE.*/
