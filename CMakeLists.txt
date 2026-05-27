cmake_minimum_required(VERSION 3.12)
project(wxMagazzino VERSION 1.0 LANGUAGES CXX)

# Mappa il tuo "-std=c++17" del Makefile
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trova wxWidgets sul tuo Mac (mappa i flag di wx-config)
find_package(wxWidgets REQUIRED COMPONENTS core base net)

include(${wxWidgets_USE_FILE})

# Mappa il tuo "SRC = $(wildcard *.cpp)" del Makefile
file(GLOB SRC_FILES "*.cpp")

# Definisce il TARGET = Magazzino
add_executable(Magazzino ${SRC_FILES})

# Mappa LDFLAGS collegando le librerie di wxWidgets
target_link_libraries(Magazzino PRIVATE ${wxWidgets_LIBRARIES})
