/**********************************License(s)***********************************
Copyright © 2010, 2011 Roy Pfund.                           All rights reserved.
Use of this source code is governed by a  BSD-style License(the "License")  that
can be found in the LICENSE file. You should have received a copy of the License
along with this distribution.  If not,  You may obtain a copy of the License  at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
******************************LIBRARY DESCRIPTION*******************************
This header may convert loops into goto statements:
break;//goes to current loop end
continue;//goes to current loop start

for ([variable declaration]; [condition]; [variable update])
[loop body statement]

do [loop body statement] while ([condition]);

while ([condition])[loop body statement]

A pointer into an array, for example, is just a pair of
* array (reference)
* index into it
when the pointer points outside of the array the behavior is undefined
in C++, so I would like the Java version to fail in a case like that.

**********************************DEPENDENCIES**********************************

***********************************Revisions************************************
(2011-Feb-2)-v0.01-1Mohs-GlassGhost File created.
*********************************System Headers********************************/

/************************************Macros************************************/

/*!***************************Structures and Unions*****************************

/**********************************Functions***********************************/
