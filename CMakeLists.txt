cmake_minimum_required(VERSION 3.10)

# Название проекта
project(NumericalIntegration VERSION 1.0 LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Включаем предупреждения компилятора
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Директория для заголовочных файлов
include_directories(${PROJECT_SOURCE_DIR}/include)

# Исходные файлы
set(SOURCES
    src/main.cpp
    src/function.cpp
    src/integration.cpp
)

# Создаем исполняемый файл
add_executable(integration ${SOURCES})

# Линкуем математическую библиотеку (для Linux)
if(UNIX AND NOT APPLE)
    target_link_libraries(integration m)
endif()

# Устанавливаем имя выходного файла
set_target_properties(integration PROPERTIES OUTPUT_NAME "integration")

# Информация о сборке
message(STATUS "Конфигурация проекта:")
message(STATUS "  Компилятор C++: ${CMAKE_CXX_COMPILER}")
message(STATUS "  Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "  Тип сборки: ${CMAKE_BUILD_TYPE}")
