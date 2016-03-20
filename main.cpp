/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: gunrock
 * Задание: Запуск независимых потоков
 * Написать программу, которая запускает N независимых потоков выполнения
 * и ожидает завершения исполнения всех потоков
 * (N пусть задаётся как параметр командной строки запуска программы).
 * Пусть каждый из потоков фиксированное число раз, в цикле,
 * только индицирует себя литерой или числом (различными для каждого потока) в общей строке индикации,
 * и выполняет кратчайшую пассивную задержку каждом цикле (чтобы дать и другим поработать).
 * Обеспечить, чтобы циклы активного выполнения потоки начали не непосредственно в момент создания каждого из них,
 * а одновременно после создания последнего из N потоков.
 * Перед завершением программы выведите строку индикации,
 * показывающую последовательность чередования потоков.
 *
 * Created on March 20, 2016, 1:53 PM
 */

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <string.h>

//using namespace std;

/*
 * 
 */

void * thread_function(int num)
{
    // TODO: add waiting for start thread function
    
    for (int i = 0; i < num; ++i)
    {
        std::cout << num << "  ";
        sleep(1);
    }
}

int main(int argc, char** argv) {

    if (argc < 2 || argc > 2)
    {
        std::cerr << "usage: " << argv[0] << " <number of threads>\n";
        return 1;
    }
    
    for (int i = 0; i < strlen(argv[1]); ++i)
    {
        if (!isdigit(argv[1][i]))
        {
            std::cerr << argv[1][i] << " is not digit\n";
            return 1;
        }
    }
    
    return 0;
}

