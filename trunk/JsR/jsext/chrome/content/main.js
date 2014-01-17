var jsCom = Components.classes["@xiao.xf.com/JsCom;1"]
                            .getService(Components.interfaces.nsIJsCom);
function jsexcute() {
    var browser=document.getElementById("browser");
    jsCom.SetBrowerInfo(browser.webNavigation,browser.webProgress);
    var script=document.getElementById("testscript");   
    jsCom.execJs(script.value);
}
function jsexcutewin() {
    var browser=document.getElementById("browser-jquery");

    var script=document.getElementById("testscript-jquery");
     jsCom.execWinJs(script.value,browser.contentWindow);
}
function go() {
    var browser=document.getElementById("browser-jquery");
    var url=document.getElementById("Address");   
    browser.loadURI(url.value,null,null);
}
