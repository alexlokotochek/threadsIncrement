# parallels_cpp
Для volatile необходимо и достаточно memory_order_relaxed, так как все действия будут выполнены атомарно из-за блокирования futex'a.    


Для обычной переменной необходим memory_order_aquire и memory_order_release, так как во время захвата и освобождения может быть нарушен барьер памяти и непонятно, кто победит,
достаточно - потому что кроме lock и unlock в принципе больше ничего не происходит.   

Скорость Futex ~ 10 секунд, VolatileFutex — 9.4 секунды, Futex — 8.7 секунд.