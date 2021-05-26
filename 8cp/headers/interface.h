#ifndef _INTERFACE_H
#define _INTERFACE_H

#define STRING_CAPACITY 512

void          clear_from_tabs(char* _word);
bool          is_command     (char* _word);
bool          is_spaces      (char* _word);
bool          read_command   (char* _word);
void          read_arguments (char* _word);
void          help           ();

void          print_error    (char* _msg);
void          print_note     (char* _msg);
void          print_interface(char* _msg);

#endif