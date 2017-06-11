#include "header/game_main.h"

/* Screen 1 could be startet from everywhere (menubar) -> all widgets from all screens have to become invisible
 */
void next_screen_1_start (gpointer data)
{
	widgets *a = (widgets *) data;

	// Screen 1
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Welcome to Hidden Demon, press the Button to choose your Champ");
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

	music_player();

}

void next_screen_2_choose (gpointer data)
{

	widgets *a = (widgets *) data;

	// Screen 1
	gtk_widget_set_visible(a->start.layout, FALSE);
	gtk_widget_set_visible(a->start.button, FALSE);

	// Screen 2
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Choose your champion and the level");

	gtk_widget_show_all(a->choose.layout);
	gtk_widget_show_all(a->choose.layout);
	gtk_widget_set_visible(a->choose.button, TRUE);


}

void next_screen_3_wait (gpointer data)
{
	widgets *a = (widgets *) data;

	// Screen 2
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.layout, FALSE);
	gtk_widget_set_visible(a->choose.button, FALSE);

	// Screen 3
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Wait, until everyone is connected");

	gtk_widget_show(a->wait.button);

}

void next_screen_4_in_game (gpointer data)
{
	widgets *a = (widgets *) data;


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
