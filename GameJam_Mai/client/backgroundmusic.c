// Hidden Demon
// This part is working quite good

#include "header/game_main.h"

/* sudo dnf install gstreamer1-devel gstreamer1-plugins-base-tools
 * gstreamer1-devel-docs gstreamer1-plugins-base-devel
 * gstreamer1-plugins-base-devel-docs gstreamer1-plugins-good
 * gstreamer1-plugins-good-extras gstreamer1-plugins-ugly
 * gstreamer1-plugins-ugly-devel-docs  gstreamer1-plugins-bad-free
 * gstreamer1-plugins-bad-free-devel gstreamer1-plugins-bad-free-extras
 *
 * pkg-config --cflags --libs gstreamer-1.0
*/

// https://gstreamer.freedesktop.org/documentation/application-development/basics/helloworld.html
// The example helped a lot! :)

static gboolean bus_call (GstBus *bus, GstMessage *msg, gpointer data)
{

	widgets *a = (widgets *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      	g_print ("End of stream\n");
      	stop_music((gpointer) a);
	play_music ((gpointer) a);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (a->music.loop);
      break;
    }
    default:
      break;
  }

  return TRUE;
}


static void on_pad_added (GstElement *element, GstPad *pad, gpointer data)
{
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;
  /* We can now link this pad with the vorbis-decoder sink pad */
  //g_print ("Dynamic pad created, linking demuxer/decoder\n");
  sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_link (pad, sinkpad);
  gst_object_unref (sinkpad);
}

// quit music - in the end (main function)
void quit_music(gpointer data){
	widgets *a = (widgets *) data;
	stop_music((gpointer)a);
	GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
	g_print("Quit music");
	gst_element_set_state (a->music.pipeline, GST_STATE_NULL);
	if(ret == GST_STATE_CHANGE_FAILURE){
		g_printerr("Error, change state failed\n");
	}
	g_main_loop_quit (a->music.loop);
	g_print("good\n");
}

// play button
void play_music (gpointer data) {
	widgets *a = (widgets *) data;
	gst_element_set_state (a->music.pipeline, GST_STATE_PLAYING);
	// Code is working like this, and I don't know why xD
	if((g_main_loop_is_running(a->music.loop)) == TRUE){
		g_main_loop_run (a->music.loop);
	}
}

// pause button
void pause_music (gpointer data) {
	widgets *a = (widgets *) data;
	gst_element_set_state (a->music.pipeline, GST_STATE_PAUSED);
	g_main_loop_quit (a->music.loop);
}

// stop button - resets music
void stop_music (gpointer data) {
	widgets *a = (widgets *) data;
  	gst_element_set_state (a->music.pipeline, GST_STATE_READY);
	g_main_loop_quit (a->music.loop);
}


void init_music (gpointer data)
{
	widgets *a = (widgets *) data;

  	// Initialisation
  	gst_init (NULL, NULL);

	// creates main loop
  	a->music.loop = g_main_loop_new (NULL, FALSE);


  	// Create gstreamer elements
  	a->music.pipeline = gst_pipeline_new ("audio-player");
  	a->music.source   = gst_element_factory_make ("filesrc",       "file-source");
  	a->music.demuxer  = gst_element_factory_make ("oggdemux",      "ogg-demuxer");
  	a->music.decoder  = gst_element_factory_make ("vorbisdec",     "vorbis-decoder");
  	a->music.conv     = gst_element_factory_make ("audioconvert",  "converter");
  	a->music.sink     = gst_element_factory_make ("autoaudiosink", "audio-output");

	if (!a->music.pipeline || !a->music.source || !a->music.demuxer || !a->music.decoder || !a->music.conv || !a->music.sink)
	{
 		g_printerr ("One element could not be created. Exiting.\n");
    		return;

	  }

	// Playing file
  	g_object_set (G_OBJECT (a->music.source), "location", "data/robin.ogg", NULL);

	// Message Handler (Error, EOF, ...)
	a->music.bus = gst_pipeline_get_bus (GST_PIPELINE (a->music.pipeline));
	a->music.bus_watch_id = gst_bus_add_watch (a->music.bus, bus_call, (gpointer) a);
	gst_object_unref (a->music.bus);

  	// Add elements to pipeline
  	/* file-source | ogg-demuxer | vorbis-decoder | converter | alsa-output */
 	gst_bin_add_many (GST_BIN (a->music.pipeline),
                    a->music.source, a->music.demuxer, a->music.decoder, a->music.conv, a->music.sink, NULL);

	// Link element together
	/* file-source -> ogg-demuxer ~> vorbis-decoder -> converter -> alsa-output */
	gst_element_link (a->music.source, a->music.demuxer);
	gst_element_link_many (a->music.decoder, a->music.conv, a->music.sink, NULL);
	g_signal_connect (a->music.demuxer, "pad-added", G_CALLBACK (on_pad_added), a->music.decoder);


	// Set pipeline to "ready" state
	g_print ("Music is ready\n");
	gst_element_set_state (a->music.pipeline, GST_STATE_READY);

}


