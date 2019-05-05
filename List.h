#ifndef LABORATORYWORK_1_LIST_H
#define LABORATORYWORK_1_LIST_H
#include <iostream>

using namespace std;

template <typename T>
class Node {
public:
    Node(T field) {
        this->field = field;
        this->nextNode = nullptr;
    }

    Node(T field, int weight) {
        this->field = field;
        this->weight = weight;
        this->nextNode = nullptr;
    }


    ~Node(){
        nextNode = nullptr;
    }
    Node *nextNode;
    T field;
    int weight;
};

template <typename T>
class List {
public:

    List() {
        sizeOfList = 0;
        head = nullptr;
    }

    ~List() {
        clear();
    }

    void push_back(T field, int weight);
    void push(T field);
    void push_front(T field);
    void pop_back();
    void pop_front();
    void insert(T field, int index);
    T At(int index);
    void remove(int index);
    int getSize() { return sizeOfList; }
    void clear();
    int find(T field);

    void set(T field, int index);
    bool isEmpty() { return ((sizeOfList == 0) && (head == nullptr)); }
    Node<T>* copy(List<T> copy);
    Node<T> *head;

    template <typename T1> friend ostream& operator<< (ostream &out, List<T1>&);

private:
   // Node<T> *head;
    int sizeOfList = 0;
};


template<typename T>
void List<T>::push_back(T field, int weight)
{
    if (head == nullptr) {
        head = new Node<T>(field, weight);
    }
    else {
        Node<T> *lastItemSearch = this->head;   //search for the last item
        while (lastItemSearch->nextNode != nullptr) {
            lastItemSearch = lastItemSearch->nextNode;
        }
        lastItemSearch->nextNode = new Node<T>(field, weight);
    }

    sizeOfList++;
}

template<typename T>
void List<T>::push(T field)
{
    if (head == nullptr) {
        head = new Node<T>(field);
    }
    else {
        Node<T> *lastItemSearch = this->head;   //search for the last item
        while (lastItemSearch->nextNode != nullptr) {
            lastItemSearch = lastItemSearch->nextNode;
        }
        lastItemSearch->nextNode = new Node<T>(field);
    }

    sizeOfList++;
}

template<typename T>
void List<T>::push_front(T field)
{
    if (head == nullptr) {
        head = new Node<T>(field);
    }
    else {
        Node<T> *firstItem = this->head;
        head = new Node<T>(field);
        head->nextNode = firstItem;
    }

    sizeOfList++;
}

template<typename T>
void List<T>::pop_back()
{
    if (head != nullptr) {
        Node<T> *penultimateItemSearch = this->head;    //search item before last

        if (head->nextNode == nullptr) {
            delete penultimateItemSearch;
            head = nullptr;
        }
        else {
            while (penultimateItemSearch->nextNode->nextNode != nullptr) {
                penultimateItemSearch = penultimateItemSearch->nextNode;
            }

            delete penultimateItemSearch->nextNode;
            penultimateItemSearch->nextNode = nullptr;
        }

        sizeOfList--;
    }
}


template<typename T>
void List<T>::pop_front()
{
    if (head != nullptr) {
        Node<T> *firstElem = this->head;

        if (head->nextNode == nullptr) {
            delete firstElem;
            head = nullptr;
        }
        else {
            head = head->nextNode;
            delete firstElem;
        }

        sizeOfList--;
    }
}


template<typename T>
void List<T>::insert(T field, int index)
{
    if (index < 0) throw invalid_argument("Index must be >= 0");
    if (index > sizeOfList) throw invalid_argument("Index is larger than size of list");

    if (index == 0) push_front(field);
    else {
        Node<T> *newItem = new Node<T>(field);
        Node<T> *beforeNewItem = this->head;    //search for an item after which a new one will be added

        int currentIndex = 0;

        while (currentIndex + 1 != index) {
            beforeNewItem = beforeNewItem->nextNode;
            currentIndex++;
        }

        newItem->nextNode = beforeNewItem->nextNode;
        beforeNewItem->nextNode = newItem;

        sizeOfList++;
    }
}

template<typename T>
T List<T>::At(int index)
{
    if (index < 0) throw out_of_range("Index must be >= 0");
    if (index > sizeOfList) throw out_of_range("Index is larger than size of list");

    Node<T> *itemSearch = this->head;   //search for the desired item by index
    int currentIndex = 0;

    while (currentIndex != index) {
        itemSearch= itemSearch->nextNode;
        currentIndex++;
    }

    return itemSearch->field;
}

template<typename T>
void List<T>::remove(int index)
{
    if (index < 0) throw invalid_argument("Index must be >= 0");
    if (index > sizeOfList) throw invalid_argument("Index is larger than size of list");

    if (index == 0) pop_front();
    else {
        Node<T> *beforeDeleted = this->head; //search for the item after which another one will be deleted
        Node<T> *Deleted;  //item that will be deleted
        int currentIndex = 0;

        while (currentIndex + 1 != index) {
            beforeDeleted = beforeDeleted->nextNode;
            currentIndex++;
        }

        Deleted = beforeDeleted->nextNode;
        beforeDeleted->nextNode = Deleted->nextNode;

        delete Deleted;

        sizeOfList--;
    }
}

template<typename T>
inline void List<T>::clear()
{
    while (head != nullptr) {
        Node<T> *itemSearch = head;
        head = head->nextNode;
        delete itemSearch;
    }

    sizeOfList = 0;
}

template<typename T>
void List<T>::set(T field, int index)
{
    if (index < 0) throw invalid_argument("Index must be >= 0");
    if (index > sizeOfList) throw invalid_argument("Index is larger than size of list");

    Node<T> *itemSearch = this->head;
    int currentIndex = 0;

    while (currentIndex != index) {
        itemSearch = itemSearch->nextNode;
        currentIndex++;
    }

    itemSearch->field = field;
}

template<class T> ostream &operator<<(ostream &out, List<T>& list) {
    Node<T> *itemSearch = list.head;
    int currentIndex = 0;
    cout << "{";
    while (currentIndex < list.getSize()) {
//        cout << "\n"<< currentIndex << " element is {" << itemSearch->field << "}";
        cout << " " << itemSearch->field << "+" << itemSearch->weight;
        currentIndex++;
        itemSearch= itemSearch->nextNode;
    }
    cout << "}" << endl;
    return out;
}

template<typename T>
int List<T>::find(T field) {
    Node<T> *itemSearch = head;
    while (itemSearch != nullptr) {
        if (itemSearch->field == field) return 1;
        itemSearch = itemSearch->nextNode;
    }
    return 0;

}

#endif //LABORATORYWORK_1_LIST_H
