#include <iostream>
#include "hashinganalysis.h"
using namespace std;

template <class T> void LinkedList<T>::print(){
	Node <T> * temp = head;
	while(temp != NULL){
		cout << temp->data << " -> ";
		temp = temp->next;
	}
	cout << "NULL\n";
}

template <class K, class V> HashNode<K,V>::HashNode(K key, V value){
	this->value = value;
	this->key = key;
}

template <class K, class V> HashMap<K,V>::HashMap(int capacity, int size){
	this->capacity = capacity;
	this->size = size;
	map = new HashNode<K,V>*[capacity];

	for(int i=0 ; i < capacity ; i++)
		map[i] = NULL;
}

template <class K, class V> int HashMap<K,V>::hashCode(K key){
	return 0;
}

template <class K, class V> void HashMap<K,V>::insertNode(K key, V value){
	;
}

template <class K, class V> V HashMap<K,V>::get(K key){
	;
}

template <class K, class V> int HashMap<K,V>::mapSize(){
	return size;
}

template <class K, class V> bool HashMap<K,V>::isEmpty(){
	return size == 0;
}

template <class K, class V> void HashMap<K,V>::display(){
	for(int i = 0; i < capacity ; i++) {
		if(map[i] != NULL && map[i]->key != -1)
			cout << "key = " << map[i]->key << "  value = " << map[i]->value << endl;
	}
}


int main(){
	return 0;
}
