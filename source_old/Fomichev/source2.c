/* Подключение заголовочных файлов */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define BMP_TYPE 0x4D42  /* Типа файла BMP */

/* Заголовок BMP файла */
/* https://ru.wikipedia.org/wiki/BMP */
struct bmp_header_s
{
 uint16_t type;   /* Тип файла */
 uint32_t size;   /* Размер */
 uint16_t __rsvd1;  /* Резервное поле (0) */
 uint16_t __rsvd2;  /* Резервное поле (0) */
 uint32_t offset;  /* Смещение от начала до данных изображения */

 uint32_t version;  /* Версия формата BMP */
 uint32_t width;   /* Ширина изображения в пикселах */
 uint32_t height;  /* Высота изображения в пикселах */
 uint16_t planes;  /* Для BMP должно быт 1 */
 uint16_t bitspp;  /* Количесво бит на пиксел */
 uint16_t compress;  /* Способ хранения пикселов */
}
__attribute__((packed)); /* Упаковка структуры (запрет выравнивания) */

/* Получения кода пиксела в зависимости от глубины цвета */
/* color - указатель на пиксел */
/* bytespp - глубина цвета в байтах (1, 2, 3, 4) */
uint32_t get_color(const void *color, int bytespp)
{
 /* Рассчитанный код цвета */
 uint32_t c;

 /* Для глубины 1, 2 и 4 просто считывается код по указателю нужного типа */
 switch ( bytespp )
 {
  case 1:
   c = *(uint8_t *)color;
   break;
  case 2:
   c = *(uint16_t *)color;
   break;
  case 4:
   c = *(uint32_t *)color;
   break;

  /* Для глубины 3 вычитывается сначала старший байт, сдвигается на 16 влево,
   затем объединяется со старшими 16 битами */
  case 3:
  default:
   c = *(((uint8_t *)color + 2));
   c «= 16;
   c |= *(uint16_t *)color;
   break;
 }

 /* Возвращается код цвета */
 return c;
}

/* Вспомогательная функция сортировки для сравнения двух кодов цветов */
/* col1, col2 - указатели на два сравнимаемых цвета */
/* bytespp - глубина цвета в байтах (1, 2, 3, 4) */
int compar(const void *col1, const void *col2, void *bytespp)
{
 /* Определение кодов цветов */
 uint32_t a = get_color(col1, *(int *)bytespp);
 uint32_t b = get_color(col2, *(int *)bytespp);

 /* Возврат результатов сравнения кодов */
 if ( a < b )
  return -1;
 if ( a > b )
  return 1;
 return 0;
}

/* Функция вывода кода цвета и его площади */
/* color - код цвета */
/* bytespp - глубина цвета в байтах (1, 2, 3, 4) */
/* rate — коеффициент площади (площадь одного пиксела) */
void print_color(uint32_t color, int bytespp, double rate)
{
 /* Выводится код цвета с выравниваем до нужной ширины (в зависимости от глубины) */
 printf((bytespp > 2 ? (bytespp > 3 ? "%08X: %f\n" : "%06X: %f\n") : (bytespp > 0 ? "%04X: %f\n" : "%02X: %f\n")), color, rate);
}

/* Функция вывода кодов цвете и их площади */
/* img - указатель на область памяти с изображением (массив пикселов) */
/* img_size - размер области памяти с изображением в байтах */
/* bytespp - глубина цвета в байтах (1, 2, 3, 4) */
/* rate — коеффициент площади (площадь одного пиксела) */
void print(uint8_t *img, size_t img_size, int bytespp, double rate)
{
 int c = 1;   /* Количество одинаковых пикселов подряд (считаем, что минимум 1) */
 uint32_t curr;  /* Код цвета текущего пиксела */
 uint32_t next;  /* Код цвета следующего пиксела */

 /* Определение код текущего пиксела (первого) */
 curr = get_color(img, bytespp);
 /* Цикл по всему изображению (по каждому пикселу) */
 for ( size_t i = 0; i < img_size; i += bytespp )
 {
  /* Если это не последний пиксел, то определяем код цвета следующего */
  if ( i + bytespp <= img_size )
   next = get_color(img + i + bytespp, bytespp);
  /* Если пиксел последний, то записываем в следующий отличный код (для вывода на экран) */
  else
   next = curr + 1;

  /* Если коды текущего и следующего пикселей различны */
  if ( next != curr )
  {
   /* Вывод кода пиксела и площади */
   print_color(curr, bytespp, (double)c * rate);
   /* Запись кода следующего пиксела в текущий */
   curr = next;
   /* Сброс количества одинаковых пикселов (будет равен 1 после строки c++) */
   c = 0;
  }

  /* Увеличение количества одинаковых пикселов */
  c++;
 }
}

