#include "header/game_main.h"

/* Screen 1 could be startet from everywhere (menubar) -> all widgets from all screens have to become invisible
 */
void next_screen_1_start (gpointer data)
{
	widgets *a = (widgets *) data;

	// Screen 1
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Welcome to Hidden Demon, enter your name, press the Button to choose your Champ");
	gtk_widget_show_all(a->start.layout);

	// Screen 2
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.button, FALSE);

	// Screen 3
	gtk_widget_set_visible(a->wait.button, FALSE);

	// Screen 4
	gtk_widget_set_visible(a->game.playground_layout, FALSE);
	gtk_widget_set_visible(a->game.playground_scroll, FALSE);
	gtk_widget_set_visible(a->game.progressbar_layout, FALSE);
	gtk_widget_set_visible(a->game.sidebar_layout, FALSE);

}

void next_screen_2_choose (GtkWidget *wid, gpointer data)
{

	widgets *a = (widgets *) data;

	a->thisplayer.player_name = (gchar*) gtk_entry_get_text (GTK_ENTRY (a->start.input_entry));

	if(strlen(a->thisplayer.player_name) < 1)
	{
		g_print("Name is too short\n");
		next_screen_1_start((gpointer) a);
	}else{

		//g_object_unref(a->start.input_entry);
		communicate((gpointer) a); // initialisation

		// Screen 1
		gtk_widget_set_visible(a->start.layout, FALSE);
		gtk_widget_set_visible(a->start.button, FALSE);

		gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
		gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Choose your champion and the level");

		gtk_widget_show_all(a->choose.layout);
		gtk_widget_show_all(a->choose.layout);
		gtk_widget_set_visible(a->choose.button, TRUE);
		gtk_widget_set_sensitive (a->choose.button, FALSE);
	}


}

void next_screen_3_wait (GtkWidget *wid, gpointer data)
{
	widgets *a = (widgets *) data;

	get_level((gpointer) a);

	// Screen 2
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.button, FALSE);

	// Screen 3
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Wait, until everyone is connected");

	gtk_widget_show(a->wait.button);

}

void next_screen_4_in_game (GtkWidget *wid, gpointer data)
{
	widgets *a = (widgets *) data;

	init_position((gpointer) a);

	// Screen 3
	gtk_widget_set_visible(a->wait.button, FALSE);


	// Screen 4
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "ToDo: Destroy the Nexus from the other team");

	gtk_widget_show_all(a->game.playground_layout);
	gtk_widget_show_all(a->game.playground_scroll);
	gtk_widget_show_all(a->game.progressbar_layout);
	gtk_widget_show_all(a->game.sidebar_layout);

}
