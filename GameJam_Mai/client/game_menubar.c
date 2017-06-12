#include "header/game_main.h"

const GActionEntry app_entries[] = {
	{ "newgame", callback_newgame, NULL, NULL, NULL, {0,0,0} },
	{ "level", callback_level, NULL, NULL, NULL, {0,0,0} },
	{ "highscore", callback_highscore, NULL, NULL, NULL, {0,0,0} },
	{ "exit", callback_exit, NULL, NULL, NULL, {0,0,0} },
	{ "music", callback_music, NULL, NULL, NULL, {0,0,0} },
	{ "about", callback_about, NULL, NULL, NULL, {0,0,0} },
	{ "help", callback_help, NULL, NULL, NULL, {0,0,0} }
};

void create_menu (gpointer data)
{
	widgets *a = (widgets *) data;

	GtkWidget *menubar;
	GMenu *menu, *menu_game, *menu_settings, *menu_help, *menu_exit;

	char c_music[2] = {"m"};

	// keyboard accelerators
	const gchar *accels_music[2] = {c_music, NULL};
	const gchar *accels_help[2] = {"F1", NULL};
	const gchar *accels_exit[2] = {"x", NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (a->app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// create the menu *****
	menu = g_menu_new();

	// create menu game *****
	menu_game = g_menu_new();
	g_menu_append (menu_game, "New Game", "app.newgame"); // restart
	g_menu_append (menu_game, "Change lvl", "app.level"); // level
	g_menu_append (menu_game, "High Score", "app.highscore"); // highscore

	// create menu exit ****
	menu_exit = g_menu_new();
	g_menu_append (menu_exit, "Exit", "app.exit"); // quit
	g_menu_append_section(menu_game, NULL, G_MENU_MODEL (menu_exit));

	g_menu_insert_submenu (menu, 0, "Game", G_MENU_MODEL (menu_game));

	g_object_unref (menu_exit);
	g_object_unref (menu_game);


	// create menu settings *****
	menu_settings = g_menu_new();
	g_menu_append (menu_settings, "Music", "app.music");
	g_menu_append_submenu (menu, "Settings", G_MENU_MODEL (menu_settings));
	g_object_unref (menu_settings);


	// create menu help *****
	menu_help = g_menu_new();
	g_menu_append(menu_help, "About", "app.about");
	g_menu_append(menu_help, "Help", "app.help");
	g_menu_append_submenu (menu, "Help", G_MENU_MODEL (menu_help));
	g_object_unref (menu_help);

	// add menus to menu bar *****
	menubar = gtk_menu_bar_new_from_model (G_MENU_MODEL (menu));
	gtk_box_pack_start (GTK_BOX (a->main_box), menubar, FALSE, FALSE, 0);
	gtk_widget_set_name(menubar, "menu");

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.music", accels_music);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.help", accels_help);
	gtk_application_set_accels_for_action (GTK_APPLICATION (a->app), "app.exit", accels_exit);

	gtk_widget_show_all(menubar);
}

void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	next_screen_1_start((gpointer) a);
}

void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("High Scoore is not working");
}

void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	quit_music((gpointer) a);
	g_print("Good Bye\n");
	g_application_quit(G_APPLICATION(a->app));
}

void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *content_area;
	GtkWidget *button_play, *button_pause, *button_stop;

	dialog = gtk_dialog_new_with_buttons("Music",
					     GTK_WINDOW (a->window),
					     GTK_DIALOG_MODAL,
					     ("Close"),
					     GTK_RESPONSE_OK,
					     NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	label = gtk_label_new("Start / Stop the music");
	gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);

	button_play = gtk_button_new_with_label("Play");
	g_signal_connect_swapped(button_play, "clicked", G_CALLBACK(play_music), (gpointer) a);

	button_pause = gtk_button_new_with_label("Pause");
	g_signal_connect_swapped(button_pause, "clicked", G_CALLBACK(pause_music), (gpointer) a);

	button_stop = gtk_button_new_with_label("Stop");
	g_signal_connect_swapped(button_stop, "clicked", G_CALLBACK(stop_music), (gpointer) a);


	gtk_grid_attach(GTK_GRID(grid), button_play, 0,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), button_pause, 1,1,1,1);
	gtk_grid_attach(GTK_GRID(grid), button_stop, 2,1,1,1);

	gtk_widget_show_all(dialog);
	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(destroy), NULL);


}

void close_dialog(GtkDialog *dialog, gint response_id, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(dialog));
}


void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	GdkPixbuf *pixbuf;
	GtkWidget *about_dialog;
	const gchar *authors[] = {"Christina Bornberg", NULL};

	// Image
	pixbuf = gdk_pixbuf_new_from_file("img/logo.png", NULL)	;

	// Layout
	about_dialog = gtk_about_dialog_new();

	gtk_show_about_dialog(GTK_WINDOW (a->window),
			      "program-name", "Hidden Demons",
			      "version", "1.0",
			      "copyright", "Copyright \xc2\xa9 elevariety",
			      "comments", "A game by some beginner-developers\nGraphics: Kathi, Betty\nMusic: Markus, Robin",
			      "authors", authors,
			      "logo", pixbuf,
			      NULL);

	g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_dialog), NULL);

	// Free
	g_object_unref (pixbuf);

}


void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	gboolean set_vis = TRUE;

	if(gtk_widget_get_visible(a->info.layout))
	{
		set_vis = FALSE;
	}

	gtk_widget_set_visible(a->info.layout, set_vis);
	gtk_widget_set_visible(a->info.statusbar, set_vis);

}

