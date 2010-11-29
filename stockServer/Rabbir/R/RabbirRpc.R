RabbirRpc <- function(host,port,exchange,key,type,marcket,code,start,end){
	  ret<-.Call(
	  "RabbirRpc",host,port,exchange,key,type,marcket,code,start,end,PACKAGE
	  = "Rabbir" )
	  if(!is.null(ret))
	  	as.timeSeries(as.data.frame(ret$result))
	  else
		ret
}
