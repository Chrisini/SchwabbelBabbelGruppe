#include "header/game_main.h"

/*
 * the infolablel (gtk statusbar) shows every player, wht he should do / is able to do
 * next. It will get (in)visible, if F1 or "Help" in the menu is clicked
 */

void create_info (gpointer data)
{

	widgets *a = (widgets *) data;


	a->info_grid = gtk_grid_new ();

	a->info_label = gtk_statusbar_new ();
	a->info_id = gtk_statusbar_get_context_id (GTK_STATUSBAR(a->info_label), "game_description");
	gtk_statusbar_push(GTK_STATUSBAR(a->info_label), a->info_id, "Welcome to Hidden Demon");
	gtk_widget_set_name(a->info_label, "info_label");
	gtk_grid_attach (GTK_GRID (a->info_grid), a->info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->info_grid, FALSE, FALSE,0);

	gtk_widget_show_all(a->info_grid);
}

/*void create_info_old (gpointer data)
{

	widgets *a = (widgets *) data;

	a->info_grid = gtk_grid_new ();

	a->info_label = gtk_label_new ("Hidden Demon");
	gtk_widget_set_name(a->info_label, "info_label");
	gtk_grid_attach (GTK_GRID (a->info_grid), a->info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->info_grid, FALSE, FALSE,0);

	gtk_widget_show_all(a->info_grid);
}*/
