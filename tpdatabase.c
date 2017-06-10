/**@authors Илья Андреев
 * @version 0.1
 * @date 18.09.16
 * @warning Данная программа создана только в учебных целях.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file_operations.c"
#include "modif_record.c"
#include "tpdatabase.h"


/**
 * @fn main
 * @brief Главная функция
 * Выводит главное пользовательское меню, принимает ответы и вызывает соответствующие вопросам функции
 * Ничего не принимает, ничего не возвращает
 * @param i - переменная цикла
 * @param а - значение выбора пользователя
 * @param res - переменная для проверки недопустимых вводимых значений
 * @param next - переменная выхода из цикла и программы
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */
int main ()
{	
	int a = 0, next = 1, i, res;
	bool flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
	enum TypeOfOS OS = type_of_os ();
	if (OS == WIN)
		system ("chcp 65001");
	
	while (next)
	{
		clear_screen ();
		printf ("%s\n\n", welcome);
		
		for (i = 0; i < 8; i ++)
			printf ("   %s\n\r", main_menu [i]);
		res = scanf ("%d", &a);
		getchar ();
		if (res != EOF && res > 0)
			switch (a)
			{
				case 1: file (); break;
				case 2: edit_doc (); break;
				case 3:	printf_doc (); break;
				case 4: record_doc (); break;
				case 5: directory (); break;
				case 6: help (); break;
				case 7: about_program (); break;
				case 8:
				{					
					if (save_tele == false ||save_name == false ||save_tariff == false ||save_benefit == false)
					{
						flag_tele = true;
						flag_name = true;
						flag_tariff = true;
						flag_benefit = true;
						warning_save (flag_tele, flag_name, flag_tariff, flag_benefit);
					}
					next = 0;
				}
				default: break;
			}
		else
			getchar ();
	}
	return (0);
}

/**
 * @fn type_of_os
 * @brief Функция для определения типа ОС пользователя
 * Ничего не принимает, возвращает тип определённой ОС
 * @param *fd - указатель на проверяемый специфичный файл
 */
int type_of_os ()
{	
	#ifdef __linux__ 
		return LIN;
	#elif _WIN32
		return WIN;
	#elif __APPLE__
		return MAC;
	#else
		return UNKN;
	#endif
}

/**
 * @fn clear_screen
 * @brief Функция для очистки экрана терминала
 * Ничего не принимает, ничего не возвращает
 */
void clear_screen ()
{
	enum TypeOfOS OS = type_of_os ();
	
	switch (OS)
	{
		case WIN: system ("cls"); break;		
		case LIN: system ("clear"); break;		
		case MAC: system ("clear");	break;
		case UNKN: break;
	}
}

/**
 * @fn reference
 * @brief Функция вывода различных типов справок, выбранных пользователем
 * Принимает тип справки, который она должна вывести
 * Возвращает "0", если всё функции не удалось открыть файл, а в случае успеха возвращает "0"
 * @param *fd - указатель на открываемый файл
 * @param s - строка, в которую построчно считывается данные из файла справки
 * @param start_ref - строка, в которой расположена кодовая фраза начала нужного блока справки в справочнике
 * @param end_ref - строка, в которой расположена кодовая фраза конца нужного блока справки в справочнике
 * @param *temp - временная переменная
 * @param flag - переменная для указания успешности выполнения задачи
 */
int reference (enum TypeOfReference type)
{
	FILE *fd = NULL;
	char s [251], start_ref [50], end_ref [50], *temp;
	bool flag = false;
	
	fd = fopen ("help.txt", "r");
	if (fd == NULL)
	{
		printf ("Ошибка при показе справки. Пожалуйста, проверьте наличие файла \"help.txt\" в текущем каталоге.\n");
		getchar ();
		return 0;
	}
	
	switch (type)
	{
		case general_info:
			strcpy (start_ref, "[start_general_information]");
			strcpy (end_ref, "[end_general_information]");
			break;
		
		case ref_file:
			strcpy (start_ref, "[start_file]");
			strcpy (end_ref, "[end_file]");
			break;
			
		case ref_edit_doc:
			strcpy (start_ref, "[start_edit_doc]");
			strcpy (end_ref, "[end_edit_doc]");
			break;
			
		case ref_printf_doc:
			strcpy (start_ref, "[start_printf_doc]");
			strcpy (end_ref, "[end_printf_doc]");
			break;
			
		case ref_record_doc:
			strcpy (start_ref, "[start_record_doc]");
			strcpy (end_ref, "[end_record_doc]");
			break;
			
		case ref_directory:
			strcpy (start_ref, "[start_directory]");
			strcpy (end_ref, "[end_directory]");
			break;
			
		case ref_about_program:
			strcpy (start_ref, "[start_about_program]");
			strcpy (end_ref, "[end_about_program]");
			break;						
	}
	
	clear_screen ();
	printf ("Справка\n\n");
	
	while (fgets (s, 251, fd))
	{
		if (flag == false)
		{
			temp = strstr (s, start_ref);
			if (temp != NULL)
				flag = true;
		}
		else
		{
			temp = strstr (s, end_ref);
			if (temp == NULL)
				printf ("%s", s);
			else
				fseek (fd, 0, SEEK_END);
		}
	}
	if (type != general_info)
	{
		printf ("\n\nДля возвращения к главному меню справки нажмите Enter: ");
		getchar ();
	}
	fclose (fd);
	return 1;
}

