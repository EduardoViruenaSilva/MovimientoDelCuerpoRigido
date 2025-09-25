all:	inercial3 trompo3

inercial3: inercial3.o Vector3D.o 
	c++ inercial3.o Vector3D.o -o inercial3 -lGLU -lGL -lglut

trompo3: trompo3.o Vector3D.o 
	c++ trompo3.o Vector3D.o -o trompo3 -lGLU -lGL -lglut

clean:	
	rm -f inercial3 trompo3 *.o

.cpp.o:
	c++ $< -o $@ -c
