#include "header/game_main.h"


void create_info(gpointer data)
{

	widgets *a = (widgets *) data;

	// GtkWidget *gtk_assistant_new (void);

	a->info_grid = gtk_grid_new ();

	a->info_label = gtk_label_new ("Welcome to Hidden Demon, press the Button to choose your Champ");
	gtk_widget_set_name(a->info_label, "info_label");
	gtk_grid_attach (GTK_GRID (a->info_grid), a->info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), a->info_grid, FALSE, FALSE,0);

	gtk_widget_show_all(a->info_grid);
}




void apply_css(GtkWidget *widget, GtkStyleProvider *css_s)
{

	gtk_style_context_add_provider (gtk_widget_get_style_context (widget),
					css_s, G_MAXUINT);
	if(GTK_IS_CONTAINER (widget)){
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, css_s);
	}

}

// (1)
void startscreen (gpointer data)
{
	widgets *a = (widgets *) data;
	GtkWidget *playbutton;
	GtkStyleContext *context;
	gtk_widget_set_name(a->main_box, "background");
	GtkWidget *grid;

	gint get_height, get_width;

	grid = gtk_fixed_new();

	playbutton = gtk_button_new_with_label("Play Hidden Demon");
	gtk_widget_set_size_request(playbutton, 300,80);
	g_signal_connect(playbutton, "clicked", G_CALLBACK(choose_game), NULL);
	context = gtk_widget_get_style_context(playbutton);
	gtk_style_context_add_class(context, "selectable");
	gtk_widget_set_name(playbutton, "playbutton");
	gtk_window_get_size(GTK_WINDOW(a->window), &get_width, &get_height);
	gtk_fixed_put(GTK_FIXED(grid), playbutton, (get_width/2)-300, (get_height/2)-0);

	gtk_box_pack_start(GTK_BOX(a->main_box), grid, FALSE, FALSE, 0);

}

// (2)
void choose_game(gpointer data){

	widgets *a = (widgets *) data;
	//in_game((gpointer) a);
}

// (3a)
void wait_connect(gpointer data){

}

// (3b)
void no_game(gpointer data){

}

// (4)
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

	// regeneration - progress bar *****
	create_progress((gpointer) a);

}

void activate (GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;

	a->css_style = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER(a->css_style), "/game_res/css/style.css");

	//GtkWidget *main_box; // layout
	//GtkWidget *a->sub_box;
	// GtkWidget *last_box;
	// GtkWidget *grid; // sub-layout


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

	//grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);


	// menu *****
	create_menu((gpointer) a);
	create_info((gpointer) a);

	// subbos *****
	gtk_box_pack_start(GTK_BOX((a->main_box)), a->sub_box, FALSE, FALSE, 0);

	// (1) startscreen *****
	startscreen((gpointer) a);

	// (2)
	choose_game((gpointer) a);

	// (3a)
	wait_connect((gpointer) a);

	// (3b)
	no_game((gpointer) a);

	// (4)
	in_game((gpointer) a);


	// css

	apply_css (a->window, a->css_style);

	// show all widgets
	gtk_widget_show (a->window);
	gtk_widget_show (a->main_box);
	gtk_widget_show (a->sub_box);
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
	return status;
}
