#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tpdatabase.h"
#include "file_operations.h"

/**
 * @fn open_file
 * @brief Функция для открытия файла и его отправку на дальнейшее чтение
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param **fd - указатель на указатель на открываемый файл
 * @param *file_name - указатель на имя файла
 * @param flag - переменная для указания успешности выполнения задачи
 */ 
void open_file (enum TypeOfFile type)
{	
	FILE** fd = NULL;
	char* file_name;
	bool flag = false;
	
	switch (type)
	{
		case File_Tele:
			file_name = "tele.db";
			fd = &files.tele;
			break;
		
		case File_Name:
			file_name = "name.db";
			fd = &files.name;
			break;
			
		case File_Tariff:
			file_name = "tariff.db";
			fd = &files.tariff;
			break;
			
		case File_Benefit:
			file_name = "benefit.db";
			fd = &files.benefit;
			break;
	}
	
	if (fd != NULL)
	{
		if (*fd == NULL)
		{
			*fd = fopen (file_name, "r+");
			if (*fd != NULL)
			{
				printf("Файл \"%s\" успешно открыт.\n", file_name);
				flag = true;
			}				
			else
				printf ("Ошибка при открытии файла %s\n", file_name);
		}
		else
			printf("Файл \"%s\" уже был открыт!\n", file_name);
	}
	
///В этом блоке кода идёт отправка открываемого файла на чтение	
	if (flag == true)
		switch (type)
		{
			case File_Tele: read_file (File_Tele); break;	
			case File_Name: read_file (File_Name); break;				
			case File_Tariff: read_file (File_Tariff); break;
			case File_Benefit: read_file (File_Benefit); break;
		}
}

/**
 * @fn read_file
 * @brief Функция для считывания данных с файла в структуру и создания указателей
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param i, j - переменные цикла
 * @param s - переменная, в которую считывается строчка
 * @param *temp - переменная-указатель для поиска ";"
 * @param flag - переменная для указания успешности выполнения задачи
 */ 
void read_file (enum TypeOfFile type)
{
	int i = 0, j;
	char s [201];
	char *temp;
	bool flag = false;
	
	switch (type)
	{		
		case File_Tele:
			while (fgets (s, 200, files.tele))
				NC_tele ++;
			NC_tele_max = NC_tele;
			sub = (struct Tele*) malloc (NC_tele * sizeof (struct Tele));
			fseek (files.tele, 0, SEEK_SET);
			
			while (fgets (s, 200, files.tele))
			{
				temp = strtok (s, ";");
				sub [i].id_tele = atoi (temp);
				temp = strtok (NULL, ";");
				sub [i].phone_number = atoi (temp);
				temp = strtok (NULL, ";");		
				sub [i].name.id = atoi (temp);
				temp = strtok (NULL, ";");
				sub [i].tariff.id = atoi (temp);
				temp = strtok (NULL, ";");
				strcpy (sub [i].address, temp);
				temp = strtok (NULL, ";");
				sub [i].benefit.id = atoi (temp);
				sub [i].del_tele = true;
				i ++;
			}
			i = 0;
			break;
			
		case File_Name:
			while (fgets (s, 200, files.name))
				NC_name ++;
			NC_name_max = NC_name;
			fio = (struct Name*) malloc (NC_name * sizeof (struct Name));
			fseek (files.name, 0, SEEK_SET);
			while (fgets (s, 200, files.name))
			{
				temp = strtok (s, ";");
				fio [i].id_name = atoi (temp);
				temp = strtok (NULL, ";");
				strcpy (fio [i].name, temp);
				fio [i].del_name = true;	
				i ++;
			}
			i = 0;
			break;
			
		case File_Tariff:
			while (fgets (s, 200, files.tariff))
				NC_tariff ++;
			NC_tariff_max = NC_tariff;
			rate = (struct Tariff*) malloc (NC_tariff * sizeof (struct Tariff));
			fseek (files.tariff, 0, SEEK_SET);
			while (fgets (s, 200, files.tariff))
			{
				temp = strtok (s, ";");
				rate [i].id_tariff = atoi (temp);
				temp = strtok (NULL, ";");
				strcpy (rate [i].tariff, temp);
				rate [i].del_tariff = true;
				i ++;				
			}
			break;
		
		case File_Benefit:
			while (fgets (s, 200, files.benefit))
				NC_benefit ++;
			NC_benefit_max = NC_benefit;
			priv = (struct Benefit*) malloc (NC_benefit * sizeof (struct Benefit));
			fseek (files.benefit, 0, SEEK_SET);
			while (fgets (s, 200, files.benefit))
			{
				temp = strtok (s, ";");
				priv [i].id_benefit = atoi (temp);
				temp = strtok (NULL, ";");
				strcpy (priv [i].benefit, temp);
				priv [i].del_benefit = true;
				i ++;				
			}
			break;
	}
	
/// В следущем блоке кода мы в документе создаём указатели на записи в справочниках	
	if (files.tele != NULL && files.name != NULL)
		for (i = 0; i < NC_tele; i ++)
			for (j = 0; j < NC_name; j ++)
			{
				if (sub [i].name.id == fio [j].id_name)
				{
					sub [i].name.str = fio [j].name;
					flag = true;
					break;
				}
				if (flag == false)
					sub [i].name.str = no_data;
			}
	
	if (files.tele != NULL && files.tariff != NULL)
		for (i = 0; i < NC_tele; i ++)
			for (j = 0; j < NC_tariff; j ++)
			{
				if (sub [i].tariff.id == rate [j].id_tariff)
				{
					sub [i].tariff.str = rate [j].tariff;
					break;
				}
				if (flag == false)
					sub [i].tariff.str = no_data;
			}
				
	if (files.tele != NULL && files.benefit != NULL)
		for (i = 0; i < NC_tele; i ++)
			for (j = 0; j < NC_benefit; j ++)
			{
				if (sub [i].benefit.id == priv [j].id_benefit)
				{
					sub [i].benefit.str = priv [j].benefit;
					break;
				}
				if (flag == false)
					sub [i].benefit.str = no_data;
			}
}

