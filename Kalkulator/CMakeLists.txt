# CMakeList.txt: Projekt CMake pro Kalkulator, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#
cmake_minimum_required (VERSION 3.8)

project ("Kalkulator")

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (Kalkulator "Kalkulator.cpp" "Kalkulator.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Kalkulator PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
