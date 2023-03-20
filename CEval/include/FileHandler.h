/* date = November 4th 2021 9:03 am */

#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

char *read_file(const char *fileName);

int file_exists(char *file_name);

void file_write(char *file_name, char *frmt, char *content);
#endif //_FILE_HANDLER_H
