#include "header/game_main.h"

/*
 * the infolablel (gtk statusbar) shows every player, what he should do / is able to do
 * next. It will get (in)visible, if F1 or "Help" in the menu is clicked
 */

void create_info (gpointer data)
{

	widgets *a = (widgets *) data;

	// Layout
	a->info.layout = gtk_grid_new ();

	// Statusbar with id
	// pop for clean, push for new message
	a->info.statusbar = gtk_statusbar_new ();
	a->info.id = gtk_statusbar_get_context_id (GTK_STATUSBAR(a->info.statusbar), "game_description");
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Welcome to Hidden Demon");

	// CSS
	gtk_widget_set_name(a->info.statusbar, "info_statusbar");

	// Layout
	gtk_grid_attach (GTK_GRID (a->info.layout), a->info.statusbar, 1,1,1,1);
	gtk_box_pack_end(GTK_BOX(a->main_box), a->info.layout, FALSE, FALSE,0);
	gtk_widget_show_all(a->info.layout);
}

/*void create_info_v2 (gpointer data)
{

	widgets *a = (widgets *) data;

	a->info.layout = gtk_grid_new ();

	a->info.statusbar = gtk_label_new ("Hidden Demon");
	gtk_widget_set_name(a->info.statusbar, "info_statusbar");
	gtk_grid_attach (GTK_GRID (a->info.layout), a->info.statusbar, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->info.layout, FALSE, FALSE,0);

	gtk_widget_show_all(a->info.layout);
}*/
