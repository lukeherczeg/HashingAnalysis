#include <iostream>
#include "hashinganalysis.h"
#include <math.h>
#include <string>
using namespace std;

int randomFrom(int min, int max){ // Helper function courtesy of stackoverflow
    int n = max - min + 1;		  // Unbiased random number generation with no library.
    int remainder = RAND_MAX % n;
    int x;
    do{
        x = rand();
    }while (x >= RAND_MAX - remainder);
    return min + x % n;
}

int toInt(string numStr){
	return numStr[0] - '0';
}

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

template <class K, class V> int HashMap<K,V>::midSquareHash(K key){
	key *= key;
	string digits = to_string(key);
	int start = ceil((double)digits.size()/4);
	int desiredLength = ceil((double)digits.size()/2);

	cout << start << endl;
	cout << digits << endl;

	if (digits.size() > 2)
		digits = digits.substr(start, desiredLength);

	cout << digits << endl;

	return toInt(digits);
}

template <class K, class V> int HashMap<K,V>::keyModTableSize(K key){
	return key % capacity;
}

template <class K, class V> int HashMap<K,V>::insertNodeOpenAddressing(K key, V value){
	HashNode<K,V> *temp = new HashNode<K,V>(key, value);
	int hashIndex = keyModTableSize(key);
	int collisions = 0;

	//find next free space
	while(map[hashIndex] != NULL && map[hashIndex]->key != key && map[hashIndex]->key != -1){
		hashIndex++;
		hashIndex %= capacity;
		collisions++;
	}

	if(map[hashIndex] == NULL || map[hashIndex]->key == -1)
		size++;
	map[hashIndex] = temp;
	return collisions;
}

template <class K, class V> V HashMap<K,V>::get(K key){
	;
}

template <class K, class V> bool HashMap<K,V>::isEmpty(){
	return size == 0;
}

template <class K, class V> void HashMap<K,V>::generate(){
	double loadFactor = 0.0;
	int collisions = 0;
	for(int i = 0; i < capacity; i++){
		int k = randomFrom(0, 3 * capacity);
		collisions += insertNodeOpenAddressing(k,i);
		loadFactor = (double)size/capacity;
		/*for(int i = 0; i < capacity ; i++) {
			if(map[i] != NULL && map[i]->key != -1)
				cout << "key = " << map[i]->key << "  value = " << map[i]->value << endl;
		}*/
		cout << collisions << endl << loadFactor << endl << endl;
	}
}


template <class K, class V> void HashMap<K,V>::display(){
	for(int i = 0; i < capacity ; i++) {
		if(map[i] != NULL && map[i]->key != -1)
			cout << "key = " << map[i]->key << "  value = " << map[i]->value << endl;
	}
}


int main(){
	HashMap <int,int> * map = new HashMap<int,int>(100,0);
	map->midSquareHash(476);
	return 0;
;}
