# CMakeList.txt: проект CMake для Log_analyser; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
file(GLOB files "./core/*.cpp" "./core/*.h"  "./tools/*.cpp"  "./tools/*.h" )
# Добавьте источник в исполняемый файл этого проекта.
add_executable (Log_analyser "main.cpp" ${files} )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Log_analyser PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.

