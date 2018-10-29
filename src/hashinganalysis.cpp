#include <iostream>
#include <list>
#include <math.h>
#include <string>
using namespace std;
#include "hashinganalysis.h"

int randomFrom(int min, int max){ // Helper function courtesy of StackOverFlow;
    int n = max - min + 1;		  // Unbiased random number generation with no library.
    int remainder = RAND_MAX % n;
    int x;
    do{ x = rand(); }
    while (x >= RAND_MAX - remainder);
    return min + x % n;
}

int keyModTableSize(int key, int tableSize){ // Key Mod Table Size hashing algorithm
	return key % tableSize;
}

int midSquareHash(int key, int tableSize){ // Mid Square hashing algorithm
	key *= key;
	string digits = to_string(key);

	if (digits.size() > 2)
		digits = digits.substr(1, digits.size()-2);

	return stoi(digits) % tableSize;
}

template <class K, class V> HashNodeOA<K,V>::HashNodeOA(K key, V value){
	this->value = value;
	this->key = key;
}

template <class K, class V> HashMapOA<K,V>::HashMapOA(int tableSize){
	this->tableSize = tableSize;
	this->currSize = 0;
	map = new HashNodeOA<K,V>*[tableSize];

	for(int i = 0 ; i < tableSize ; i++){
		map[i] = NULL;
	}
}

template <class K, class V> int HashMapOA<K,V>::insertNode(K key, V value, bool midSquare){
	HashNodeOA<K,V> *temp = new HashNodeOA<K,V>(key, value);
	int hashIndex = 0, collisions = 0;
	if(midSquare)
		hashIndex = midSquareHash(key, tableSize);
	else
		hashIndex = keyModTableSize(key, tableSize);

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

template <class K, class V> void HashMapOA<K,V>::setTableSize(int tableSize){
	this->tableSize = tableSize;
	for(int i = 0 ; i < tableSize ; i++)
		map[i] = NULL;
}

template <class K, class V> bool HashMapOA<K,V>::isEmpty(){
	return currSize == 0;
}

template <class K, class V> void HashMapOA<K,V>::clear(){
	int count = 0;
	while(!isEmpty()){
		map[count] = NULL;
		delete map[count];
		currSize--;
		count++;
	}
}

template <class K, class V> void HashMapOA<K,V>::generate(bool midSquare){
	double loadFactor = 0.0;
	int collisions = 0;
	int insertions = 0;
	while(currSize < tableSize){
		int k = randomFrom(0, 3 * tableSize);
		collisions += insertNode(k,insertions,midSquare);
		loadFactor = (double)currSize/(double)tableSize;
		cout << "Total Collisions: " << collisions << " " << endl << "Load Factor: " << loadFactor << " " << endl << "Current Size: " << currSize << "\n\n";
		insertions++;
	}
	//cout << "Insertions: " << insertions-1 << "\n\n";
}

template <class K, class V> void HashMapOA<K,V>::display(){
	for(int i = 0; i < tableSize ; i++) {
		if(map[i] != NULL && map[i]->key != -1)
			cout << "key = " << map[i]->key << "  value = " << map[i]->value << "\n";
		else
			cout << "Empty" << endl;
	}
	cout << endl;
}

template <class K, class V> void HashMapOA<K,V>::MS(){ // MidSquare Hashing with Open Addressing
	bool midSquare = true;
	this->setTableSize(15);
	this->generate(midSquare); // MidSquare hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generate(midSquare); // MidSquare hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generate(midSquare); // MidSquare hashing test 3
	this->display();
	this->clear();
}

template <class K, class V> void HashMapOA<K,V>::MT(){ // Mod TableSize Hashing with Open Addressing
	bool midSquare = true;
	this->setTableSize(15);
	this->generate(!midSquare); // Mod TableSize hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generate(!midSquare); // Mod TableSize hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generate(!midSquare); // Mod TableSize hashing test 3
	this->display();
	this->clear();
}

HashMapSC::HashMapSC(int tableSize){
	this->tableSize = tableSize;
	this->currSize = 0;
	map = new list<int>[tableSize];
}

int HashMapSC::insertNode(int key, bool midSquare){
	int hashIndex = 0, collisions = 0;
	if(midSquare)
		hashIndex = midSquareHash(key, tableSize);
	else
		hashIndex = keyModTableSize(key, tableSize);

	collisions = map[hashIndex].size();
	if(collisions == 0)
		currSize++;
	map[hashIndex].push_back(key);
	return collisions;
}

void HashMapSC::setTableSize(int tableSize){
	this->tableSize = tableSize;
	delete map;
	map = new list<int>[tableSize];
}

void HashMapSC::clear(){
	bool popped = false;
	for(int i = 0; i < tableSize; i++){
		while(!map[i].empty()){
			map[i].pop_front();
			popped = true;
		}
		if(popped)
			currSize--;
		popped = false;
	}
}

void HashMapSC::generate(bool midSquare){
	double loadFactor = 0.0;
	int collisions = 0;
	int insertions = 0;
	while(currSize < tableSize/1.35){ // Arbitrary value to stop the Mid Square Chaining from infinite loops.
		int k = randomFrom(0, 3 * tableSize);
		collisions += insertNode(k,midSquare);
		loadFactor = (double)currSize/(double)tableSize;
		cout << "Total Collisions: " << collisions << " " << endl << "Load Factor: " << loadFactor << " " << endl << "Current Size: " << currSize << "\n\n";
		insertions++;
	}
}

void HashMapSC::display(){
	for (int i = 0; i < tableSize; i++) {
		cout << i+1;
		for (auto x : map[i])
		  cout << " --> " << x;
		cout << endl;
	}
	cout << endl;
}

void HashMapSC::MS(){ // MidSquare Hashing with Separate Chaining
	bool midSquare = true;
	this->setTableSize(15);
	this->generate(midSquare); // MidSquare hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generate(midSquare); // MidSquare hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generate(midSquare); // MidSquare hashing test 3
	this->display();
	this->clear();
}

void HashMapSC::MT(){ // Mod TableSize Hashing with Separate Chaining
	bool midSquare = true;
	this->setTableSize(15);
	this->generate(!midSquare); // Mod TableSize hashing test 1
	this->display();
	this->clear();

	this->setTableSize(20);
	this->generate(!midSquare); // Mod TableSize hashing test 2
	this->display();
	this->clear();

	this->setTableSize(25);
	this->generate(!midSquare); // Mod TableSize hashing test 3
	this->display();
	this->clear();
}

int main(){
	HashMapOA <int,int> * mapOA = new HashMapOA<int,int>(10); // 2 Different Hash tables for the different experiments
	HashMapSC * mapSC = new HashMapSC(10);

	mapOA->MS(); // MidSquare Hashing with Open Addressing
	mapOA->MT(); // Mod TableSize Hashing with Open Addressing
	mapSC->MS(); // MidSquare Hashing with Separate Chaining
	mapSC->MT(); // Mod TableSize Hashing with Separate Chaining

	return 0;
;}
