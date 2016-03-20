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
#include <string.h>
#include <vector>
#include <memory>

// quantity of cycles of each thread
static const int g_cycles = 8;

// condition for threads to start
pthread_cond_t g_cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t g_cond_mutex = PTHREAD_MUTEX_INITIALIZER;

// control mutex
pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

// for saving of threads work order
pthread_mutex_t g_order_mutex = PTHREAD_MUTEX_INITIALIZER;
static std::string g_order;

// quantity of ready threads
static int g_threads_ready = 0;

// thread info structure
struct thread_info
{
    pthread_t thread_id;
    int       thread_num;
};


void * thread_function(void *arg)
{
    // at first, I wanted to use shared pointer
    //std::shared_ptr<int> num(reinterpret_cast<int *>(arg));
    
    int *pnum = reinterpret_cast<int *>(arg);
    pthread_mutex_lock(&g_mutex);
    // saving in stack needs because
    // it happens some wonder with dereferenced pointer in to_string function
    int num = *pnum;
    std::cout << "thread " << *pnum << std::endl;
    g_threads_ready++;
    pthread_mutex_unlock(&g_mutex);
    
    // all threads wait to start
    pthread_mutex_lock(&g_cond_mutex);
    pthread_cond_wait(&g_cond, &g_cond_mutex);
    pthread_mutex_unlock(&g_cond_mutex);
    
    for (int i = 0; i < g_cycles; ++i)
    {
        std::cout << num << "  ";
        // is it need to use mutex to write info to string?
        // p.s. it could be problem with memory corruption without mutex
        pthread_mutex_lock(&g_order_mutex);
        g_order.append(std::to_string(num) + ", ");
        pthread_mutex_unlock(&g_order_mutex);
        // ===================================
        usleep(100);
        // it needs because output hangs without it
        fflush(stdout);
    }
    return (void *) 0;
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
    
    g_order.clear();
    int error = 0;
    int num_threads = atoi(argv[1]);
    if (num_threads < 0)
    {
        std::cerr << "input parameter must be positive\n";
        return 1;
    }
    
    std::vector<struct thread_info> thrs;
    
    for (int i = 0; i < num_threads; ++i)
    {
        // at first, I wanted to use shared pointer
        /*std::shared_ptr<int> arg(new int);
        *arg = i;*/
        thrs.push_back(thread_info());
        thrs[i].thread_num = i;
        if ((error = pthread_create(&thrs[i].thread_id, NULL, thread_function, &thrs[i].thread_num)))
        {
            std::cerr << "thread " << i << "; pthread_create() err = " << error << std::endl;
            thrs.pop_back();
        }
    }
    
    // wait until all threads will be ready
    while(true)
    {
        pthread_mutex_lock(&g_mutex);
        if (g_threads_ready == thrs.size())
        {
            pthread_mutex_unlock(&g_mutex);
            break;
        }
        pthread_mutex_unlock(&g_mutex);
    }
    
    // make all threads start
    pthread_mutex_lock(&g_cond_mutex);
    pthread_cond_broadcast(&g_cond);
    pthread_mutex_unlock(&g_cond_mutex);
    
    // wait for all treads
    for (std::vector<struct thread_info>::iterator it = thrs.begin(); it != thrs.end(); ++it)
    {
        if ((error = pthread_join(it->thread_id, NULL)))
        {
            std::cerr << "thread " << it->thread_num << "; pthread_join() err = " << error << std::endl;
        }
        // it needs because output hangs without it
        fflush(stdout);
    }
    
    std::cout << "\n order of threads:\n" << g_order << std::endl;
    
    return 0;
}

