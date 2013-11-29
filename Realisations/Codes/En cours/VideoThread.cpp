/*
 * VideoThread.cpp
 *
 *      Author: Frédéric Gicquel
 *
 */

#include "VideoThread.h"

/* Constructeur */
VideoThread::VideoThread()
{
    /* Initialisation du thread caméra */
    m_stateCamera = false;

    /* Contrôle dans un terminal :
     *
     * \E[3x;1m ... \E[m : couleur d'affichage (30 < x < 37) => ici bleu
     *
     */
    cout << "\E[34;1mVideoThread::Constructeur(0) :\E[m\n";
}

/* Destructeur */
VideoThread::~VideoThread()
{
    /* Contrôle dans un terminal */
    cout << "\E[34;1mVideoThread::Desstructeur(0) :\E[m\n";
}

/*
* Méthode isOpen()
*
* @param:
* @return:
*/
bool VideoThread::isOpen()
{
    /* Le thread passe à l'état vrai */
    m_stateCamera = true;

    /* Contrôle dans un terminal */
    cout << "\E[34;1mVideoThread::isOpen(1) :\E[m\n";
    return m_stateCamera;
}

/*
* Méthode
*
* @param:
* @return:
*/
bool VideoThread::isClose()
{
    m_stateCamera = false;

    /* Contrôle dans un terminal */
    cout << "\E[34;1mVideoThread::isClose() :\E[m\n";
    return m_stateCamera;
}

/*
* Méthode
*
* @param:
* @return:
*/
void* VideoThread::startThread(void* arg)
{
    /* Contrôle dans un terminal */
    cout<<"Demarrage des threads"<<endl;
    int th1 = 0;
    int i, j1;
    for( i=0; i < NUM_THREADS; i++ )
    {
        /* Contrôle dans un terminal */
        cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        //td[i].message = "This is message";

        th1 = pthread_create(&threads[i], NULL,VideoThread::wait, (void*)this);//=> ok
        //th1 = pthread_create(&threads[i], NULL,PrintHello, (void *)&td[i]);
        if(th1 != 0)
        {
            /* Contrôle dans un terminal */
            cout << "Error:unable to create thread," << th1 << endl;
            exit(1);
        }

        printf ("thread %s \n", (char*)arg);

        if(th1 == 0) // th1 -> serveur normal
        {
            j1 = pthread_join(threads[i], NULL);

            /* Contrôle dans un terminal */
            printf ("thread %s pthread_join in first\n", (char*)arg);

            if(j1 == 0)
            {
                /* Contrôle dans un terminal */
                cout<<"Reception donnees du serveur normal en cours"<<endl;
            }
            nbrThread++;
        }
        /* Contrôle dans un terminal */
        printf ("thread %s pthread_join in wait\n", (char*)arg);

    }
    pthread_exit(NULL);
}

/*
* Méthode
*
* @param:
* @return:
*/
void* VideoThread::stopThread(void* arg)
{

    int i;

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    /* Contrôle dans un terminal */
    printf ("thread %s stopThread\n", (char*)arg);
    for (i = 0 ; i < 5 ; i++)
    {
        /* Contrôle dans un terminal */
        printf ("Thread %s: %d\n", (char*)arg, i);
        sleep (1);
        pthread_testcancel ();
    }

    pthread_exit(NULL);
}

/*
* Méthode
*
* @param:
* @return:
*/
void* VideoThread::wait(void *arg)
{
    /* Contrôle dans un terminal */
    cout<<"fonction wait"<<endl;
    int i;
    VideoThread * tid=(VideoThread*)arg;
    for (i=0; i<NUM_THREADS; i++)
    {
        sleep(1);

        /* Contrôle dans un terminal */
        cout << "Sleeping in thread " << endl;
        cout << "Thread with id : " << tid << "  ...wait " << endl;
        //cout << "Thread with id : " << td[i].thread_id << "  ...exiting " << endl;
        printf ("thread %s \n", (char*)arg);
    }

    pthread_exit(NULL);
}

/*
* Méthode
*
* @param:
* @return:
*/
void* VideoThread::wait2(void *arg)
{
    /* Contrôle dans un terminal */
    printf ("thread %s \n", (char*)arg);
    cout<<"fonction wait deuxieme"<<endl;

    sleep(1);

    /* Contrôle dans un terminal */
    printf ("thread %s \n", (char*)arg);
    cout << "Sleeping in thread 1" << endl;

    sleep(1);

    /* Contrôle dans un terminal */
    printf ("thread %s \n", (char*)arg);
    cout << "Sleeping in thread 2" << endl;
    //cout << "Thread with id : " << tid << "  ...wait " << endl;
    //cout << "Thread with id : " << td[i].thread_id << "  ...exiting " << endl;
    pthread_exit(NULL);
}

/*
* Méthode
*
* @param:
* @return:
*/
/*
void *PrintHello(void *threadarg)
{
   struct thread_data *my_data;

   my_data = (struct thread_data *) threadarg;*/

/* Contrôle dans un terminal */
/*cout << "Thread ID : " << my_data->thread_id ;
cout << " Message : " << my_data->message << endl;

pthread_exit(NULL);
}*/
