#ifndef FILE_OPERATIONS_H_INCLUDED
#define FILE_OPERATIONS_H_INCLUDED

void open_file (enum TypeOfFile type);
void read_file (enum TypeOfFile type);
void save_file (enum TypeOfFile type);
int insp_file (bool flag_tele, bool flag_name, bool flag_tariff, bool flag_benefit);
void warning_save (bool flag_tele, bool flag_name, bool flag_tariff, bool flag_benefit);
void close_file (enum TypeOfFile type);

#endif // FILE_OPERATIONS_INCLUDED
