#ifndef GUI_H
#define GUI_H

/*
 * Module for handling gui, i.e. tray icon.
 */


typedef void (*gui_start_callback_t)(void);


void gui_start(gui_start_callback_t callback);

void gui_set(char *str);


#endif /* GUI_H */
