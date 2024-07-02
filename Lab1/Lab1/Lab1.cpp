#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>

#define ENTER 13 //обозначение кнопок 
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79

using namespace std;
using namespace System;
using namespace System::IO;
struct z {
    char nicname[20]; //модель
    long price; //цена
    char mark[10]; //производитель 
	long year; //год
	char os[12]; //ОС

}; //шаблон структуры для исходных данных 
struct sp {
    char mark[10];
    long price;
    struct sp* sled;
	struct sp* pred;
}; 


int menu(int); //указание шаблонов используемых функций 
void first(struct z*,int NC);
void fir(struct z*,int NC);
void cena(struct z*,int NC);
void alfalist(struct z*,struct sp** spisok,int NC);
void vstavka(struct z*,char*,struct sp** spisok,int NC);
void diagram (struct z*, struct sp** spisok,int NC);
void listing (struct z*,int NC);


int main(array<System::String ^> ^args)
{//на локальном уровне осуществляем открытие файла,
 //считывыем данные из файла в выделенную память



	char dan[8][100] = {
	"Сколько стоит самый дешёвый телефон?                  ",
	"В каком году выпустили самую позднюю модель?          ",
	"Сколько моделей телефонов стоят больше 30000р?        ",
	"Алфавитный список всех фирм.                          ",
	"Диаграмма.                                            ",
	"Телефоны, выпущенные в один год, с одинаковой ОС.     ",
	"Выход                                                 "
	}; //задание списка вопросов - пунктов меню


	struct sp *spisok=nullptr;

	char BlankLine[100] = "                                                        ";


	int NC; //количество позиций 
    BlankLine[100] = 0;
    

    int i, n;
    FILE* in;
    struct z* mobile;
    setlocale(LC_CTYPE, "Russian"); //поддержка русского языка
    Console::CursorVisible::set(false); //отключаем видимость курсора
    Console::BufferHeight = Console::WindowHeight;//установка размера буфера по высоте 
    Console::BufferWidth = Console::WindowWidth; ; //установка размера буфера по ширине
    if ((in = fopen("Phones.txt", "r")) == NULL) //попытка открыть файл
    {
        printf("\nФайл Phones.txt не открыт !"); // при неудачной попытке выводим сообщение “Файл Phones.txt не открыт”
        getch(); exit(1);
    }
    fscanf(in, "%d", &NC);
    mobile = (struct z*)malloc(NC * sizeof(struct z));
    for (i = 0; i < NC; i++)
        fscanf(in, "%s%ld%s%ld%s", mobile[i].nicname,&mobile[i].price, mobile[i].mark,&mobile[i].year,mobile[i].os);
    for (i = 0; i < NC; i++) //выводим данные из списка на экран
        printf("\n%-15s %-7ld %7s %7ld %-7s",mobile[i].nicname,mobile[i].price, mobile[i].mark,mobile[i].year,mobile[i].os);
    getch();
    while (1) //в цикле создаем область для вопросов и окрашиваем её в цвета
               //устанавливаем для букв цвет и подсветку для выбранного вопроса

    {
		Console::ForegroundColor = ConsoleColor::White;
        Console::BackgroundColor = ConsoleColor::DarkGray;
        Console::Clear();
        Console::ForegroundColor = ConsoleColor::DarkGray;
        Console::BackgroundColor = ConsoleColor::White;
        Console::CursorLeft = 10; //первая точка, откуда будем закрашивать область меню
        Console::CursorTop = 4;
        printf(BlankLine);
        for (i = 0; i < 7; i++) //размещение вопросов
        {
            Console::CursorLeft = 10;
            Console::CursorTop = i + 5;
            printf(" %s ", dan[i]);
        }
        Console::CursorLeft = 10;//последняя точка, где будет заканчиваться выделенная область под меню
        Console::CursorTop = 12;
        printf(BlankLine);
        n = menu(7); //выбор вопроса меню
        switch (n) {
        case 1: first (mobile,NC);break;
        case 2: fir (mobile,NC);break;
        case 3: cena (mobile,NC);break;
        case 4: alfalist(mobile,&spisok,NC);break;
        case 5: diagram(mobile,&spisok,NC);break;
        case 6: listing(mobile,NC);break;
        case 7: exit(0);
        }
    } // конец while(1)...

    return 0;
} //конец main()

