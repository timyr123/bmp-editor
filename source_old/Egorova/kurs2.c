
//kyrsovaya Преобразование изображений средствами языка С
//sravnit 2 bmp i poschitat kolichestvo raznih tochek


#include "stdio.h"
#include "string.h"
#define MAX_FILE_SIZE 1000

typedef unsigned char BYTE;
enum colors {blue, green, red};

//struct {BYTE blue ; BYTE green; BYTE red;} ;


main()
{
    printf("%d %d %d\n", blue , green, red);
    int i,j,z, chet, dlya_vivoda;
    char type[2];  
    int size;
    int res;
    int off;
    int ssz;
    int w;
    int h;
    int end[7];
    char type2[2];  
    int size2;
    int res2;
    int off2;
    int ssz2;
    int w2;
    int h2;
    int end2[7];
    chet = 0;
    FILE * fin1 = fopen("3.bmp", "r");
    perror("Open file");

    FILE * fin2 = fopen("4.bmp", "r");
    perror("Open file");
    

    fread(&type, 2, 1, fin1);
    fread(&size, 4, 1, fin1);
    fread(&res, 4, 1, fin1);
    fread(&off, 4, 1, fin1);
    fread(&ssz, 4, 1, fin1);
    fread(&w, 4, 1, fin1);
    fread(&h, 4, 1, fin1);
    fread(end, 4, 7, fin1);
    fread(&type2, 2, 1, fin2);
    fread(&size2, 4, 1, fin2);
    fread(&res2, 4, 1, fin2);
    fread(&off2, 4, 1, fin2);
    fread(&ssz2, 4, 1, fin2);
    fread(&w2, 4, 1, fin2);
    fread(&h2, 4, 1, fin2);
    fread(end2, 4, 7, fin2);


     BYTE rastr1[MAX_FILE_SIZE][MAX_FILE_SIZE][3];
     BYTE rastr2[MAX_FILE_SIZE][MAX_FILE_SIZE][3];

    int padding1=(size-off-h*w*3)/h;
    BYTE pad1[30];   
    int padding2=(size2-off2-h2*w2*3)/h2;
    BYTE pad2[30];
    
    for(i=0; i<h ; i++)
    {
	for(j=0; j<w ; j++)
		fread(&rastr1[i][j], 3, 1, fin1);
        fread(pad1, padding1, 1, fin1);        
    }	


    for(i=0; i<h2 ; i++)
    {
	for(j=0; j<w2 ; j++)
		fread(&rastr2[i][j], 3, 1, fin2);
        fread(pad2, padding2, 1, fin2);        
    }


    printf(" razmery: %d %d\n", size , size2);
    


   for(i=0; i<h ; i++)
    {
	for(j=0; j<w ; j++)
        {
		for (z=0; z<3; z++)
                   
                        if (rastr1[i][j][z] != rastr2[i][j][z])	{		
                              chet++;
	          break;  
                   }
                    
 
        }
    }  

    printf(" kolichestvo raznih pixelei: %d\n", chet); 

	
    return 0; 
}

