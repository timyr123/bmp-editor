### Пример оформления кода согласно код-стайлу и функциональному стилю.

'''C
#include <stdio.h>
#include <stdlib.h>


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
'''
