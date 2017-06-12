SOURCES = client_communication.c backgroundmusic.c game_main.c in_game_popup_shop.c choose_champs.c game_infolabel.c game_menubar.c game_visible.c in_game_algorithm.c in_game_playground.c in_game_progressbar.c in_game_sidebar.c
RESOURCE = game_res

TARGET = main

CXX = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0 gstreamer-1.0` -Wall -g
CXXFLAGS += -I.
LDFLAGS = -lm


$(TARGET): $(SOURCES) $(RESOURCE).c
	$(CXX) $(SOURCES) $(RESOURCE).c $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
