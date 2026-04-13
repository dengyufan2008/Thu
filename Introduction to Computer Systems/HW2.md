# Homework Set 1

By Deng Yufan.

## Prob 1: Regular Expressions and Shell Programming

Tsinghua has a very complicated email domain naming convention. There are two campuswide email domains:

1. Faculty and regular staff members use the ``@mail.tsinghua.edu.cn`` domain, and it can also be written as ``@tsinghua.edu.cn``.

2. Students use the ``@mails.tsinghua.edu.cn`` domain.

Also, departments and large labs have their own email servers. For example, our institute has the ``@iiis.tsinghua.edu.cn`` domain.
Tsinghua alumni can apply for email addresses in the ``@mail.tsinghua.org.cn`` domain.

Consider that you have a text file containing email addresses with both Tsinghua email addresses and non-Tsinghua addresses, one address per line. Please complete the following tasks:

1. Write a regular expression that matches:
a. All student email addresses ONLY.
b. All faculty and regular staff member email addresses ONLY.
c. All campus-wide email addresses.

> a. ``[^@]+@mails\.tsinghua\.edu\.cn``.
> b. ``[^@]+@mail\.tsinghua\.edu\.cn|[^@]+@tsinghua\.edu\.cn``.
> c. ``[^@]+@([^.]+\.)?tsinghua\.edu\.cn``.

2. Write a regular expression that matches all Tsinghua email addresses, including alumni addresses.

> ``[^@]+@([^.]+\.)?tsinghua\.edu\.cn|[^@]+@mail\.tsinghua\.org\.cn``.

3. Write a regular expression that extracts all department server names, not including campus-wide servers such as mail, mails, or tsinghua. For example, in the email address ``xuw@iiis.tsinghua.edu.cn``, the department server name is iiis. You should look up regular expression documentation to learn how to extract capturing groups.

> ``@(?!mails\.|mail\.|tsinghua\.)([^.]+)\.``. Where ``([^.]+)`` is the capturing group.

4. Assume that you store the matching server names from question 3. in a text file called ``departments.txt``, one name per line. Write a single-line bash command that outputs the distinct department server names in case-insensitive alphabetical order, printing all names in lowercase, one per line. The command should also output the total number of such distinct department server names on a separate line after the list.

> ``tr '[:upper:]' '[:lower:]' < departments.txt | sort -u | awk '{print} END{print NR}'``.

## Prob 2: Basic Synchronization

Threads A and B both share references to the same already initialized doubly linked ``List`` object, which currently contains multiple nodes (more than 2 nodes). Each thread calls the ``removeTail()`` method once. Consider the three scenarios (see the comments in the code) where thread A runs initially and then switches to thread B, which completes the entire ``removeTail()`` method before switching back to thread A. Which of these scenarios would lead to incorrect behavior of ``removeTail()``? Incorrect behavior means that the final ``List`` object has missing deletions (a node that should have been removed is not removed), incorrect pointers, a broken list structure, double free, or any other invalid memory behavior.

```c++
class Node {
  Object entry;
  Node next;
  Node prev;
  Node(Object entry) {
    this.entry = entry;
  }
}

class List {
  Node head = new Node(null);
  Node tail = head;
  /*
  // initialization operations
  */
  void removeTail() {
    Node oldTail = tail;  // scenario 1: A switches to B after this line
    tail = tail.prev;     // scenario 2: A switches to B after this line
    tail.next = null;     // scenario 3: A switches to B after this line
    delete oldTail;
  }
}
```

> Scenario 1: ``oldTail`` defined in ``A::removeTail`` will become a wild pointer to a released space, so ``deletee oldTail`` will be undefined behavior, or say double free. And the second last ``Node`` have not been deleted.
>
> Scenario 2: Correct.
>
> Scenario 3: Correct.

## Prob 3: Monitors

Consider the following code that implements a synchronized unbounded queue using monitors that we discussed in lecture:

```c
Lock lock;
Condition dataready;
Queue queue;

AddToQueue(item) {
  lock.Acquire();       // Get Lock
  queue.enqueue(item);  // Add item
  dataready.signal();   // Signal any waiters
  lock.Release();       // Release Lock
}

RemoveFromQueue() {
  lock.Acquire();  // Get Lock
  while (queue.isEmpty()) {
    dataready.wait(&lock);  // If nothing, sleep
  }
  item = queue.dequeue();  // Get next item
  lock.Release();          // Release Lock
  return(item);
}
```

1. Assume that we have multiple producers running ``AddToQueue()`` and multiple consumers running ``RemoveFromQueue()``. Do you need to make any changes to the code? If yes, specify the changes in the above code by indicating the line you need to modify, the line #'s between which you need to add new code, or the line # you need to delete. If not, use no more than two sentences to explain why.

> Dont need to make changes. The ``lock`` ensure that only one thread can access the queue, and ``while - wait`` ensure that always have element to dequeue.

2. Change the code to implement a bounded queue, i.e., make sure that the producer cannot write when the queue is full. Add your changes in the empty space of the code below.

> ```c
> Lock lock;
> Condition dataready;
> Condition datafull;
> Queue queue;
> 
> AddToQueue(item) {
>   lock.Acquire();       // Get Lock
>   while (queue.isFull()) {
>     datafull.wait(&lock);  // If full, sleep
>   }
>   queue.enqueue(item);  // Add item
>   dataready.signal();   // Signal any consumer
>   lock.Release();       // Release Lock
> }
> 
> RemoveFromQueue() {
>   lock.Acquire();  // Get Lock
>   while (queue.isEmpty()) {
>     dataready.wait(&lock);  // If nothing, sleep
>   }
>   item = queue.dequeue();  // Get next item
>   datafull.signal();       // Signal any producer
>   lock.Release();          // Release Lock
>   return(item);
> }
> ```

