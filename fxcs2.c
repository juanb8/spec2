#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MSJE_DESCRI_GENER "descripcion"
#define SIZE_ARRY 5
#define MAX_DESCRIP 128
#define CHOP_SIZE 3
#define INIT_SIZE 5
#define CSV_DELIMITER '|'
	
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
status_t get_regist (FILE *,regist_t *);



status_t get_regist  (FILE *fi, regist_t * reg)
{
	char *aux,aux_char,*val,delimiter;
	size_t used_size,alloc_size,alloc_size_reg;
	


	if (fi == NULL || reg == NULL)
		return st_err;

	delimiter = CSV_DELIMITER;

	if ((aux = (char *)malloc (sizeof (char )*INIT_SIZE))==NULL)
		return st_err;

	alloc_size = INIT_SIZE;

	for (used_size = 0; (aux_char = fgetc (fi))!= EOF || aux_char != delimiter; used_size++)

	{
		if (used_size == alloc_size-1)
		{
			if ((val = (char *)realloc (aux,sizeof (char )*(alloc_size+= CHOP_SIZE)))==NULL)
			{
				free (aux);
				return st_err;
			}

			aux = val;
			}
		aux [used_size]=aux_char;
	}

	if (aux_char == EOF)
	{
		free (aux );
		return st_err;
	}

	reg->id  = atoi (aux);

	if ((reg->des = (char *)malloc (sizeof (char )*INIT_SIZE))==NULL)
	{
		free (aux );
		return st_err;
	}

	alloc_size_reg = INIT_SIZE;

	for (used_size = 0; (aux_char = fgetc (fi))!= EOF || aux_char != delimiter;used_size++)

	{
		if (used_size == alloc_size_reg-1)
		{
			if ((val = (char *)realloc (reg->des,sizeof (char )*(alloc_size+= CHOP_SIZE)))==NULL)
			{
				free (aux);
				return st_err;
			}

			reg->des = val;
			}
		reg->des [used_size]=aux_char;
	}

	if (used_size == MAX_DESCRIP)
	{
		free (aux);
		free (reg->des);
		return st_err;
	}

	
	if (aux_char == EOF)
	{
		free (aux );
		free (reg->des);
		return st_err;
	}

	
	for (used_size = 0; (aux_char = fgetc (fi))!= EOF || aux_char != delimiter;used_size++)

	{
		if (used_size == alloc_size-1)
		{
			if ((val = (char *)realloc (aux,sizeof (char )*(alloc_size+= CHOP_SIZE)))==NULL)
			{
				free (aux);
				free (reg->des);
				return st_err;
			}

			aux = val;
			}
		aux [used_size]=aux_char;
	}

	
	if (aux_char == EOF)
	
	{
		free (aux );
		free (reg->des);
		return st_err;
	}

	
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



if ((file = fopen ("csv.txt","rt"))==NULL)
	{	
		puts ("erro al abrir el archivo");
		return EXIT_FAILURE;

	}


	if ((st = get_regist (file,&reg))== st_err)
	{
		puts ("error al codificar");
		fclose (file);
		return EXIT_FAILURE;
	}
	puts (reg.des);
	printf(" %u %f\n",reg.id,reg.tyme);

	return 0;
}