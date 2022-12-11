cmake_minimum_required(VERSION 3.22)
project(Documentation C)
set(CMAKE_C_STANDARD 17)

find_package(Doxygen REQUIRED dot)

add_definitions(-DLOCALE_PATH= "${PROJECT_SOURCE_DIR}/translations")

add_executable(I18n src/I18n.c)
add_dependencies(I18n translate)

add_custom_target(distclean COMMAND git clean -fd ${CMAKE_SOURCE_DIR})

add_custom_target(translate
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES/I18n.mo ${CMAKE_SOURCE_DIR}/translations/ru.po
        )

add_custom_target(update-translation DEPENDS translate
        COMMAND xgettext --keyword=_ --add-comments ${CMAKE_SOURCE_DIR}/src/I18n.c -o ${CMAKE_CURRENT_BINARY_DIR}/translations/I18n.pot
        COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/translations/ru.po ${CMAKE_CURRENT_BINARY_DIR}/translations/I18n.pot
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES/I18n.mo ${CMAKE_SOURCE_DIR}/translations/ru.po
        COMMAND rm -rf ${CMAKE_CURRENT_BINARY_DIR}/I18n.pot
        )

configure_file(${CMAKE_SOURCE_DIR}/Doxygen.conf ${CMAKE_CURRENT_BINARY_DIR}/Doxygen.conf)
add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxygen.conf
        )

add_custom_target(man DEPENDS I18n
        COMMAND help2man --no-info --output=${CMAKE_BINARY_DIR}/I18n.l --name=${CMAKE_BINARY_DIR}/I18n ${CMAKE_BINARY_DIR}/I18n
        )