#include "header/game_main.h"

static void create_sidebar (GtkApplication *app, GtkWidget *box, gpointer user_data)
{

	widgets *a = (widgets *) user_data;

	GtkWidget *button;
	GtkWidget *grid;

	// layout containers *****
	grid = gtk_grid_new ();
	// gtk_container_add (GTK_CONTAINER (a->window), grid);

	char c_life[2] = {"l"};
	char c_twice[2] = {"2"};
	char c_ability1[2] = {"q"};
	char c_ability2[2] = {"w"};
	char c_ability3[2] = {"e"};
	char c_ult[2] = {"r"};
	char c_base[2] = {"b"};

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
	gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);
	// Two turns for Mr X
	button = gtk_button_new_with_label ("x2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_twice), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);
	// Ability - Q - Point / Click Ability
	button = gtk_button_new_with_label ("ability 1");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability1), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
	// Ability - W - Area / Flaechenschaden
	button = gtk_button_new_with_label ("ability 2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability2), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);
	// Ability - E - passive damage
	button = gtk_button_new_with_label ("ability 3");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability3), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 1, 1);
	// Ability  - R - ulti
	button = gtk_button_new_with_label ("ult");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ult), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 1, 1);
	// Base - B
	button = gtk_button_new_with_label ("base");
	g_signal_connect (button, "clicked", G_CALLBACK (but_base), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 7, 1, 1);

		// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.life", accels_life);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.twice", accels_twice);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability1", accels_ability1);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability2", accels_ability2);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability3", accels_ability3);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ult", accels_ult);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.base", accels_base);
//	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.help", accels_help);
//	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.exit", accels_exit);
//	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.music", accels_music);
//	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.help", accels_help);
//	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.exit", accels_exit);

	gtk_box_pack_end(GTK_BOX(box), grid, FALSE, FALSE,0);

}