/* Главная функция программы (начало программы) */
/* argc - количество аргументов командной строки */
/* argv - массив аргументов командной строки*/
int main(int argc, char *argv[])
{
 uint8_t *img;  /* img - указатель на область памяти с изображением (массив пикселов) */
 size_t img_size; /* img_size - размер области памяти с изображением в байтах */
 int bytespp;  /* bytespp - глубина цвета в байтах (1, 2, 3, 4) */

 char *filename;  /* Имя фвйла с изображением BMP */
 FILE *pf;   /* Указатель на файл */

 double width, height;  /* Размер изображения в метрах */
 struct bmp_header_s hdr; /* Заголовок изображения BMP */

 /* Если программа запущена без параметров (первый аргкмент - имя программы) */
 if ( argc == 1 )
 {
  /* Вывод формата запуска программы */
  printf("Usage: %s filename width height\n", argv[0]);
  /* Завершение работы программы (успешное) */
  exit(EXIT_SUCCESS);
 }

 /* Если указано мало аргументов */
 if ( argc < 4 )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Missing argument!\n");
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Сохранение аргументов командной строки */
 filename = argv[1];   /* Имя файла BMP */
 width = atof(argv[2]);  /* Ширина изображения в метрах (перевод строки в тип float) */
 height = atof(argv[3]);  /* Высота изображения в метрах (перевод строки в тип float) */

 /* Проверка корректности ширины и высоты (не должны быть меньше или равны 0) */
 if ( (width <= 0) || (height <= 0) )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Incorrect width (%f) or/and height (%f)\n", width, height);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Открытие файла на чтение, если указатель равен NULL, то */
 if ( (pf = fopen(filename, "r")) == NULL )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("open()");
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Чтение заголовка изображения, если не удалось прочитать, то */
 if ( fread(&hdr, sizeof(hdr), 1, pf) != 1 )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("fread()");
  /* Закрытие файла */
  fclose(pf);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Закрытие файла */
 fclose(pf);

 /* Проверка типа файла, если неправильный, то */
 if ( (hdr.type != BMP_TYPE) || (hdr.planes != 1) )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Not a BMP file!\n");
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Проверка версии заголовка BMP, если не поддерживается, то */
 if ( (hdr.version != 40) && (hdr.version != 108) && (hdr.version != 124) )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Unsupported BMP version: %u\n", hdr.version);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Проверка формата пиксела (глубины цвета), если не поддерживается, то */
 if ( (hdr.bitspp != 8) && (hdr.bitspp != 16) && (hdr.bitspp != 24) && (hdr.bitspp != 32) )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Unsupported bits per pixel: %u\n", hdr.bitspp);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Проверка способа хранения пкселов, если не поддерживается, то */
 if ( hdr.compress != 0 )
 {
  /* Вывод сообщения об ошибке */
  fprintf(stderr, "Unsupported compression: %u\n", hdr.compress);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Пересчёт глубины цвета в битах в глубину цвета в байтах */
 bytespp = hdr.bitspp / 8;
 /* Рассчёт размера области памяти для хранения пикселов изображения (в байтах) */
 img_size = hdr.width * hdr.height * bytespp;

 /* Выделение памяти для изображения */
 if ( (img = malloc(img_size)) == NULL )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("malloc()");
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Открытие файла на чтение, если указатель равен NULL, то */
 if ( (pf = fopen(filename, "r")) == NULL )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("open()");
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Перемещение позиции чтения в файле на начало данных изображения */
 if ( fseek(pf, hdr.offset, SEEK_SET) < 0 )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("fseek()");
  /* Закрытие файла */
  fclose(pf);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Чтение изображения в память */
 if ( fread(img, img_size, 1, pf) != 1 )
 {
  /* Вывод сообщения об ошибке (имя функции и текст ошибки) */
  perror("fread()");
  /* Закрытие файла */
  fclose(pf);
  /* Завершение работы программы (аварийное) */
  exit(EXIT_FAILURE);
 }

 /* Закрытие файла */
 fclose(pf);

 /* Сортировка пикселей изображения */
 qsort_r(img, hdr.width * hdr.height, bytespp, compar, &bytespp);

 /* Вывод кодов пикселей и их площади */
 print(img, img_size, bytespp, width / (double)hdr.width * height / (double)hdr.height);

 /* Высвобождение памяти изображения */
 free(img);

 /* Завершение работы программы (успешное) */
 return EXIT_SUCCESS;
}
