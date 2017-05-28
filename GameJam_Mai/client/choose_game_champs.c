#include "header/game_main.h"


void but_demon(gpointer data)
{}

void create_champions(/*gpointer champ_data, */gpointer data){

	widgets *a = (widgets *) data;
	//champ *c = (champ *) champ_data; // todo: allocate champ

	GtkWidget *button;
	GtkWidget *image;

	image = gtk_image_new_from_file("img/drake.png");


	a->choose_grid = gtk_grid_new();

	button = gtk_button_new (); //c->player_name
	gtk_button_set_image(GTK_BUTTON(button), image);
	g_signal_connect (button, "clicked", G_CALLBACK (but_demon), (gpointer) data);
	gtk_grid_attach (GTK_GRID (a->choose_grid), button, 0, 0, 1, 1);
	gtk_box_pack_start(GTK_BOX (a->main_box), a->choose_grid, FALSE, FALSE, 0);

/*
	typedef struct {
		char player_name[30];
		int player_id;
		abilities life;
		//abilities ability1;
		//abilities ability2;
		abilities ability;
		abilities ult;
	}player;
 */
/*
int j = i[0];

	button[j].name = gtk_button_new_with_label (kategory);
	gtk_widget_set_name(button[j].name, name);
	g_signal_connect (button[j].name, "clicked", G_CALLBACK (step_to_but), NULL);
	gtk_grid_attach (GTK_GRID (grid), button[j].name, pos_left, pos_top, 1, 1);

	i[0]++;
}
*/
}
