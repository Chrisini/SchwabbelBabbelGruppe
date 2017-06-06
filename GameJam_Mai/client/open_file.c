#include "header/game_main.h"
#include <gio/gio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void open_file(gpointer champ_data, gpointer ability_data)
{
	champ *c = (champ *) champ_data;
	gint i = 0;

	GIOChannel *channel = g_io_channel_new_file("data/champ_db.txt", "r", NULL);
	gchar **msg = g_malloc (sizeof(gchar)*100);
	gsize length = 0;
	gsize pos = 0;
	//GError **err = NULL;
	GIOStatus stat;
	int a = 1;

	while(TRUE)
	{
		stat = g_io_channel_read_line(channel, msg, &length, &pos, NULL);

		if(stat == G_IO_STATUS_EOF){
			break;
		}

		switch (a){
		case 1: c[i].name = msg[0]; break;
		case 2: c[i].state = msg[0]; break;
		case 3: c[i].image_path = msg[0];
			/*g_strlcpy(c[i].image_path, msg[0], length-1);*/ break;
		case 4: c[i].life.ability_name = msg[0]; break;
		case 5: c[i].life.ability_max = (gint) msg[0]; break;
		case 6: c[i].life.ability_regeneration = (gint) msg[0]; break;
		case 7: c[i].ability.ability_name = msg[0]; break;
		case 8: c[i].ability.ability_max = (gint) msg[0]; break;
		case 9: c[i].ability.ability_regeneration = (gint) msg[0]; break;
		case 10: c[i].ult.ability_name = msg[0]; break;
		case 11: c[i].ult.ability_max = (gint) msg[0]; break;
		case 12: c[i].ult.ability_regeneration = (gint) msg[0]; break;
		case 13: c[i].id = i;
			c[i].life.ability_fill = 1.0;
			c[i].ability.ability_fill = 1.0;
			c[i].ult.ability_fill = 1.0;
			i++;
			a = 0;
			break;
		default: g_print("This number is not available in the struct\n"); break;
		}

		//g_print("%s", msg[0]);
		a++;

	}

	//g_io_channel_unref (channel);
	//stat = g_io_channel_shutdown (channel, TRUE, err);
	/*if(stat == G_IO_STATUS_ERROR){
		perror("Error cant read Champs");
		exit(EXIT_ON_FAILURE);
	}*/


}

// OLD VERSIONS BELOW



	//GFile *readFile = g_file_new_for_path("data/champ_db.txt");

	/*GFileInputStream *input = g_file_read(readFile, NULL, NULL);
	if(!input)
	{
		perror("Error Message Data File");
		exit(EXIT_FAILURE);
	}*/


/*
	gchar buf[500];
	char tmp;

	while(TRUE){
		read = g_input_stream_read(G_INPUT_STREAM(input), buf, G_N_ELEMENTS(buf) -1, NULL, NULL);
		//read = g_input_stream_read(G_INPUT_STREAM(input), buf, 10, NULL, NULL);
		if(read > 0)
		{
			//buf[read] = '\0';
			g_print("%s\n", buf);
			getc(stdin);

		}
		else if(read < 0)
		{
			g_print("%s\n", buf);
			getc(stdin);
			return;
		}else{
			break;
		}
*/

		//c[i].name = (gchar) buf;
		//fscanf(readFile, "%s", c[i].state);
		//c[i].id = i;
		/*fgets(readFile, "%s", c[i].image_path);
		fgets(c[i].life.ability_name, 100, readFile);
		fgets(c[i].life.ability_max, 100, readFile);
		fgets(c[i].life.ability_fill, 100, readFile);
		fgets(c[i].life.ability_regeneration, 100, readFile);
		fgets(c[i].ability.ability_name, 100, readFile);
		fgets(c[i].ability.ability_max, 100, readFile);
		fgets(c[i].ability.ability_fill, 100, readFile);
		fgets(c[i].ability.ability_regeneration, 100, readFile);
		fgets(c[i].ult.ability_name, 100, readFile);
		fgets(c[i].ult.ability_max, 100, readFile);
		fgets(c[i].ult.ability_fill, 100, readFile);
		fgets(c[i].ult.ability_regeneration, 100, readFile);*/
/*
	}

	g_object_unref(readFile);
		g_object_unref(input);
		g_object_unref(buf);*/

