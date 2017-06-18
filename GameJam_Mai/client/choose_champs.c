/*
 * Opening a file with gio
 * Champions are created with data from the data/champ_db.txt
 * (Buttons + Label)
 * IDEA at fieldbutton box instead of grid
 */

#include "header/game_main.h"
#include <string.h>
#include <gio/gio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// this player gets the id from selected champion
void get_champ(GtkWidget *wid, gpointer data)
{
	widgets *a = (widgets *) data;

	gint id;

	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(wid), TRUE);
	id = g_strtod (gtk_widget_get_name(wid), NULL);
	a->thisplayer.id_from_champ = a->champ[id].id;
	gtk_widget_set_sensitive (a->choose.button, TRUE);
}

// reads champion data from file to the champ / ability struct
void open_file(gpointer data)
{
	widgets *a = (widgets *) data;

	gint i = 0;
	gint count = 1;

	GIOChannel *channel = g_io_channel_new_file("data/champ_db.txt", "r", NULL);
	gchar **msg = g_malloc (sizeof(gchar)*100);
	gsize length = 0;
	gsize pos = 0;
	GError *err = NULL;
	GIOStatus stat;
	gsize cut = 0;

	while(TRUE)
	{
		stat = g_io_channel_read_line(channel, msg, &length, &pos, &err);

		if(stat == G_IO_STATUS_EOF){
			break;
		}
		if(err != NULL){
			g_printerr ("Error: %s\n", err->message);
      			g_error_free (err);
		}

		switch (count){
		case 1: a->champ[i].name = msg[0];
			cut = strlen(a->champ[i].name);
			a->champ[i].name[cut-1] = '\0';
			break;
		case 2: a->champ[i].state = msg[0];
			cut = strlen(a->champ[i].state);
			a->champ[i].state[cut-1] = '\0';
			break;
		case 3: a->champ[i].image_path = msg[0];
			cut = strlen(a->champ[i].image_path);
			a->champ[i].image_path[cut-1] = '\0';
			break;
		case 4: a->champ[i].life.ability_name = msg[0];
			cut = strlen(a->champ[i].life.ability_name);
			a->champ[i].life.ability_name[cut-1] = '\0';
			break;
		case 5: a->champ[i].life.ability_max = g_ascii_strtod (msg[0], NULL); break;
		case 6: a->champ[i].life.ability_regeneration = g_ascii_strtod (msg[0], NULL); break;
		case 7: a->champ[i].ability.ability_name = msg[0];
			cut = strlen(a->champ[i].ability.ability_name);
			a->champ[i].ability.ability_name[cut-1] = '\0';
			break;
		case 8: a->champ[i].ability.ability_max = g_ascii_strtod (msg[0], NULL); break;
		case 9: a->champ[i].ability.ability_regeneration = g_ascii_strtod (msg[0], NULL); break;
		case 10: a->champ[i].ult.ability_name = msg[0];
			cut = strlen(a->champ[i].ult.ability_name);
			a->champ[i].ult.ability_name[cut-1] = '\0';
			break;
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

		count++;
	}
	g_io_channel_unref (channel);
}

// Level detection
void get_level(gpointer data)
{

	widgets *a = (widgets *) data;

	if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(a->level.level1))){
		g_print("Whatever in LVL1 is different\n");
	}else if(gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(a->level.level2))){
		g_print("Whatever in LVL2 is different\n");
	}else{
		g_print("Whatever in LVL3 is different\n");
	}

}

// Player could choose a level
// Idea: Just set visible, if player is demon ?
void choose_level(gpointer data)
{
	widgets *a = (widgets *) data;

	a->level.level1 = gtk_radio_button_new_with_label (NULL, "Level 1");

	gtk_radio_button_get_group(GTK_RADIO_BUTTON(a->level.level1));

	a->level.level2 = gtk_radio_button_new_with_label(
                 gtk_radio_button_get_group (GTK_RADIO_BUTTON (a->level.level1)),
                 "Level 2");

	a->level.level3 = gtk_radio_button_new_with_label(
                 gtk_radio_button_get_group (GTK_RADIO_BUTTON (a->level.level2)),
                 "Level 3");

	gtk_toggle_button_set_active( GTK_TOGGLE_BUTTON(a->level.level2), TRUE);

	// Pack them into a box, then show all the widgets
	gtk_grid_attach (GTK_GRID (a->choose.layout), a->level.level1, 0, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (a->choose.layout), a->level.level2, 1, 2, 1, 1);
	gtk_grid_attach (GTK_GRID (a->choose.layout), a->level.level3, 2, 2, 1, 1);

}
void create_champions(gpointer data)
{
	widgets *a = (widgets *) data;

	GtkWidget *label;
	GtkStyleContext *context;
	gchar *buf;
	gint i = 0;
	GtkWidget **buttons = g_malloc(6 * sizeof(GtkWidget));

	open_file((gpointer) a);

	a->choose.layout = gtk_grid_new();

	for(i = 0; i < 6; i++){

		a->champ[i].image = gtk_image_new_from_file(a->champ[i].image_path);

		gtk_image_set_pixel_size(GTK_IMAGE(a->champ[i].image), 50);
		buttons[i] = gtk_toggle_button_new ();
		gtk_widget_set_size_request(buttons[i], 200, 100);
		gtk_button_set_image(GTK_BUTTON(buttons[i]), a->champ[i].image);

		buf = g_malloc(2*sizeof(gchar));
		g_ascii_dtostr (buf, 2, i);
		gtk_widget_set_name(GTK_WIDGET(buttons[i]), buf);
		g_free(buf);
		g_signal_connect (buttons[i], "toggled", G_CALLBACK (get_champ), (gpointer) a);
		gtk_grid_attach (GTK_GRID (a->choose.layout), buttons[i], i, 0, 1, 1);
		label = gtk_label_new (a->champ[i].name);

		// CSS
		context = gtk_widget_get_style_context(buttons[i]);
		gtk_style_context_add_class(context, "focused");
		gtk_grid_attach (GTK_GRID (a->choose.layout), label, i, 1, 1, 1);
	}

	choose_level((gpointer) a);

	gtk_box_pack_start(GTK_BOX (a->main_box), a->choose.layout, FALSE, FALSE, 0);
}