/**
 * @fn printf_file
 * @brief Функция для вывода документа на экран
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param i - переменная цикла
 * @param res - переменная, в которую передаётся возвращение функции "insp_file"
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */
void printf_file (enum TypeOfFile type)
{
	int i, res;
	bool flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;	
	
	switch (type)
	{
		case File_Tele:
		{
			flag_tele = true;
			flag_name = true;
			flag_tariff = true;
			if (third_dir == true)
				flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			
			if (third_dir == false)
			{
				printf ("\n%s\n", contents);
				for (i = 0; i < NC_tele; i ++)
					if (sub [i].del_tele == true)
						printf ("\n %3d %8d   %-28s \t %-9s \t %s", sub [i].id_tele, sub [i].phone_number, sub [i].name.str, sub [i].tariff.str, sub [i].address);
			}			
			else
			{
				printf ("\n%s\n", contents_add);
				for (i = 0; i < NC_tele; i ++)
					if (sub [i].del_tele == true)
						printf ("\n %3d %8d   %-28s \t %-9s \t %s \t %s", sub [i].id_tele, sub [i].phone_number, sub [i].name.str, sub [i].tariff.str, sub [i].address, sub [i].benefit.str);
			}				
			break;
		}
		
		case File_Name:
		{
			flag_name = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			printf ("\nСправочник \"name.db\":\n");
			printf ("\n%s\n", contents_dir);
			for (i = 0; i < NC_name; i ++)
				if (fio [i].del_name == true)
					printf ("\n %3d %5s", fio [i].id_name, fio [i].name);
			break;
		}
		
		case File_Tariff:
		{
			flag_tariff = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;	
			printf ("\nСправочник \"tariff.db\":\n");	
			printf ("\n%s\n", contents_dir);
			for (i = 0; i < NC_tariff; i ++)
				if (rate [i].del_tariff == true)
					printf ("\n %3d %5s", rate [i].id_tariff, rate [i].tariff);
			break;
		}
		
		case File_Benefit:
		{
			flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			printf ("\nСправочник \"benefit.db\":\n");	
			printf ("\n%s\n", contents_dir);
			for (i = 0; i < NC_benefit; i ++)
				if (priv [i].del_benefit == true)
					printf ("\n %3d %5s", priv [i].id_benefit, priv [i].benefit);
			break;
		}
	}		
}

