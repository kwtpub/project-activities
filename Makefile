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

# Исполняемый файл
TARGET = integration

# Правила сборки
.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(SOURCES)
	@echo "Компиляция проекта..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SOURCES) -o $(TARGET) $(LIBS)
	@echo "Сборка завершена! Исполняемый файл: ./$(TARGET)"

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
	@echo "  make run      - Собрать и запустить"
	@echo "  make interactive - Запустить в интерактивном режиме"
	@echo "  make clean    - Удалить собранные файлы"
	@echo "  make help     - Показать эту справку"
