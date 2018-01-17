#include "header/game_main.h"

void destroy(GtkDialog *dialog, gint response_id, gpointer data)
{
	widgets *a = (widgets *) data;
	gtk_widget_destroy (GTK_WIDGET(dialog));
	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "Buy the things you want");

}


void shop_popup(GtkWidget *wid, gpointer data)
{

	widgets *a = (widgets *) data;
	GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;

	gtk_statusbar_pop(GTK_STATUSBAR(a->info.statusbar), a->info.id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info.statusbar), a->info.id, "In the shop, you can buy the things you want");

	dialog = gtk_dialog_new_with_buttons("Shop",
					     GTK_WINDOW (a->window),
					     GTK_DIALOG_MODAL,
					     ("Close"),
					     GTK_RESPONSE_OK,
					     NULL);
	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	grid = gtk_grid_new();
	gtk_container_add(GTK_CONTAINER(content_area), grid);
	label = gtk_label_new("Buy the things you need");
	gtk_grid_attach(GTK_GRID(grid), label, 0,0,1,1);

	gtk_widget_show_all(dialog);
	g_signal_connect(GTK_DIALOG(dialog), "response", G_CALLBACK(destroy), (gpointer) a);

}
