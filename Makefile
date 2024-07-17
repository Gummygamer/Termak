run: termak3d
	./termak3d
termak3d: principal.cpp 
	g++ *.cpp -lglut -lGLU -lGL -o termak3d
clean: termak3d
	rm termak3d
