#include <stdio.h>
#include <conio.h>

void clrbuf();

struct gallego
{
int nro_libro;
char nom_libro[20];
};

int main (void)
{
FILE *stream;

struct gallego a;
struct gallego b;

if ((stream = fopen("DUMMY.TXT", "w+")) == NULL) /* open file TEST.$$$ */
{
	fprintf(stderr, "Cannot open output file.\n");
	return 1;
}

for(int i=1;i<3;i++){
	scanf("%d",&a.nro_libro);
	clrbuf();
	fflush(stdin);
	gets(a.nom_libro);


	fwrite(&a, sizeof(a), 1, stream); /* write struct a to file */
}

	/* seek to the beginning of the file */
	fseek(stream, SEEK_SET, 0);
	fread(&b, sizeof(a), 1, stream);
	while(!feof(stream)){
	/* read the data and display it */
		printf("%s  %d\n", b.nom_libro,b.nro_libro);
		fread(&b, sizeof(a), 1, stream);

	}
	fclose(stream);


return 0;
}


//Pre{...}//
void clrbuf()
{
char a;
while (kbhit() != 0){
			a=getch();
		}
}
//Pos{Borra el buffer del getch}//
/*-------------------------------*/

