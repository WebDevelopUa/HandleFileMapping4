// Консольное приложение, C++
// https://wiki.sei.cmu.edu/confluence/display/c/WIN02-C.+Restrict+privileges+when+spawning+child+processes
// https://msdn.microsoft.com/en-us/library/ms682512(VS.85).aspx
// https://msdn.microsoft.com/en-us/library/ms682499(v=vs.85).aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx
/** HandleFileMapping4.cpp: определяет точку входа для консольного приложения.

Приложение позволяет дочернему процессу наследовать дескрипторы из родительского процесса,
передавая TRUE параметру bInheritsHandles.

*/
#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

void main(void) {

	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);

	if (CreateProcess(
		TEXT("C:\\Windows\\Notepad.exe"),
		NULL,
		NULL,
		NULL,
		TRUE, //FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {


		printf("Process (Notepad) has been created \n");

		CreateProcess(

			// имя исполняемого модуля
			TEXT("Process2.exe"),

			// Командная строка, передаваемая этому процессу
			NULL,

			// Указатель на структуру SECURITY_ATTRIBUTES процесса
			NULL,

			// Указатель на структуру SECURITY_ATTRIBUTES потока
			NULL,

			// Флаг наследования текущего процесса
			TRUE,

			// Флаги способов создания процесса
			0,

			// Указатель на блок среды
			NULL,

			// Текущий диск или каталог
			NULL,

			// Указатель на структуру STARTUPINFO
			&si,

			// Указатель на структуру PROCESS_INFORMATION
			&pi
		);


		// функция ждёт нажатия ENTER
		getwchar();

		// дождитесь завершения дочернего процесса
		WaitForSingleObject(pi.hProcess, INFINITE);

		// закройте процесс и обработчики потоков
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
}