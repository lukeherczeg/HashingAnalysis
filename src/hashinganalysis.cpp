#include <iostream>
#include "hashinganalysis.h"
#include <math.h>
#include <string>
using namespace std;

int randomFrom(int min, int max){ // Helper function courtesy of stackoverflow
    int n = max - min + 1;		  // Unbiased random number generation with no library.
    int remainder = RAND_MAX % n;
    int x;
    do{ x = rand(); }
    while (x >= RAND_MAX - remainder);
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

template <class K, class V> HashMap<K,V>::HashMap(int tableSize, int currSize){
	this->tableSize = tableSize;
	this->currSize = currSize;
	map = new HashNode<K,V>*[tableSize];

	for(int i = 0 ; i < tableSize ; i++)
		map[i] = NULL;
}

template <class K, class V> int HashMap<K,V>::midSquareHash(K key){
	key *= key;
	string digits = to_string(key);

	if (digits.size() > 2)
		digits = digits.substr(1, digits.size()-2);

	return toInt(digits);
}

template <class K, class V> int HashMap<K,V>::keyModTableSize(K key){
	return key % tableSize;
}

template <class K, class V> int HashMap<K,V>::insertNodeOA(K key, V value, bool midSquare){
	HashNode<K,V> *temp = new HashNode<K,V>(key, value);
	int hashIndex = 0;
	if(midSquare)
		hashIndex = midSquareHash(key);
	else
		hashIndex = keyModTableSize(key);
	int collisions = 0;
	//find next free space
	while(map[hashIndex] != NULL && map[hashIndex]->key != key && map[hashIndex]->key != -1){
		hashIndex++;
		hashIndex %= tableSize;
		collisions++;
	}

	if(map[hashIndex] == NULL || map[hashIndex]->key == -1)
		currSize++;
	map[hashIndex] = temp;
	return collisions;
}

template <class K, class V> V HashMap<K,V>::get(K key){
	;
}

template <class K, class V> void HashMap<K,V>::setTableSize(int tableSize){
	this->tableSize = tableSize;
	for(int i = 0 ; i < tableSize ; i++)
		map[i] = NULL;
}

template <class K, class V> bool HashMap<K,V>::isEmpty(){
	return currSize == 0;
}

template <class K, class V> void HashMap<K,V>::clear(){
	int count = 0;
	while(!isEmpty()){
		map[count] = NULL;
		delete map[count];
		currSize--;
		count++;
	}
}

template <class K, class V> void HashMap<K,V>::generateOA(bool midSquare){
	double loadFactor = 0.0;
	int collisions = 0;
	int insertions = 0;
	while(currSize < tableSize){
		int k = randomFrom(0, 3 * tableSize);
		collisions += insertNodeOA(k,insertions,midSquare);
		loadFactor = (double)currSize/(double)tableSize;
		cout << "Total Collisions: " << collisions << " " << endl << "Load Factor: " << loadFactor << " " << endl << "Current Size: " << currSize << "\n\n";
		insertions++;
	}
	//cout << "Insertions: " << insertions-1 << "\n\n";
}

template <class K, class V> void HashMap<K,V>::display(){
	for(int i = 0; i < tableSize ; i++) {
		if(map[i] != NULL && map[i]->key != -1)
			cout << "key = " << map[i]->key << "  value = " << map[i]->value << "\n";
		else
			cout << "Empty" << endl;
	}
	cout << endl;
}

template <class K, class V> void HashMap<K,V>::MSOA(){ // MidSquare Hashing with Open Addressing
	bool midSquare = true;
	this->generateOA(midSquare); // MidSquare hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generateOA(midSquare); // MidSquare hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generateOA(midSquare); // MidSquare hashing test 3
	this->display();
	this->clear();
}

template <class K, class V> void HashMap<K,V>::MTOA(){ // Mod TableSize Hashing with Open Addressing
	bool midSquare = true;
	this->setTableSize(15);
	this->generateOA(!midSquare); // Mod TableSize hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generateOA(!midSquare); // Mod TableSize hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generateOA(!midSquare); // Mod TableSize hashing test 3
	this->display();
	this->clear();
}

template <class K, class V> void HashMap<K,V>::MSSC(){}

template <class K, class V> void HashMap<K,V>::MTSC(){}

int main(){
	bool midSquare = true;
	HashMap <int,int> * map1 = new HashMap<int,int>(15,0);


	// MidSquare Hashing with Open Addressing
	map1->MSOA();


	// Mod TableSize Hashing with Open Addressing
	map1->MTOA();

	// MidSquare Hashing with Separate Chaining


	// Mod TableSize Hashing with Separate Chaining


	return 0;
;}
