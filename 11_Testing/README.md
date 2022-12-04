# Создать директорию и запустить cmake

```
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

# Тесты

```
// Как починить зависимости между gtest в ctest и cmake я так и не понял (похоже что никак и никак уже давно и это грустно). Так что забилдить тесты нужно ручками
make all 

ctest --verbose
```

# Получение покрытия
```
make coverage
```
Note: Для получения покрытия нужно собрать проект в режиме Debug
# Открытие готового отчёта
```
firefox CODE_COVERAGE/index.html
```

