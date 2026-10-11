cmake_minimum_required(VERSION 3.16) 
project(arraylib VERSION 1.0.0 LANGUAGES CXX) 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF) 
# ---- Динамическая библиотека ---- 
add_library(arraylib SHARED src/arraylib.cpp) 
#SHARED в add_library — сборка .so / .dll. 
#target_include_directories(... PUBLIC ...) — объекты, #которые линкуется с arraylib, получают путь к include/ 
target_include_directories(arraylib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ) 
#target_compile_definitions(... PRIVATE ARRAYLIB_BUILD) #— макрос ARRAYLIB_BUILD определён только при
 #сборке библиотеки, чтобы функции экспортировались 
target_compile_definitions(arraylib PRIVATE ARRAYLIB_BUILD) 
if (MSVC) 
target_compile_options(arraylib PRIVATE /W4) 
else() 
target_compile_options(arraylib PRIVATE -Wall -Wextra -Wpedantic) 
endif() 
# ---- Демонстрационная программа ---- 
add_executable(app main.cpp) 
target_link_libraries(app PRIVATE arraylib) 
# Автоматически искать .so/.dll рядом с исполняемым #файлом 
#BUILD_RPATH "$ORIGIN" — программа ищет .so рядом с #собой без LD_LIBRARY_PATH 
set_target_properties(app PROPERTIES BUILD_RPATH "$ORIGIN") 
# Все артефакты — в каталог сборки 
#ARCHIVE_OUTPUT_DIRECTORY — путь для .a / .lib; 
#LIBRARY_OUTPUT_DIRECTORY — для .so; #RUNTIME_OUTPUT_DIRECTORY — для .dll и exe. 
set_target_properties(arraylib app PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}" 
LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"  
ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}") 
# ---- Тесты ---- 
#include(CTest) — учитывает опцию BUILD_TESTING; #тесты можно отключить через DBUILD_TESTING=OFF 
include(CTest) 
if (BUILD_TESTING) 
add_executable(test_unit tests/test_unit.cpp) 
target_link_libraries(test_unit PRIVATE arraylib) 
# Отключение -DNDEBUG, чтобы assert() не пропадали #в Release 
#-UNDEBUG обеспечивает работу  assert()  даже в #Release-сборке 
target_compile_options(test_unit PRIVATE -UNDEBUG) 
add_test(NAME unit COMMAND test_unit) 
add_executable(test_integration tests/test_integration.cpp) 
target_link_libraries(test_integration PRIVATE arraylib) 
target_compile_options(test_integration PRIVATE -UNDEBUG) 
add_test(NAME integration COMMAND test_integration) 
endif() 
# ---- Пример по варианту ---- 
add_executable(variant_13 examples/variant_13.cpp) 
target_link_libraries(variant_13 PRIVATE arraylib)



include(CTest) 
if (BUILD_TESTING) 
# add_executable(test_unit tests/test_unit.cpp) 
target_link_libraries(test_unit PRIVATE arraylib) 
# Отключаем NDEBUG, чтобы assert работал и в Release 
target_compile_options(test_unit PRIVATE -UNDEBUG) 
# add_test(NAME unit COMMAND test_unit) 
# add_executable(test_integration tests/test_integration.cpp) 
target_link_libraries(test_integration PRIVATE arraylib) 
target_compile_options(test_integration PRIVATE -UNDEBUG) 
# add_test(NAME integration COMMAND test_integration) 
endif()