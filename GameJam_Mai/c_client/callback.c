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

void callback_about(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	/*GtkWidget *about_window;
	about_window = gtk_window_new(GTK_WINDOW_POPUP);
	/*GtkWidget *about;
	about = gtk_about_dialog_new ();
	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about), "About Hidden Demons");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(about), "Chrisy, Kathi, Sammy, Beety, John");
	gtk_show_about_dialog(about_window, "About Hidden Demons");
	g_print("Music");*/
}

void callback_help(GSimpleAction *action, GVariant *parameter, gpointer data)
{
	g_print("Music");
}
							   
