output:	main.o glad.o
	g++ -Wall main.o glad.o -o main.exe -Llib-mingw-w64 -lglfw3 -lgdi32 -lopengl32
	python clear.py

main.o:	src/main.cpp
	g++ src/main.cpp -c -I include

glad.o: src/glad.c
	g++ src/glad.c include/glad/glad.h -c -I include
