// Where anyone could go next
#include "header/game_main.h"

// Dialog forthe special fields: fight, inhibitor, tower, drake, basilisk
void special_dialogs(gchar title[20], gint id, gpointer data){ //GtkWidget *champ, GtkWidget *building,

	widgets *a = (widgets *) data;

	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;

		dialog = gtk_dialog_new_with_buttons(title,
					     GTK_WINDOW (a->window),
					     GTK_DIALOG_MODAL,
					     ("Close"),
					     GTK_RESPONSE_OK,
					     NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	label = gtk_label_new(title);
	gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);

	gtk_widget_show_all(dialog);
	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(destroy), (gpointer) a);
}

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
			button_nexus(id, TRUE, (gpointer) a); // TRUE if won
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "t_base"))
		{
			button_die(id, (gpointer) a); // not allowed to go into the other base
		}
		else
		{
			 gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
			 gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Congratulation, you have found a secret button, maybe you'll get a gift");

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
			button_nexus(id, TRUE, (gpointer) a); // TRUE if won
		}
		else if (g_str_has_prefix(gtk_widget_get_name(a->game.fieldbutton[id].name), "d_base"))
		{
			button_die(id, (gpointer) a); // not allowed to go into the other base
		}
		else
		{
			gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
			gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Congratulation, you have found a secret button, maybe you'll get a gift");

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

	special_dialogs("Tower", 0, (gpointer) a);


	update_progress (a->game.progressbar[2], -0.25, (gpointer) a);
}

void button_inhi(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Destroy the inhibitor");

	special_dialogs("Inhibitor", 0, (gpointer) a);
}

void button_nexus(gint id, gboolean detection, gpointer data){
	widgets *a = (widgets *) data;

	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;
	gchar title[7];

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	if(detection){
		gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You have won the game !!! :D");
		label = gtk_label_new("You have won the game! :D");
		g_strlcpy(title, "Winner", 7);
	}else{
		gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You have lost the game !!! :(");
		label = gtk_label_new("You have lost the game !!! :(");
		g_strlcpy(title, "Looser", 7);
	}

	dialog = gtk_dialog_new_with_buttons(title,
					     GTK_WINDOW (a->window),
					     GTK_DIALOG_MODAL,
					     ("Close"),
					     GTK_RESPONSE_OK,
					     NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);

	gtk_widget_show_all(dialog);
	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(callback_exit), (gpointer) a);
}

void button_die(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "You are dead now! Back to base is not working, you get full life");
	// go back to base
}

void button_basil(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Kill the basilisk");
	special_dialogs("Basilisk", 0, (gpointer) a);
}

void button_drake(gint id, gpointer data){
	widgets *a = (widgets *) data;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id,
			   "Kill the dragon");
	special_dialogs("Drake", 0, (gpointer) a);

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
