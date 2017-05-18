#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <gtk/gtk.h>

typedef struct {
	GtkApplication *app;
	GtkWidget *window;
} widgets;

// PROTOTYPES

void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data);

void but_life(GtkWidget *widget, gpointer data);
void but_twice(GtkWidget *widget, gpointer data);
void but_ability1(GtkWidget *widget, gpointer data);
void but_ability2(GtkWidget *widget, gpointer data);
void but_ability3(GtkWidget *widget, gpointer data);
void but_ult(GtkWidget *widget, gpointer data);
void but_base(GtkWidget *widget, gpointer data);


const GActionEntry app_entries[] = {
	{ "newgame", callback_newgame, NULL, NULL, NULL, {0,0,0} },
	{ "level", callback_level, NULL, NULL, NULL, {0,0,0} },
	{ "highscore", callback_highscore, NULL, NULL, NULL, {0,0,0} },
	{ "exit", callback_exit, NULL, NULL, NULL, {0,0,0} },
	{ "music", callback_music, NULL, NULL, NULL, {0,0,0} },
	{ "about", callback_about, NULL, NULL, NULL, {0,0,0} },
	{ "help", callback_help, NULL, NULL, NULL, {0,0,0} }

};

#endif
