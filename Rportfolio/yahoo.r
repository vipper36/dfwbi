yahooReturn<-function(C,f=NULL,val="Close"){
	first<-yahooSeries(C[1],from=f)
	firstClose<-first[,paste(C[1],".",val,sep="")]
	for(stock in C[2:length(C)])
	{
		tmp<-yahooSeries(stock,from=f)
		tmpClose<-tmp[,paste(stock,".",val,sep="")]
		firstClose<-cbind(firstClose,tmpClose)	
	}
	firstClose
}
