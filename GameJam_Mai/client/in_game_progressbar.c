#include "header/game_main.h"

void create_progress (GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;
	GtkWidget *progb_attack, *progb_protection, *progb_life, *progb_energy;
	GtkWidget *grid;

	// layout containers *****
	grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);

	// attack - Schade
	progb_attack = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_attack, 1, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_attack), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_attack), NULL);
	gdouble val_attack;
	val_attack = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_attack)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_attack), val_attack);
	// protection - Ruestung
	progb_protection = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_protection, 2, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_protection), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_protection), NULL);
	gdouble val_protect;
	val_protect = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_protection)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_protection), val_protect);

	// life / dead - Leben / Tod
	progb_life = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_life, 3, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_life), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_life), NULL);
	gdouble val_life;
	val_life = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_life)) + 0.3;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_life), val_life);

	// energy - Energie, Mana
	progb_energy = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_energy, 4, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_energy), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_energy), NULL);
	gdouble val_energy;
	val_energy = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_energy)) + 0.3;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_energy), val_energy);


	gtk_box_pack_end(GTK_BOX(a->main_box), grid, FALSE, FALSE,0);

}
