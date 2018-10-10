#include <iostream>
using namespace std;

template<class T>
class Node {
public:
	T data;
	Node<T> * next;
};

template <class T>
class LinkedList{
private:
	Node<T> * head;
	Node<T> * tail;
public:
	void insertEnd(T value);
	void insert(int index, T value);
	void edit(int index, T value);
	void remove(int index);
	void print();
};

template <class T> void LinkedList<T>::print(){
	Node <T> * temp = head;
	while(temp != NULL){
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}




int main(){
	return 0;
}
