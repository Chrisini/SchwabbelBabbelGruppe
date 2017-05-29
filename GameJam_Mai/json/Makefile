SOURCES = code.c

TARGET = main

CXX = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0 --libs glib --libs json-glib` -Wall -g
CXXFLAGS += -I.
LDFLAGS = -lm

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

