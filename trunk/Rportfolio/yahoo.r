yahooReturn<-function(C,val="Close"){
	first<-yahooSeries(C[1])
	firstClose<-first[,paste(C[1],".",val,sep="")]
	for(stock in C[2:length(C)])
	{
		tmp<-yahooSeries(stock)
		tmpClose<-tmp[,paste(stock,".",val,sep="")]
		firstClose<-cbind(firstClose,tmpClose)	
	}
	firstClose
}
