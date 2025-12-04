# Makefile для проекта численного интегрирования

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
INCLUDES = -I./include
LIBS = -lm

# Директории
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build

# Исходные файлы
SOURCES = $(SRC_DIR)/main.cpp $(SRC_DIR)/function.cpp $(SRC_DIR)/integration.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Заголовочные файлы
HEADERS = $(INCLUDE_DIR)/function.h $(INCLUDE_DIR)/integration.h

# Исполняемый файл
TARGET = integration

# Правила сборки
.PHONY: all clean run help rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Линковка проекта..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LIBS)
	@echo "Сборка завершена! Исполняемый файл: ./$(TARGET)"

$(SRC_DIR)/main.o: $(SRC_DIR)/main.cpp $(HEADERS)
	@echo "Компиляция main.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/main.cpp -o $(SRC_DIR)/main.o

$(SRC_DIR)/function.o: $(SRC_DIR)/function.cpp $(INCLUDE_DIR)/function.h
	@echo "Компиляция function.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/function.cpp -o $(SRC_DIR)/function.o

$(SRC_DIR)/integration.o: $(SRC_DIR)/integration.cpp $(INCLUDE_DIR)/integration.h
	@echo "Компиляция integration.cpp..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SRC_DIR)/integration.cpp -o $(SRC_DIR)/integration.o

rebuild: clean all

run: $(TARGET)
	@echo "Запуск программы..."
	@echo ""
	./$(TARGET)

interactive: $(TARGET)
	@echo "Запуск в интерактивном режиме..."
	@echo ""
	./$(TARGET) --interactive

clean:
	@echo "Очистка..."
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(BUILD_DIR)
	@echo "Очистка завершена."

help:
	@echo "Доступные команды:"
	@echo "  make          - Собрать проект"
	@echo "  make rebuild  - Пересобрать проект с нуля"
	@echo "  make run      - Собрать и запустить"
	@echo "  make interactive - Запустить в интерактивном режиме"
	@echo "  make clean    - Удалить собранные файлы"
	@echo "  make help     - Показать эту справку"
