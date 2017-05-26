SOURCES = game_main.c callback.c buttons.c sidebar.c playground.c
RESOURCE = game_res

TARGET = main

CXX = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g
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
