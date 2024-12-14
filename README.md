# Руководство пользователя интерфейса прототипа пакетного менеджера

## Основные команды

### 1. Установка пакета
```
install <package_name> <major> <minor> <patch> [dependencies...]
```
- `package_name` - имя пакета
- `major.minor.patch` - версия пакета
- `dependencies` - опциональный список зависимостей

Пример:
```
install mypackage 1 0 0 dep1 dep2
```

### 2. Удаление пакета
```
remove <package_name> <major> <minor> <patch>
```
Пример:
```
remove mypackage 1 0 0
```

### 3. Просмотр списка установленных пакетов
```
list
```

### 4. Просмотр информации о конкретном пакете
```
show <package_name>
```

### 5. Очистка консоли
```
clear
```

## Тестирование

### Функциональное тестирование
- `fseq` - тест Sequence
- `flistseq` - тест ListSequence
- `farrseq` - тест ArraySequence
- `fhasht` - тест HashTable
- `fiset` - тест ISet
- `fpkgmn` - тест PackageManager

### Нагрузочное тестирование
- `chseq`
  `<values>` - сравнение Sequence и std::vector
- `chlistseq`
   `<values>` - сравнение ListSequence и std::list
- `charrseq`
  `<values>` - сравнение ArraySequence и std::vector
- `chhasht`
  `<values>` - сравнение HashTable и std::unordered_map
- `chiset`
  `<values>` - сравнение ISet и std::set

### Построение графиков
- `pseq`
  `<values>` - график Sequence vs std::vector
- `plistseq`
  `<values>` - график ListSequence vs std::list
- `parrseq`
  `<values>` - график ArraySequence vs std::vector
- `phasht`
  `<values>` - график HashTable vs std::unordered_map
- `piset`
  `<values>` - график ISet vs std::set

## Дополнительные команды

### Справка
- `help` - показать список доступных команд
- `admin` - показать список административных команд

### Выход
```
exit
```
- Сохраняет состояние менеджера пакетов в файл и завершает программу

## Примечания
- Все версии пакетов должны быть положительными числами
- При установке пакета можно указать несколько зависимостей
- Данные автоматически сохраняются в файл при выходе и загружаются при запуске
- При возникновении ошибок выводятся соответствующие сообщения
