#include <header/game_main.h>

void shop_popup(){

	gtk_statusbar_pop(GTK_STATUSBAR(a->info_label), a->info_id); // removes content
	gtk_statusbar_push(GTK_STATUSBAR(a->info_label), a->info_id, "Buy the things you want");



}
