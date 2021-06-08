# The Orbits Makefile

Pre:
	g++ -c source/main.cpp -o source/main.o -I"C:\Projetos\Programação\Proj\Physics\Orbits\include"

Snake:
	g++ source/main.o -o program/Orbits.exe -L"C:\Projetos\Programação\Proj\Physics\Orbits\libraries" -lfreeglut -lopengl32 -Wl,--subsystem,windows