#include "header/game_main.h"

void create_info(gpointer data)
{

	widgets *a = (widgets *) data;

	a->info_grid = gtk_grid_new ();

	a->info_label = gtk_label_new ("Hidden Demon");
	gtk_widget_set_name(a->info_label, "info_label");
	gtk_grid_attach (GTK_GRID (a->info_grid), a->info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->info_grid, FALSE, FALSE,0);

	gtk_widget_show_all(a->info_grid);
}