int menu(int n) //n=9
{

	
	char dan[8][100] = {
	"Сколько стоит самый дешёвый телефон?                  ",
	"В каком году выпустили самую позднюю модель?          ",
	"Сколько моделей телефонов стоят больше 30000р?        ",
	"Алфавитный список всех фирм.                          ",
	"Диаграмма.                                            ",
	"Телефоны, выпущенные в один год, с одинаковой ОС.     ",
	"Выход                                                 "
	}; //задание списка вопросов - пунктов меню


    int y1 = 0, y2 = n - 1; //устанавливаем выделение для строчки
    char c = 1;
    while (c != ESC) // при нажатии ESC, меню закроется
    {
        switch (c) {
        case DOWN: y2 = y1; y1++; break;//программирование кнопки DOWN, которая позволяет перемещаться вниз по меню
        case UP: y2 = y1; y1--; break;//программирование кнопки UP, которая позволяет перемещаться ВВЕРХ по меню
        case ENTER: return y1 + 1;//программирование кнопки ENTER, которая позволяет перемещаться вниз по меню
		case HOME: y2=y1;y1=0;break;
		case END:y2=y1;y1=n-1;break;
        }
        if (y1 > n - 1) { y2 = n - 1; y1 = 0; } //условие,когда срабатывает кнопка DOWN
        if (y1 < 0) { y2 = 0; y1 = n - 1; } //условие,когда срабатывает кнопка UP
        Console::ForegroundColor = ConsoleColor::White; //привыборе вопроса,буквы окрашиваются в белый цвет
        Console::BackgroundColor = ConsoleColor::Red; //привыборе вопроса, план за буквами подсвечивается красным
        Console::CursorLeft = 11;
        Console::CursorTop = y1 + 5;
        printf("%s", dan[y1]);
        Console::ForegroundColor = ConsoleColor::Red;
        Console::BackgroundColor = ConsoleColor::White;
        Console::CursorLeft = 11;
        Console::CursorTop = y2 + 5;
        printf("%s", dan[y2]);
        c = getch();
    } // конец while(c!=ESC)...
    exit(0);
}
// какой телефон самый дешёвый?(функция поиска минимума)
void first(struct z* mobile,int NC)
{
    int i;

    struct z best;
 best.price = mobile[0].price; //в переменную структуры записываем нулевой элемент
 for (i = 1; i < NC; i++)
  if ( mobile[i].price<best.price )// условие поиска минимума
    best.price=mobile[i].price;
 Console::ForegroundColor=ConsoleColor::Blue;
    Console::BackgroundColor=ConsoleColor::White;
 Console::CursorLeft=20;// задаем область, где будет выведен минимум
 Console::CursorTop=20;
 printf("Цена самого дешёвого телефона: %ld", best.price);//вывод минимума
 getch();
}
//функция поиска самого позднего года
void fir(struct z* mobile,int NC)
{
int i;

struct z best;
best.year = mobile[0].year;
for(i=1;i<NC;i++)
if (mobile[i].year>best.year)
best.year=mobile[i].year;
 Console::ForegroundColor=ConsoleColor::Blue;
 Console::BackgroundColor=ConsoleColor::White;
 Console::CursorLeft=20;
 Console::CursorTop=20;
 printf("Год выпуска самой поздней модели: %ld", best.year);
 getch();
}
// количество телефонов, стоимость которых больше 30000
void cena(struct z* mobile,int NC)
{
    int i,k=0;

    struct z best;
 best.price = mobile[0].price;
 for (i = 1; i < NC; i++)
  if ( mobile[i].price>30000 )
    k++;
 Console::ForegroundColor=ConsoleColor::Blue;
    Console::BackgroundColor=ConsoleColor::White;
 Console::CursorLeft=20;
 Console::CursorTop=20;
 printf("Количество телефонов стоимость выше 30000 рублей: %d", k);
 getch();
}
//алфавитный список производителей

