#ifndef GAME_MAIN_H
#define GAME_MAIN_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <gst/gst.h>
#include <glib.h>
#include <string.h>

#define MAX_STEP_NUMBER 2

typedef struct{
	GtkWidget *layout;
	GtkWidget *statusbar;
	guint id;
}info_struct;

typedef struct{
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *input_entry;
}start_struct;

typedef struct{
	GtkWidget *layout;
	GtkWidget *button;
	GtkWidget *grid;
}choose_struct;

typedef struct{
	GtkWidget *button;
}wait_struct;

typedef struct { // array -60x
	GtkWidget *name;
	int enable; // 1 = enable, 0 = disable
	GtkWidget *beside_1;
	GtkWidget *beside_2;
	GtkWidget *beside_3;
	GtkWidget *beside_4;
}fieldbutton_struct;

typedef struct{
	GtkWidget *playground_layout;
	GtkWidget *playground_scroll;
	GtkWidget *progressbar_layout;
	GtkWidget *sidebar_layout;
	fieldbutton_struct *fieldbutton;
}game_struct;

typedef struct{
	gchar *ability_name;
	gint ability_max; // Max Fuellstatus zb 40 oder 100
	gdouble ability_fill; // Fuellstatus 0.0 - 1.0
	gint ability_regeneration; // how long it takes, until regenerated (round / move / time)
}abilities_struct;

typedef struct { // array - 8x
	gchar *name;
	gchar *state;
	gboolean *is_in_game;
	gint id;
	gint position;
	gchar *image_path;
	abilities_struct life;
	//abilities ability1;
	//abilities ability2;
	abilities_struct ability;
	abilities_struct ult;
}champ_struct;

typedef struct{
	GMainLoop *loop;
	GstElement *source;
	GstElement *demuxer;
	GstElement *decoder;
	GstElement *conv;
	GstElement *sink;
  	GstBus *bus;
  	guint bus_watch_id;
	GstElement *pipeline;
}music_struct;


typedef struct {
	GtkApplication *app;
	GtkWidget *window;
	GtkWidget *main_box;
	GtkWidget *sub_box;
	GtkStyleProvider *css_style;
	gchar *player_name;
	gint player_id;
	GSocketConnection * socket_connection;
	gchar message_buf[1024];
	// FUNCTION - WIDGETS
	info_struct info; // statusbar
	start_struct start; // startscreen
	choose_struct choose; // choose champs screen
	wait_struct wait; // wait screen / connecting of champs
	game_struct game; // in game
	champ_struct *champ; // struct of all champions
	music_struct music;
} widgets;

// PROTOTYPES

// GAME (0) *****
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

// START (1) *****
void next_screen_1_start (gpointer data); // visible


// CHOOSE (2) *****
void choose_game(gpointer data);
void next_screen_2_choose (GtkWidget *wid, gpointer data); // visible
void create_champions(gpointer data);
void generate_champions(gint i[1], gpointer data);
void open_file(gpointer data);

// WAIT (3) *****
void wait_connect(gpointer data);
void next_screen_3_wait (GtkWidget *wid, gpointer data); // visible

// IN GAME (4) *****
void in_game(gpointer data);
void next_screen_4_in_game (GtkWidget *wid, gpointer data); // visible
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
// shop
void shop_popup(GtkWidget *wid, gpointer data); // callback
void destroy(GtkDialog *dialog, gint response_id);

// music
void music_player (gpointer data);
void play_music (gpointer data); // callback swapped
void pause_music (gpointer data); // callback swapped
void stop_music (gpointer data); // callback swapped
void quit_music(gpointer data);

void communicate(gpointer data);

#endif
