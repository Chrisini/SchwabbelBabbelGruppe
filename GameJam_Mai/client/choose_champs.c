#include "header/game_main.h"


void but_demon(gpointer data)
{

	gtk_widget_set_name(GTK_WIDGET(data), "selectable");

}


void generate_champions(gpointer champ_data, gpointer ability_data)
{
	champ *c = (champ *) champ_data;
	abilities *ab = (abilities *) ability_data;

	c[0].name = "Demon of wind";
	c[0].id = 0;
	c[0].image_path = "img/drake.png";
	c[0].life.ability_name = "Life";
	c[0].life.ability_max = 100;
	c[0].life.ability_fill = 0.5; // de: Fuellstatus
	c[0].life.ability_regeneration = 3; // how fast it regenerates

}


void create_champions(gpointer champ_data, gpointer ability_data, gpointer data){

	widgets *a = (widgets *) data;
	champ *c = (champ *) champ_data;
	abilities *ab = (abilities *) ability_data;

	GtkWidget *button;
	GtkWidget *image;

	generate_champions((gpointer) c, (gpointer) ab);

	image = gtk_image_new_from_file(c[0].image_path);


	a->choose_layout = gtk_grid_new();

	button = gtk_button_new (); //c->player_name
	gtk_button_set_image(GTK_BUTTON(button), image);
	//gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(button), TRUE);
	g_signal_connect (button, "clicked", G_CALLBACK (but_demon), button);
	gtk_grid_attach (GTK_GRID (a->choose_layout), button, 0, 0, 1, 1);
	gtk_box_pack_start(GTK_BOX (a->main_box), a->choose_layout, FALSE, FALSE, 0);

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
