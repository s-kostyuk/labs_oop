### Лабораторная работа номер 3, вариант У-2

#### Задание:

**(C) 2013-2015, Sergei Zaychenko, KNURE, Kharkiv, Ukraine**

1. Создайте иерархию классов, моделирующую информацию о различных типах логических элементов комбинационных схем:
  - [X] абстрактный класс, представляющий все логические элементы (Element):
    * содержит виртуальный деструктор;
    * содержит чисто виртуальный метод evaluate, возвращающий значение на выходе элемента (false или true);

  - [X] производный класс, представляющий одновходовые элементы (UnaryElement):
    * содержит связь с элементом-аргументом - указатель на объект Element без ответственности за уничтожение;
    * содержит код операции - буфер или инвертор;
    * реализует метод evaluate в соответствии с кодом операции:
      * для буфера => повторяет значение аргумента;
      * для инвертора => возвращает логическое отрицание значения аргумента;

  - [X] производный класс, представляющий двувходовые элементы (BinaryElement):
    * содержит 2 связи с элементами-аргументами  - указатели на объекты Element без ответственности за уничтожение;
    * содержит код операции - AND, OR, XOR;
    * реализует метод evaluate в соответствии с кодом операции (воспользуйтесь прямым эквивалентом с операторами языка - &&, ||, ^);

  - [X] производный класс, представляющий входной порт схемы (InputPortElement):
    * содержит связь с объектом-портом (ссылка на объект InputPort);
    * реализует метод evaluate считыванием текущего значения, установленного в порте

  - [X] конкретный класс, представляющий комбинационную схему - CombinationalCircuit:
    * состоит из набора элементов - указатели на объекты Element с ответственностью за уничтожение;
    * состоит из набора (наборов) портов - указатели на объекты Port с ответственностью за уничтожение;

  - [X] базовый класс, представляющий внешний порт схемы (Port):
    * содержит имя порта;
    * чисто виртуальный метод getValue(), извлекающий его текущее значение;

  - [X] производный класс, представляющий собой входной порт схемы (InputPort):
    * содержит переменную типа bool, хранящую поданное извне значение, по умолчанию false;
    * имеет метод для установки текущего значения;
    * возвращает текущее значение в реализации метода getValue();

  - [X] производный класс, представляющий собой выходной порт схемы (OutputPort):
    * имеет разрываемую связь с объектом-элементом, чье значение он продвигает на выход схемы;
    * при реализации метода getValue():
      * при наличии связи, запрашивает значение у обеспечивающего элемента;
      * при разрыве связи, возвращает false

2. Создайте текстовый файл “simulation.txt”, содержащий поданные на схему тестовые воздействия:

  ```
  SET_INPUT a true
  SET_INPUT b false
  SHOW_PORT c
  ```

3. Разработайте тестовую консольную программу, использующую разработанную иерархию:
  - [X] напишите функцию, которая создаст объекты любой нетривиальной комбинационной схемы на ваш выбор, известной из курса “Компьютерная логика” (например, мультиплексор с 4 входами данных, 2 входами управления и 1 выходом);
  - [X] считывайте данные из файла “simulation.txt” и поочередно выполняйте команды:
    * команда SET_INPUT должна устанавливать текущее значение указанного входного порта (обработайте все возможные здесь ошибки)
    * команда SHOW_PORT должна печатать на консоли сообщение о текущем значении указанного порта (обработайте все возможные здесь ошибки);
  - [X] убедитесь в соответствии результатов вашей программы и результатов, известных из теории курса “Компьютерная логика”;
  - [X] корректно уничтожьте все объекты модели.
