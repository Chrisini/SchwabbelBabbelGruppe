#include "header/game_main.h"
#include <string.h>

// this example helped me a lot :)
// https://stackoverflow.com/questions/9513327/gio-socket-server-client-example

int send_message(gpointer data){

	widgets *a = (widgets *) data;
	GError *error = NULL;


	/* use the connection */
	GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (a->socket_connection));
	g_output_stream_write  (ostream,
 		a->message_buf, /* your message goes here */
		1024, /* length of your message */
  		NULL,
 		&error);

	// Error Handling
	if (error != NULL)
	{
		g_print("Error");
	}
	else
	{
		g_print ("Sended data succesfully!\n");
	}
	return 1;
}

void recieve_message(gpointer data){

	widgets *a = (widgets *) data;
	GError *error = NULL;

	/* use the connection */
	GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (a->socket_connection));


}

void communicate(gpointer data){

	widgets *a = (widgets *) data;

	// Client *****
	GSocketClient * socket_client;
	socket_client = g_socket_client_new ();

	gchar *host_and_port = "localhost";
	guint16 default_port = 1500; // any port?
	GCancellable *cancellable = NULL;
	GError *error = NULL;

	// Connection *****
	// Attempts to create a TCP connection to the named host.
	a->socket_connection = g_socket_client_connect_to_host (socket_client,
                                 host_and_port,
                                 default_port,
                                 cancellable,
                                 &error);


	// Error Handling
	if (error != NULL)
	{
		g_print("Error");
	}
	else
	{
		g_print ("Connection successful!\n");
	}


	// First Message is the name - it's the inital message
	g_strlcpy(a->message_buf, a->thisplayer.player_name, 1024);
	send_message((gpointer) a);

	// TODO Free with: g_object_unref()
	// TODO close socket connection:  g_io_stream_close()
}
