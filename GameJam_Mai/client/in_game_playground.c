#include "header/game_main.h"



void step_to_but(GtkWidget *wid, gpointer data)
{
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wid), TRUE);

	widgets *a = (widgets *) data;

	// get more life in every round
	update_progress (a->game.progressbar[2], 0.1, (gpointer) a);

	champ_to_button(a->champ[a->thisplayer.id_from_champ].position, a->thisplayer.id_from_champ, FALSE, (gpointer)a);

	en_disable_button(a->champ[a->thisplayer.id_from_champ].position, FALSE, (gpointer) a);

	int i = 0;
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].name)))
	{
		a->champ[a->thisplayer.id_from_champ].position =
				a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].name_pos;
		// g_print("your Button %d\n", a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].name_pos);
	}

	for(i=0; i <4; i++){

		if(a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].beside[i] == NULL)
		{
			break;
		}
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].beside[i])))
		{
			a->champ[a->thisplayer.id_from_champ].position =
				a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].beside_pos[i];

			// g_print("Button %d\n", a->game.fieldbutton[a->champ[a->thisplayer.id_from_champ].position].name_pos);
		}
	}

	en_disable_button(a->champ[a->thisplayer.id_from_champ].position, TRUE, (gpointer) a);

	special_button(a->champ[a->thisplayer.id_from_champ].position, (gpointer) a);

	champ_to_button(a->champ[a->thisplayer.id_from_champ].position, a->thisplayer.id_from_champ, TRUE, (gpointer)a);
	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wid), FALSE);
}

// is working for all champions - also the positions from server
void champ_to_button(gint pos, gint champ_id, gboolean visible, gpointer data)
{
	widgets *a = (widgets *) data;
	a->champ[champ_id].image = gtk_image_new_from_file(a->champ[champ_id].image_path);

	if(visible){
		gtk_grid_attach(GTK_GRID(a->game.fieldbutton[pos].grid), a->champ[champ_id].image, 1,0,1,1);
	}else{
		gtk_grid_remove_column(GTK_GRID(a->game.fieldbutton[pos].grid), 1);
	}
	gtk_widget_show(a->champ[champ_id].image);

}



void init_position(gpointer data){
	widgets *a = (widgets *) data;

	// demon
	if(a->thisplayer.id_from_champ == 0){
		a->champ[a->thisplayer.id_from_champ].position = 0;
	}else{
		a->champ[a->thisplayer.id_from_champ].position = 53;
	}
	champ_to_button(a->champ[a->thisplayer.id_from_champ].position, a->thisplayer.id_from_champ, TRUE, (gpointer) a);
	en_disable_button(a->champ[a->thisplayer.id_from_champ].position, TRUE, (gpointer) a);
}

void en_disable_button(gint i, gboolean sens, gpointer data)
{
	widgets *a = (widgets *) data;
	// enable - disable of the button
	gint tmp;
	// clicked button
	gtk_widget_set_sensitive (a->game.fieldbutton[i].name, sens);
	// neibourgh buttons
	for(tmp = 0; tmp < 4; tmp ++){
			if(a->game.fieldbutton[i].beside[tmp] == NULL)
			{
				break;
			}
			gtk_widget_set_sensitive (a->game.fieldbutton[i].beside[tmp], sens);
	}
}

