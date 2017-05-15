#include <gtk/gtk.h>

void but_life(GtkWidget *widget, gpointer data)
{}

void but_twice(GtkWidget *widget, gpointer data)
{}

void but_ability1(GtkWidget *widget, gpointer data)
{}

void but_ability2(GtkWidget *widget, gpointer data)
{}

void but_ability3(GtkWidget *widget, gpointer data)
{}

void but_ult(GtkWidget *widget, gpointer data)
{}

static void activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *button;

	// create window and set title *****
	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Game Jam");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 400);

	// layout containers *****
	grid = gtk_grid_new ();
	gtk_container_add (GTK_CONTAINER (window), grid);

	// skill - buttons
	button = gtk_button_new_with_label ("Life");
	g_signal_connect (button, "clicked", G_CALLBACK (but_life), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

	button = gtk_button_new_with_label ("x2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_twice), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);

	button = gtk_button_new_with_label ("ability 1");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability1), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);

	button = gtk_button_new_with_label ("ability 2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability2), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);

	button = gtk_button_new_with_label ("ability 3");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability3), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 1, 1);

	button = gtk_button_new_with_label ("ult");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ult), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 6, 0, 1, 1);

	button = gtk_button_new_with_label("Quit");
	//g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy) window);

	// regeneration - progress bar

	/*progb_attack = // Schaden
	progb_protection = // Ruestung
	progb_life = // Leben
	progb_energy = // Energie

	//

*/
	// show all widgets
	gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.game", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
