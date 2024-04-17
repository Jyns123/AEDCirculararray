#include <iostream>
#include <stdexcept>

using namespace std;

class Queue {
private:
  int* array;
  int capacity;
  int frontindex;
  int rear;

public:
  Queue(int capacity) {
    this->capacity = capacity;
    this->array = new int[capacity];
    this->frontindex = 0;
    this->rear = 0;
  }

  ~Queue() {
    delete[] array;
  }

  void enqueue(int data) {
    if (isFull()) {
      throw runtime_error("Error: La cola está llena");
    }

    array[rear] = data;
    rear = (rear + 1) % capacity;
  }

  int dequeue() {
    if (isEmpty()) {
      throw runtime_error("Error: La cola está vacía");
    }

    int frontElement = array[frontindex];
    frontindex = (frontindex + 1) % capacity;
    return frontElement;
  }

  int front() {
    if (isEmpty()) {
      throw runtime_error("Error: La cola está vacía");
    }

    return array[frontindex];
  }

  int back() {
    if (isEmpty()) {
      throw runtime_error("Error: La cola está vacía");
    }

    int rearIndex = (rear - 1 + capacity) % capacity;
    return array[rearIndex];
  }

  void insert(int data, int position) {
    if (position < 0 || position > size()) {
      throw runtime_error("Error: Posición inválida");
    }

    if (isFull()) {
      throw runtime_error("Error: La cola está llena");
    }

    for (int i = size() - 1; i >= position; i--) {
      array[(i + 1) % capacity] = array[i];
    }

    array[position] = data;

    rear = (rear + 1) % capacity;
  }

  bool isEmpty() const {
    return frontindex == rear;
  }

  bool isFull() const {
    return (rear + 1) % capacity == frontindex;
  }

  int size() const {
    if (frontindex == rear) {
      return 0;
    } else if (rear > frontindex) {
      return rear - frontindex;
    } else {
      return capacity - frontindex + rear;
    }
  }

  void clear() {
    frontindex = 0;
    rear = 0;
  }

  void display() {
    if (isEmpty()) {
      cout << "La cola está vacía" << endl;
      return;
    }

    cout << "Elementos de la cola: ";
    for (int i = frontindex; i != rear; i = (i + 1) % capacity) {
      cout << array[i] << " ";
    }
    cout << endl;
  }
};

int main() {
  Queue queue(5);

  queue.enqueue(10);
  queue.enqueue(20);
  queue.enqueue(30);

  try {
    cout << "Elemento al frente: " << queue.front() << endl;
    cout << "Elemento al final: " << queue.back() << endl;
  } catch (const runtime_error& e) {
    cerr << "Error: " << e.what() << endl;
  }

  return 0;
}