#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MSJE_DESCRI_GENER "descripcion"
#define SIZE_ARRY 5
#define MAX_DESCRIP 128
#define CHOP_SIZE 3
#define INIT_SIZE 5
	
typedef struct {
	size_t id;
	char *des;
	float tyme;
}regist_t;

typedef enum
{
	st_ok,
	st_err
}status_t;

char *file_generator (char *,char,size_t);
char get_csv_delimiter (FILE *);
status_t get_reg (FILE *,regist_t *);



status_t get_reg (FILE *fi,regist_t *reg)
{
	char *aux,*val,delimiter,aux_char;
	size_t alloc_size,used_size;
	
	if (fi == NULL || reg == NULL)
		return st_err;
/*
	if ((delimiter = get_csv_delimiter (fi))==EOF)
		return st_err;
*/
	delimiter = '|';




	if ((aux = (char *)malloc (sizeof (char )*(sizeof (size_t)+1)))==NULL)
		return st_err;

	alloc_size = sizeof (size_t)+1;

	if (fgets (aux,sizeof (size_t)+1,fi)==NULL)
	{
	 	free (aux);
	 	return st_err;
	 }
	aux [alloc_size-1] = '\0';

	
	reg->id = atoi (aux);  	

	free (aux);

	printf(" %li\n", ftell (fi));

	aux_char = fgetc (fi);
	putchar (aux_char);

	if ((reg->des = (char *)malloc ( sizeof (char )*INIT_SIZE))== NULL)
		return st_err;
	
	 
	alloc_size = INIT_SIZE; 

	for (used_size = 0 ; used_size <= MAX_DESCRIP ; used_size ++ )

	{
		if (used_size == alloc_size-1)
		{
			if ((val = (char*)realloc (reg->des, sizeof (char )*(alloc_size+=CHOP_SIZE)))==NULL)
			{
				free (reg->des);
				return st_err;
			}
			reg->des = val;
		}

		if ((aux_char = fgetc (fi)) == delimiter || aux_char == EOF)
			break;


		reg->des [used_size] = aux_char;
	}

	puts (reg->des);

	if (used_size == MAX_DESCRIP || aux_char == EOF)
	{
		free (reg->des);
		return st_err;
	}

	if ((aux = (char *)malloc (sizeof (char )*(sizeof (float)+1)))==NULL)
		{	
			free (reg->des);
			return st_err;
		}

	alloc_size = sizeof (float)+1; 	
	
	if (fgets (aux,sizeof (float)+1,fi)==NULL)
	 	{
	 		free (reg->des);
	 		free (aux);
	 		return st_err;
	 	}

	aux [alloc_size-1] = '\0';

	
	reg->tyme = atof (aux);

	free (aux);

	return st_ok;
}

char get_csv_delimiter (FILE *file)
{
	char delimiter;

	if (file == NULL)
		return EOF;
	
	fseek (file , sizeof (size_t)+2,SEEK_SET);

	delimiter = fgetc (file );
	

	rewind (file);
	
	putchar (delimiter);
			
	return delimiter;
}



char* file_generator (char *name,char csv_delimiter,size_t cant){
	FILE *file;
	size_t i; 		
	time_t my_time = time (&my_time);


	if ((file = fopen (name ,"wt"))==NULL)
		return NULL;


	for  (i =0;i<cant;i++)
	{

	fprintf(file, "%u",i);

	fputc (csv_delimiter,file);

	fputs (MSJE_DESCRI_GENER,file);
	
	fputc (csv_delimiter,file);

	fprintf( file, "%.3f",(float)my_time);

	fputc (csv_delimiter,file);

}	

	if (fclose (file )==EOF)
	return NULL;
	
	return name;
}



int main (void )
{

	FILE *file;
	regist_t reg;
	status_t st;
	char *val; 
if ((val=file_generator("csv.txt",'|',10))==NULL)
		{	
		puts ("erro al crear el archivo");
		return EXIT_FAILURE;

	}	

if ((file = fopen ("csv.txt","rt"))==NULL)
	{	
		puts ("erro al abrir el archivo");
		return EXIT_FAILURE;

	}
	if ((st = get_reg (file,&reg))== st_err)
	{
		puts ("error al codificar");
		fclose (file);
		return EXIT_FAILURE;
	}
	puts (reg.des);
	printf(" %u %f\n",reg.id,reg.tyme);

	return 0;
}