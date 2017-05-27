#include "header/game_main.h"


void create_info(GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;
	GtkWidget *info_label;
	// GtkWidget *gtk_assistant_new (void);

	GtkWidget *grid;
	grid = gtk_grid_new ();

	//gtk_seperator_new(GTK_ORIENTATION_HORIZONTAL);

	info_label = gtk_label_new ("What to do: Count til 100, if you are ready, begin again");
	gtk_widget_set_name(info_label, "info_label");
	gtk_grid_attach (GTK_GRID (grid), info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(a->main_box), grid, FALSE, FALSE,0);
}




void apply_css(GtkWidget *widget, GtkStyleProvider *css_style)
{
	gtk_style_context_add_provider (gtk_widget_get_style_context (widget),
					css_style, G_MAXUINT);
	if(GTK_IS_CONTAINER (widget)){
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, css_style);
	}

}

// (1)
void startscreen (GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;
	GtkWidget *playbutton;
	GtkStyleContext *context;
	gtk_widget_set_name(a->main_box, "background");
	GtkWidget *grid;

	grid = gtk_grid_new();

	playbutton = gtk_button_new_with_label("Play Hidden Demon");
	gtk_widget_set_size_request(playbutton, 100,100);
	g_signal_connect(playbutton, "clicked", G_CALLBACK(choose_game), NULL);
	context = gtk_widget_get_style_context(playbutton);
	gtk_style_context_add_class(context, "selectable");
	gtk_widget_set_name(playbutton, "playbutton");
	gtk_grid_attach(GTK_GRID(grid), playbutton, 0,0,1,1);
	gtk_box_pack_start(GTK_BOX(a->main_box), grid, FALSE, FALSE, 0);


}

// (2)
void choose_game(GSimpleAction *action, GVariant *parameter, gpointer data){
	widgets *a = (widgets *) data;
	in_game(a->app, (gpointer) a);
}

// (3a)
void wait_connect(GtkApplication *app, gpointer data){

}

// (3b)
void no_game(GtkApplication *app, gpointer data){

}

// (4)
void in_game (GtkApplication *app, gpointer data){

	widgets *a = (widgets *) data;

	// playground *****
	create_playground(app, (gpointer) a);

	// seperstor
	GtkWidget *separator;
	separator = gtk_separator_new (GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(a->sub_box), separator, FALSE, FALSE, 0);

	// ability - (sidebar) *****
	create_sidebar(app, (gpointer) a);

	// info - field
	create_info(app, (gpointer) a);

	// regeneration - progress bar *****
	create_progress(app, (gpointer) a);

}

void activate (GtkApplication *app, gpointer data)
{
	widgets *a = (widgets *) data;
	GtkStyleProvider *css_style;

	//GtkWidget *main_box; // layout
	//GtkWidget *a->sub_box;
	// GtkWidget *last_box;
	// GtkWidget *grid; // sub-layout


	// create window and set title *****
	a->window = gtk_application_window_new (app);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (app));
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
	create_menu(app, (gpointer) a);

	// subbos *****
	gtk_box_pack_start(GTK_BOX((a->main_box)), a->sub_box, FALSE, FALSE, 0);

	// startscreen *****
	startscreen(app, (gpointer) a);

	// wait scree calls "in game"
	//in_game(app, (gpointer) a);


	// css
	css_style = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER(css_style), "/game_res/css/style.css");
	apply_css (a->window, css_style);

	// show all widgets
	gtk_widget_show_all (a->window);
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
