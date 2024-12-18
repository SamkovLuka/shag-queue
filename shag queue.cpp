#include <iostream>
using namespace std;







struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};




Queue* createQueue(unsigned capacity) {
    Queue* queue = new Queue();
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = new int[capacity];
    return queue;
}





bool isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}





bool isEmpty(Queue* queue) {
    return (queue->size == 0);
}





void enqueue(Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}





int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}





int front(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    return queue->array[queue->front];
}





struct Passenger {
    int arrivalTime;
};





struct Minibus {
    int arrivalTime;
    int freeSeats;
};





struct PrintJob {
    int priority;
    int pages;
    char username[20];
};





void copyString(char* dest, const char* src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}






int main() {
    const int MAX_PASSENGERS = 10;
    const int SIMULATION_TIME = 100;
    int currentTime = 0;

    Queue* passengerQueue = createQueue(MAX_PASSENGERS);
    Queue* minibusQueue = createQueue(5);





    srand(123);

    while (currentTime < SIMULATION_TIME) {
        int passengerArrival = rand() % 10;
        int minibusArrival = rand() % 30;


        if (passengerArrival < 5) {
            if (!isFull(passengerQueue)) {
                enqueue(passengerQueue, currentTime);
                cout << "Passenger arrived at: " << currentTime << " seconds\n";
            }
            else {
                cout << "Passenger left, no space at the stop\n";
            }
        }






        if (minibusArrival < 10) {
            if (!isFull(minibusQueue)) {
                enqueue(minibusQueue, rand() % 10 + 5);
                cout << "Minibus arrived at: " << currentTime << " seconds\n";
            }


            int freeSeats = dequeue(minibusQueue);
            while (!isEmpty(passengerQueue) && freeSeats > 0) {
                dequeue(passengerQueue);
                freeSeats--;
            }
        }

        currentTime++;
    }

    cout << "\n--- End of Bus Stop Simulation ---\n";



    const int MAX_PRINT_JOBS = 5;
    Queue* printQueue = createQueue(MAX_PRINT_JOBS);

    PrintJob jobs[MAX_PRINT_JOBS];
    int jobCount = 0;





    for (int i = 0; i < 5; ++i) {
        PrintJob job;
        job.priority = rand() % 5;
        job.pages = rand() % 50 + 1;
        copyString(job.username, "User");
        job.username[4] = 'A' + i;
        job.username[5] = '\0';

        jobs[jobCount++] = job;
        enqueue(printQueue, job.priority);
        cout << "Added print job: " << job.username
            << ", Priority=" << job.priority
            << ", Pages=" << job.pages << "\n";
    }





    cout << "\nProcessing print queue:\n";
    while (!isEmpty(printQueue)) {
        int priority = dequeue(printQueue);




        for (int i = 0; i < jobCount; ++i) {
            if (jobs[i].priority == priority) {
                cout << "Printing job: " << jobs[i].username
                    << ", Pages=" << jobs[i].pages
                    << ", Priority=" << jobs[i].priority << "\n";
                break;
            }
        }
    }

    cout << "\n--- End of Print Queue Simulation ---\n";
}