/**
 * @fn file
 * @brief Функция для вывода пользовательского меню "Файл", считывания ответа пользователя и вызова соответствующей функции
 * Ничего не принимает, ничего не возвращает
 * @param i - переменная цикла
 * @param а - значение выбора пользователя
 * @param res - переменная для проверки недопустимых вводимых значений
 * @param next - переменная выхода из цикла и программы
 */
void file ()
{
	int a = 0, next = 1, i, res;
	
	while (next)
	{
		clear_screen ();
		printf ("Файл\n\n");
		for (i = 0; i < 4; i ++)
			printf ("   %s\n\r", file_menu [i]);
		res = scanf ("%d", &a);
		getchar ();
		if (res != EOF && res > 0)
			switch (a)
			{
				case 1:
					open_file (File_Tele);
					getchar ();
					break;
					
				case 2:
					save_file (File_Tele);
					save_file (File_Name);
					save_file (File_Tariff);
					if (third_dir == true)
						save_file (File_Benefit);
					getchar ();
					break;
					
				case 3:
					close_file (File_Tele);
					getchar ();
					break;
				case 4: next = 0;
				default: break;
			}
		else
			getchar ();
	}
}

/**
 * @fn edit_doc
 * @brief Функция для вывода пользовательского меню "Редактировать документ", считывания ответа пользователя и вызова соответствующей функции
 * Ничего не принимает, ничего не возвращает
 * @param i - переменная цикла
 * @param а - значение выбора пользователя
 * @param res - переменная для проверки недопустимых вводимых значений
 * @param next - переменная выхода из цикла и программы
 */
void edit_doc ()
{
	int i, a = 0, next = 1, res;
	
	while (next)
	{
		clear_screen ();
		printf ("Редактировать документ\n\n");
		for (i = 0; i < 4; i ++)
		printf ("   %s\n\r", edit_doc_menu [i]);
		res = scanf ("%d", &a);
		getchar ();
		if (res != EOF && res > 0)
			switch (a)
			{
				case 1:
					add_record (File_Tele);
					break;	
				case 2:
					remove_record (File_Tele);
					break;
				case 3: 
					edit_record (File_Tele);
					break;
				case 4: next = 0;
				default: break;
			}
		else
			getchar ();
	}
}

/**
 * @fn printf_doc
 * @brief функция для вызова функции "printf_doc"
 * Ничего не принимает, ничего не возвращает, ничего не делает
 */
void printf_doc ()
{
	printf_file (File_Tele);
	getchar ();
}

/**
 * @fn record_doc
 * @brief Функция для записи документа в файл txt
 * Записывает все данные из открытых справочников в файл, название которого пользователь должен ввести
 * Ничего не принимает, ничего не возвращает
 * @param *fd - указатель на файл
 * @param i - переменная цикла
 * @param res - переменная, в которую передаётся возвращение функции "insp_file"
 * @param int_answer, answer - ответы пользователей на вопросы открытия файлов
 * @param name_txt - имя нового файла, в который будет записан документ
 * @param *temp - временная переменная
 */
