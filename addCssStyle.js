/**********************************License(s)***********************************
	Copyright 2011 Roy Pfund
	Licensed under the Apache License, Version 2.0 (the  "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable  law  or  agreed  to  in  writing,
	software distributed under the License is distributed on an  "AS
	IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,  either
	express or implied. See the License for  the  specific  language
	governing permissions and limitations under the License.
********************************************************************************

/*! addCssStyle() applies the text value $CssText$ to the the specified document
$Doc$ e.g. an IFrame; or if none specified, default to the current document,
*/function addCssStyle(CssText, Doc){

//Secure $Doc$
	Doc = Doc||document;	var head = Doc.getElementsByTagName('head')[0];
	if(!head || head == null){
		head = Doc.createElement('div');	Doc.body.appendChild(head);
	} if(!head || head == null){return false;}

//createElement('style')
	var PendingStyle = Doc.createElement('style');
//	if (is_gecko){PendingStyle.href = 'FireFox.css';}//???needeed???
	PendingStyle.type = 'text/css';
	PendingStyle.rel = 'stylesheet';
//	PendingStyle.media = 'screen';//???needeed???
	PendingStyle.innerHTML = CssText;
	head.appendChild(PendingStyle);

//createElement('div')
//	var PendingStyleDiv = doc.createElement('div');
//	PendingStyleDiv.innerHTML = 
//	'&nbsp;<style id="" type="text/css">'+CssText+'</style>&nbsp;';
//	if (head.firstChild){// Add the new style of higher priority than the last 
//						 // ones if there's already other elements in the head
//		head.insertBefore(PendingStyleDiv.childNodes[1], head.firstChild);
//	}else {
//		head.appendChild(PendingStyleDiv.childNodes[1]);
//	}

}/*___________________________________________________________________________*/