/**
 * @fn save_file
 * @brief Функция для сохранения всех изменений во все открытые файлы
 * Ничего не принимает, ничего не возвращает
 * @param i - переменная цикла
 * @param **fd - указатель на указатель на открытый файл
 */
void save_file (enum TypeOfFile type)
{
	FILE** fd;
	int i;
	
	switch (type)
	{
		case File_Tele:
		{
			if (files.tele == NULL || save_tele == true)
				return;
			fd = &files.tele;
			fclose (*fd);
			*fd = fopen ("tele.db", "w");
			
			for (i = 0; i < NC_tele; i ++)
				if (sub [i].del_tele == true)
				{
					fprintf (files.tele, "%d;%d;%d;%d;%s;%d;", sub [i].id_tele, sub [i].phone_number, sub [i].name.id, sub [i].tariff.id, sub [i].address, sub [i].benefit.id);
					break;
				}
			for (i ++; i < NC_tele; i ++)
				if (sub [i].del_tele == true)
					fprintf (files.tele, "\n%d;%d;%d;%d;%s;%d;", sub [i].id_tele, sub [i].phone_number, sub [i].name.id, sub [i].tariff.id, sub [i].address, sub [i].benefit.id);
				
			if (*fd >= 0)
				printf ("Файл \"tele.db\" успешно сохранён.\n");
			else
				printf ("При сохранении файла \"tele.db\" произошла ошибка.");
			fflush (files.tele);
			fclose (files.tele);
			*fd = fopen ("tele.db", "r+");
			NC_tele = 0;
			read_file (File_Tele);
			save_tele = true;		
			break;
		}
	
		case File_Name:
		{
			if (files.name == NULL || save_name == true)
				return;
			fd = &files.name;	
			fclose (*fd);
			*fd = fopen ("name.db", "w");
			
			for (i = 0; i < NC_name; i ++)
				if (fio [i].del_name == true)
				{
					fprintf (files.name, "%d;%s;", fio [i].id_name, fio [i].name);
					break;
				}
			for (i ++; i < NC_name; i ++)
				if (fio [i].del_name == true)
					fprintf (files.name, "\n%d;%s;", fio [i].id_name, fio [i].name);
			if (*fd >= 0)
				printf ("Файл \"name.db\" успешно сохранёт.\n");
			else
				printf ("При сохранении файла \"name.db\" произошла ошибка.");
			fflush (files.name);
			fclose (files.name);
			*fd = fopen ("name.db", "r+");
			NC_name = 0;
			read_file (File_Name);
			save_name = true;
			break;
		}
		case File_Tariff:
		{
			if (files.tariff == NULL || save_tariff == true)
				return;
			fd = &files.tariff;
			fclose (*fd);
			*fd = fopen ("tariff.db", "w");
			
			for (i = 0; i < NC_tariff; i ++)
				if (rate [i].del_tariff == true)
				{
					fprintf (files.tariff, "%d;%s;", rate [i].id_tariff, rate [i].tariff);
					break;
				}
			for (i ++; i < NC_tariff; i ++)
				if (rate [i].del_tariff == true)
					fprintf (files.tariff, "\n%d;%s;", rate [i].id_tariff, rate [i].tariff);
			if (*fd >= 0)
				printf ("Файл \"tariff.db\" успешно сохранёт.\n");
			else
				printf ("При сохранении файла \"tariff.db\" произошла ошибка.");
			fflush (files.tariff);
			fclose (files.tariff);
			*fd = fopen ("tariff.db", "r+");
			NC_tariff = 0;
			read_file (File_Tariff);
			save_tariff = true;
			break;
		}
		case File_Benefit:
		{
			if (files.benefit == NULL || save_benefit == true)
				return;
			fd = &files.benefit;
			fclose (*fd);
			*fd = fopen ("benefit.db", "w");
			
			for (i = 0; i < NC_benefit; i ++)
				if (priv [i].del_benefit == true)
				{
					fprintf (files.benefit, "%d;%s;", priv [i].id_benefit, priv [i].benefit);
					break;
				}
			for (i ++; i < NC_benefit; i ++)
				if (priv [i].del_benefit == true)
					fprintf (files.benefit, "\n%d;%s;", priv [i].id_benefit, priv [i].benefit);
			if (*fd >= 0)
				printf ("Файл \"benefit.db\" успешно сохранёт.\n");
			else
				printf ("При сохранении файла \"benefit.db\" произошла ошибка.");
			fflush (files.benefit);
			fclose (files.benefit);
			*fd = fopen ("benefit.db", "r+");
			NC_benefit = 0;
			read_file (File_Benefit);
			save_benefit = true;
			break;
		}
	}
	getchar ();
}

