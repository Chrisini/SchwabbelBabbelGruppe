#include "header/game_main.h"


void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void callback_quit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;
	widgets *all = (widgets *) data;

	dialog = gtk_message_dialog_new_with_buttons ("Quit",
					GTK_WINDOW (a->window),
					GTK_DIALOG_MODAL,
					_ ("_NO"),
					GTK_RESPONSE_CANCEL,
					_ ("YES"),
					GTK_RESPONSE_OK,
					 GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_INFO,
					 GTK_BUTTON_CLOSE,
					 "Do you want to quit?");
	g_signal_connect(dialog, "response",
			 G_CALLBACK (gtk_widget_destroy), NULL);
	gtk_widget_show(dialog);

}

void but_life(GtkWidget *widget, gpointer data)
{}

void but_twice(GtkWidget *widget, gpointer data)
{}

void but_ability1(GtkWidget *widget, gpointer data)
{}

void but_ability2(GtkWidget *widget, gpointer data)
{}

void but_ability3(GtkWidget *widget, gpointer data)
{}

void but_ult(GtkWidget *widget, gpointer data)
{}

void but_base(GtkWidget *widget, gpointer data)
{}

const GActionEntry app_entries[] = {
	{ "music", callback_music, NULL, NULL, NULL, {0,0,0} },
	{ "quit", callback_quit, NULL, NULL, NULL, {0,0,0} }

};

static void create_menu (GtkApplication *app, GtkWidget *box, gpointer user_data)
{
	widgets *a = (widgets *) user_data;

	GtkWidget *menubar;
	GMenu *menu, *menu_game, *menu_settings, *menu_help, *menu_quit;

	char c_music = 'm';

	// keyboard accelerators
	const gchar *accels_music[2] = {c_music, NULL};
	const gchar *accels_help[2] = {"F1", NULL};
	const gchar *accels_quit[2] = {"q", NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// create the menu *****
	menu = g_menu_new();

	// create game *****
	// restart
	// lvl
	// high score
	// quit
	menu_game = g_menu_new();
	g_menu_append (menu_game, "New Game", "app.newgame"); // restart
	g_menu_append (menu_game, "Change lvl", "app.changelvl");
	g_menu_append (menu_game, "High Score", "app.highscore");

	menu_quit = g_menu_new();
	g_menu_append (menu_quit, "Quit", "app.quit");
	g_menu_append_section(menu_game, NULL, G_MENU_MODEL (menu_quit));

	g_menu_insert_submenu (menu, 0, "Game", G_MENU_MODEL (menu_game));
	g_object_unref (menu_quit);


	// create settings *****
	menu_settings = g_menu_new();
	g_menu_append (menu_settings, "Music", "app.music");
	g_menu_append_submenu (menu, "Settings", G_MENU_MODEL (menu_settings));
	g_object_unref (menu_settings);


	// create help *****
	// about
	menu_help = g_menu_new();
	g_menu_append(menu_help, "About", "app.about");
	g_menu_append(menu_help, "Help", "app.help");
	g_menu_append_submenu (menu, "Help", G_MENU_MODEL (menu_help));
	g_object_unref (menu_help);

	// add menus to menu bar *****
	menubar = gtk_menu_bar_new_from_model (G_MENU_MODEL (menu));
	gtk_box_pack_start (GTK_BOX (box), menubar, FALSE, FALSE, 0);

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.music", accels_music);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.help", accels_help);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.quit", accels_quit);


}

static void create_sidebar (GtkApplication *app, GtkWidget *box, gpointer user_data)
{

	widgets *a = (widgets *) user_data;

	GtkWidget *button;


	char c_life = 'l';
	char c_twice = '2';
	char c_ability1 = 'q';
	char c_ability2 = 'w';
	char c_ability3 = 'e';
	char c_ult = 'r';
	char c_base = 'b';

	// keyboard accelerators
	const gchar *accels_life[2] = {c_life, NULL};
	const gchar *accels_twice[2] = {c_twice, NULL};
	const gchar *accels_ability1[2] = {c_ability1, NULL};
	const gchar *accels_ability2[2] = {c_ability2, NULL};
	const gchar *accels_ability3[2] = {c_ability3, NULL};
	const gchar *accels_ult[2] = {c_ult, NULL};
	const gchar *accels_base[2] = {c_base, NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// ability - buttons *****
	// Life - Lebenspunkte aufladen
	button = gtk_button_new_with_label ("Life");
	g_signal_connect (button, "clicked", G_CALLBACK (but_life), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
	// Two turns for Mr X
	button = gtk_button_new_with_label ("x2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_twice), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);
	// Ability - Q - Point / Click Ability
	button = gtk_button_new_with_label ("ability 1");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability1), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);
	// Ability - W - Area / Flaechenschaden
	button = gtk_button_new_with_label ("ability 2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability2), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);
	// Ability - E - passive damage
	button = gtk_button_new_with_label ("ability 3");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability3), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 1, 1);
	// Ability  - R - ulti
	button = gtk_button_new_with_label ("ult");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ult), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 6, 0, 1, 1);
	// Base - B
	button = gtk_button_new_with_label ("base");
	g_signal_connect (button, "clicked", G_CALLBACK (but_base), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 7, 0, 1, 1);

}

static void create_prgress (GtkApplication *app, GtkApplication *box, gpointer user_data)
{
	widgets *a = (widgets *) user_data;
	GtkWidget *progb_attack;

	int progb_timer;

	// attack - Schaden
	progb_attack = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_attack, 1, 10, 3, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_attack), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_attack), NULL);
	gdouble val;
	val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_attack)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_attack), val);
	/*progb_protection = // Ruestung
	progb_life = // Leben
	progb_energy = // Energie
	progb_dead = // Time until live again
	*/
}

static void activate (GtkApplication *app, gpointer user_data)
{
	widgets *a = (widgets *) user_data;

	GtkWidget *box;

	// create window and set title *****
	a->window = gtk_application_window_new (app);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (app));
	gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW (a->window), "Game Jam");
	gtk_window_set_default_size (GTK_WINDOW (a->window), 400, 400);


	// layout containers *****
	// grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);

	// menu *****


	// ability *****


	// regeneration - progress bar *****

	// show all widgets
	gtk_widget_show_all (a->window);
}

int main (int argc, char **argv)
{
	int status;

	widgets *a = g_malloc (sizeof(widgets));

	a->app = gtk_application_new ("org.gtk.game", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (a->app, "activate", G_CALLBACK (activate), (gpointer) a);
	status = g_application_run (G_APPLICATION (a->app), argc, argv);
	g_object_unref (a->app);

	g_free (a);
	return status;
}
