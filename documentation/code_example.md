### Пример оформления кода согласно код-стайлу и функциональному стилю.
<hr>

    #include <stdio.h>
    #include <stdlib.h>


    file *openFile (char *fileName, char *openAction) 
    /* 
	Функция принимает строку, содержащую имя файла и строку наименования действия, производимого над
	файлом(чтение("r")/запись("w"));
	    
	Создает указатель на файл;
	Открывает файл;
	Возвращает указатель на файл; 
    */
    {
	    file *inputFile = fopen(fileName, openAction);
	    return inputFile;
    }
     
     
    int checkLength(int arrayLength)
    /* 
        Функция проверки длины массива на корректность.
        1 - длина корректна(>0); 
        0 - длина некорректна(<=0).
    */
    {
        if (arrayLength > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }


    int arrayLengthInput()
    /*
        Функция ввода длины массива.
    */
    {
        int arrayLength;

        printf("Enter the length of the array:");
        scanf("%d", &arrayLength);
        printf("\n");

        return arrayLength;
    }


    int dataInput()
    /*
        Функция ввода данных в динамический массив.
    */
    {
        int *arrayData = NULL;
        int arrayLength = arrayLengthInput();
        int currentValue = 0;

        arrayData = (int*)malloc(arrayLength * sizeof(int));

        if (checkLength(arrayLength))
        {
            while(currentValue != arrayLength)
            {
                printf("arrayData[%d/%d]:", currentValue+1, arrayLength);
                scanf("%d", &arrayData[currentValue]);
                printf("\n");

                currentValue++;
            }
            printf("Complete!\n");
        }
        else
        {
            printf("Error checking the length of the array.\n");
        }

        free(arrayData);

        return 0;
    }


    int main()
    {
        printf("\n");
        dataInput();
        return 0;
    }

<hr>
