var jsCom = Components.classes["@xiao.xf.com/JsCom;1"]
                            .getService(Components.interfaces.nsIJsCom);
function jsexcutewin() {
	var mainWindow = window.QueryInterface(Components.interfaces.nsIInterfaceRequestor)
                       .getInterface(Components.interfaces.nsIWebNavigation)
                       .QueryInterface(Components.interfaces.nsIDocShellTreeItem)
                       .rootTreeItem
                       .QueryInterface(Components.interfaces.nsIInterfaceRequestor)
                       .getInterface(Components.interfaces.nsIDOMWindow);
	var browser = mainWindow.gBrowser.selectedBrowser;
	var script=document.getElementById("testscript-jquery");
     	jsCom.execWinJs(script.value,browser.contentWindow);
}
