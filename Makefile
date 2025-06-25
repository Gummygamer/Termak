run: termak3d
	./termak3d
termak3d: main.cpp 
	g++ *.cpp -lglut -lGLU -lGL -o termak3d
clean: termak3d
	rm termak3d
