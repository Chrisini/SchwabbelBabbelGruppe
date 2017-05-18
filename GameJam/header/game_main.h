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
void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data);

#include "header/game_main.h"

void but_life(GtkWidget *widget, gpointer data);
void but_twice(GtkWidget *widget, gpointer data);
void but_ability1(GtkWidget *widget, gpointer data);
void but_ability2(GtkWidget *widget, gpointer data);
void but_ability3(GtkWidget *widget, gpointer data);
void but_ult(GtkWidget *widget, gpointer data);
void but_base(GtkWidget *widget, gpointer data);

#endif
