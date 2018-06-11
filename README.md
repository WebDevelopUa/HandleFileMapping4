# HandleFileMapping4
#### Консольное приложение, C++

*HandleFileMapping4.cpp* определяет точку входа для консольного приложения.

Приложение позволяет дочернему процессу наследовать дескрипторы из родительского процесса, передавая **TRUE** параметру **bInheritsHandles**.

*Process2.cpp*: определяет точку входа для консольного приложения.
 
**Процесс #2**

Приложение создает/открывает текстовый файл *test2.txt*, используя фукуцию **CreateFile()**.
В текстовый файл записывается строка **“new text (Process 2)”** используя фукуцию **sprintf_s()**;


***

#### Console application, C ++

*HandleFileMapping4.cpp*: Specifies the entry point for the console application.

The application allows the child process to inherit descriptors from the parent process, passing **TRUE** to the **bInheritsHandles** parameter.

*Process2.cpp*: Specifies the entry point for the console application.
 
 
**Process #2**

The application creates/opens a text file *test2.txt*, using the function **CreateFile()**.
The text **“new text (Process 2)”** is written to the text file using the function **sprintf_s()**;
