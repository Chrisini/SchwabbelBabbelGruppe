#include "header/game_main.h"


const GActionEntry app_entries[] = {
	{ "newgame", callback_newgame, NULL, NULL, NULL, {0,0,0} },
	{ "level", callback_level, NULL, NULL, NULL, {0,0,0} },
	{ "highscore", callback_highscore, NULL, NULL, NULL, {0,0,0} },
	{ "exit", callback_exit, NULL, NULL, NULL, {0,0,0} },
	{ "music", callback_music, NULL, NULL, NULL, {0,0,0} },
	{ "about", callback_about, NULL, NULL, NULL, {0,0,0} },
	{ "help", callback_help, NULL, NULL, NULL, {0,0,0} }
};


void create_menu (GtkApplication *app, GtkWidget *box, gpointer user_data)
{
	widgets *a = (widgets *) user_data;

	GtkWidget *menubar;
	GMenu *menu, *menu_game, *menu_settings, *menu_help, *menu_exit;

	char c_music[2] = {"m"};

	// keyboard accelerators
	const gchar *accels_music[2] = {c_music, NULL};
	const gchar *accels_help[2] = {"F1", NULL};
	const gchar *accels_exit[2] = {"x", NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// create the menu *****
	menu = g_menu_new();

	// create game *****
	menu_game = g_menu_new();
	g_menu_append (menu_game, "New Game", "app.newgame"); // restart
	g_menu_append (menu_game, "Change lvl", "app.level"); // level
	g_menu_append (menu_game, "High Score", "app.highscore"); // highscore

	menu_exit = g_menu_new();
	g_menu_append (menu_exit, "Exit", "app.exit"); // quit
	g_menu_append_section(menu_game, NULL, G_MENU_MODEL (menu_exit));

	g_menu_insert_submenu (menu, 0, "Game", G_MENU_MODEL (menu_game));
	g_object_unref (menu_exit);


	// create settings *****
	menu_settings = g_menu_new();
	g_menu_append (menu_settings, "Music", "app.music");
	g_menu_append_submenu (menu, "Settings", G_MENU_MODEL (menu_settings));
	g_object_unref (menu_settings);


	// create help *****
	// about
	menu_help = g_menu_new();
	g_menu_append(menu_help, "About", "app.about");
	g_menu_append(menu_help, "Help", "app.help");
	g_menu_append_submenu (menu, "Help", G_MENU_MODEL (menu_help));
	g_object_unref (menu_help);

	// add menus to menu bar *****
	menubar = gtk_menu_bar_new_from_model (G_MENU_MODEL (menu));
	gtk_box_pack_start (GTK_BOX (box), menubar, FALSE, FALSE, 0);

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.music", accels_music);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.help", accels_help);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.exit", accels_exit);

}

void create_sidebar (GtkApplication *app, GtkWidget *box, gpointer user_data)
{

	widgets *a = (widgets *) user_data;

	GtkWidget *button;

	GtkWidget *grid;

	// layout containers *****
	grid = gtk_grid_new();
	// gtk_container_add (GTK_CONTAINER (a->window), grid);

	char c_life[2] = {"l"};
	char c_twice[2] = {"2"};
	char c_ability1[2] = {"q"};
	char c_ability2[2] = {"w"};
	char c_ability3[2] = {"e"};
	char c_ult[2] = {"r"};
	char c_base[2] = {"b"};

	// keyboard accelerators
	const gchar *accels_life[2] = {c_life, NULL};
	const gchar *accels_twice[2] = {c_twice, NULL};
	const gchar *accels_ability1[2] = {c_ability1, NULL};
	const gchar *accels_ability2[2] = {c_ability2, NULL};
	const gchar *accels_ability3[2] = {c_ability3, NULL};
	const gchar *accels_ult[2] = {c_ult, NULL};
	const gchar *accels_base[2] = {c_base, NULL};

	// map entries and actions *****
	g_action_map_add_action_entries (G_ACTION_MAP (app), app_entries,
					 G_N_ELEMENTS (app_entries), (gpointer) a);

	// ability - buttons *****
	// Base - B
	button = gtk_button_new_with_label ("base");
	g_signal_connect (button, "clicked", G_CALLBACK (but_base), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);
	// Life - Lebenspunkte aufladen
	button = gtk_button_new_with_label ("Life");
	g_signal_connect (button, "clicked", G_CALLBACK (but_life), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);
	// Ability - Q - Point / Click Ability
	button = gtk_button_new_with_label ("ability 1");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability1), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);
	// Ability - W - Area / Flaechenschaden
	button = gtk_button_new_with_label ("ability 2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability2), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);
	// Ability - E - passive damage
	button = gtk_button_new_with_label ("ability 3");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ability3), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);
	// Ability  - R - ulti
	button = gtk_button_new_with_label ("ult");
	g_signal_connect (button, "clicked", G_CALLBACK (but_ult), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 1, 1);
	// Two turns for Mr X
	button = gtk_button_new_with_label ("x2");
	g_signal_connect (button, "clicked", G_CALLBACK (but_twice), NULL);
	gtk_grid_attach (GTK_GRID (grid), button, 0, 6, 1, 1);

	// connect keyboard accelerators *****
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.life", accels_life);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.twice", accels_twice);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability1", accels_ability1);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability2", accels_ability2);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ability3", accels_ability3);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.ult", accels_ult);
	gtk_application_set_accels_for_action (GTK_APPLICATION (app), "app.base", accels_base);

	gtk_box_pack_end(GTK_BOX(box), grid, FALSE, FALSE,0);
}

