#ifndef TPDATABASE_H_INCLUDED
#define TPDATABASE_H_INCLUDED

struct Tele
{
	int id_tele;		/// @param id_tele - id записи документа
	int phone_number;	/// @param phone_number - номер телефона
	struct				/// Структура с id структуры Name и указателем на её второе значение - имя
	{
		int id;
		char *str;
	} name;
	struct				/// Структура с id структуры Tariff и указателем на её второе значение - тариф
	{
		int id;
		char *str;
	} tariff;
	char address [80];	/// @param address - адрес.
	struct				/// Структура с id структуры Benefit и указателем на её второе значение - льгота
	{
		int id;
		char *str;
	} benefit;
	bool del_tele;		/// @param del_tele - значение, которое равно true, если запись не удалена и false, если удалена
} *sub;

struct Name
{
	int id_name;		/// @param id_name - id записи справочника
	char name [50];		/// @param name - имя, на которое ссылается указатель во втором значении вложенной структуры Tele
	bool del_name;		/// @param del_name - значение, которое равно true, если запись не удалена и false, если удалена
} *fio;

struct Tariff
{
	int id_tariff;		/// @param id_tariff - id записи справочника.
	char tariff [50];	/// @param tariff - nариф, на который ссылается указатель во втором значении вложенной структуры Tele
	bool del_tariff;	/// @param del_tariff - значение, которое равно true, если запись не удалена и false, если удалена
} *rate;

struct Benefit
{
	int id_benefit;		/// @param id_benefit - id записи справочника.
	char benefit [50];	/// @param benefit - льгота, на которую ссылается указатель во втором значении вложенной структуры Tele
	bool del_benefit;	/// @param del_benefit - значение, которое равно true, если запись не удалена и false, если удалена
} *priv;

///Эта структура позволяет обращаться к указателям файлов
struct 
{
	FILE *tele;
	FILE *name;
	FILE *tariff;
	FILE *benefit;
} files = {NULL, NULL, NULL, NULL};

///@details Данная конструкция позволяет передавать функциям тип файлов
enum TypeOfFile
{
	File_Tele, File_Name, File_Tariff, File_Benefit
};

///@details Данная конструкция позволяет пердавать функции referance тип справки, которую нужно вывести
enum TypeOfReference
{
	general_info, ref_file, ref_edit_doc, ref_printf_doc, ref_record_doc, ref_directory, ref_about_program
};

///@details Данная конструкция позволяет определить тип ОС пользователя
enum TypeOfOS 
{
	WIN, LIN, MAC, UNKN
};

/** NC_*** - переменные, обозначающие количество записей в соответствующем файле
 * NC_***_max - переменнные, хранящие максимальное количество записей
 */
int NC_tele = 0, NC_name = 0, NC_tariff = 0, NC_benefit = 0, NC_tele_max, NC_name_max, NC_tariff_max, NC_benefit_max;

///Главное меню, которое выводится при запуске программы
char main_menu [8][80] =
{
	"1) Файл",
	"2) Редактировать документ",
	"3) Вывести на экран документ",
	"4) Записать документ в файл txt",
	"5) Справочник",
	"6) Помощь",
	"7) О программе",
	"8) Выход"
};

///Меню, выводящаяся при выборе пункта меню "Файл"
char file_menu [4][50] =
{
	"1. Открыть",
	"2. Сохранить",
	"3. Закрыть",
	"4. Назад"
};
	
///Меню, выводящаяся при выборе пункта меню "Редактирование документа"
char edit_doc_menu [4][80] =
{
	"1. Добавить запись",
	"2. Удалить запись",
	"3. Редактировать существующую запись",
	"4. Назад"
};

///Меню, выводящаяся при выборе пункта меню "Справочник"
char directory_menu [8][80] =
{
	"1. Открыть справочник",
	"2. Редактировать запись в справочнике",
	"3. Добавить запись в справочник",
	"4. Удалить запись",
	"5. Закрыть справочник",
	"6. Добавать еще один справочник",
	"7. Вывести на экран",
	"8. Назад"
};
	
char welcome [] = "Выберите пункт меню при помощи цифр и нажмите ENTER";
char contents [] = "  id  Телефон            ФИО               Тариф               Адрес";
char contents_add [] = "  id  Телефон            ФИО               Тариф               Адрес          Запись справочника";
char contents_dir [] = "  id Запись справочника";
char no_data [] = "(нет данных)";

/// Данная логическая переменная равна false, если третий справочник не добавлен и true, если он добавлен
bool third_dir = false;
/// Данная логическая переменная равна false, если изменения не сохранены и true, если изменений не было или они сохранены
bool save_tele = true;
bool save_name = true;
bool save_tariff = true;
bool save_benefit = true;

void printf_file (enum TypeOfFile type);
void save_file (enum TypeOfFile type);
void warning_save (bool flag_tele, bool flag_name, bool flag_tariff, bool flag_benefit);

/// Функции

int type_of_os ();
void clear_screen ();
int reference (enum TypeOfReference type);
void file ();
void edit_doc ();
void printf_doc ();
void record_doc ();
void directory ();
void help ();
void about_program ();


#endif // TPDATABASE_INCLUDED
