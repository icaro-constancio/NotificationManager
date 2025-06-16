CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lcurl
TARGET = notify
SRC_DIR = src

all: $(TARGET)

$(TARGET): $(SRC_DIR)/NotificationManager.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -f $(TARGET)