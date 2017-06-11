#include "header/game_main.h"


// 62 + 4 buttons
void create_button (int i[1], gchar *kategory, gchar *name, gint pos_left, gint pos_top, gpointer data){

	widgets *a = (widgets *) data;
	int j = i[0];

	a->game.fieldbutton[j].name = gtk_button_new_with_label (kategory);
	gtk_widget_set_name(a->game.fieldbutton[j].name, name);
	g_signal_connect (a->game.fieldbutton[j].name, "clicked", G_CALLBACK (step_to_but), NULL);
	gtk_grid_attach (GTK_GRID (a->game.playground_layout), a->game.fieldbutton[j].name, pos_left, pos_top, 1, 1);

	i[0]++;
}
void create_sep_hor(int aa, int b, int c, int d, gpointer data){

	widgets *a = (widgets *) data;
	GtkStyleContext *context;
	GtkWidget *sep_hor;

	sep_hor = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	context = gtk_widget_get_style_context(sep_hor);
	gtk_style_context_add_class(context, "hor");
	gtk_grid_attach (GTK_GRID (a->game.playground_layout), sep_hor, aa, b, c, d);

}

void create_sep_ver(int aa, int b, int c, int d, gpointer data){

	widgets *a = (widgets *) data;
	GtkStyleContext *context;
	GtkWidget *sep_ver;

	sep_ver = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
	context = gtk_widget_get_style_context(sep_ver);
	gtk_style_context_add_class(context, "ver");
	gtk_grid_attach (GTK_GRID (a->game.playground_layout), sep_ver, aa, b, c, d);

}
void step_to_but(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("but");
}