/**
 * @fn insp_file
 * @brief Функция для проверки и открытия файлов
 * Принимает типы каждого из файлов и проверяет их значение
 * Проверяет каждый файл, значение которого равно "true", закрыт ли он и если закрыт, то открывает его
 * Возвращает "1", если все файлы, значение которых равно "true", открыты, в обратном случае возвращает "0"
 * @param int_answer, answer - ответы пользователя на вопрос открытия файла или файлов
 * @param *temp - временная переменная
 * @param flag - переменная для указания успешности выполнения задачи
 */
int insp_file (bool flag_tele, bool flag_name, bool flag_tariff, bool flag_benefit)
{
	int int_answer;
	char answer [10], *temp;
	
	if (flag_tele == true && files.tele != NULL)
		flag_tele = false;
	if (flag_name == true && files.name != NULL)
		flag_name = false;
	if (flag_tariff == true && files.tariff != NULL)
		flag_tariff = false;
	if (flag_benefit == true && files.benefit != NULL)
		flag_benefit = false;
	if (flag_tele == false && flag_name == false && flag_tariff == false && flag_benefit == false)
		return 1;
	
	printf ("Файлы ");	
	if (flag_tele == true)
		printf ("%s", "\"tele.db\", ");
	if (flag_name == true)
		printf ("%s", "\"name.db\", ");
	if (flag_tariff == true)
		printf ("%s", "\"tariff.db\", ");
	if (flag_benefit == true)
		printf ("%s", "\"benefit.db\", ");
	printf ("необходимые для данной операции, закрыты.\nВыберите вариант действия: Открыть их (Enter, 1), Назад (0): ");
	fgets (answer, 10, stdin);
	temp = strchr (answer, '\n');
	if (temp != NULL)
		*temp = '\0';
	int_answer = atoi (answer);
	if (int_answer == 1 || (strcmp (answer, "\0") == 0))
	{
		if (flag_tele == true)
			open_file (File_Tele);
		if (flag_name == true)
			open_file (File_Name);
		if (flag_tariff == true)
			open_file (File_Tariff);
		if (flag_benefit == true)
			open_file (File_Benefit);
	}
	else
	{
		flag_tele = false;
		flag_name = false;
		flag_tariff = false;
		flag_benefit = false;
		return 0;
		
	}
	flag_tele = false;
	flag_name = false;
	flag_tariff = false;
	flag_benefit = false;
	return 1;
}

/**
 * @fn warning_save
 * @brief Функция для проверки и сохранения изменений файлов
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * Проверяет каждый файл, значение которого равно true, сохранён ли он и если сохранён, то открывает его
 * @param int_answer- ответ пользователей на вопрос сохранения файла или файлов
 * @param all_save - если значение переменной равно true, то был запрос на проверку сохранения всех файлов, иначе только одного
 */