// 62 + 4 buttons
void create_button (int i[1], gchar *kategory, gchar *name, gint pos_left, gint pos_top, gpointer data)
{
	widgets *a = (widgets *) data;
	int j = i[0];

	gchar *c = g_malloc(5*sizeof(gchar));
	g_ascii_dtostr (c, 5*sizeof(gchar), j);

	a->game.fieldbutton[j].grid = gtk_grid_new();
	GtkWidget *label = gtk_label_new(kategory);
	GtkWidget *label2 = gtk_label_new(c);

	a->game.fieldbutton[j].name_pos = j;
	a->game.fieldbutton[j].name = gtk_toggle_button_new();
	//gtk_grid_attach(GTK_GRID(a->game.fieldbutton[j].grid), label2, 1,0,1,1);
	gtk_grid_attach(GTK_GRID(a->game.fieldbutton[j].grid), label, 0,0,1,1);

	gtk_widget_show(a->game.fieldbutton[j].grid);
	gtk_widget_show(label);
	gtk_widget_show(label2);

	gtk_widget_set_size_request(a->game.fieldbutton[j].name, 150, 50);
	gtk_button_set_image(GTK_BUTTON(a->game.fieldbutton[j].name), a->game.fieldbutton[j].grid);
	gtk_widget_set_name(a->game.fieldbutton[j].name, name);
	g_signal_connect (a->game.fieldbutton[j].name, "pressed", G_CALLBACK (step_to_but), (gpointer) a);
	gtk_grid_attach (GTK_GRID (a->game.playground_layout), a->game.fieldbutton[j].name, pos_left, pos_top, 1, 1);
	// init: all deactivated
	gtk_widget_set_sensitive (a->game.fieldbutton[j].name, FALSE);
	i[0]++;
}

