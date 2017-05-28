#include "header/game_main.h"

void next_screen_2 (gpointer data)
{

	widgets *a = (widgets *) data;

	// Screen 1
	gtk_widget_set_visible(a->start_layout, FALSE);
	gtk_widget_set_visible(a->start_button, FALSE);

	// Screen 2
	gtk_widget_show_all(a->choose_grid);


}

void next_screen_3 (GSimpleAction *action, GVariant *parameter, gpointer data)
{

}
