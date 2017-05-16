#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <gtk/gtk.h>

typedef struct {
	GtkApplication *app;
	GtkWidget *window;
} widgets;

// PROTOTYPES
#include "header/game_main.h"


void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_quit(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data);


#endif
