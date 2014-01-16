Components.utils.import("resource://gre/modules/XPCOMUtils.jsm");

function UrlScript(url, script) {
this.url = url;
this.script = script;
this.opened=false;
}
function SandBoxEcec(script,win)
{
    var sandbox=new Components.utils.Sandbox(win);
    sandbox.window = win;
    scriptLoader.loadSubScript("chrome://mybrowser/content/jquery.js",
                               win, "UTF-8");
    if(sandbox.window.jQuery)
        sandbox.jQuery=sandbox.window.jQuery;
    if(sandbox.window.$)
        sandbox.$=sandbox.window.$;
    Components.utils.evalInSandbox("var tmpfun="+script+";tmpfun()", sandbox);
}

// nsIWebProgressListener implementation to monitor activity in the browser.
function WebProgressListener() {
}
WebProgressListener.prototype = {
_requestsStarted: 0,
_requestsFinished: 0,
urlscript:null,
nav:null,
fin:true,
// We need to advertize that we support weak references.  This is done simply
// by saying that we QI to nsISupportsWeakReference.  XPConnect will take
// care of actually implementing that interface on our behalf.
QueryInterface: function(iid) {
	  if (iid.equals(Components.interfaces.nsIWebProgressListener) ||
	      iid.equals(Components.interfaces.nsISupportsWeakReference) ||
	      iid.equals(Components.interfaces.nsISupports))
	       return this;
    
	  throw Components.results.NS_ERROR_NO_INTERFACE;
     },

// This method is called to indicate state changes.
onStateChange: function(webProgress, request, stateFlags, status) {
	  const WPL = Components.interfaces.nsIWebProgressListener;
	  if (stateFlags & WPL.STATE_IS_REQUEST) {
	       if (stateFlags & WPL.STATE_START) {
		    this._requestsStarted++;
	       } else if (stateFlags & WPL.STATE_STOP) {
		    this._requestsFinished++;
	       }
	  }
          if (stateFlags & WPL.STATE_IS_NETWORK) {
              if (stateFlags & WPL.STATE_STOP) {
                  if(this._requestsStarted != 0)
                  {
                      this.onStatusChange(webProgress, request, 0, "Done");
                      this._requestsStarted = this._requestsFinished = 0;
                  }
              }
          }
    },

// This method is called to indicate progress changes for the currently
// loading page.
onProgressChange: function(webProgress, request, curSelf, maxSelf,
			   curTotal, maxTotal) {
     },

// This method is called to indicate a change to the current location.
onLocationChange: function(webProgress, request, location) {
     },

// This method is called to indicate a status changes for the currently
// loading page.  The message is already formatted for display.
onStatusChange: function(webProgress, request, status, message) {
        if(status==0)
        {
            var us=this.urlscript.shift();
            if(us!=null)
            {
                if(us.opened)
                {
                    if(us.script!=null&&us.script.length>0)
                        SandBoxEcec(us.script,webProgress.DOMWindow);
                }else
                {
                    this.nav.loadURI(us.url,0,null,null,null);
                    us.opened=true;
                    this.urlscript.unshift(us);
                }
            }else
            {
                fin=true;
            }
        }
     },

// This method is called when the security state of the browser changes.
onSecurityChange: function(webProgress, request, state) {

     }
}; 
var scriptLoader = Components.classes["@mozilla.org/moz/jssubscript-loader;1"]
                            .getService(Components.interfaces.mozIJSSubScriptLoader);
function JsCom() { }
 
JsCom.prototype = {
classDescription: "JsCOM Component",
classID:          Components.ID("{4c7d8c9f-c8bb-4f53-bd5f-3d737302e9a3}"),
contractID:       "@xiao.xf.com/JsCom;1",
QueryInterface: XPCOMUtils.generateQI([Components.interfaces.nsIJsCom]),
nav:null,
progress:null,
listener:null,
navready:false,
SetBrowerInfo: function(nav,progress) {
        this.nav=nav;
        this.progress=progress;
        if(this.listener!=null)
        {
            this.progress.removeProgressListener(this.listener);
        } 
        this.listener = new WebProgressListener();
        this.listener.nav=nav;
        this.listener.urlscript=new Array();
        this.progress.addProgressListener(this.listener,
                                    Components.interfaces.nsIWebProgress.NOTIFY_ALL);
    },
execJs: function(script) {
        eval(script);
        var us=this.listener.urlscript.shift();
        if(us!=null)
        {
            if(this.listener.fin)
            {
                this.nav.loadURI(us.url,0,null,null,null);
                us.opened=true;
                this.listener.urlscript.unshift(us);
                this.listener.fin=false;
            }
        }
    },
execWinJs: function(script,win) {
        if(script!=null&&script.length>0)
            SandBoxEcec(script,win);
    },
open:function(url,script){
        var us=new UrlScript(url,script);
        this.listener.urlscript.push(us);
    }
};
if (XPCOMUtils.generateNSGetFactory)
  var NSGetFactory = XPCOMUtils.generateNSGetFactory([JsCom]);  // Firefox 4.0 and higher
else
  var NSGetModule = XPCOMUtils.generateNSGetModule([JsCom]);    // Firefox 3.x
