### Занятие 3

**Тема**: Разработка динамически подключаемых библиотек и приложений, их использующих.

**Задачи**: 
1.&nbsp;Экспорт/импорт ресурсов

**Результат**: Решение, которое включает проекты:
1.&nbsp;DLL и клиент для Задачи 1;
2.&nbsp;StrTableContainer и ClientStrTable для Задачи 2;
3.&nbsp;DLL и клиент для Домашнего задания.

**Описание**:

1.&nbsp;Создать DLL-модуль (Empty Project), который экспортирует только ресурс String Table (три строки).

При создании DLL установить опцию компоновщика:
/NOENTRY
>This option is required for creating a resource-only DLL.
Use this option to prevent LINK from linking a reference to _main into the DLL.
DLL.Properties->Configuration Properties->Linker->Advanced->No Entry Point

2.&nbsp;Создать EXE-модуль, который использует явное связывание с DLL-модулем следующим образом:
EXE-модуль – Win32 Project; Application Settings=Windows Application;
Добавить в главное меню подменю «Strings» с тремя  пунктами для выбора строк из библиотеки;
Написать обработчики пунктов меню: обработчик отображает строку с соответствующим идентификатором (MessageBox).

Добавить в проект и подключить заголовочный файл с идентификаторами ресурсов DLL.
Третий параметр функции LoadLibraryEx – флаг LOAD_LIBRARY_AS_DATAFILE.
API-функция LoadString(…) для извлечения строки из библиотеки.

3.&nbsp;Построить map-файлы для различных DLL-модулей (экспортирующих данные, функции, ресурсы). 

DLL.Properties->Configuration Properties->Linker ->Debugging->Generate Map File.

map-файл
A mapfile is a text file that contains the following information about the program being linked: 
The module name, which is the base name of the file
The timestamp from the program file header (not from the file system)
A list of groups in the program, with each group’s start address (as section:offset), length, group name, and class
A list of public symbols, with each address (as section:offset), symbol name, flat address, and .OBJ file where the symbol is defined
The entry point (as section:offset) 
To find this option in the development environment, click Settings on the Project menu. Then click the Link tab, and click Debug in the Category box. 