#include "header/game_main.h"


void callback_newgame(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void callback_level(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void callback_highscore(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void callback_exit(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_application_quit(data);
	/*GtkWidget *dialog;
	GtkWidget *grid;
	GtkWidget *label;
	GtkWidget *content_area;
	widgets *a = (widgets *) data;

	dialog = gtk_message_dialog_new_with_buttons ("Quit",
					GTK_WINDOW (a->window),
					GTK_DIALOG_MODAL,
					_ ("_NO"),
					GTK_RESPONSE_CANCEL,
					_ ("YES"),
					GTK_RESPONSE_OK,
					 GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_INFO,
					 //GTK_BUTTON_CLOSE,
					 "Do you want to quit?");
	g_signal_connect(dialog, "response",
			 G_CALLBACK (gtk_widget_destroy), NULL);*/
	//gtk_widget_show(dialog);

}

void callback_music(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}

void close_dialog(GtkDialog *dialog, gint response_id, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(dialog));

}


void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	//GdkPixbuf *pixbuf;
	GtkWidget *about_dialog;
	about_dialog = gtk_about_dialog_new();
	//pixbuf = gtk_pixbuf_new_from_file("images/logo.png", NULL)	;
	gtk_show_about_dialog(GTK_WINDOW (data),
			      "program-name", "About Hidden Demons",
			      "version", "1.0",
			      "copyright", "Copyright \xc2\xa9 elevariety",
			      "comments", "A game by some beginner-developers",
			      //"authors", "chrisy",
			      //"logo", pixbuf,
			      "title", "About: Hidden Demons",
			      NULL);

	g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_dialog), NULL);
	//g_object_unref (pixbuf);
}

void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}
							   
