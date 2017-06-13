/*
 * Champions are created with data from the data/champ_db.txt
 * (Buttons + Label)
 */

#include "header/game_main.h"
#include <string.h>
#include <gio/gio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>



void but_demon(GtkWidget *wid, gpointer data)
{
	widgets *a = (widgets *) data;
	// gboolean 	gtk_widget_is_focus (widget)
	//a->champ[]

}



void open_file(gpointer data)
{

	widgets *a = (widgets *) data;

	gint i = 0;
	gint count = 1;

	GIOChannel *channel = g_io_channel_new_file("data/champ_db.txt", "r", NULL);
	gchar **msg = g_malloc (sizeof(gchar)*100);
	gsize length = 0;
	gsize pos = 0;
	//GError **err = NULL;
	GIOStatus stat;


	while(TRUE)
	{
		stat = g_io_channel_read_line(channel, msg, &length, &pos, NULL); // err

		if(stat == G_IO_STATUS_EOF){
			break;
		}

		switch (count){
		case 1: a->champ[i].name = msg[0]; break;
		case 2: a->champ[i].state = msg[0]; break;
		case 3: a->champ[i].image_path = msg[0];
			/*g_strlcpy(a->champ[i].image_path, msg[0], length-1);*/ break;
		case 4: a->champ[i].life.ability_name = msg[0]; break;
		case 5: a->champ[i].life.ability_max = g_ascii_strtod (msg[0], NULL); break;
		case 6: a->champ[i].life.ability_regeneration = g_ascii_strtod (msg[0], NULL); break;
		case 7: a->champ[i].ability.ability_name = msg[0]; break;
		case 8: a->champ[i].ability.ability_max = g_ascii_strtod (msg[0], NULL); break;
		case 9: a->champ[i].ability.ability_regeneration = g_ascii_strtod (msg[0], NULL); break;
		case 10: a->champ[i].ult.ability_name = msg[0]; break;
		case 11: a->champ[i].ult.ability_max = g_ascii_strtod (msg[0], NULL); break;
		case 12: a->champ[i].ult.ability_regeneration = g_ascii_strtod (msg[0], NULL); break;
		case 13: a->champ[i].id = i;
			a->champ[i].life.ability_fill = 1.0;
			a->champ[i].ability.ability_fill = 1.0;
			a->champ[i].ult.ability_fill = 1.0;
			i++;
			count = 0;
			break;
		default: g_print("This number is not available in the struct\n"); break;
		}

		//g_print("%s", msg[0]);
		count++;

	}

	//g_io_channel_unref (channel);
	//stat = g_io_channel_shutdown (channel, TRUE, err);
	/*if(stat == G_IO_STATUS_ERROR){
		perror("Error cant read Champs");
		exit(EXIT_ON_FAILURE);
	}*/


}

void create_champions(gpointer data){


	widgets *a = (widgets *) data;

	GtkWidget *button, *label;
	GtkWidget *image;
	gchar *tmp_img;

	gint i = 0;

	open_file((gpointer) a);

	a->choose.layout = gtk_grid_new();

	for(i = 0; i < 6; i++){
		// cut off /n - image
		gsize length = strlen(a->champ[i].image_path);
		tmp_img = g_strndup(a->champ[i].image_path, length-1);
		image = gtk_image_new_from_file(tmp_img);
		//image = gtk_label_new("Text");

		button = gtk_toggle_button_new ();
		gtk_button_set_image(GTK_BUTTON(button), image);
		g_signal_connect (button, "toggled", G_CALLBACK (but_demon), (gpointer) a);
		gtk_grid_attach (GTK_GRID (a->choose.layout), button, i, 0, 1, 1);
		//gtk_widget_set_visible(image, FALSE);
		label = gtk_label_new (a->champ[i].name);
		gtk_grid_attach (GTK_GRID (a->choose.layout), label, i, 1, 1, 1);
		gtk_widget_set_name(GTK_WIDGET(button), "champs");
	}

	gtk_box_pack_start(GTK_BOX (a->main_box), a->choose.layout, FALSE, FALSE, 0);


}
