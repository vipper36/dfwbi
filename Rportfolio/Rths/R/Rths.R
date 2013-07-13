thsInit<-function(dir){
	.Call("thsInit",dir,PACKAGE
          = "Rths")
	TRUE
}
thsDay <- function(code,marcket,start=""){
	  ret<-.Call(
	  "thsDay",code,marcket,start,PACKAGE
	  = "Rths" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret)[,2:7],as.data.frame(ret)[,1])
	  else
		ret
}
thsMin <- function(code,marcket,start=""){
	  ret<-.Call(
	  "thsMin",code,marcket,start,PACKAGE
	  = "Rths" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret)[,2:7],as.data.frame(ret)[,1])
	  else
		ret
}
thsMinOfDay <- function(code,marcket,day=""){
	  ret<-.Call(
	  "thsMinOfDay",code,marcket,day,PACKAGE
	  = "Rths" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret)[,2:7],as.data.frame(ret)[,1])
	  else
		ret
}
thsMin5 <- function(code,marcket,start=""){
	  ret<-.Call(
	  "thsMin5",code,marcket,start,PACKAGE
	  = "Rths" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret)[,2:7],as.data.frame(ret)[,1])
	  else
		ret
}
thsMin5OfDay <- function(code,marcket,day=""){
	  ret<-.Call(
	  "thsMin5OfDay",code,marcket,day,PACKAGE
	  = "Rths" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret)[,2:7],as.data.frame(ret)[,1])
	  else
		ret
}
