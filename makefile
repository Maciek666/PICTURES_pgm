a.exe: main.c onPicture.c funktion.c option.c
		gcc -pedantic -Wall main.c onPicture.c funktion.c option.c
main.c: main.c
		gcc -Wall -pedantic -c main.c
onPicture.c: onPicture.c
		gcc -Wall -pedantic -c onPicture.c
funktion.c: funktion.c
		gcc -Wall -pedantic -c funktion.c
option.c: option.c
		gcc -Wall -pedantic -c option.c
