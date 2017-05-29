#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>

#define MAX_STEP_NUMBER 2

typedef struct {
	GtkApplication *app;
	GtkWidget *window;
	GtkWidget *main_box;
	GtkWidget *sub_box;
	//GtkWidget *grid;
	gboolean visible;
	GtkStyleProvider *css_style;
	// FUNCTION - WIDGETS
	// info
	GtkWidget *info_grid;
	GtkWidget *info_label;
	// startscreen
	GtkWidget *start_layout;
	GtkWidget *start_button;
	// choose
	GtkWidget *choose_layout;
	GtkWidget *choose_button;
	// in game
	GtkWidget *in_playground_layout;
	GtkWidget *in_playground_scroll;
	GtkWidget *in_progressbar_layout;
	GtkWidget *in_sidebar_layout;
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
	gchar ability_name;
	gint ability_max;
	gint ability_fill;
	gint ability_regeneration;
}abilities;

typedef struct {
	gchar name;
	gint id;
	GtkWidget *image;
	abilities life;
	//abilities ability1;
	//abilities ability2;
	abilities ability;
	abilities ult;
}champ;

typedef struct {
	GtkWidget *button;
	int col;
	int enabled; // enabled = 1, disabled = 0
}playground;

// PROTOTYPES

// GAME
void activate (GtkApplication *app, gpointer data);
void apply_css(GtkWidget *widget, GtkStyleProvider *css_s);
// info
void create_info(gpointer data);
// menu
void create_menu (gpointer data);
void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data);
void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data);

// START (1)
void next_screen_1_start (gpointer data); // visible


// CHOOSE (2)
void choose_game(gpointer data);
void next_screen_2_choose (gpointer data); // visible
void create_champions(/*gpointer champ_data, */gpointer data);

// WAIT (3)

// IN GAME (4)
void in_game(gpointer data);
void next_screen_4_in_game (gpointer data);
// progress
void create_progress (gpointer data);
// plaground
void create_playground (gpointer data);
void step_to_but(GSimpleAction *action, GVariant *parameter, gpointer data);
// sidebar
void create_sidebar (gpointer data);
void but_life(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_twice(GSimpleAction *action, GVariant *parameter, gpointer data);
//void but_ability1(GSimpleAction *action, GVariant *parameter, gpointer data);
//void but_ability2(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_ability(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_ult(GSimpleAction *action, GVariant *parameter, gpointer data);
void but_base(GSimpleAction *action, GVariant *parameter, gpointer data);




#endif
