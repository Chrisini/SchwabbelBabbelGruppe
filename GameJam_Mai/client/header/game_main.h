#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>

#define MAX_STEP_NUMBER 2

typedef struct {
	GtkApplication *app;
	GtkWidget *window;
} widgets;

struct but_field{
	GtkWidget *name;
	int invisible; // 1 = invisible, 0 = visible
	GtkWidget *nex_1;
	GtkWidget *nex_2;
	GtkWidget *nex_3;
	GtkWidget *nex_4;
	GtkWidget *nex_5;
	GtkWidget *nex_6;
};

typedef struct but_field BUTTONS;

typedef struct{
	char ability_name[30];
	int ability_max;
	int ability_fill;
	int ability_regeneration;
}abilities;

typedef struct {
	char player_name[30];
	int player_id;
	abilities life;
	abilities ability1;
	abilities ability2;
	abilities ability3;
	abilities ult;
}player;

typedef struct {
	GtkWidget *button;
	int col;
	int enabled; // enabled = 1, disabled = 0
}playground;

// PROTOTYPES

void activate (GtkApplication *app, gpointer user_data);

void create_progress (GtkApplication *app, GtkWidget *box, gpointer user_data);
void create_menu (GtkApplication *app, GtkWidget *box, gpointer user_data);
void create_sidebar (GtkApplication *app, GtkWidget *box, gpointer user_data);
void create_info(GtkApplication *app, GtkWidget *box, gpointer user_data);
void create_playground (GtkApplication *app, GtkWidget *box, gpointer user_data);

void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data);

void but_life(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_twice(GSimpleAction *action, GVariant *parameter, gpointer data);
//void but_ability1(GSimpleAction *action, GVariant *parameter, gpointer data);
//void but_ability2(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_ability(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_ult(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_base(GSimpleAction *action, GVariant *parameter, gpointer data);

void step_to_but(GSimpleAction *action, GVariant *parameter, gpointer data);


#endif
