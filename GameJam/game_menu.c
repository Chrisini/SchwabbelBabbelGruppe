#include "header/game_main.h"

static void create_menu (GtkApplication *app, GtkWidget *box, gpointer user_data)
{
	widgets *a = (widgets *) user_data;

	GtkWidget *menubar;
	GMenu *menu, *menu_game, *menu_settings, *menu_help, *menu_exit;

	char c_music[2] = {"m"};

	// keyboard accelerators
	const gchar *accels_music[2] = {c_music, NULL};
	const gchar *accels_help[2] = {"F1", NULL};
	const gchar *accels_exit[2] = {"x", NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// create the menu *****
	menu = g_menu_new();

	// create game *****
	menu_game = g_menu_new();
	g_menu_append (menu_game, "New Game", "app.newgame"); // restart
	g_menu_append (menu_game, "Change lvl", "app.level"); // level
	g_menu_append (menu_game, "High Score", "app.highscore"); // highscore

	menu_exit = g_menu_new();
	g_menu_append (menu_exit, "Exit", "app.exit"); // quit
	g_menu_append_section(menu_game, NULL, G_MENU_MODEL (menu_exit));

	g_menu_insert_submenu (menu, 0, "Game", G_MENU_MODEL (menu_game));
	g_object_unref (menu_exit);


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
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.exit", accels_exit);

}
