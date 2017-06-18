#include "header/game_main.h"

// Nothing is working here

void name_initialisation(gpointer data)
{

}

void listen_for_id(gpointer data)
{
	widgets *a = (widgets *) data;
	a->thisplayer.id_from_server = 0;
}

void listen_for_player(gpointer data)
{
	widgets *a = (widgets *) data;
	if(a->thisplayer.id_from_server == 0){

	}else{
		// wait - listen
	}
}

void listen_for_data(gpointer data)
{

}


void if_tower(gpointer data)
{
	widgets *a = (widgets *) data;
	if(a->champ[a->thisplayer.id_from_champ].position == 5){

	}
}

void if_nexus(gpointer data)
{
	widgets *a = (widgets *) data;
	if(a->champ[a->thisplayer.id_from_champ].position == 1){

	}
}

void if_inhibitor(gpointer data)
{
	widgets *a = (widgets *) data;
	if(a->champ[a->thisplayer.id_from_champ].position == 7){

	}

}

/*
 * This function reads all the data, which is send to the server
 * after clicking the "Move complete Button" (Sidebar)
 */
void move_complete(GtkWidget *wid, gpointer data){
	//widgets *a = (widgets *) data;

}
