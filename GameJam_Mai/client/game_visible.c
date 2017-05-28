#include "header/game_main.h"

void next_screen_2 (gpointer data)
{

	widgets *a = (widgets *) data;



	//gtk_widget_hide(GTK_WIDGET(a->start_layout));
	//gtk_widget_hide(GTK_WIDGET(a->start_button));
	//gtk_widget_set_visible(a->start_layout, FALSE);
	gtk_widget_set_visible(a->start_button, FALSE);

	gtk_widget_set_visible(a->info_grid, TRUE);
	gtk_widget_set_visible(a->info_label, TRUE);

}

void next_screen_3 (GSimpleAction *action, GVariant *parameter, gpointer data)
{

}
