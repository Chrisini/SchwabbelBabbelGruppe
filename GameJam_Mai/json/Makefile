SOURCES = code.c

TARGET = main

CXX = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0 json-glib-1.0` -Wall -g
CXXFLAGS += -I.
LDFLAGS = -lm

$(TARGET): $(SOURCES)
	$(CXX) $(SOURCES) $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

