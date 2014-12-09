/* fgetpos and fsetpos example */

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>


void showpos(FILE *stream);
char texto[42] = "These are tests";


int main(void)
{
	FILE *stream;
	fpos_t filepos;

	/* open a file for update */
	stream = fopen("DUMMY.TXT", "r+");

	/* save the file pointer position */
	fgetpos(stream, &filepos);

	/* write some data to the file */
	fwrite(&texto,sizeof(texto),1,stream);

	/* show the current file position */
	showpos(stream);

	/* set a new file position, display it */
	filepos=0;
	if (fsetpos(stream, &filepos) == 0){
		showpos(stream);
		fwrite("This is a WesT",sizeof("This is a zest"),1,stream);
	}else{
		fprintf(stderr, "Error setting file pointer.\n");
		exit(1);
	}

	filepos=120;
	if (fsetpos(stream, &filepos) == 0){
		showpos(stream);
		fwrite(&texto,sizeof(texto),1,stream);
	}else{
		fprintf(stderr, "Error setting file pointer.\n");
		exit(1);
	}

	filepos=40;
	strcpy(texto,"esto es una prueba");
	if (fsetpos(stream, &filepos) == 0){
		showpos(stream);
		fwrite(&texto,sizeof(texto),1,stream);
	}else{
		fprintf(stderr, "Error setting file pointer.\n");
		exit(1);
	}

	/* close the file */
	fclose(stream);
	return 0;
}

void showpos(FILE *stream)

{
	fpos_t pos;

	/* display the current file pointer
		position of a stream */
	fgetpos(stream, &pos);
	printf("File position: %ld\n", pos);
}