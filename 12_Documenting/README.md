Doxygen на основе этого README.md будет пытаться сделать man для утилиты. Я это игнорирую и делаю man с помощью help2man.
### Сборка
```
mkdir build
cd build
cmake ..
make all
```
### Запуск
Русская версия:
```
LANGUAGE=ru_RU ./I18n 
```
Английская версия:
```
LANGUAGE=en_EN ./I18n 
```

### Документация
Для открытия документации в firefox нужно выполнить команды:
```
make doc
firefox Doxygen/html/index.html
```

### Man
```
make man
man ./I18n.l
```
