#include <stdio.h>
#include <stdlib.h>

void clean_window(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void clean_buffer(){
	int c;
	while ((c = getchar()) != '\n' && c != EOF); 
}
