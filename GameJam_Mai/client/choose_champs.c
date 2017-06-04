#include "header/game_main.h"
#include <string.h>
/*
 * Champions are created with data from the data/champ_db.txt
 *
 */

void but_demon(gpointer data)
{

	gtk_widget_set_name(GTK_WIDGET(data), "selectable");

}


void create_champions(gpointer champ_data, gpointer ability_data, gpointer data){

	widgets *a = (widgets *) data;
	champ *c = (champ *) champ_data;
	abilities *ab = (abilities *) ability_data;

	GtkWidget *button, *label;
	GtkWidget *image;
	gchar *tmp_img;

	gint i = 0;

	open_file((gpointer) c, (gpointer) ab);

	a->choose_layout = gtk_grid_new();

	for(i = 0; i < 6; i++){
		// cut off /n - image
		gsize length = strlen(c[i].image_path);
		tmp_img = g_strndup(c[i].image_path, length-1);
		image = gtk_image_new_from_file(tmp_img);

		button = gtk_toggle_button_new ();
		gtk_button_set_image(GTK_BUTTON(button), image);
		//gtk_toggle_button_set_mode(GTK_TOGGLE_BUTTON(button), TRUE);
		g_signal_connect (button, "toggled", G_CALLBACK (but_demon), button);
		gtk_grid_attach (GTK_GRID (a->choose_layout), button, i, 0, 1, 1);


		label = gtk_label_new (c[i].name);
		gtk_grid_attach (GTK_GRID (a->choose_layout), label, i, 1, 1, 1);

	}

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