void create_info(GtkApplication *app, GtkWidget *box, gpointer user_data)
{

	GtkWidget *info_label;
	// GtkWidget *gtk_assistant_new (void);

	GtkWidget *grid;
	grid = gtk_grid_new ();

	//gtk_seperator_new(GTK_ORIENTATION_HORIZONTAL);

	info_label = gtk_label_new ("What to do: Count til 100, if you are ready, begin again");
	gtk_widget_set_name(info_label, "info_label");
	gtk_grid_attach (GTK_GRID (grid), info_label, 1,1,1,1);

	gtk_box_pack_end(GTK_BOX(box), grid, FALSE, FALSE,0);

}

void create_progress (GtkApplication *app, GtkWidget *box, gpointer user_data)
{
	//widgets *a = (widgets *) user_data;
	GtkWidget *progb_attack, *progb_protection, *progb_life, *progb_energy;
	GtkWidget *grid;

	// layout containers *****
	grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);

	// attack - Schade
	progb_attack = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_attack, 1, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_attack), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_attack), NULL);
	gdouble val_attack;
	val_attack = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_attack)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_attack), val_attack);
	// protection - Ruestung
	progb_protection = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_protection, 2, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_protection), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_protection), NULL);
	gdouble val_protect;
	val_protect = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_protection)) + 0.1;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_protection), val_protect);

	// life / dead - Leben / Tod
	progb_life = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_life, 3, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_life), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_life), NULL);
	gdouble val_life;
	val_life = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_life)) + 0.3;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_life), val_life);

	// energy - Energie, Mana
	progb_energy = gtk_progress_bar_new();
	gtk_grid_attach (GTK_GRID (grid), progb_energy, 4, 1, 1, 1);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progb_energy), TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progb_energy), NULL);
	gdouble val_energy;
	val_energy = gtk_progress_bar_get_fraction (GTK_PROGRESS_BAR (progb_energy)) + 0.3;
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progb_energy), val_energy);


	gtk_box_pack_end(GTK_BOX(box), grid, FALSE, FALSE,0);

}


void apply_css(GtkWidget *widget, GtkStyleProvider *css_style)
{
	gtk_style_context_add_provider (gtk_widget_get_style_context (widget),
					css_style, G_MAXUINT);
	if(GTK_IS_CONTAINER (widget)){
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, css_style);
	}

}
static void activate (GtkApplication *app, gpointer user_data)
{
	widgets *a = (widgets *) user_data;
	GtkStyleProvider *css_style;

	GtkWidget *main_box; // layout
	GtkWidget *sub_box;
	// GtkWidget *last_box;
	// GtkWidget *grid; // sub-layout


	// create window and set title *****
	a->window = gtk_application_window_new (app);
	gtk_window_set_application (GTK_WINDOW (a->window), GTK_APPLICATION (app));
	gtk_window_set_position (GTK_WINDOW (a->window), GTK_WIN_POS_CENTER);
	gtk_window_set_title (GTK_WINDOW (a->window), "Game Jam");
	gtk_window_set_default_size (GTK_WINDOW (a->window), 800, 500); // width, height


	// layout containers *****
	main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add( GTK_CONTAINER (a->window), main_box);
	sub_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

	//grid = gtk_grid_new ();
	//gtk_container_add (GTK_CONTAINER (a->window), grid);


	// menu *****
	create_menu(app, GTK_WIDGET (main_box), (gpointer) a);

	gtk_box_pack_start(GTK_BOX(main_box), sub_box, FALSE, FALSE, 0);

	// ability - (sidebar) *****
	create_sidebar(app, GTK_WIDGET(sub_box), (gpointer) a);



	// info - field
	create_info(app, GTK_WIDGET (main_box), (gpointer) a);

	// regeneration - progress bar *****
	create_progress(app, GTK_WIDGET (main_box), (gpointer) a);

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
