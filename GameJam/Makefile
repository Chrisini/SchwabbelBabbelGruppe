SOURCES = game_main.c callback.c buttons.c
# RESOURCE

TARGET = main

CXX = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g
CXXFLAGS += -I.
LDFLAGS = -lm

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

.PHONY: clean
clean:
	@rm -rf $(OBJECT) $(TARGET) core *~
