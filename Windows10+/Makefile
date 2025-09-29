all: trompo3 inercial3

trompo3: trompo3.o Vector3D.o
	c++ trompo3.o Vector3D.o -o trompo3.exe -lopengl32 -lfreeglut -lglu32

inercial3: inercial3.o Vector3D.o
	c++ inercial3.o Vector3D.o -o inercial3.exe -lopengl32 -lfreeglut -lglu32

clear:
	rm -rf *.o *.exe

.cpp.o:
	c++ -c $< -o $@