3. Implement a new function, ``ReadFromQueue()``, which uses the function ``item = queue.read()`` to read an item from the queue without removing it.

> ```c
> ReadFromQueue() {
>   lock.Acquire();  // Get Lock
>   while (queue.isEmpty()) {
>     dataready.wait(&lock);  // If nothing, sleep
>   }
>   item = queue.read();  // Get front item
>   lock.Release();       // Release Lock
>   return(item);
> }
> ```

## Prob 4: New Locking Primitives Using Semaphores

As we have discussed in class, a *Reentrant Lock* is owned by the thread last successfully locking, but not yet unlocking it. A thread invoking ``RLock()`` will return, successfully acquiring the lock, when the lock is not owned by another thread. The ``RLock()`` method will also return immediately if the current thread already owns the lock (the unlock only need to happen once, no matter how many times a thread locks it). Otherwise the thread is put on sleep until the lock holder calls ``RUnLock()``.

Please use the Semaphore ``P()`` and ``V()`` primitive to implement an reentrant lock. You can obtain the thread id by calling the function ``getMyTID()``. E.g. ``int cur_id = getMyTID();``.

> ```c
> Semaphore sem = 1;  // Only one thread can hold the lock
> int owner_id = -1;  // Different from any thread id
> 
> void RLock() {
>   int cur_id = getMyTID();
>   if (cur_id != owner_id) {  // Need to get the lock
>     sem.P();                 // Wait until the owner release the lock
>     owner_id = cur_id;       // Become owner
>   }
> }
> 
> void RUnLock() {
>   int cur_id = getMyTID();
>   if (cur_id == owner_id) {  // Able to release the lock
>     owner_id = -1;           // No owner
>     sem.V();                 // Welcome other thread to get the lock
>   }
> }
> ```
>
> This code seems wrong since ``owner_id`` is not protected by a lock, but easy to prove that this won't affect the result in ``if`` condition; and the value in ``owner_id``.

## Prob 5: Modeling the Real World

A machine learning inference server has one GPU worker and a waiting queue with $N$ slots for pending requests. The GPU worker goes to sleep if there are no requests to process. If a client request arrives and the GPU is currently busy while all $N$ waiting slots are occupied, the request is dropped immediately. Otherwise, the request joins the waiting queue and waits. If the GPU worker is asleep when a request arrives, the request wakes it up. Whenever the GPU worker becomes available, it selects the next request from the waiting queue with the shortest estimated processing time and processes it.

1. The following code segment models the GPU worker and each client request as independent, concurrent threads. Fill in the following blanks to ensure that the GPU worker and the client requests are synchronized and deadlock-free. Assume each semaphore has ``P()`` and ``V()`` functions available as ``semaphore.P()`` and ``semaphore.V()``.

```c
Semaphore gpuReady = 0;
Semaphore accessQueue = 1;
Semaphore requestReady = 0;
int numberOfFreeQueueSlots = N;

void GPUWorker() {
  while (true) {
    ___________________________
    ___________________________
    numberOfFreeQueueSlots += 1;
    ___________________________
    processRequest();  // Process one request on the GPU
    ___________________________
  }
}

void ClientRequest() {
  ___________________________
  if (numberOfFreeQueueSlots > 0) {
    numberOfFreeQueueSlots -= 1;
    ___________________________
    ___________________________
    ___________________________
    waitForCompletion();  // Client waits until its request is processed
  } else {
    ___________________________
    dropRequest();  // No available queue slot
  }
}
```

> ```c
> Semaphore gpuReady = 0;
> Semaphore accessQueue = 1;
> Semaphore requestReady = 0;
> int numberOfFreeQueueSlots = N;
> 
> void GPUWorker() {
>   while (true) {
>     requestReady().P();
>     accessQueue().P();
>     numberOfFreeQueueSlots += 1;
>     accessQueue().V();
>     processRequest();  // Process one request on the GPU
>     gpuReady.V();
>   }
> }
> 
> void ClientRequest() {
>   accessQueue.P();
>   if (numberOfFreeQueueSlots > 0) {
>     numberOfFreeQueueSlots -= 1;
>     requestReady.V();
>     accessQueue.V();
>     gpuReady.P();
>     waitForCompletion();  // Client waits until its request is processed
>   } else {
>     accessQueue.V();
>     dropRequest();  // No available queue slot
>   }
> }
> ```

2. Which of the semaphores are used for mutex, and which are used for scheduling constraints, respectively?

> ``accessQueue`` used for mutex, ``requestReady`` and ``gpuReady`` used for scheduling constraints.

3. Describe a scenario where a request can get starved, i.e., remain in the waiting queue forever without being processed. Is there a deadlock when this happens? Can starvation still happen if the GPU worker randomly picks one request from the waiting queue? Can you propose a way to guarantee that no starvation happens?

> A request can get starved: Infinite quicker requests get in the queue one-by-one, then the slow request will never be picked.
>
> Deadlock: No, since the GPU keeps running requests.
>
> Randomly pick: If a request has very bad luck, it will never be picked after infinite time (though the probability of the event is approch zero).
>
> Strategy: Pick the oldest request.
