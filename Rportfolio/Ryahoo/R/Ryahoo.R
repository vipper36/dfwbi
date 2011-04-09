yahooDatas<-function(C,f="",val="close"){
	first<-yahooData(C[1],start=f)
	firstClose<-first[,val]
        colnames(firstClose)<-C[1]
	for(stock in C[2:length(C)])
	{
		tmp<-yahooData(stock,start=f)
		tmpClose<-tmp[,val]
		colnames(tmpClose)<-stock
		firstClose<-cbind(firstClose,tmpClose)	
	}
	firstClose
}
yahooData <- function(code,start=""){
	  ret<-.Call(
	  "yahooData",code,start,PACKAGE
	  = "Ryahoo" )
	  if(!is.null(ret))
	  	timeSeries(as.data.frame(ret$result)[,2:7],as.data.frame(ret$result)[,1])
	  else
		ret
}
