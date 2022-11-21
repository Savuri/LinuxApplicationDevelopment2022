cmake_minimum_required(VERSION 3.22)
project(rhasher C)
set(CMAKE_C_STANDARD 17)

add_definitions(-DLOCALE_PATH="${PROJECT_SOURCE_DIR}/translations")

add_executable(I18n src/I18n.c)


add_custom_target(distclean COMMAND git clean -fd ${CMAKE_SOURCE_DIR})

add_custom_target(translate DEPENDS I18n
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES/I18n.mo ${CMAKE_SOURCE_DIR}/translations/ru.po
        )

add_custom_target(update-translation DEPENDS translate
        COMMAND xgettext --keyword=_ --add-comments ${CMAKE_SOURCE_DIR}/src/I18n.c -o ${CMAKE_CURRENT_BINARY_DIR}/translations/I18n.pot
        COMMAND msgmerge -U ${CMAKE_SOURCE_DIR}/translations/ru.po ${CMAKE_CURRENT_BINARY_DIR}/translations/I18n.pot
        COMMAND msgfmt -o ${CMAKE_CURRENT_BINARY_DIR}/translations/ru/LC_MESSAGES/I18n.mo ${CMAKE_SOURCE_DIR}/translations/ru.po
        COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/I18n.pot
        )

add_custom_target(run_I18n_ru DEPENDS I18n translate
        COMMAND LANGUAGE=ru_RU ${CMAKE_CURRENT_BINARY_DIR}/I18n
        )

add_custom_target(run_I18n_en DEPENDS I18n
        COMMAND LANGUAGE=en_EN ${CMAKE_CURRENT_BINARY_DIR}/I18n
        )
