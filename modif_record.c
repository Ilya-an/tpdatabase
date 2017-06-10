#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tpdatabase.h"
#include "modif_record.h"

/**
 * @fn add_record
 * @brief Функция для добавления записи в файл
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param i - переменная цикла
 * @param i_var - значение i, которое совпадает с значением изменяемой записи
 * @param i_n, i_t, i_b - переменные цикла для проверки на существование вводимых данных в соответствущих справочниках
 * @param res - переменная, в которую передаётся возвращение функции "insp_file"
 * @param add_id_tele, add_id_name, add_id_tariff, add_id_benefit - значения добавляемых id-записей в соответстующих файлах
 * @param add_phone_number, add_name, add_tariff, add_address, add_benefit - добавляемые значения соответсвующих значений
 * @param temp_int, temp_char, *temp - временные переменные
 * @param int_answer, answer - ответы пользователя на вопросы открытия файлов
 * @param flag - переменная для указания успешности выполнения задачи
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */
void add_record (enum TypeOfFile type)
{
	int i, i_n, i_t, i_b, res, add_id_tele = 0, add_phone_number = 0, add_id_name = 0, add_id_tariff = 0, add_id_benefit = 0, int_answer;
	char add_name [80], add_tariff [80], add_address [80], add_benefit [80], temp_char [80], answer [10], *temp;
	bool flag = true, flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
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
			printf ("Введите id добавляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			add_id_tele = atoi (temp_char);
			if (add_id_tele > 0)
				for (i = 0; i < NC_tele; i ++)
					if (add_id_tele == sub [i].id_tele && sub [i].del_tele == true)
					{
						printf ("Ошибка, запись с id \"%d\" уже существует.\n", add_id_tele);
						getchar ();
						return;
					}
					else;
			else
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
					
			printf ("Введите телефон добавляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			add_phone_number = atoi (temp_char);
			if (add_phone_number == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			//if (temp != NULL && temp [1] != '\0')
			for (i = 0; i < NC_tele; i ++)
				if (add_phone_number == sub [i].phone_number && sub [i].del_tele == true)
				{
					printf ("Ошибка, запись с телефоном \"%d\" уже существует.\n", add_phone_number);
					getchar ();
					return;
				}
				
			printf ("Введите ФИО добавляемой записи или его id: ");
			fgets (add_name, 80, stdin);
			temp = strchr (add_name, '\n');
			if (temp != NULL)
				*temp = '\0';
			add_id_name = atoi (add_name);
			for (i_n = 0; i_n < NC_name; i_n ++)
				if (strcmp (add_name, fio [i_n].name) == 0 || add_id_name == fio [i_n].id_name)
					if (fio [i_n].del_name == true)
					{
						flag = false;
						break;
					}
			if (flag == true)
				if (add_id_name != 0)
				{
					printf ("Ошибка, запись с id \"%d\" в справочнике \"name.db\" отсутствует.\n", add_id_name);
					getchar ();
					return;
				}
				else if (add_name [0] != '\0')
					{
						printf ("Ошибка, запись с ФИО \"%s\" в справочнике \"name.db\" отсутствует.\n", add_name);
						getchar ();
						return;
					}
					else
					{
						printf ("Ошибка, добавляемая запись не может быть пустой.");
						getchar ();
						return;
					}
			else
				flag = true;
			
			printf ("Введите тариф добавляемой записи или его id: ");
			fgets (add_tariff, 80, stdin);
			temp = strchr (add_tariff, '\n');
			if (temp != NULL)
				*temp = '\0';
			add_id_tariff = atoi (add_tariff);
			for (i_t = 0; i_t < NC_tariff; i_t ++)
				if (strcmp (add_tariff, rate [i_t].tariff) == 0 || add_id_tariff == rate [i_t].id_tariff)
					if (rate [i_t].del_tariff == true)
					{
						flag = false;
						break;
					}
			if (flag == true)
				if (add_id_tariff != 0)
				{
					printf ("Ошибка, запись с id \"%d\" в справочнике \"tariff.db\" отсутствует.\n", add_id_tariff);
					getchar ();
				return;
				}
				else if (add_tariff [0] != '\0')
					{
						printf ("Ошибка, запись с тарифом \"%s\" в справочнике \"tariff.db\" отсутствует.\n", add_tariff);
						getchar ();
						return;
					}
					else
					{
						printf ("Ошибка, добавляемая запись не может быть пустой.");
						getchar ();
						return;
					}
			else
				flag = true;
			
			printf ("Введите адрес добавляемой записи: ");
			fgets (add_address, 80, stdin);
			temp = strchr (add_address, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (add_address [0] == '\0')
			{
				printf ("Ошибка, добавляемая запись не может быть пустой.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_tele; i ++)
				if (strcmp (add_address, sub [i].address) == 0 && sub [i].del_tele == true)
				{
					printf ("Ошибка, запись с адресом \"%s\" уже существует.\n", add_address);
					getchar ();
					return;
				}
			if (NC_tele == NC_tele_max)
			{
				sub = realloc (sub, (NC_tele + 1) * sizeof (struct Tele));
				NC_tele_max ++;
			}
			
			if (third_dir == true)
			{
				printf ("Введите льготу добавляемой записи или её id: ");
				fgets (add_benefit, 80, stdin);
				temp = strchr (add_benefit, '\n');
				if (temp != NULL)
					*temp = '\0';
				add_id_benefit = atoi (add_benefit);
				for (i_b = 0; i_b < NC_benefit; i_b ++)
					if (strcmp (add_benefit, priv [i_b].benefit) == 0 || add_id_benefit == priv [i_b].id_benefit)
						if (priv [i_b].del_benefit == true)
						{
							flag = false;
							break;
						}
				if (flag == true)
					if (add_id_benefit != 0)
					{
						printf ("Ошибка, запись с id \"%d\" в справочнике \"benefit.db\" отсутствует.\n", add_id_benefit);
						getchar ();
					return;
					}
					else if (add_benefit [0] != '\0')
						{
							printf ("Ошибка, запись с льготой \"%s\" в справочнике \"benefit.db\" отсутствует.\n", add_benefit);
							getchar ();
							return;
						}
						else
						{
							printf ("Ошибка, добавляемая запись не может быть пустой.");
							getchar ();
							return;
						}
				else
					flag = true;
			}	
			
			sub [NC_tele].id_tele = add_id_tele;
			sub [NC_tele].phone_number = add_phone_number;	
			sub [NC_tele].name.id = fio [i_n].id_name;
			sub [NC_tele].name.str = fio [i_n].name;
			sub [NC_tele].tariff.id = rate [i_t].id_tariff;
			sub [NC_tele].tariff.str = rate [i_t].tariff;
			strcpy (sub [NC_tele].address, add_address);
			if (third_dir == true)
				sub [NC_tele].benefit.str = priv [i_b].benefit;
			else
			{
				sub [NC_tele].benefit.id = 0;
				sub [NC_tele].benefit.str = no_data;
			}
			sub [NC_tele].del_tele = true;
			
			printf ("Добавленная запись:\n");	
			if (third_dir == false)
			{
				printf ("%s\n", contents);
				printf ("\n %3d %8d   %-28s \t %-9s \t %s", sub [NC_tele].id_tele, sub [NC_tele].phone_number, sub [NC_tele].name.str, sub [NC_tele].tariff.str, sub [NC_tele].address);
			}
			else
			{
				printf ("%s\n", contents_add);
				printf ("\n %3d %8d   %-28s \t %-9s \t %s \t %s", sub [NC_tele].id_tele, sub [NC_tele].phone_number, sub [NC_tele].name.str, sub [NC_tele].tariff.str, sub [NC_tele].address, sub [NC_tele].benefit.str);
			}
			NC_tele ++;
			save_tele = false;
			//printf ("\n");
			//printf_file (File_Tele);
			break;
		}
	
		case File_Name:
		{
			flag_name = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;				
			printf ("Введите id добавляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			add_id_name = atoi (temp_char);
			if (add_id_name == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_name; i ++)
				if (add_id_name == fio [i].id_name && fio [i].del_name == true)
				{
					printf ("Ошибка, запись с id \"%d\" уже существует.\n", add_id_name);
					getchar ();
					return;
				}
				
			printf ("Введите ФИО добавляемой записи: ");
			fgets (add_name, 80, stdin);
			temp = strchr (add_name, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (add_name [0] == '\0')
			{
				printf ("Ошибка, добавляемая запись не может быть пустой.");
				getchar ();
				return;
			}
				for (i = 0; i < NC_name; i ++)
					if (strcmp (add_name, fio [i].name) == 0 && fio [i].del_name == true)
					{
						printf ("Ошибка, запись с именем \"%s\" уже существует.", add_name);
						getchar ();
						return;
					}
			if (NC_name == NC_name_max)
			{
				fio = realloc (fio, (NC_name + 1) * sizeof (struct Name));
				NC_name_max ++;
			}
			
			//if (temp != NULL)
			//	fio = (int)temp;
			
			fio [NC_name].id_name = add_id_name;
			strcpy (fio [NC_name].name, add_name);
			fio [NC_name].del_name = true;
			for (i = 0; i < NC_tele; i ++)
				if (fio [NC_name].id_name == sub [i].name.id)
					{
						sub [i].name.str = fio [NC_name].name;
						break;
					}
								
			printf ("Добавленная запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", fio [NC_name].id_name, fio [NC_name].name);
			
			NC_name ++;
			save_name = false;
			break;
		}
	
		case File_Tariff:
		{
			flag_tariff = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			printf ("Введите id добавляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			add_id_tariff = atoi (temp_char);
			if (add_id_tariff == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_tariff; i ++)
				if (add_id_tariff == rate [i].id_tariff && rate [i].del_tariff == true)
				{
					printf ("Ошибка, запись с id \"%d\" уже существует.\n", add_id_tariff);
					getchar ();
					return;
				}
				
			printf ("Введите тариф добавляемой записи: ");
			fgets (add_tariff, 80, stdin);
			temp = strchr (add_tariff, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (add_tariff [0] == '\0')
			{
				printf ("Ошибка, добавляемая запись не может быть пустой.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_tariff; i ++)
				if (strcmp (add_tariff, rate [i].tariff) == 0 && rate [i].del_tariff == true)
				{
					printf ("Ошибка, запись с именем \"%s\" уже существует.", add_tariff);
					getchar ();
					return;
				}
			if (NC_tariff == NC_tariff_max)
			{		
				rate = realloc (rate, (NC_tariff + 1) * sizeof (struct Tariff));
				NC_tariff_max ++;
			}
			//if (temp != NULL)
			//	rate = (int)temp;
			
			rate [NC_tariff].id_tariff = add_id_tariff;
			strcpy (rate [NC_tariff].tariff, add_tariff);
			rate [NC_tariff].del_tariff = true;
			for (i = 0; i < NC_tele; i ++)
				if (rate [NC_tariff].id_tariff == sub [i].tariff.id)
					{
						sub [i].tariff.str = rate [NC_tariff].tariff;
						break;
					}
			
			printf ("Добавленная запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", rate [NC_tariff].id_tariff, rate [NC_tariff].tariff);
			
			NC_tariff ++;
			save_tariff = false;
			break;
		}
		
		case File_Benefit:
		{
			flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			if (files.benefit == NULL)
			{
				printf ("Файл \"benefit.db\", необходимый для данной операции, закрыт.\nВыберите вариант действия: Открыть его (Enter, 1), Назад (0): ");
				getchar ();
				fgets (answer, 10, stdin);
				temp = strchr (answer, '\n');
				if (temp != NULL)
					*temp = '\0';
				int_answer = atoi (answer);
				if (int_answer == 1 || (strcmp (answer, "\0") == 0))
					open_file (File_Benefit);
				else
					return;	
			}
			
			printf ("Введите id добавляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			add_id_benefit = atoi (temp_char);
			if (add_id_benefit == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_benefit; i ++)
				if (add_id_benefit == priv [i].id_benefit && priv [i].del_benefit == true)
				{
					printf ("Ошибка, запись с id \"%d\" уже существует.\n", add_id_benefit);
					getchar ();
					return;
				}
				
			printf ("Введите льготу добавляемой записи: ");
			fgets (add_benefit, 80, stdin);
			temp = strchr (add_benefit, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (add_benefit [0] == '\0')
			{
				printf ("Ошибка, добавляемая запись не может быть пустой.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_benefit; i ++)
				if (strcmp (add_benefit, priv [i].benefit) == 0 && priv [i].del_benefit == true)
				{
					printf ("Ошибка, запись с именем \"%s\" уже существует.", add_benefit);
					getchar ();
					return;
				}
			if (NC_benefit == NC_benefit_max)
			{		
				priv = realloc (priv, (NC_benefit + 1) * sizeof (struct Benefit));
				NC_benefit_max ++;
			}
			//if (temp != NULL)
			//	rate = (int)temp;
			
			priv [NC_benefit].id_benefit = add_id_benefit;
			strcpy (priv [NC_benefit].benefit, add_benefit);
			priv [NC_tariff].del_benefit = true;
			for (i = 0; i < NC_tele; i ++)
				if (priv [NC_benefit].id_benefit == sub [i].benefit.id)
					{
						sub [i].benefit.str = priv [NC_benefit].benefit;
						break;
					}
			
			printf ("Добавленная запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", priv [NC_benefit].id_benefit, priv [NC_benefit].benefit);
			
			NC_benefit ++;
			save_benefit = false;
			break;
		}
	}
	getchar ();
}

/**
 * @fn edit_record
 * @brief Функция для изменения содержимого записи файла
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param i - переменная цикла
 * @param i_var - значение i, которое совпадает с значением изменяемой записи
 * @param res - переменная, в которую передаётся возвращение функции "insp_file"
 * @param edit_id_tele, edit_id_name, edit_id_tariff, edit_id_benefit - значения изменяемый id-записей в соответстующих файлах
 * @param edit_phone_number, edit_name [80], edit_tariff, edit_address, edit_benefit - изменяемые значения соответсвующих значений
 * @param temp_int, temp_char, *temp - временные переменные
 * @param int_answer, answer - ответы пользователей на вопросы открытия файла
 * @param flag - переменная для указания успешности выполнения задачи
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */ 
void edit_record (enum TypeOfFile type)
{
	int i, i_var, res, edit_id_tele, edit_id_name, edit_id_tariff, edit_id_benefit, edit_phone_number, temp_int, int_answer;
	char edit_name [80], edit_tariff [80], edit_address [80], edit_benefit [80], temp_char [80], *temp;
	bool flag = true, flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
	switch (type)
	{
		case File_Tele:
		{
			///Этот блок кода проверяет файлы на их открытость и открывает их в случае необходимости
			flag_tele = true;
			flag_name = true;
			flag_tariff = true;
			if (third_dir == true)
				flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			
			printf ("\nВведите id изменяемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			temp_int = atoi (temp_char);
			for (i_var = 0; i_var < NC_tele; i_var ++)
				if (temp_int == sub [i_var].id_tele)
					if (sub [i_var].del_tele == true)
					{
						flag = false;
						break;
					}
			if (flag == true)
				if (temp_int != 0)
				{
					printf ("Ошибка, записи с id \"%d\" не существует.\n", temp_int);
					getchar ();
					return;
				}
				else
				{
					printf ("Ошибка, вводимое значение id должно быть положительным числом.\n");
					getchar ();
					return;
				}
			else
				flag = true;
			
			printf ("Введите новое значение или id записи.\nОставьте поле пустым, если вы не хотите его менять:\n\n");
			
			//fgets (temp_char, 40, stdin);
			
			printf ("Старый id: %d   Новое id: ", sub [i_var].id_tele);
			fgets (temp_char, 40, stdin);
			edit_id_tele = atoi (temp_char);
			if (edit_id_tele != 0)			
				for (i = 0; i < NC_tele; i ++)
					if (edit_id_tele == sub [i].id_tele && sub [i].del_tele == true)
					{
						printf ("Ошибка, запись с id \"%d\" уже существует. Оставлено старое значение id.\n", edit_id_tele);
						flag = false;
						break;
					}
					else;
			else
				if (temp_char [0] != '\n')
					printf ("Ошибка, вводимое значение должно быть числом. Оставлено старое значение id.\n");
			if (flag == true && edit_id_tele != 0)
				sub [i_var].id_tele = edit_id_tele;
			else
				flag = true;
			
			printf ("Старый телефон: %d   Новый телефон: ", sub [i_var].phone_number);
			fgets (temp_char, 40, stdin);
			edit_phone_number = atoi (temp_char);
			if (edit_phone_number != 0)
				for (i = 0; i < NC_tele; i ++)
					if (edit_phone_number == sub [i].phone_number && sub [i].del_tele == true)
					{
						printf ("Ошибка, запись с телефоном \"%d\" уже существует. Оставлено старое значение телефона.\n", edit_phone_number);
						flag = false;
						break;
					}
					else;				
			else if (temp_char [0] != '\n')
					printf ("Ошибка, вводимое значение должно быть числом. Оставлено старое значение телефона.\n");
			if (flag == true)
				if (edit_phone_number != 0)
					sub [i_var].phone_number = edit_phone_number;
				else;
			else
				flag = true;
				
			printf ("Старое ФИО: %s   Новое ФИО или его id: ", sub [i_var].name.str);
			fgets (edit_name, 80, stdin);
			temp = strchr (edit_name, '\n');
			if (temp != NULL)
				*temp = '\0';
			edit_id_name = atoi (edit_name);
			if (edit_name [0] != '\0')
				for (i = 0; i < NC_name; i ++)
					if (strcmp (edit_name, fio [i].name) == 0 || edit_id_name == fio [i].id_name)
						if (fio [i].del_name == true)
						{
							sub [i_var].name.id = fio [i].id_name;
							sub [i_var].name.str = fio [i].name;
							flag = false;
							break;
						}		
			if (flag == true && edit_name [0] != '\0')
				if (edit_id_name != 0)
					printf ("Ошибка, запись с id \"%d\" в справочнике \"name.db\" отсутствует. Оставлено старое значение ФИО.\n", edit_id_name);
				else
					printf ("Ошибка, запись с ФИО \"%s\" в справочнике \"name.db\" отсутствует. Оставлено старое значение ФИО.\n", edit_name);
			else
				flag = true;
			
			printf ("Старый тариф: %s   Новый тариф или его id: ", sub [i_var].tariff.str);
			fgets (edit_tariff, 80, stdin);
			temp = strchr (edit_tariff, '\n');
			if (temp != NULL)
				*temp = '\0';
			edit_id_tariff = atoi (edit_tariff);
			if (edit_tariff [0] != '\0')
				for (i = 0; i < NC_tariff; i ++)
					if (strcmp (edit_tariff, rate [i].tariff) == 0 || edit_id_tariff == rate [i].id_tariff)
						if (rate [i].del_tariff == true)
						{
							sub [i_var].tariff.id = rate [i].id_tariff;
							sub [i_var].tariff.str = rate [i].tariff;
							flag = false;
							break;
						}
			if (flag == true)
				if (edit_tariff [0] != '\0')
					if (edit_id_tariff != 0)
						printf ("Ошибка, запись с id \"%d\" в справочнике \"tariff.db\" отсутствует. Оставлено старое значение тарифа.\n", edit_id_tariff);
					else
						printf ("Ошибка, запись с ФИО \"%s\" в справочнике \"tariff.db\" отсутствует. Оставлено старое значение тарифа.\n", edit_tariff);
				else;
			else
				flag = true;
			
			printf ("Старый адрес: %s   Новый адрес: ", sub [i_var].address);
			fgets (edit_address, 80, stdin);
			temp = strchr (edit_address, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (edit_address [0] != '\0')
				for (i = 0; i < NC_tariff; i ++)
					if (strcmp (edit_address, sub [i].address) == 0 && sub [i].del_tele == true)
					{
						printf ("Ошибка, запись с адресом \"%s\" уже существует. Оставлено старое значение адреса.\n", edit_address);
						flag = false;
						break;
					}
			if (flag == true)
				if (edit_address [0] != '\0')
					strcpy (sub [i_var].address, edit_address);
				else;
			else
				flag = true;
				
			if (third_dir == true)
			{
				printf ("Старая льгота: %s   Новая льгота: ", sub [i_var].benefit.str);
				fgets (edit_benefit, 80, stdin);
				temp = strchr (edit_address, '\n');
				if (temp != NULL)
					*temp = '\0';
				if (edit_benefit [0] != '\0')
					for (i = 0; i < NC_benefit; i ++)
						if (strcmp (edit_benefit, sub [i].benefit.str) == 0 && sub [i].del_tele == true)
						{
							printf ("Ошибка, запись с адресом \"%s\" уже существует. Оставлено старое значение адреса.\n", edit_benefit);
							flag = false;
							break;
						}
				if (flag == true)
					if (edit_benefit [0] != '\0')
						strcpy (sub [i_var].benefit.str, edit_benefit);
					else;
				else
					flag = true;
			}
			
			printf ("Новая запись:\n");
			if (third_dir == false)
			{	
				printf ("%s\n", contents);
				printf ("\n %3d %8d   %-28s \t %-9s \t %s", sub [i_var].id_tele, sub [i_var].phone_number, sub [i_var].name.str, sub [i_var].tariff.str, sub [i_var].address);
			}
			else
			{	
				printf ("%s\n", contents_add);
				printf ("\n %3d %8d   %-28s \t %-9s \t %s \t %s", sub [i_var].id_tele, sub [i_var].phone_number, sub [i_var].name.str, sub [i_var].tariff.str, sub [i_var].address, sub [i_var].benefit.str);
			}
			save_tele = false;
			break;
		}
		
		case (File_Name):
		{
			flag_tele = true;
			flag_name = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			printf_file (File_Name);					
			printf ("\n\nВведите id изменяемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			temp_int = atoi (temp_char);
				
			for (i_var = 0; i_var < NC_name; i_var ++)
				if (temp_int == fio [i_var].id_name)
				{
					flag = false;
					break;
				}
			if (flag == true)
				if (temp_int != 0)
				{
					printf ("Ошибка, записи с id \"%d\" не существует.\n", temp_int);
					getchar ();
					return;
				}
				else
				{
					printf ("Ошибка, вводимое значение id должно быть положительным числом.");
					getchar ();
					return;
				}
			else
				flag = true;
			
			printf ("Введите новое значение или id записи.\nОставьте поле пустым, если вы не хотите его менять:\n");
			
			printf ("Старый id: %d   Новое id: ", fio [i_var].id_name);
			fgets (temp_char, 40, stdin);
			edit_id_name = atoi (temp_char);
			if (edit_id_name != 0)
				for (i = 0; i < NC_name; i ++)
					if (edit_id_name == fio [i].id_name && fio [i].del_name == true)
					{
						printf ("Ошибка, запись с id \"%d\" уже существует. Оставлено старое значение id.\n", edit_id_name);
						flag = false;
						break;
					}
					else;
			else if (strlen (temp_char) == 0)
					printf ("Ошибка, вводимое значение должно быть числом. Оставлено старое значение id.\n");
			if (flag == true && edit_id_name != 0)
			{
				for (i = 0; i < NC_tele; i ++)
					if (fio [i_var].id_name == sub [i].name.id)
					{
						printf ("Внимание, запись с id \"%d\", которую вы хотите изменить, используется в документе.\n", fio [i_var].id_name);
						printf ("Вы хотите изменить одну или несколько аналогичных записей в документе? Да (1), Нет (0): ");
						scanf ("%d", &int_answer);
						getchar ();
						break;
					}			
				if (int_answer == 1)
				{
					for (; i < NC_tele; i ++)
						if (fio [i_var].id_name == sub [i].name.id)
							sub [i].name.id = edit_id_name;
					save_tele = false;
				}
				else
					for (; i < NC_tele; i ++)
						if (fio [i_var].id_name == sub [i].name.id)
							sub [i].name.str = no_data;
				fio [i_var].id_name = edit_id_name;
			}
			else
				flag = true;
							
			printf ("Старое ФИО: %s   Новое ФИО: ", fio [i_var].name);
			fgets (edit_name, 80, stdin);
			temp = strchr (edit_name, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (edit_name [0] != '\0')
				for (i = 0; i < NC_name; i ++)
					if (strcmp (edit_name, fio [i].name) == 0 && fio [i].del_name == true)
					{
						printf ("Ошибка, запись с ФИО \"%s\" уже существует. Оставлено старое значение ФИО.\n", edit_name);
						flag = false;
						break;
					}						
			if (flag == true)
				if (edit_name [0] != '\0')
					strcpy (fio [i_var].name, edit_name);
				else;
			else
				flag = true;
			
			printf ("Новая запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", fio [i_var].id_name, fio [i_var].name);
			save_name = false;
			break;
		}
	
		case File_Tariff:
		{
			flag_tele = true;
			flag_tariff = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			printf_file (File_Tariff);					
			printf ("\n\nВведите id изменяемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			temp_int = atoi (temp_char);
							
			for (i_var = 0; i_var < NC_tariff; i_var ++)
				if (temp_int == rate [i_var].id_tariff)
				{
					flag = false;
					break;
				}
			if (flag == true)
				if (temp_int != 0)
				{
					printf ("Ошибка, записи с id \"%d\" не существует.\n", temp_int);
					getchar ();
					return;
				}
				else
				{
					printf ("Ошибка, вводимое значение id должно быть положительным числом.\n");
					getchar ();
					return;
				}
			else
				flag = true;
			
			printf ("Введите новое значение или id записи.\nОставьте поле пустым, если вы не хотите его менять:\n");
			
			printf ("Старый id: %d   Новое id: ", rate [i_var].id_tariff);
			fgets (temp_char, 40, stdin);
			edit_id_tariff = atoi (temp_char);
			if (edit_id_tariff != 0)
				for (i = 0; i < NC_tariff; i ++)
					if (edit_id_tariff == rate [i].id_tariff && rate [i].del_tariff == true)
					{
						printf ("Ошибка, запись с id \"%d\" уже существует. Оставлено старое значение id.\n", edit_id_tariff);
						flag = false;
						break;
					}
					else;
			else if (strlen (temp_char) == 0)
					printf ("Ошибка, вводимое значение должно быть числом. Оставлено старое значение id.\n");
				
			if (flag == true && edit_id_tariff != 0)
			{
				for (i = 0; i < NC_tele; i ++)
					if (rate [i_var].id_tariff == sub [i].tariff.id)
					{
						printf ("Внимание, запись с id \"%d\", которую вы хотите изменить, используется в документе.\n", rate [i_var].id_tariff);
						printf ("Вы хотите изменить одну или несколько аналогичных записей в документе? Да (1), Нет (0): ");
						scanf ("%d", &int_answer);
						getchar ();
						break;
					}			
				if (int_answer == 1)
				{
					for (; i < NC_tele; i ++)
						if (rate [i_var].id_tariff == sub [i].tariff.id)
							sub [i].tariff.id = edit_id_tariff;
					save_tariff = false;
				}
				else
					for (; i < NC_tele; i ++)
						if (rate [i_var].id_tariff == sub [i].tariff.id)
							sub [i].tariff.str = no_data;
				rate [i_var].id_tariff = edit_id_tariff;
			}
			else
				flag = true;
				
			printf ("Старый тариф: %s   Новый тариф: ", rate [i_var].tariff);
			fgets (edit_tariff, 80, stdin);
			temp = strchr (edit_tariff, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (edit_tariff [0] != '\0')
				for (i = 0; i < NC_tariff; i ++)
					if (strcmp (edit_tariff, rate [i].tariff) == 0 && rate [i].del_tariff == true)
					{
						printf ("Ошибка, запись с ФИО \"%s\" уже существует. Оставлено старое значение ФИО.\n", edit_tariff);
						flag = false;
						break;
					}						
			if (flag == true)
				if (edit_tariff [0] != '\0')
					strcpy (rate [i_var].tariff, edit_tariff);
				else;
			else
				flag = true;
			
			printf ("Новая запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", rate [i_var].id_tariff, rate [i_var].tariff);
			save_tariff = false;
			break;
		}
		
		case File_Benefit:
		{
			flag_tele = true;
			flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;
			
			printf ("%s\n", contents_dir);
			printf_file (File_Benefit);					
			printf ("\n\nВведите id изменяемой записи:\n");
			scanf ("%s", temp_char);
			getchar ();
			temp_int = atoi (temp_char);			
				
			for (i_var = 0; i_var < NC_benefit; i_var ++)
				if (temp_int == priv [i_var].id_benefit)
				{
					flag = false;
					break;
				}
			if (flag == true)
				if (temp_int == 0)
				{
					printf ("Ошибка, записи с id \"%d\" не существует.\n", temp_int);
					getchar ();
					return;
				}
				else
				{
					printf ("Ошибка, вводимое значение должно быть положительным числом.\n");
					getchar ();
					return;
				}
			else
				flag = true;
			
			printf ("Введите новое значение или id записи.\nОставьте поле пустым, если вы не хотите его менять:\n");
			
			printf ("Старый id: %d   Новое id: ", priv [i_var].id_benefit);
			fgets (temp_char, 40, stdin);
			edit_id_benefit = atoi (temp_char);
			if (edit_id_benefit != 0)
				for (i = 0; i < NC_benefit; i ++)
					if (edit_id_benefit == priv [i].id_benefit && priv [i].del_benefit == true)
					{
						printf ("Ошибка, запись с id \"%d\" уже существует. Оставлено старое значение id.\n", edit_id_benefit);
						flag = false;
						break;
					}
					else;
			else if (strlen (temp_char) == 0)
					printf ("Ошибка, вводимое значение должно быть числом. Оставлено старое значение id.\n");		
			if (flag == true && edit_id_benefit != 0)
			{
				for (i = 0; i < NC_tele; i ++)
					if (priv [i_var].id_benefit == sub [i].benefit.id)
					{
						printf ("Внимание, запись с id \"%d\", которую вы хотите изменить, используется в документе.\n", priv [i_var].id_benefit);
						printf ("Вы хотите изменить одну или несколько аналогичных записей в документе? Да (1), Нет (0): ");
						scanf ("%d", &int_answer);
						getchar ();
						break;
					}			
				if (int_answer == 1)
				{
					for (; i < NC_tele; i ++)
						if (priv [i_var].id_benefit == sub [i].benefit.id)
							sub [i].benefit.id = edit_id_benefit;
					save_benefit = false;
				}
				else
					for (; i < NC_tele; i ++)
						if (priv [i_var].id_benefit == sub [i].benefit.id)
							sub [i].benefit.str = no_data;
				priv [i_var].id_benefit = edit_id_benefit;
			}
			else
				flag = true;
				
			printf ("Старая льгота: %s   Новая льгота: ", priv [i_var].benefit);
			fgets (edit_benefit, 80, stdin);
			temp = strchr (edit_benefit, '\n');
			if (temp != NULL)
				*temp = '\0';
			if (edit_benefit [0] != '\0')
				for (i = 0; i < NC_benefit; i ++)
					if (strcmp (edit_benefit, priv [i].benefit) == 0 && priv [i].del_benefit == true)
					{
						printf ("Ошибка, запись с ФИО \"%s\" уже существует. Оставлено старое значение ФИО.\n", edit_benefit);
						flag = false;
						break;
					}						
			if (flag == true)
				if (edit_benefit [0] != '\0')
					strcpy (priv [i_var].benefit, edit_benefit);
				else;
			else
				flag = true;
			
			printf ("Новая запись:\n");	
			printf ("%s\n", contents_dir);
			printf ("\n %3d %5s", priv [i_var].id_benefit, priv [i_var].benefit);
			save_benefit = false;
			break;
		}
	}	
	getchar ();
}

/**
 * @fn remove_record
 * @brief Функция для удаления записи из файла
 * Принимает тип файла, с которым она должна работать, ничего не возвращает
 * @param i, j - переменные цикла
 * @param res - переменная, в которую передаётся возвращение функции "insp_file"
 * @param del_id - значение i, которое совпадает с значением удаляемой записи
 * @param *temp - временная переменная
 * @param int_answer - ответ пользователей на вопрос открытия файлов
 * @param temp_char - временная переменная
 * @param flag - переменная для указания успешности выполнения задачи
 * @param flag_tele, flag_name, flag_tariff, flag_benefit - переменные, которые равны true, если их надо проверять на открытость, иначе - false
 */
void remove_record (enum TypeOfFile type)
{
	int i, j, res, del_id = 0, int_answer;
	char temp_char [80];
	bool flag = false, flag_tele = false, flag_name = false, flag_tariff = false, flag_benefit = false;
	
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
			printf_file (File_Tele);
				
			printf ("\n\nВведите id удаляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			del_id = atoi (temp_char);
			
			if (del_id == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_tele; i ++)
				if (del_id == sub [i].id_tele && sub [i].del_tele == true)
				{
					flag = true;
					break;
				}
			if (flag == false)
			{
				printf ("Ошибка, записи с id \"%d\" не обнаружено.", del_id);
				getchar ();
				return;
			}
			printf ("Удаляемая запись:\n");
			printf ("%s\n", contents);
			printf ("\n %3d %10d   %-30s \t %-10s \t %s", sub [i].id_tele, sub [i].phone_number, sub [i].name.str, sub [i].tariff.str, sub [i].address);
			printf ("\n\nВыберите действие: Удалить запись (1), Назад (0): ");
			scanf ("%d", &int_answer);
			getchar ();
			if (int_answer == 1)
			{
				sub [i].del_tele = false;
				printf ("Запись с id \"%d\" успешно удалена.", del_id);
			}
			else
				return;
			save_tele = false;
			break;
		}
		
		case File_Name:
		{
			flag_tele = true;
			flag_name = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;		
			printf_file (File_Name);
				
			printf ("\n\nВведите id удаляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			del_id = atoi (temp_char);
			
			if (del_id == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_name; i ++)
				if (del_id == fio [i].id_name && fio [i].del_name == true)
				{
					flag = true;
					break;
				}
			if (flag == false)
			{
				printf ("Ошибка, записи с id \"%d\" не обнаружено.", del_id);
				getchar ();
				return;
			}
			
			for (j = 0; j < NC_tele; j ++)
			{
				if (sub [j].name.id == del_id)
				{
					printf ("Внимание, запись с id \"%d\" и ФИО \"%s\", которую вы хотите удалить, используется в документе.\nВы действительно хотите её удалить? Да (1), Назад (0): ", del_id, fio [i].name);
					scanf ("%d", &int_answer);
					getchar ();					
					if (int_answer == 1)
					{
						fio [i].del_name = false;
						sub [j].name.str = no_data;
					}
					else
						return;
					break;
				}
			}
			printf ("Запись с id \"%d\" успешно удалена.", del_id);
			save_name = false;
			break;
		}
				
		case File_Tariff:
		{
			flag_tele = true;
			flag_tariff = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;						
			printf_file (File_Tariff);
				
			printf ("\n\nВведите id удаляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			del_id = atoi (temp_char);
			
			if (del_id == 0)
			{
				printf ("Ошибка, вводимое значение id должно быть положительным числом.");
				getchar ();
				return;
			}
			for (i = 0; i < NC_tariff; i ++)
				if (del_id == rate [i].id_tariff && rate [i].del_tariff == true)
				{
					flag = true;
					break;
				}
			if (flag == false)
			{
				printf ("Ошибка, записи с id \"%d\" не обнаружено.", del_id);
				getchar ();
				return;
			}
			
			for (j = 0; j < NC_tele; j ++)
			{
				if (sub [j].tariff.id == del_id)
				{
					printf ("Внимание, запись с id \"%d\" и тарифом \"%s\", которую вы хотите удалить, используется в документе.\nВы действительно хотите её удалить? Да (1), Назад (0): ", del_id, rate [i].tariff);
					scanf ("%d", &int_answer);
					getchar ();					
					if (int_answer == 1)
					{
						rate [i].del_tariff = false;
						sub [j].tariff.str = no_data;
					}
					else
						return;
					break;
				}
			}
			
			printf ("Запись с id \"%d\" успешно удалена.", del_id);
			save_tariff = false;
			break;	
		}
		
		case File_Benefit:
		{
			flag_tele = true;
			flag_benefit = true;
			res = insp_file (flag_tele, flag_name, flag_tariff, flag_benefit);
			if (res == 0)
				return;		
			printf_file (File_Benefit);
				
			printf ("\n\nВведите id удаляемой записи: ");
			scanf ("%s", temp_char);
			getchar ();
			del_id = atoi (temp_char);
			
			for (i = 0; i < NC_benefit; i ++)
				if (del_id == priv [i].id_benefit && priv [i].del_benefit == true)
				{
					flag = true;
					break;
				}
			if (flag == false)
			{
				printf ("Ошибка, записи с id \"%d\" не обнаружено.", del_id);
				getchar ();
				return;
			}
			
			for (j = 0; j < NC_tele; j ++)
			{
				if (sub [j].benefit.id == del_id)
				{
					printf ("Внимание, запись с id \"%d\" и льготой \"%s\", которую вы хотите удалить, используется в документе.\nВы действительно хотите её удалить? Да (1), Назад (0): ", del_id, rate [i].tariff);
					scanf ("%d", &int_answer);
					getchar ();					
					if (int_answer == 1)
					{
						priv [i].del_benefit = false;
						sub [j].benefit.str = no_data;
					}
					else
						return;
					break;
				}
			}
			
			printf ("Запись с id \"%d\" успешно удалена.", del_id);
			save_benefit = false;
			break;	
		}
	}
	getchar ();
}
