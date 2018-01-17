#include "header/game_main.h"


// This functionallity is not done yet
// It should get life, protection and life by every round
// function is not called
// gdouble could also be a minus number
void update_progress (GtkWidget *progressbar, gdouble change, gpointer data)
{
	widgets *a = (widgets *) data;
	gdouble val_energy;
	val_energy = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progressbar)) + change;
	if(val_energy > 1.0)
	{
		val_energy = 1.0;
	}else if(val_energy <= 0.0){
		button_die(0, (gpointer) a);
		val_energy = 1.0;
	}
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar), val_energy);

}

void create_progress (gpointer data)
{
	widgets *a = (widgets *) data;

	// layout containers *****
	a->game.progressbar_layout = gtk_grid_new ();

	// attack - Schaden
	a->game.progressbar[0] = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (a->game.progressbar_layout), a->game.progressbar[0], 1, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (a->game.progressbar[0]), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (a->game.progressbar[0]), NULL);
	gdouble val_attack;
	val_attack = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (a->game.progressbar[0])) + 1.0;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (a->game.progressbar[0]), val_attack);

	// protection - Ruestung
	a->game.progressbar[1] = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (a->game.progressbar_layout), a->game.progressbar[1], 2, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (a->game.progressbar[1]), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (a->game.progressbar[1]), NULL);
	gdouble val_protect;
	val_protect = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (a->game.progressbar[1])) + 1.0;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (a->game.progressbar[1]), val_protect);

	// life / dead - Leben / Tod
	a->game.progressbar[2] = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (a->game.progressbar_layout), a->game.progressbar[2], 3, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (a->game.progressbar[2]), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (a->game.progressbar[2]), NULL);
	gdouble val_life;
	val_life = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (a->game.progressbar[2])) + 1.0;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (a->game.progressbar[2]), val_life);

	// energy - Energie, Mana
	a->game.progressbar[3] = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (a->game.progressbar_layout), a->game.progressbar[3], 4, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (a->game.progressbar[3]), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (a->game.progressbar[3]), NULL);
	gdouble val_energy;
	val_energy = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (a->game.progressbar[3])) + 1.0;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (a->game.progressbar[3]), val_energy);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->game.progressbar_layout, FALSE, FALSE,0);
}
