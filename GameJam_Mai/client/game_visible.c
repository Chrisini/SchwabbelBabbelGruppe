#include "header/game_main.h"

void next_screen_1_start (gpointer data)
{
	widgets *a = (widgets *) data;

	// Screen 1
	gtk_label_set_text(GTK_LABEL(a->info_label), "Welcome to Hidden Demon, press the Button to choose your Champ");
	gtk_widget_show_all(a->start_layout);

	//gtk_widget_set_visible(a->choose_layout, FALSE);


}

void next_screen_2_choose (gpointer data)
{

	widgets *a = (widgets *) data;

	// Screen 1
	gtk_widget_set_visible(a->start_layout, FALSE);
	gtk_widget_set_visible(a->start_button, FALSE);

	// Screen 2
	gtk_label_set_text(GTK_LABEL(a->info_label), "Choose your champion and the level");
	gtk_widget_show_all(a->choose_layout);
	gtk_widget_show(a->choose_button);


}

void next_screen_3 (GSimpleAction *action, GVariant *parameter, gpointer data)
{

}

void next_screen_4_in_game (gpointer data)
{
	widgets *a = (widgets *) data;

	gtk_widget_set_visible(a->choose_layout, FALSE);
	gtk_widget_set_visible(a->choose_button, FALSE);

	gtk_widget_show_all(a->in_playground_layout);
	gtk_widget_show_all(a->in_playground_scroll);
	gtk_widget_show_all(a->in_progressbar_layout);
	gtk_widget_show_all(a->in_sidebar_layout);
}
