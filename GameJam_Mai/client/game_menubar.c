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

	// create menu exit *****							  //
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
	g_print("Music");
}

void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;

	g_print("Good Bye\n");
	g_application_quit(G_APPLICATION(a->app));
	/*GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;
	widgets *a = (widgets *) data;

	dialog = gtk_message_dialog_new_with_buttons ("Quit",
					GTK_WINDOW (a->window),
					GTK_DIALOG_MODAL,
					_ ("_NO"),
					GTK_RESPONSE_CANCEL,
					_ ("YES"),
					GTK_RESPONSE_OK,
					 GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_INFO,
					 //GTK_BUTTON_CLOSE,
					 "Do you want to quit?");
	g_signal_connect(dialog, "response",
			 G_CALLBACK (gtk_widget_destroy), NULL);*/
	//gtk_widget_show(dialog);

}

void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
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
	about_dialog = gtk_about_dialog_new();
	pixbuf = gdk_pixbuf_new_from_file("img/logo.png", NULL)	;
	gtk_show_about_dialog(GTK_WINDOW (a->window),
			      "program-name", "Hidden Demons",
			      "version", "1.0",
			      "copyright", "Copyright \xc2\xa9 elevariety",
			      "comments", "A game by some beginner-developers\nGraphics: Kathi, Betty\nMusic: Markus, Robin",
			      "authors", authors,
			      "logo", pixbuf,
			      NULL);

	g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_dialog), NULL);
	g_object_unref (pixbuf);

}


void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	widgets *a = (widgets *) data;
	gboolean set_vis = TRUE;

	if(gtk_widget_get_visible(a->info_grid))
	{
		set_vis = FALSE;
	}

	gtk_widget_set_visible(a->info_grid, set_vis);
	gtk_widget_set_visible(a->info_label, set_vis);

}

