// Консольное приложение, C++
// Process2.cpp: определяет точку входа для консольного приложения.
// https://msdn.microsoft.com/en-us/library/ms682512(VS.85).aspx
/*
Процесс #2, Ниже приведен код для дочернего процесса.
Приложение создает/открывает текстовый файл test2.txt, используя фукуцию CreateFile()
В текстовый файл записывается строка “new text (Process 2)” используя фукуцию sprintf_s();
*/

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

HANDLE hFile;

TCHAR fileName[256] = TEXT("test2.txt");
TCHAR szName[] = TEXT("TEST 2 - MyFileMappingObject");

HANDLE hMemFile;
char *lpData;

int main() {

	// открываем существующий файл
	hFile = CreateFile(

		// имя файла
		fileName,

		// режим доступа - чтение-запись
		GENERIC_READ | GENERIC_WRITE,

		// совместный доступ (0 - нет)
		0,

		// описатель (дескриптор) защиты (NULL по-умолчанию)
		NULL,

		// как действовать - открывать (или создавать CREATE_NEW)
		OPEN_ALWAYS,

		// атрибуты файла
		FILE_ATTRIBUTE_NORMAL,

		// описатель (дескриптор) шаблона файла
		NULL
	);

	// Узнать подробности об ошибке можно с помощью GetLastError().
	if (hFile == INVALID_HANDLE_VALUE) {
		printf("ERROR %x \n", GetLastError());
		return 1;
	}

	// инициализирует структуру SECURITY_ATTRIBUTES, указывая, что объект следует создать 
	// с защитой по умолчанию и что возвращаемый описатель должен быть наследуемым
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	// делаем возвращаемый описатель наследуемым 
	sa.bInheritHandle = TRUE;
	//sa.bInheritHandle = FALSE;

	// создаем объект "проекция файла", связанный с файлом данных
	hMemFile = CreateFileMapping(

		// описатель (дескриптор) отображаемого файла
		hFile,

		// необязательные атрибуты безопасности (SECURITY_ATTRIBUTES - NULL по-умолчанию)
		&sa,

		// защита для объекта отображения
		PAGE_READWRITE,

		// старшие бит размера объекта
		0,

		// младшие бит размера объекта
		1024,

		//имя объекта отображения
		szName
	);

	// Узнать подробности об ошибке можно с помощью GetLastError().
	if (hMemFile == NULL) {
		printf("Could not create file mapping object (%d).\n"), GetLastError();
		return 1;
	}

	// проецируем представление всего файла на наше адресное пространство
	// чтобы использовать отображаемые файлы
	lpData = (char *)MapViewOfFile(

		// описатель (дескриптор) объекта проецируемый файл
		hMemFile,

		// режим доступа
		FILE_MAP_ALL_ACCESS,

		// старшие 32 разряда смещения в файле
		0,

		// младшие 32 разряда смещения в файле
		0,

		// количество отображаемых байт
		1024
	);

	// вывод содержимого файла на экран 
	printf("(Process 2) has been created \n");
	printf("%s Process2 Console\n", lpData);

	// изменение содержимого файла, записав строку «new text (Process 2)»
	// начиная с 10-го символа с новой строки, 160 - размер буфера
	sprintf_s(lpData + 10, 160, "\n new text (Process 2)");

	// функция ждёт нажатия ENTER
	//getwchar();

	// снятие отображения содержимого файла
	//UnmapViewOfFile(lpData);

	// закрытие открытых описателей (дескрипторов)
	//CloseHandle(hFile);
	//CloseHandle(hMemFile);

	return 0;
}