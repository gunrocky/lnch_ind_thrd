# lnch_ind_thrd
2. Запуск независимых потоков
Написать программу, которая запускает N независимых потоков выполнения
и ожидает завершения исполнения всех потоков
(N пусть задаётся как параметр командной строки запуска программы).
Пусть каждый из потоков фиксированное число раз, в цикле,
только индицирует себя литерой или числом (различными для каждого потока)
в общей строке индикации, и выполняет кратчайшую пассивную задержку каждом цикле
(чтобы дать и другим поработать).
Обеспечить, чтобы циклы активного выполнения потоки начали не непосредственно в момент создания каждого из них,
а одновременно после создания последнего из N потоков.
Перед завершением программы выведите строку индикации,
показывающую последовательность чередования потоков.
