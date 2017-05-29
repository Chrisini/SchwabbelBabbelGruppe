#include "header/game_main.h"

void create_button (int i[1], BUTTONS *button, gchar *kategory, gchar *name, gint pos_left, gint pos_top, gpointer data){

	widgets *a = (widgets *) data;
	int j = i[0];

	button[j].name = gtk_button_new_with_label (kategory);
	gtk_widget_set_name(button[j].name, name);
	g_signal_connect (button[j].name, "clicked", G_CALLBACK (step_to_but), NULL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), button[j].name, pos_left, pos_top, 1, 1);

	i[0]++;
}

void step_to_but(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("but");
}

void create_playground (gpointer data){

	BUTTONS *button;
	widgets *a = (widgets *) data;

	button = (BUTTONS *)g_malloc(62 * sizeof (BUTTONS));

	// layout containers *****
	a->in_playground_layout = gtk_grid_new ();
	gtk_widget_set_name(a->in_playground_layout, "playground");

	int i[1];
	i[0] = 0;

	a->in_playground_scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(a->in_playground_scroll), 700);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(a->in_playground_scroll), 400);
	gtk_container_add(GTK_CONTAINER(a->in_playground_scroll), a->in_playground_layout);



	//scrollable_set_vadjustment (NULL ,NULL);

	create_button(i, button, "Demon", "d_base", 4, 0, (gpointer) a);

	create_button(i, button, "Nexus", "d_nex", 4, 1, (gpointer) a);

	create_button(i, button, "Inhibitor", "d_in1", 0, 2, (gpointer) a);
	create_button(i, button, "Inhibitor", "d_in2", 4, 2, (gpointer) a);
	create_button(i, button, "Inhibitor", "d_in3", 8, 2, (gpointer) a);

	create_button(i, button, "Turm", "d_tu1", 0, 3, (gpointer) a);
	create_button(i, button, "Turm", "d_tu2", 4, 3, (gpointer) a);
	create_button(i, button, "Turm", "d_tu3", 8, 3, (gpointer) a);

	GtkWidget *separator;
	separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 4, 9, 1);

	create_button(i, button, "Feld", "d_fe1", 0, 5, (gpointer) a);
	create_button(i, button, "Feld", "d_fe2", 2, 5, (gpointer) a);
	create_button(i, button, "Feld", "d_fe3", 4, 5, (gpointer) a);
	create_button(i, button, "Feld", "d_fe4", 6, 5, (gpointer) a);
	create_button(i, button, "Feld", "d_fe5", 8, 5, (gpointer) a);

	create_button(i, button, "Turm", "d_tu4", 0, 6, (gpointer) a);
	create_button(i, button, "Turm", "d_tu5", 4, 6, (gpointer) a);
	create_button(i, button, "Turm", "d_tu6", 8, 6, (gpointer) a);

	create_button(i, button, "Feld", "d_fe6", 0, 7, (gpointer) a);
	create_button(i, button, "Feld", "d_fe7", 2, 7, (gpointer) a);
	create_button(i, button, "Feld", "d_fe8", 4, 7, (gpointer) a);
	create_button(i, button, "Feld", "d_fe9", 6, 7, (gpointer) a);
	create_button(i, button, "Feld", "d_fe10", 8, 7, (gpointer) a);

	create_button(i, button, "Turm", "d_tu7", 0, 8, (gpointer) a);
	create_button(i, button, "Feld", "d_fe11", 1, 8, (gpointer) a);
	create_button(i, button, "Feld", "d_fe12", 3, 8, (gpointer) a);
	create_button(i, button, "Turm", "d_tu8", 4, 8, (gpointer) a);
	create_button(i, button, "Feld", "d_fe13", 5, 8, (gpointer) a);
	create_button(i, button, "Feld", "d_fe14", 7, 8, (gpointer) a);
	create_button(i, button, "Turm", "d_tu9", 8, 8, (gpointer) a);

	create_button(i, button, "Basilisk", "basilisk", 2, 9, (gpointer) a);
	create_button(i, button, "Drake", "drake", 6, 9, (gpointer) a);

	create_button(i, button, "Turm", "t_tu9", 0, 10, (gpointer) a);
	create_button(i, button, "Feld", "d_fe14", 1, 10, (gpointer) a);
	create_button(i, button, "Feld", "d_fe13", 3, 10, (gpointer) a);
	create_button(i, button, "Turm", "t_tu9", 4, 10, (gpointer) a);
	create_button(i, button, "Feld", "d_fe12", 5, 10, (gpointer) a);
	create_button(i, button, "Feld", "d_fe11", 7, 10, (gpointer) a);
	create_button(i, button, "Turm", "t_tu9", 8, 10, (gpointer) a);

	create_button(i, button, "Feld", "d_fe10", 0, 11, (gpointer) a);
	create_button(i, button, "Feld", "d_fe9", 2, 11, (gpointer) a);
	create_button(i, button, "Feld", "d_fe8", 4, 11, (gpointer) a);
	create_button(i, button, "Feld", "d_fe7", 6, 11, (gpointer) a);
	create_button(i, button, "Feld", "d_fe6", 8, 11, (gpointer) a);

	create_button(i, button, "Turm", "t_tu6", 0, 12, (gpointer) a);
	create_button(i, button, "Turm", "t_tu5", 4, 12, (gpointer) a);
	create_button(i, button, "Turm", "t_tu4", 8, 12, (gpointer) a);

	create_button(i, button, "Feld", "d_fe5", 0, 13, (gpointer) a);
	create_button(i, button, "Feld", "d_fe4", 2, 13, (gpointer) a);
	create_button(i, button, "Feld", "d_fe3", 4, 13, (gpointer) a);
	create_button(i, button, "Feld", "d_fe2", 6, 13, (gpointer) a);
	create_button(i, button, "Feld", "d_fe1", 8, 13, (gpointer) a);

	separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 14, 9, 1);

	create_button(i, button, "Turm", "t_tu3", 0, 15, (gpointer) a);
	create_button(i, button, "Turm", "t_tu2", 4, 15, (gpointer) a);
	create_button(i, button, "Turm", "t_tu1", 8, 15, (gpointer) a);

	create_button(i, button, "Inhibitor", "t_in3", 0, 16, (gpointer) a);
	create_button(i, button, "Inhibitor", "t_in2", 4, 16, (gpointer) a);
	create_button(i, button, "Inhibitor", "t_in1", 8, 16, (gpointer) a);

	create_button(i, button, "Nexus", "t_nexus", 4, 17, (gpointer) a);

	create_button(i, button, "Team", "t_base5", 0, 18, (gpointer) a);
	create_button(i, button, "Team", "t_base4", 2, 18, (gpointer) a);
	create_button(i, button, "Team", "t_base3", 4, 18, (gpointer) a);
	create_button(i, button, "Team", "t_base2", 6, 18, (gpointer) a);
	create_button(i, button, "Team", "t_base1", 8, 18, (gpointer) a);


	gtk_box_pack_start(GTK_BOX(a->sub_box), a->in_playground_scroll, FALSE, FALSE, 0);

}


