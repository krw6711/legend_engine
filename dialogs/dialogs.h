#ifndef DIALOGS_H
#define DIALOGS_H

#define DIALOGS_AMOUNT 5

extern char *dialogs;
extern long file_length;

int init_dialogs(void);
int get_dialog_cursor_by_id(int id);
int get_dialog_length_by_cursor(int cursor);
int redner_dialog_by_id(int id);

#endif