# Лабораторная работа № 3.1. Файловый обозреватель
# Постановка задачи
Используя паттерн "Стратегия", необходимо реализовать консольное приложение, принцип работы которого следующий: пользователь указывает директорию, для которой требуется вычислить размер содержимого. 
Функция, в зависимости от выбранной стратегии, проводит вычисление, где результатом является набор соответствующих данных вида списка файлов и папок (только верхнего уровня) / списка типов файлов, содержащихся в директории, а также занимаемый ими объём в процентах (точность два знака после запятой; если точности не хватает, а размер элемента не равен нулю, требуется это показать, например, в виде "< 0.01%")
# Лабораторная работа № 3.2. Графическое приложение
# Постановка задачи
Используя концепцию MVC, требуется разработать модель, данные в которой будут заполняться с помощью реализованных ранее стратегий обхода содержимого папки.
Модель должна содержать, название и занимаемый объём в процентах. Использовать модель файловой системы (QFileSystemModel), отображаемая в двух представлениях: QTreeView (слева) и QTableView (справа).
После реализации модели, достаточно просто сменить тип отображаемой модели у QTableView.
Таким образом, пользователь, выбрав директорию в левой части окна, запускает процесс её сканирования и может увидеть содержимое директории (относительно заданного типа группировки) в правой части окна.
Соответственно, также требуется доработать графический интерфейс, позволив пользователю выбирать способ группировки содержимого.
# Дополнительно
Библиотека: Qt 5.15.2

Система сборки: Qmake
