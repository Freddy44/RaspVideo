/*
 * VideoThread.h
 *
 *      Author: Frédéric Gicquel
 *
 *  Classe qui
 *  @return:
 */
#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //fonction sleep...#include <iostream>

#include <iostream>
using namespace std;

#define NUM_THREADS     1
struct thread_data
{
    int  thread_id;
    char *message;
};

class VideoThread
{



public:
    VideoThread();

    virtual ~VideoThread();

    //Process Camera
    bool isOpen();
    bool isClose();
    void* startThread(void* arg);
    void* stopThread(void* arg);
    //méthodes startThread, stopThread, wait,
    //void *PrintHello(void *threadarg);
    void* wait2(void *);

protected:


private:
    //attributs
    bool m_stateCamera;

    char nbrThread;
    pthread_t threads[NUM_THREADS];
    struct thread_data td[NUM_THREADS];

    pthread_mutex_t m_mutex;

    //methodes

    void * MaFonctionPourPThread(void * );
    static void* wait(void *);

};

#endif // VIDEOTHREAD_H
