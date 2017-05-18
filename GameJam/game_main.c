#include "header/game_main.h"


static void create_progress (GtkApplication *app, GtkWidget *box, gpointer user_data)
{
	widgets *a = (widgets *) user_data;
	GtkWidget *progb_attack;
	GtkWidget *grid;

	int progb_timer;

	// layout containers *****
	grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);

	// attack - Schaden
	progb_attack = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_attack, 1, 10, 3, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_attack), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_attack), NULL);
	gdouble val;
	val = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_attack)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_attack), val);
	/*progb_protection = // Ruestung
	progb_life = // Leben
	progb_energy = // Energie
	progb_dead = // Time until live again
	*/

	gtk_box_pack_end(GTK_BOX(box), grid, FALSE, FALSE,0);

}

static void activate (GtkApplication *app, gpointer user_data)
{
	widgets *a = (widgets *) user_data;

	GtkWidget *box; // layout
	// GtkWidget *grid; // sub-layout

	// create window and set title *****
	a->window = gtk_application_window_new (app);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (app));
	gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW (a->window), "Game Jam");
	gtk_window_set_default_size (GTK_WINDOW (a->window), 800, 500); // width, height


	// layout containers *****
	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add( GTK_CONTAINER (a->window), box);
	//grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);

	// menu *****
	create_menu(app, GTK_WIDGET (box), (gpointer) a);

	// ability *****
	create_sidebar(app, GTK_WIDGET (box), (gpointer) a);

	// regeneration - progress bar *****
	create_progress(app, GTK_WIDGET (box), (gpointer) a);

	// show all widgets
	gtk_widget_show_all (a->window);
}

int main (int argc, char **argv)
{
	int status;

	widgets *a = g_malloc (sizeof(widgets));

	a->app = gtk_application_new ("org.gtk.game", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (a->app, "activate", G_CALLBACK (activate), (gpointer) a);
	status = g_application_run (G_APPLICATION (a->app), argc, argv);
	g_object_unref (a->app);

	g_free (a);
	return status;
}
