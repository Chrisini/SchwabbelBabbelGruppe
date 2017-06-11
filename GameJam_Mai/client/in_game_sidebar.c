#include "header/game_main.h"

const GActionEntry app_entries_but[] = {
	{ "life", but_life, NULL, NULL, NULL},
	{ "twice", but_twice, NULL, NULL, NULL},
	{ "ability", but_ability, NULL, NULL, NULL},
	{ "ult", but_ult, NULL, NULL, NULL},
	{ "base", but_base, NULL, NULL, NULL}
};

void create_sidebar (gpointer data)
{

	widgets *a = (widgets *) data;

	GtkWidget *button;

	// layout containers *****
	a->game.sidebar_layout = gtk_grid_new();


	char c_life[2] = {"l"};
	char c_twice[2] = {"2"};
	//char c_ability1[2] = {"q"};
	//char c_ability2[2] = {"w"};
	char c_ability[2] = {"e"};
	char c_ult[2] = {"r"};
	char c_base[2] = {"b"};

	// keyboard accelerators
	const gchar *accels_life[2] = {c_life, NULL};
	const gchar *accels_twice[2] = {c_twice, NULL};
	//const gchar *accels_ability1[2] = {c_ability1, NULL};
	//const gchar *accels_ability2[2] = {c_ability2, NULL};
	const gchar *accels_ability[2] = {c_ability, NULL};
	const gchar *accels_ult[2] = {c_ult, NULL};
	const gchar *accels_base[2] = {c_base, NULL};


	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (a->app), app_entries_but,
					 G_N_ELEMENTS (app_entries_but), (gpointer) a);

	// Shop Button
	// display only, when player is in the base
	button = gtk_button_new_with_label ("Shop");
	g_signal_connect_swapped (button, "clicked", G_CALLBACK (shop_popup), (gpointer) a);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 0, 0, 1, 1);

	// ability - buttons *****
	// Base - B
	button = gtk_button_new_with_label ("Base");
	g_signal_connect (button, "clicked", G_CALLBACK (but_base), NULL);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 1, 0, 1, 1);
	// Life - Lebenspunkte aufladen
	button = gtk_button_new_with_label ("Life");
	g_signal_connect (button, "clicked", G_CALLBACK (but_life), NULL);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 1, 1, 1, 1);
	// Ability - Q - Point / Click Ability
	//button = gtk_button_new_with_label ("ability 1");
	//g_signal_connect (button, "clicked", G_CALLBACK (but_ability1), NULL);
	//gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 0, 2, 1, 1);
	// Ability - W - Area / Flaechenschaden
	//button = gtk_button_new_with_label ("ability 2");
	//g_signal_connect (button, "clicked", G_CALLBACK (but_ability2), NULL);
	//gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 0, 3, 1, 1);
	// Ability - E - passive damage
	button = gtk_button_new_with_label ("Ability");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability), NULL);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 1, 4, 1, 1);
	// Ability  - R - ulti
	button = gtk_button_new_with_label ("Ult");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ult), NULL);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 1, 5, 1, 1);
	// Two turns for Mr X
	button = gtk_button_new_with_label ("x2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_twice), NULL);
	gtk_grid_attach (GTK_GRID (a->game.sidebar_layout), button, 1, 6, 1, 1);

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.life", accels_life);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.twice", accels_twice);
	//gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability1", accels_ability1);
	//gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability2", accels_ability2);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.ability", accels_ability);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.ult", accels_ult);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.base", accels_base);

	gtk_box_pack_end(GTK_BOX(a->sub_box), (a->game.sidebar_layout), FALSE, FALSE,0);
}


void but_life(GSimpleAction *action, GVariant *parameter, gpointer data)
{}

void but_twice(GSimpleAction *action, GVariant *parameter, gpointer data)
{}

//void but_ability1(GSimpleAction *action, GVariant *parameter, gpointer data){}
//void but_ability2(GSimpleAction *action, GVariant *parameter, gpointer data){}

void but_ability(GSimpleAction *action, GVariant *parameter, gpointer data)
{}

void but_ult(GSimpleAction *action, GVariant *parameter, gpointer data)
{}


void but_base(GSimpleAction *action, GVariant *parameter, gpointer data)
{}

