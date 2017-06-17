// Where anyone could go next
#include "header/game_main.h"


// Every button has its own special "power"
void special_button(gint id, gpointer data)
{
	widgets *a = (widgets *) data;
	if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "fi"))
	{
		button_field(id, (gpointer) a);
	}
	else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "drake"))
	{
		button_drake(id, (gpointer) a);
	}
	else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "basil"))
	{
		button_basil(id, (gpointer) a);
	}
	else if(a->thisplayer.id_from_champ == 0){

		if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d"))
		{
			if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_base"))
			{
				button_base(id, (gpointer) a); // shop available
			}else{
			    button_field(id, (gpointer) a);
			}
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_to"))
		{
			button_tower(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_in"))
		{
			button_inhi(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_nexus"))
		{
			button_nexus(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_base"))
		{
			button_die(id, (gpointer) a); // not allowed to go into the other base
		}
		else
		{
			 g_print("You have clicked a button, we don't know :(");
		}

	}else{
		if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t"))
		{
			if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_base"))
			{
				button_base(id, (gpointer) a); // shop available
			}else{
			    button_field(id, (gpointer) a);
			}
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_to"))
		{
			button_tower(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_in"))
		{
			button_inhi(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_nexus"))
		{
			button_nexus(id, (gpointer) a);
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_base"))
		{
			button_die(id, (gpointer) a); // not allowed to go into the other base
		}
		else
		{
			 g_print("You have clicked a button, we don't know :(");
		}
	}


}

void button_field(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Nothing happens here");


}

void button_tower(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Destroy the tower, be careful, it hits you back");


}

void button_inhi(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Destroy the inhibitor");


}

void button_nexus(gint id, gpointer data){
	widgets *a = (widgets *) data;

	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You have won the game !!! :D");

	dialog = gtk_dialog_new_with_buttons("Winner",
					     GTK_WINDOW (a->window),
					     GTK_DIALOG_MODAL,
					     ("Close"),
					     GTK_RESPONSE_OK,
					     NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	label = gtk_label_new("You have won the game! :D");
	gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);

	gtk_widget_show_all(dialog);
	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(destroy), (gpointer) a);

	next_screen_1_start ((gpointer) a);
}

void button_die(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You are dead now!");
	if(a->thisplayer.id_from_champ == 0){
		a->champ[a->thisplayer.id_from_champ].position = 0;
	}else{
		a->champ[a->thisplayer.id_from_champ].position = 52;
	}

}

void button_basil(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Kill the basilisk");
}

void button_drake(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Kill the dragon");


}

void button_fight(gint id, gpointer data)
{
	widgets *a = (widgets *) data;
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Fight against the enemie");
}

void button_base(gint id, gpointer data)
{
	widgets *a = (widgets *) data;
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You can buy things in the shop");
}		 
