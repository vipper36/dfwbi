chinese.seg.txt: chinese.raw.txt ictclas
	./ictclas < chinese.raw.txt > chinese.seg.txt

ictclas: main.cpp Source/libictclas.a
	g++ -g -o ictclas main.cpp -L./Source -lictclas 

Source/libictclas.a: Source/*.cpp
	cd Source; g++ -g -c *.cpp
	cd Source; ar -r libictclas.a *.o
clean:
	rm ictclas Source/libictclas.a Source/*.o