void create_playground (gpointer data)
{

	widgets *a = (widgets *) data;


	// layout containers *****
	a->game.playground_layout = gtk_grid_new ();
	gtk_widget_set_name(a->game.playground_layout, "playground");

	int i[1];
	i[0] = 0;

	a->game.playground_scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(a->game.playground_scroll), 700);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(a->game.playground_scroll), 400);
	gtk_container_add(GTK_CONTAINER(a->game.playground_scroll), a->game.playground_layout);



	//scrollable_set_vadjustment (NULL ,NULL);

	// 01
	create_button(i, "Demon", "d_base", 4, 0, (gpointer) a);
	create_sep_ver(4, 1, 1, 1, (gpointer) a);
	// 23
	create_button(i, "Nexus", "d_nex", 4, 2, (gpointer) a);
	create_sep_ver(4, 3, 1, 1, (gpointer) a);
	// 45
	create_button(i, "Inhibitor", "d_in1", 0, 4, (gpointer) a);
	create_sep_hor(1, 4, 3, 1, (gpointer) a);
	create_sep_ver(0, 5, 1, 1, (gpointer) a);
	create_button(i, "Inhibitor", "d_in2", 4, 4, (gpointer) a);
	create_sep_hor(5, 4, 3, 1, (gpointer) a);
	// NO CONNECTION TO TOWER
	create_button(i, "Inhibitor", "d_in3", 8, 4, (gpointer) a);
	create_sep_ver(8, 5, 1, 1, (gpointer) a);
	// 67
	create_button(i, "Turm", "d_tu1", 0, 6, (gpointer) a);
	create_sep_hor(1, 6, 3, 1, (gpointer) a);
	create_sep_ver(0, 7, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu2", 4, 6, (gpointer) a);
	create_sep_hor(5, 6, 3, 1, (gpointer) a);
	create_sep_ver(4, 7, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu3", 8, 6, (gpointer) a);
	create_sep_ver(8, 7, 1, 1, (gpointer) a);
	// 8
	/*separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 4, 9, 1);
	j[0]++;
*/
	// 9-10
	create_button(i, "Feld", "d_fe1", 0, 9, (gpointer) a);
	create_sep_hor(1, 9, 1, 1, (gpointer) a);
	create_sep_ver(0, 10, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe2", 2, 9, (gpointer) a);
	create_sep_hor(3, 9, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe3", 4, 9, (gpointer) a);
	create_sep_hor(5, 9, 1, 1, (gpointer) a);
	create_sep_ver(4, 10, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe4", 6, 9, (gpointer) a);
	create_sep_hor(7, 9, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe5", 8, 9, (gpointer) a);
	create_sep_ver(8, 10, 1, 1, (gpointer) a);

	// 11-12
	create_button(i, "Turm", "d_tu4", 0, 11, (gpointer) a);
	create_sep_hor(1, 11, 3, 1, (gpointer) a);
	create_sep_ver(0, 12, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu5", 4, 11, (gpointer) a);
	create_sep_hor(5, 11, 3, 1, (gpointer) a);
	create_sep_ver(4, 12, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu6", 8, 11, (gpointer) a);
	create_sep_ver(8, 12, 1, 1, (gpointer) a);

	// 13-14
	create_button(i, "Feld", "d_fe6", 0, 13, (gpointer) a);
	create_sep_hor(1, 13, 1, 1, (gpointer) a);
	create_sep_ver(0, 14, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe7", 2, 13, (gpointer) a);
	create_sep_hor(3, 13, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe8", 4, 13, (gpointer) a);
	create_sep_hor(5, 13, 1, 1, (gpointer) a);
	create_sep_ver(4, 14, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe9", 6, 13, (gpointer) a);
	create_sep_hor(7, 13, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe10", 8, 13, (gpointer) a);
	create_sep_ver(8, 14, 1, 1, (gpointer) a);

	// 15-16
	create_button(i, "Turm", "d_tu7", 0, 15, (gpointer) a);
	create_sep_hor(1, 15, 1, 1, (gpointer) a);
	create_sep_ver(0, 16, 1, 3, (gpointer) a);
	create_button(i, "Feld", "d_fe11", 2, 15, (gpointer) a);
	create_sep_hor(3, 15, 1, 1, (gpointer) a);
	create_sep_ver(2, 16, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu8", 4, 15, (gpointer) a);
	create_sep_hor(5, 15, 1, 1, (gpointer) a);
	create_sep_ver(4, 16, 1, 3, (gpointer) a);
	create_button(i, "Feld", "d_fe13", 6, 15, (gpointer) a);
	create_sep_hor(7, 15, 1, 1, (gpointer) a);
	create_sep_ver(6, 16, 1, 1, (gpointer) a);
	create_button(i, "Turm", "d_tu9", 8, 15, (gpointer) a);
	create_sep_ver(8, 16, 1, 3, (gpointer) a);

	// 17-18
	create_button(i, "Basilisk", "basilisk", 2, 17, (gpointer) a);
	create_sep_ver(2, 18, 1, 1, (gpointer) a);
	create_button(i, "Drake", "drake", 6, 17, (gpointer) a);
	create_sep_ver(6, 18, 1, 1, (gpointer) a);

	// 19-20
	create_button(i, "Turm", "t_tu9", 0, 19, (gpointer) a);
	create_sep_hor(1, 19, 1, 1, (gpointer) a);
	create_sep_ver(0, 20, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe14", 2, 19, (gpointer) a);
	create_sep_hor(3, 19, 1, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu9", 4, 19, (gpointer) a);
	create_sep_hor(5, 19, 1, 1, (gpointer) a);
	create_sep_ver(4, 20, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe12", 6, 19, (gpointer) a);
	create_sep_hor(7, 19, 1, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu9", 8, 19, (gpointer) a);
	create_sep_ver(8, 20, 1, 1, (gpointer) a);

	// 21-22
	create_button(i, "Feld", "d_fe10", 0, 21, (gpointer) a);
	create_sep_hor(1, 21, 1, 1, (gpointer) a);
	create_sep_ver(0, 22, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe9", 2, 21, (gpointer) a);
	create_sep_hor(3, 21, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe8", 4, 21, (gpointer) a);
	create_sep_hor(5, 21, 1, 1, (gpointer) a);
	create_sep_ver(4, 22, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe7", 6, 21, (gpointer) a);
	create_sep_hor(7, 21, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe6", 8, 21, (gpointer) a);
	create_sep_ver(8, 22, 1, 1, (gpointer) a);
	// 23-24
	create_button(i, "Turm", "t_tu6", 0, 23, (gpointer) a);
	create_sep_hor(1, 23, 3, 1, (gpointer) a);
	create_sep_ver(0, 24, 1, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu5", 4, 23, (gpointer) a);
	create_sep_hor(5, 23, 3, 1, (gpointer) a);
	create_sep_ver(4, 24, 1, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu4", 8, 23, (gpointer) a);
	create_sep_ver(8, 24, 1, 1, (gpointer) a);

	// 25-26
	create_button(i, "Feld", "d_fe5", 0, 25, (gpointer) a);
	create_sep_hor(1, 25, 1, 1, (gpointer) a);
	create_sep_ver(0, 26, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe4", 2, 25, (gpointer) a);
	create_sep_hor(3, 25, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe3", 4, 25, (gpointer) a);
	create_sep_hor(5, 25, 1, 1, (gpointer) a);
	create_sep_ver(4, 26, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe2", 6, 25, (gpointer) a);
	create_sep_hor(7, 25, 1, 1, (gpointer) a);
	create_button(i, "Feld", "d_fe1", 8, 25, (gpointer) a);
	create_sep_ver(8, 26, 1, 1, (gpointer) a);
	// 27
/*	separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 14, 9, 1);
*/
	// 28-29
	create_button(i, "Turm", "t_tu3", 0, 28, (gpointer) a);
	create_sep_hor(1, 28, 3, 1, (gpointer) a);
	create_sep_ver(0, 29, 1, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu2", 4, 28, (gpointer) a);
	create_sep_hor(5, 28, 3, 1, (gpointer) a);
	create_button(i, "Turm", "t_tu1", 8, 28, (gpointer) a);
	create_sep_ver(8, 29, 1, 1, (gpointer) a);

	// 30-31
	create_button(i, "Inhibitor", "t_in3", 0, 30, (gpointer) a);
	create_sep_hor(1, 30, 3, 1, (gpointer) a);
	create_button(i, "Inhibitor", "t_in2", 4, 30, (gpointer) a);
	create_sep_hor(5, 30, 3, 1, (gpointer) a);
	create_sep_ver(4, 31, 1, 1, (gpointer) a);
	create_button(i, "Inhibitor", "t_in1", 8, 30, (gpointer) a);

	// 32-33
	create_button(i, "Nexus", "t_nexus", 4, 32, (gpointer) a);
	create_sep_ver(4, 33, 1, 1, (gpointer) a);
	// 34-35
	create_button(i, "Team", "t_base5", 0, 34, (gpointer) a);
	create_button(i, "Team", "t_base4", 2, 34, (gpointer) a);
	create_button(i, "Team", "t_base3", 4, 34, (gpointer) a);
	create_button(i, "Team", "t_base2", 6, 34, (gpointer) a);
	create_button(i, "Team", "t_base1", 8, 34, (gpointer) a);


	//gtk_widget_set_name(sep_ver, "ver");







	gtk_box_pack_start(GTK_BOX(a->sub_box), a->game.playground_scroll, FALSE, FALSE, 0);

}


