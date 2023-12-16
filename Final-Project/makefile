finalProject: finalProject.o projectHelper.o
	g++ -ggdb -o finalProject finalProject.o projectHelper.o

finalProject.o: finalProject.cpp projectHelper.h
	g++ -c -ggdb finalProject.cpp -o finalProject.o

projectHelper.o: projectHelper.cpp projectHelper.h
	g++ -c -ggdb projectHelper.cpp -o projectHelper.o

clean:
	/bin/rm -f finalProject finalProject.o projectHelper.o *~