void warning_save (bool flag_tele, bool flag_name, bool flag_tariff, bool flag_benefit)
{
	int int_answer;
	char name_of_file [40];
	bool all_save;
	
	if (flag_tele == true && flag_name == true && flag_tariff == true && flag_benefit == true)		
		all_save = true;
	else
	{
		all_save = false;
		if (flag_tele == true && save_tele == false)
			strcpy (name_of_file, "tele.db");
		if (flag_name == true && save_name == false)
			strcpy (name_of_file, "name.db");
		if (flag_tariff == true && save_tariff == false)
			strcpy (name_of_file, "tariff.db");
		if (flag_benefit == true && save_benefit == false)
			strcpy (name_of_file, "benefit.db"); 
	}
	
	/**
	 *  Этот блок кода отсекает среди тех файлов, которые были выбраны, те, которые сохранены или не изменялись.
	 *  Также он преждевременно выходит из функции, если среди выбранных файлов не оказалось не сохранённых.
	 */
	if (flag_tele == true && save_tele == true)
		flag_tele = false;
	if (flag_name == true && save_name == true)
		flag_name = false;
	if (flag_tariff == true && save_tariff == true)
		flag_tariff = false;
	if (flag_benefit == true && save_benefit == true)
		flag_benefit = false;
	if (flag_tele == false && flag_name == false && flag_tariff == false && flag_benefit == false)
		return;
	
	if (all_save == true)
	{
		printf ("Вы внесли изменения в файлы ");
		if (flag_tele == true)
			printf ("%s", "\"tele.db\", ");
		if (flag_name == true)
			printf ("%s", "\"name.db\", ");
		if (flag_tariff == true)
			printf ("%s", "\"tariff.db\", ");
		if (flag_benefit == true)
			printf ("%s", "\"benefit.db\", ");
		printf ("которые не были сохранены.\nВыберите действие: Сохранить изменения и выйти (1), Выйти без сохранения (0): ");		
	}
	else
	{
		printf ("В файл \"%s\", который вы хотите закрыть, были внесены изменения.\n", name_of_file);
		printf ("Выберите действие: Сохранить изменения и закрыть файл (1), Закрыть файл без сохранения (0): ");
	}
	scanf ("%d", &int_answer);
	getchar ();
	if (int_answer == 1)
	{
		if (flag_tele == true)
			save_file (File_Tele);
		if (flag_name == true)
			save_file (File_Name);
		if (flag_tariff == true)
			save_file (File_Tariff);
		if (flag_benefit == true)
			save_file (File_Benefit);		
	}
	save_tele = true;
	save_name = true;
	save_tariff = true;
	save_benefit = true;	
	flag_tele = false;
	flag_name = false;
	flag_tariff = false;
	flag_benefit = false;
	return;
}

/**
 * @fn close_file
 * @brief Функция для закрытия файла
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param **fd - указатель на указатель на открываемый файл
 * @param *file_name - указатель на имя файла
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */ 
void close_file (enum TypeOfFile type)
{
	char* file_name;
	FILE** fd = NULL;
	bool flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
	switch (type)
	{
		case File_Tele:
			file_name = "tele.db";
			fd = &files.tele;
			break;
		
		case File_Name:
			file_name = "name.db";
			fd = &files.name;
			break;
		
		case File_Tariff:
			file_name = "tariff.db";
			fd = &files.tariff;
			break;
		
		case File_Benefit:
			file_name = "benefit.db";
			fd = &files.benefit;
			break;
	}
	
	if (fd != NULL)
	{
		if (*fd != NULL)
		{
			switch (type)
			{
				case File_Tele:
					flag_tele = true;
					warning_save (flag_tele, flag_name, flag_tariff, flag_benefit);
					break;
				case File_Name:
					flag_name = true;
					warning_save (flag_tele, flag_name, flag_tariff, flag_benefit);
					break;
				case File_Tariff:
					flag_tariff = true;
					warning_save (flag_tele, flag_name, flag_tariff, flag_benefit);
					break;
				case File_Benefit:
					flag_benefit = true;
					warning_save (flag_tele, flag_name, flag_tariff, flag_benefit);
					break;
			}
			if (fclose (*fd) == 0)
				printf ("Файл \"%s\" успешно закрыт.\n", file_name);
			else printf ("Ошибка при закрытии файла.\"%s\"\n", file_name);
			*fd = NULL;
		}
		else
			printf("Файл \"%s\" не открывался или уже был закрыт.\n", file_name);
	}
}