void define_connections(int n[1], int b1, int b2, int b3, int b4, gpointer data)
{
	widgets *a = (widgets *) data;
	int j = n[0];


	a->game.fieldbutton[j].beside_pos[0] = a->game.fieldbutton[b1].name_pos;
	a->game.fieldbutton[j].beside[0] = a->game.fieldbutton[b1].name;
		if(b2 != -1){
		a->game.fieldbutton[j].beside_pos[1] = a->game.fieldbutton[b2].name_pos;
		a->game.fieldbutton[j].beside[1] = a->game.fieldbutton[b2].name;
		if(b3 != -1){
			a->game.fieldbutton[j].beside_pos[2] = a->game.fieldbutton[b3].name_pos;
			a->game.fieldbutton[j].beside[2] = a->game.fieldbutton[b3].name;
			if(b4 != -1){
				a->game.fieldbutton[j].beside_pos[3] = a->game.fieldbutton[b4].name_pos;
				a->game.fieldbutton[j].beside[3] = a->game.fieldbutton[b4].name;
			}else{
				a->game.fieldbutton[j].beside_pos[3] = -1;
				a->game.fieldbutton[j].beside[3] = NULL;
			}
		}else{
			a->game.fieldbutton[j].beside_pos[2] = -1;
			a->game.fieldbutton[j].beside[2] = NULL;
		}
	}else{
		a->game.fieldbutton[j].beside_pos[1] = -1;
		a->game.fieldbutton[j].beside[1] = NULL;
	}
	n[0]++;
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

void create_playground (gpointer data)
{

	widgets *a = (widgets *) data;


	// layout containers *****
	a->game.playground_layout = gtk_grid_new ();
	gtk_widget_set_name(a->game.playground_layout, "playground");

	int i[1];
	i[0] = 0;

	a->game.playground_scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(a->game.playground_scroll), 800);
	gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(a->game.playground_scroll), 400);
	gtk_container_add(GTK_CONTAINER(a->game.playground_scroll), a->game.playground_layout);



	//scrollable_set_vadjustment (NULL ,NULL);

	// 01
	create_button(i, "Demon", "d_base", 4, 0, (gpointer) a);
	create_sep_ver(4, 1, 1, 1, (gpointer) a);
	// 23
	create_button(i, "Nexus", "d_nexus", 4, 2, (gpointer) a);
	create_sep_ver(4, 3, 1, 1, (gpointer) a);
	// 45
	create_button(i, "Inhibitor", "d_in1", 0, 4, (gpointer) a);
	create_sep_hor(1, 4, 3, 1, (gpointer) a);
	create_sep_ver(0, 5, 1, 1, (gpointer) a);
	create_button(i, "Inhibitor", "d_in2", 4, 4, (gpointer) a);
	create_sep_hor(5, 4, 3, 1, (gpointer) a);
	// NO CONNECTION TO Tower
	create_button(i, "Inhibitor", "d_in3", 8, 4, (gpointer) a);
	create_sep_ver(8, 5, 1, 1, (gpointer) a);
	// 67
	create_button(i, "Tower", "d_to1", 0, 6, (gpointer) a);
	create_sep_hor(1, 6, 3, 1, (gpointer) a);
	create_sep_ver(0, 7, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to2", 4, 6, (gpointer) a);
	create_sep_hor(5, 6, 3, 1, (gpointer) a);
	create_sep_ver(4, 7, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to3", 8, 6, (gpointer) a);
	create_sep_ver(8, 7, 1, 1, (gpointer) a);
	// 8
	/*separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 4, 9, 1);
	j[0]++;
*/
	// 9-10
	create_button(i, "Field", "fi1", 0, 9, (gpointer) a);
	create_sep_hor(1, 9, 1, 1, (gpointer) a);
	create_sep_ver(0, 10, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi2", 2, 9, (gpointer) a);
	create_sep_hor(3, 9, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi3", 4, 9, (gpointer) a);
	create_sep_hor(5, 9, 1, 1, (gpointer) a);
	create_sep_ver(4, 10, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi4", 6, 9, (gpointer) a);
	create_sep_hor(7, 9, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi5", 8, 9, (gpointer) a);
	create_sep_ver(8, 10, 1, 1, (gpointer) a);

	// 11-12
	create_button(i, "Tower", "d_to4", 0, 11, (gpointer) a);
	create_sep_hor(1, 11, 3, 1, (gpointer) a);
	create_sep_ver(0, 12, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to5", 4, 11, (gpointer) a);
	create_sep_hor(5, 11, 3, 1, (gpointer) a);
	create_sep_ver(4, 12, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to6", 8, 11, (gpointer) a);
	create_sep_ver(8, 12, 1, 1, (gpointer) a);

	// 13-14
	create_button(i, "Field", "fi6", 0, 13, (gpointer) a);
	create_sep_hor(1, 13, 1, 1, (gpointer) a);
	create_sep_ver(0, 14, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi7", 2, 13, (gpointer) a);
	create_sep_hor(3, 13, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi8", 4, 13, (gpointer) a);
	create_sep_hor(5, 13, 1, 1, (gpointer) a);
	create_sep_ver(4, 14, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi9", 6, 13, (gpointer) a);
	create_sep_hor(7, 13, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi10", 8, 13, (gpointer) a);
	create_sep_ver(8, 14, 1, 1, (gpointer) a);

	// 15-16
	create_button(i, "Tower", "d_to7", 0, 15, (gpointer) a);
	create_sep_hor(1, 15, 1, 1, (gpointer) a);
	create_sep_ver(0, 16, 1, 3, (gpointer) a);
	create_button(i, "Field", "fi11", 2, 15, (gpointer) a);
	create_sep_hor(3, 15, 1, 1, (gpointer) a);
	create_sep_ver(2, 16, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to8", 4, 15, (gpointer) a);
	create_sep_hor(5, 15, 1, 1, (gpointer) a);
	create_sep_ver(4, 16, 1, 3, (gpointer) a);
	create_button(i, "Field", "fi13", 6, 15, (gpointer) a);
	create_sep_hor(7, 15, 1, 1, (gpointer) a);
	create_sep_ver(6, 16, 1, 1, (gpointer) a);
	create_button(i, "Tower", "d_to9", 8, 15, (gpointer) a);
	create_sep_ver(8, 16, 1, 3, (gpointer) a);

	// 17-18
	create_button(i, "Basilisk", "basilisk", 2, 17, (gpointer) a);
	create_sep_ver(2, 18, 1, 1, (gpointer) a);
	create_button(i, "Drake", "drake", 6, 17, (gpointer) a);
	create_sep_ver(6, 18, 1, 1, (gpointer) a);

	// 19-20
	create_button(i, "Tower", "t_to9", 0, 19, (gpointer) a);
	create_sep_hor(1, 19, 1, 1, (gpointer) a);
	create_sep_ver(0, 20, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi14", 2, 19, (gpointer) a);
	create_sep_hor(3, 19, 1, 1, (gpointer) a);
	create_button(i, "Tower", "t_to9", 4, 19, (gpointer) a);
	create_sep_hor(5, 19, 1, 1, (gpointer) a);
	create_sep_ver(4, 20, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi12", 6, 19, (gpointer) a);
	create_sep_hor(7, 19, 1, 1, (gpointer) a);
	create_button(i, "Tower", "t_to9", 8, 19, (gpointer) a);
	create_sep_ver(8, 20, 1, 1, (gpointer) a);

	// 21-22
	create_button(i, "Field", "fi10", 0, 21, (gpointer) a);
	create_sep_hor(1, 21, 1, 1, (gpointer) a);
	create_sep_ver(0, 22, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi9", 2, 21, (gpointer) a);
	create_sep_hor(3, 21, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi8", 4, 21, (gpointer) a);
	create_sep_hor(5, 21, 1, 1, (gpointer) a);
	create_sep_ver(4, 22, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi7", 6, 21, (gpointer) a);
	create_sep_hor(7, 21, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi6", 8, 21, (gpointer) a);
	create_sep_ver(8, 22, 1, 1, (gpointer) a);
	// 23-24
	create_button(i, "Tower", "t_to6", 0, 23, (gpointer) a);
	create_sep_hor(1, 23, 3, 1, (gpointer) a);
	create_sep_ver(0, 24, 1, 1, (gpointer) a);
	create_button(i, "Tower", "t_to5", 4, 23, (gpointer) a);
	create_sep_hor(5, 23, 3, 1, (gpointer) a);
	create_sep_ver(4, 24, 1, 1, (gpointer) a);
	create_button(i, "Tower", "t_to4", 8, 23, (gpointer) a);
	create_sep_ver(8, 24, 1, 1, (gpointer) a);

	// 25-26
	create_button(i, "Field", "fi5", 0, 25, (gpointer) a);
	create_sep_hor(1, 25, 1, 1, (gpointer) a);
	create_sep_ver(0, 26, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi4", 2, 25, (gpointer) a);
	create_sep_hor(3, 25, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi3", 4, 25, (gpointer) a);
	create_sep_hor(5, 25, 1, 1, (gpointer) a);
	create_sep_ver(4, 26, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi2", 6, 25, (gpointer) a);
	create_sep_hor(7, 25, 1, 1, (gpointer) a);
	create_button(i, "Field", "fi1", 8, 25, (gpointer) a);
	create_sep_ver(8, 26, 1, 1, (gpointer) a);
	// 27
/*	separator = gtk_separator_new (GTK_ORIENTATION_HORIZONTAL);
	gtk_grid_attach (GTK_GRID (a->in_playground_layout), separator, 0, 14, 9, 1);
*/
	// 28-29
	create_button(i, "Tower", "t_to3", 0, 28, (gpointer) a);
	create_sep_hor(1, 28, 3, 1, (gpointer) a);
	create_sep_ver(0, 29, 1, 1, (gpointer) a);
	create_button(i, "Tower", "t_to2", 4, 28, (gpointer) a);
	create_sep_hor(5, 28, 3, 1, (gpointer) a);
	create_button(i, "Tower", "t_to1", 8, 28, (gpointer) a);
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
	// 34
	create_button(i, "Team", "t_base", 4, 34, (gpointer) a);


	i[0] = 0;
	//int n, int b1, int b2, int b3, int b4
	define_connections(i, 1, -1, -1, -1, (gpointer) a); // demon
	define_connections(i, 0, 3, -1, -1, (gpointer) a); // Nexus
	define_connections(i, 3, 5, -1, -1, (gpointer) a); // inhibitor
	define_connections(i, 1, 2, 4, -1, (gpointer) a);
	define_connections(i, 3, 7, -1, -1, (gpointer) a);
	define_connections(i, 2, 6, 8, -1, (gpointer) a); // 5
	define_connections(i, 5, 7, 10, -1, (gpointer) a);
	define_connections(i, 4, 6, 12, -1, (gpointer) a);
	define_connections(i, 5, 9, 13, -1, (gpointer) a);
	define_connections(i, 8, 10, -1, -1, (gpointer) a);
	define_connections(i, 6, 9, 11, 14, (gpointer) a); // 10
	define_connections(i, 10, 12, -1, -1, (gpointer) a);
	define_connections(i, 7, 11, 15, -1, (gpointer) a);
	define_connections(i, 8, 16, -1, -1, (gpointer) a);
	define_connections(i, 10, 13, 15, 18, (gpointer) a);
	define_connections(i, 12, 14, 20, -1, (gpointer) a); // 5
	define_connections(i, 13, 17, 21, -1, (gpointer) a);
	define_connections(i, 16, 18, -1, -1, (gpointer) a);
	define_connections(i, 14, 17, 19, 23, (gpointer) a);
	define_connections(i, 18, 20, -1, -1, (gpointer) a);
	define_connections(i, 15, 19, 25, -1, (gpointer) a); // 20
	define_connections(i, 16, 22, 28, -1, (gpointer) a);
	define_connections(i, 21, 23, 26, -1, (gpointer) a);
	define_connections(i, 18, 22, 24, 30, (gpointer) a);
	define_connections(i, 23, 25, 27, -1, (gpointer) a);
	define_connections(i, 20, 24, 32, -1, (gpointer) a); // 5
	define_connections(i, 22, 29, -1, -1, (gpointer) a);
	define_connections(i, 24, 31, -1, -1, (gpointer) a);
	define_connections(i, 21, 29, 33, -1, (gpointer) a);
	define_connections(i, 26, 28, 30, -1, (gpointer) a);
	define_connections(i, 23, 29, 31, 35, (gpointer) a); // 30
	define_connections(i, 27, 30, 32, -1, (gpointer) a);
	define_connections(i, 25, 31, 37, -1, (gpointer) a);
	define_connections(i, 28, 34, 38, -1, (gpointer) a);
	define_connections(i, 33, 35, -1, -1, (gpointer) a);
	define_connections(i, 30, 34, 36, 39, (gpointer) a); // 5
	define_connections(i, 35, 37, -1, -1, (gpointer) a);
	define_connections(i, 32, 36, 40, -1, (gpointer) a);
	define_connections(i, 33, 39, 41, -1, (gpointer) a);
	define_connections(i, 35, 38, 40, 43, (gpointer) a);
	define_connections(i, 37, 39, 45, -1, (gpointer) a); // 40
	define_connections(i, 38, 42, 46, -1, (gpointer) a);
	define_connections(i, 41, 43, -1, -1, (gpointer) a);
	define_connections(i, 39, 42, 44, 47, (gpointer) a);
	define_connections(i, 43, 45, -1, -1, (gpointer) a);
	define_connections(i, 40, 44, 48, -1, (gpointer) a); // 5
	define_connections(i, 41, 47, 49, -1, (gpointer) a);
	define_connections(i, 43, 46, 48, -1, (gpointer) a);
	define_connections(i, 45, 47, 51, -1, (gpointer) a);
	define_connections(i, 46, 50, -1, -1, (gpointer) a);
	define_connections(i, 49, 51, 52, -1, (gpointer) a); // 50
	define_connections(i, 48, 50, -1, -1, (gpointer) a);
	define_connections(i, 53, 50, -1, -1, (gpointer) a);
	define_connections(i, 52, -1, -1, -1, (gpointer) a); // base of team work



	gtk_box_pack_start(GTK_BOX(a->sub_box), a->game.playground_scroll, FALSE, FALSE, 0);

}


