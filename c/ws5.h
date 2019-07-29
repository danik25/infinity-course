#ifndef _WS5_H_
#define _WS5_H_

/*enum definition*/
enum Boolean { False, True };

/*comparison functions*/  
int  Cmp( char *str_user, char *str_array );

/*removes the file*/
enum Boolean RemoveCommand(char *file_name);

/*counts the commands lines on the file*/
enum Boolean CountCommand(char *file_name);

/*exits the program*/
enum Boolean ExitCommand(char *file_name);

/*a function that pre-append a string when a "<" is entered*/
void InsertFirstCommand(char *str_user, char *file_name);

void Logger(char *file_name);


#endif
