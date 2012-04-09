/*	Copyright © 2012 Roy Pfund

	Licensed under the Apache License, Version 2.0 (the  "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable  law  or  agreed  to  in  writing,
	software distributed under the License is distributed on an  "AS
	IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,  either
	express or implied. See the License for  the  specific  language
	governing permissions and limitations under the License.
*/
/* Creating and using Your own custom events in Java.

5 Things needed on throwing side:
	* import of java.util.event
	* a declaration of the events that can caught by a catcher
	* a list of catchers
	* a way to add someone to the list of catchers
	* 1 or more times, a Notification that an event happened is thrown.
*/
//import of java.util.event
import java.util.*;

//a declaration of the events that can caught by a catcher
interface ThrowListener {
	public void Catch();
}

class Thrower {
	//a list of catchers
	List<ThrowListener> listeners = new ArrayList<ThrowListener>();
	//a way to add someone to the list of catchers
	public void addThrowListener(ThrowListener toAdd){
		listeners.add(toAdd);
	}

	public void Throw() {
		System.out.println("Something thrown");

		//1 or more times, a Notification that an event happened is thrown.
		for (ThrowListener hl : listeners) hl.Catch();
	}
}

/* 3 Things needed on catching side:
	* implement added to class
	* instantiation of a thrower object and use of it's addListener function
	* an override of 1 events that can caught by this type of catcher
*/
//the 1 class catch method:
class Catcher1 implements ThrowListener {//implement added to class
	public static void main(String[] args) {
		//instantiation of a thrower object and use of it's addListener function
		Thrower ThrowerInstance = new Thrower();
		ThrowerInstance.addThrowListener(this);

		ThrowerInstance.Throw();
	}
	//an override of 1 events that can caught by this type of catcher
	@Override public void Catch() {
		System.out.println("I caught something!!");
	}
}

//the 2 class catch method
class Catcher2 implements ThrowListener {//implement added to class
	//an override of 1 events that can caught by this type of catcher
	@Override public void Catch() {
		System.out.println("I caught something!!");
	}
}

class Umpire1 {
	public static void main(String[] args) {
		Catcher2 Catcher2Instance = new Catcher2();
		//instantiation of a thrower object and use of it's addListener function
		Thrower ThrowerInstance = new Thrower();
		ThrowerInstance.addThrowListener(Catcher2Instance);

		ThrowerInstance.Throw();
	}
}