void alfalist(struct z* mobile,sp** spisok,int NC)
{
int i;
struct sp* nt,*z=0;
Console::ForegroundColor=ConsoleColor::Black;
Console::BackgroundColor=ConsoleColor::Cyan;
Console::Clear();
if(!*spisok)
 for(i=0;i<NC;i++)
	 vstavka(mobile,mobile[i].mark,spisok,NC);
 
Console::Clear();
printf("\n Алфавитный список владельцев    Обратный алфавитный список");
printf("\n ============================    ===========================\n");
for(nt=*spisok; nt!=0; nt=nt->sled)
printf("\n %-20s",nt->mark);
for(nt=*spisok,z=0; nt!=0; z=nt,nt=nt->sled);
for(nt=z, i = 0; nt!=0; nt=nt->pred, i++ ){
Console::CursorLeft=35;
Console::CursorTop = i + 4;
printf(" %-30s",nt->mark);
}
getch();
}
void vstavka(struct z* mobile , char* mark,sp** spisok,int NC )//вставка в список
{
	int i ;
	struct sp *New,*nt,*z=0;
	for(nt=*spisok; nt!=0 && strcmp(nt->mark,mark)<0;z=nt,nt=nt->sled);
		if(nt && strcmp(nt->mark,mark)==0) 
			return;
	New=(struct sp *) malloc(sizeof(struct sp));
	strcpy(New->mark,mark);
	New->sled=nt;
	New->price=0;
	New->pred=z;
	for( i = 0; i < NC; i++ )	
		if ( strcmp(mobile[i].mark, mark ) == 0 )
		{

			New->price += mobile[i].price;
			

		}
if(!z) *spisok=New;
if(nt) nt->pred=New;
New->sled=nt;
if (z)z->sled=New;
New->pred=z;

return;
}
//диаграмма
void diagram(struct z *mobile,sp** spisok,int NC)//создаем диаграмму
{
	struct sp *nt ;//перемеенная для работы со списком
	int len,i,NColor;//i-для номера строки
	long sum = 0 ;//число-100%
	char str1[20];
	char str2[20];
	System::ConsoleColor Color;//Задаѐт константы, которые определяют основной цвет и цвет фона консоли
	Console::ForegroundColor=ConsoleColor::Black;//цвет символов
	Console::BackgroundColor=ConsoleColor::Gray;//цвет заднего фона
	Console::Clear();




	for(i=0;i<NC;i++) 
		sum = sum+mobile[i].price ;
	if(!*spisok)
		for(i=0;i<NC;i++)
			vstavka(mobile,mobile[i].mark,spisok,NC);//вставляем из списка названия имен и красим символы в чѐрный цвет
	Color=ConsoleColor::Black; NColor=0;
	for(nt=*spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		
		sprintf(str1,"%s",nt->mark);
		sprintf(str2,"%3.1f%%",(nt->price*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for(len=0; len<nt->price*100/sum; len++) 
			printf(" ");
		if(NColor==14){ //выделяем на диаграмму 14 цветов
			Color=ConsoleColor::Black; NColor=0; 
		}
	}
	getch();
	return;
}
void listing(struct z *mobile,int NC)//телефоны, выпущенные в один год и имеющие одну ОС(сложный вопрос)
{
struct z best;
int a=0;
for (int i=0; i<NC;i++){
best.year=mobile[i].year;
strcpy(best.os,mobile[i].os);
for (int g=i+1;g<NC;g++){
	if (best.year == mobile[g].year){
		if (strcmp(best.os,mobile[g].os)==0){
Console::ForegroundColor=ConsoleColor::Blue;
Console::BackgroundColor=ConsoleColor::White;
Console::CursorLeft=20;
Console::CursorTop=20;
printf("%s %s",mobile[i].nicname,mobile[g].nicname);a++;break;
		}
	}
}
if(a>0)break;
}
if(a==0){
	Console::ForegroundColor=ConsoleColor::Blue;
Console::BackgroundColor=ConsoleColor::White;
Console::CursorLeft=20;
Console::CursorTop=20;
printf("совпадений нет");}
getch();
return;
}