void record_doc ()
{
	FILE* fd = NULL;
	int i, res, int_answer;
	char name_txt [40];
	bool flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
	flag_tele = true;
	flag_name = true;
	flag_tariff = true;
	if (third_dir == true)
		flag_benefit = true;
	res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
	if (res == 0)
		return;
	printf ("Введите название файла, в который вы бы хотели записать документ: ");
	scanf ("%s", name_txt);
	getchar ();
	fd = fopen (name_txt, "r");
	if (fd != NULL)
	{
		printf ("Внимание, файл \"%s\" уже существует.\nВы уверены, что хотите перезаписать его? Да (1), Назад (0): ", name_txt);
		scanf ("%d", &int_answer);
		getchar ();
		fclose (fd);
		if (int_answer != 1)
			return;
	}
	else
	{
		fd = fopen (name_txt, "w");
		if (fd != NULL)
			printf ("Файл \"%s\" успешно создан.\n", name_txt);
		else
		{
			printf ("Ошибка, файл \"%s\" создан не был.\n", name_txt);
			getchar ();
			return;
		}
		getchar ();
	}
			
	if (third_dir == false)
		for (i = 0; i < NC_tele; i ++)
			if (sub [i].del_tele == true)
				fprintf (fd, "%d;%d;%s;%s;%s;\n", sub [i].id_tele, sub [i].phone_number, sub [i].name.str, sub [i].tariff.str, sub [i].address);
	if (third_dir == true)
		for (i = 0; i < NC_tele; i ++)
			if (sub [i].del_tele == true)
				fprintf (fd, "%d;%d;%s;%s;%s;%s;\n", sub [i].id_tele, sub [i].phone_number, sub [i].name.str, sub [i].tariff.str, sub [i].address, sub [i].benefit.str);
		
	fflush (fd);
	if (fd >= 0)
		printf ("Запись документа в файл \"%s\" прошла успешно.\n", name_txt);
	else
		printf ("При записи документа в файл \"%s\" произошла ошибка.\n", name_txt);
	getchar ();
}

/**
 * @fn directory
 * @brief Функция для вывода пользовательского меню "Справочник", считывания ответа пользователя и вызова соответствующей фунции
 * Ничего не принимает, ничего не возвращает
 * @param i - переменная цикла
 * @param а - значение выбора пользователя
 * @param res - переменная для проверки недопустимых вводимых значений
 * @param next - переменная выхода из цикла и программы
 * @param name_of_dir - имя справочника, который пользователь выберет
 */
