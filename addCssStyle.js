/*! addCssStyle() applies the text value $CssText$ to the the specified document
$Doc$ e.g. an IFrame; or if none specified, default to the current document,
*/function addCssStyle(CssText, Doc){
//Secure $head$
	Doc = Doc||document;	var head = Doc.getElementsByTagName('head')[0];
	if(!head || head == null){
		head = Doc.createElement('div');	Doc.body.appendChild(head);
	} if(!head || head == null){return false;}
//createElement('style')
	var PendingStyle = Doc.createElement('style');
	PendingStyle.type = 'text/css';	PendingStyle.rel = 'stylesheet';
	PendingStyle.innerHTML = CssText;
	head.appendChild(PendingStyle);
}/*___________________________________________________________________________*/
