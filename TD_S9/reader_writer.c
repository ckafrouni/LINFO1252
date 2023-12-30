#include <pthread.h>
#include <semaphore.h>

sem_t sread;  // accès à la db
sem_t swrite; // accès à readcount

pthread_mutex_t mread;
int readcount = 0; // nombre de readers

pthread_mutex_t mwrite;
int writecount = 0; // nombre de writers

void *reader(void *)
{
    while (1)
    {
        if (writecount != 0)
            sem_wait(&sread);

        pthread_mutex_lock(&mread);
        //! Critical section
        readcount++;
        if (readcount == 1)
            sem_wait(&db);
        pthread_mutex_unlock(&mread);

        read_database();

        pthread_mutex_lock(&mread);
        //! Critical section
        readcount--;
        if (readcount == 0)
            sem_post(&);
        pthread_mutex_unlock(&mread);

        process_data();
    }
}

void *writer(void *)
{
    while (1)
    {
        prepare_data();

        pthread_mutex_lock(&mwrite);
        writecount++;
        if (writer == 1) // First writer blocs readers
            sem_wait(&sread);
        pthread_mutex_unlock(&mwrite);

        sem_wait(&swrite);
        //! Critical section
        write_database();
        sem_post(&swrite);

        pthread_mutex_lock(&mwrite);
        writecount--;
        if (writecount == 0)
        {
            sem_post(&sread);
        }
        pthread_mutex_unlock(&mwrite);
    }
}

int main()
{
    sem_init(&sread, 0, 1);
    sem_init(&swrite, 0, 1);

    pthread_mutex_init(&mread, NULL);
    pthread_mutex_init(&mwrite, NULL);
}