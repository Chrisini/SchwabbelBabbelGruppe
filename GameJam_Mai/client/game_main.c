#include "header/game_main.h"


// BEI HOVER: INFO ÄNDERT SICH IDEE ToDo
void apply_css(GtkWidget *widget, GtkStyleProvider *css_s)
{
	gtk_style_context_add_provider (gtk_widget_get_style_context (widget),
					css_s, G_MAXUINT);
	if(GTK_IS_CONTAINER (widget)){
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, css_s);
	}
}

// START (1)
void start_screen (gpointer data)
{
	widgets *a = (widgets *) data;

	GtkStyleContext *context;
	gint get_height, get_width;

	gtk_widget_set_name(a->main_box, "background");

	// Layout
	a->start_layout = gtk_fixed_new();

	// Button
	a->start_button = gtk_button_new_with_label("Play Hidden Demon");
	gtk_widget_set_size_request(a->start_button, 400,100);
	g_signal_connect_swapped(a->start_button, "clicked", G_CALLBACK(next_screen_2_choose), (gpointer) a);
	context = gtk_widget_get_style_context(a->start_button);
	gtk_style_context_add_class(context, "selectable");
	gtk_widget_set_name(a->start_button, "start_button");
	gtk_window_get_size(GTK_WINDOW(a->window), &get_width, &get_height);
	gtk_fixed_put(GTK_FIXED(a->start_layout), a->start_button, (get_width-400) / 2, (get_height/2)-100);

	gtk_box_pack_start(GTK_BOX(a->main_box), a->start_layout, FALSE, FALSE, 0);



}

// CHOOSE (2)
void choose_game(gpointer data){

	widgets *a = (widgets *) data;
	champ *c = g_malloc (8*sizeof(champ));
	abilities *ab = g_malloc (8*sizeof(abilities));

	create_champions((gpointer) c, (gpointer) ab, (gpointer) a);

	a->choose_button = gtk_button_new_with_label("Ready");
	gtk_widget_set_halign (a->choose_button, GTK_ALIGN_CENTER);
	// SET CENTER WIDGET
	gtk_widget_set_size_request (a->choose_button, 150, 80);
	g_signal_connect_swapped(a->choose_button, "clicked", G_CALLBACK(next_screen_3_wait), (gpointer) a);
	gtk_widget_set_name(a->choose_button, "choose_button");
	gtk_box_pack_end(GTK_BOX(a->main_box), a->choose_button, FALSE, FALSE, 0);

	//a->visible = FALSE;
	//g_signal_connect(a->start_button, "clicked", G_CALLBACK(in_visible_start_screen), NULL);


}

// WAIT (3)
void wait_connect(gpointer data){

	widgets *a = (widgets *) data;

	/*GtkWidget *spinner;

	spinner = gtk_spinner_new();
	gtk_spinner_start(spinner);*/

	//gtk_box_pack_start(GTK_BOX(a->main_box), spinner, FALSE, FALSE, 0);

	a->wait_button = gtk_button_new_with_label("Connect");
	g_signal_connect_swapped(a->wait_button, "clicked", G_CALLBACK(next_screen_4_in_game), (gpointer) a);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->wait_button, FALSE, FALSE, 0);


}

// (3b)
void no_game(gpointer data){

}

// IN GAME (4)
void in_game (gpointer data){

	widgets *a = (widgets *) data;

	// playground *****
	create_playground((gpointer) a);

	// seperstor
	GtkWidget *separator;
	separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(a->sub_box), separator, FALSE, FALSE, 0);

	// ability - (sidebar) *****
	create_sidebar((gpointer) a);

	// regeneration - (progressbar) *****
	create_progress((gpointer) a);
}

void activate (GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;

	a->css_style = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER(a->css_style), "/game_res/css/style.css");


	// create window and set title *****
	a->window = gtk_application_window_new (a->app);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (a->app));
	gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW (a->window), "Game Jam");
	gtk_window_set_default_size (GTK_WINDOW (a->window), 800, 500); // width, height


	// layout containers *****
	a->main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add( GTK_CONTAINER (a->window), a->main_box);
	a->sub_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);

	// Calling all GUI functions
	// in game_visible.c the visibility is handled

	// menu and info are shown everywhere *****
	create_menu((gpointer) a);
	create_info((gpointer) a);

	// sub_box *****
	gtk_box_pack_start(GTK_BOX((a->main_box)), a->sub_box, FALSE, FALSE, 0);

	// SCREENS
	// (1) startscreen *****
	// calls the first screen
	start_screen((gpointer) a);
	// (2)
	choose_game((gpointer) a);
	// (3)
	wait_connect((gpointer) a);
	// (3b)
	no_game((gpointer) a);
	// (4)
	in_game((gpointer) a);

	// css
	apply_css (a->window, a->css_style);

	// show widgets: window, box-layout
	gtk_widget_show (a->window);
	gtk_widget_show (a->main_box);
	gtk_widget_show (a->sub_box);

	// First Screen is available
	next_screen_1_start((gpointer) a);
}

int main (int argc, char **argv)
{
	int status;

	widgets *a = g_malloc (sizeof(widgets));

	a->app = gtk_application_new ("org.gtk.game", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (a->app, "activate", G_CALLBACK (activate), (gpointer) a);
	status = g_application_run (G_APPLICATION (a->app), argc, argv);
	g_object_unref (a->app);

	g_free (a);
	//	g_free (c);
	// 	g_free (ab);
	return status;
}