void directory ()
{
	int i, a, res, next = 1;
	char name_of_dir [40];
	
	while (next)
	{
		clear_screen ();
		printf ("Справочник\n\n");
		for (i = 0; i < 8; i ++)
		printf ("   %s\n\r", directory_menu [i]);
		res = scanf ("%d", &a);
		getchar ();
		if (res != EOF && res > 0)
			switch (a)
			{
				case 1:
					printf ("Введите имя открываемого справочника: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (strcmp (name_of_dir, "name.db") == 0)
						open_file (File_Name);
					else if (strcmp(name_of_dir, "tariff.db") == 0)
							open_file (File_Tariff);
						else if (strcmp(name_of_dir, "benefit.db") == 0 && third_dir == true)
								open_file (File_Benefit);
							else
							{
								printf ("Справочник \"%s\" не существует или не добавлен в программу.\n", name_of_dir);
								getchar ();
							}
					getchar ();
					break;
					
				case 2:
					printf ("Введите название справочника, запись которого вы хотели бы изменить: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (strcmp (name_of_dir, "name.db") == 0)
						edit_record (File_Name);
					else if (strcmp (name_of_dir, "tariff.db") == 0)
							edit_record (File_Tariff);
						else if (strcmp (name_of_dir, "benefit.db") == 0 && third_dir == true)
								edit_record (File_Benefit);						
							else
							{
								printf ("Ошибка, справочник \"%s\" не существует или не добавлен в программу.", name_of_dir);
								getchar ();
							}
					break;
				
				case 3:
					printf ("Введите название справочника, в который вы хотели бы добавить запись: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (strcmp (name_of_dir, "name.db") == 0)
						add_record (File_Name);
					else if (strcmp (name_of_dir, "tariff.db") == 0)
							add_record (File_Tariff);
						else if (strcmp (name_of_dir, "benefit.db") == 0 && third_dir == true)
								add_record (File_Benefit);							
						else
						{
							printf ("Ошибка, справочник \"%s\" не существует или не добавлен в программу.", name_of_dir);
							getchar ();
						}
					break;
					
				case 4:
					printf ("Введите название справочника, запись которого вы хотели бы удалить: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (strcmp (name_of_dir, "name.db") == 0)
						remove_record (File_Name);
					else if (strcmp (name_of_dir, "tariff.db") == 0)
							remove_record (File_Tariff);
						else if (strcmp (name_of_dir, "benefit.db") == 0 && third_dir == true)
								remove_record (File_Benefit);
							else
							{
								printf ("Ошибка, справочник \"%s\" не существует или не добавлен в программу.", name_of_dir);
								getchar ();
							}
					break;
				
				case 5:
					printf ("Введите имя закрываемого справочника: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (strcmp (name_of_dir, "name.db") == 0)
					{
						close_file (File_Name);
						getchar ();
					}
					else if (strcmp(name_of_dir, "tariff.db") == 0)
						{
							close_file (File_Tariff);
							getchar ();
						}
					else if (strcmp(name_of_dir, "benefit.db") == 0 && third_dir == true)
						{
							close_file (File_Benefit);
							getchar ();
						}
						else
						{
							printf ("Справочник \"%s\" не существует или не добавлен в программу.\n", name_of_dir);
							getchar ();
						}
					break;
				
				case 6:
				{
					printf ("Введите имя добавляемого справочника: ");
					scanf ("%s", name_of_dir);
					getchar ();
					if (third_dir == true)
					{
						printf ("Ошибка, справочник \"%s\" уже добавлен в программу.", name_of_dir);						
						getchar ();
						break;
					}
					if (strcmp (name_of_dir, "benefit.db") == 0)
					{
						third_dir = true;
						printf ("Справочник \"%s\" успешно добавлен.", name_of_dir);
						getchar ();
					}
					else
					{
						printf ("Ошибка, справочник \"%s\" в каталоге \"/home/ilya/projects/tpdatabase/\" не найден.\n", name_of_dir);
						getchar ();
					}
					break;					
				}
				case 7:
				{
					printf_file (File_Name);
					getchar ();
					printf_file (File_Tariff);
					getchar ();
					if (third_dir == true)
						printf_file (File_Benefit);
					getchar ();
					break;
				}
				case 8:	next = 0;
				default: break;
			}
		else
			getchar ();
	}	
}

/**
 * @fn help
 * @brief Функция для вывода главного меню "Справка", а также справки других пунктов, выбранных пользователем
 * Считывает ответ пользователя и вызывает соответствующую фунцию
 * Ничего не принимает, ничего не возвращает
 * @param а - значение выбора пользователя
 * @param res - переменная для проверки недопустимых вводимых значений
 * @param next - переменная выхода из цикла
 * @param temp_int - временная переменная
 */
void help ()
{
	int a = 0, next = 1, res, temp_int;	
	
	while (next)
	{
		res = reference (general_info);
		if (res == 0)
			return;
		
		temp_int = scanf ("%d", &a);
		getchar ();
		if (temp_int != EOF && res > 0)
			switch (a)
			{
				case 1: reference (ref_file); break;				
				case 2: reference (ref_edit_doc); break;
				case 3: reference (ref_printf_doc); break;					
				case 4: reference (ref_record_doc); break;
				case 5: reference (ref_directory); break;
				case 6: reference (ref_about_program); break;
				case 7: next = 0;				
			}
	}
}

/**
 * @fn about_program
 * @brief Функция для вывода информации о программе из файла
 * Ничего не принимает, ничего не возвращает
 * @param *fd - указатель на открываемый файл
 * @param s - строка, в которую построчно считывается данные из файла справки
 */
void about_program ()
{
	FILE *fd = NULL;
	char s [200], *temp;
	bool flag = false;	
	
	fd = fopen ("about_program.txt", "r");
	if (fd == NULL)
	{
		printf ("Ошибка при показе информации о программе. Пожалуйста, проверьте наличие файла \"about_program.txt\" в текущем каталоге.\n");
		getchar ();
		return;
	}
	fseek (fd, 0, SEEK_SET);
	
	enum TypeOfOS OS = type_of_os ();		
	while (fgets (s, 200, fd))
	{
		if (flag == false)
		{
			temp = strstr (s, "[start_version]");
			if (temp != NULL)
			{
				fgets (s, 200, fd);
				temp = strtok (s, "|");
				printf ("%s", temp);
				switch (OS)
				{
					case WIN: printf ("Windows"); break;
					case LIN: printf ("Linux"); break;
					case MAC: printf ("Mac OS X"); break;
					case UNKN: printf ("(Операционная система не определена)");
				}
				fgets (s, 200, fd);
				printf ("\n");
				flag = true;
			}
			else
				printf ("%s", s);
		}
		else
			printf ("%s", s);
	}
	fclose (fd);
	getchar ();	
}
