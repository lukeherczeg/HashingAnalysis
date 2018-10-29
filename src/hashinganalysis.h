#ifndef HASHINGANALYSIS_H_
#define HASHINGANALYSIS_H_

template<typename K, typename V>
class HashNodeOA {
public:
    HashNodeOA(K key, V value);
    V value;
    K key;
};

template<typename K, typename V>
class HashMapOA
{
private:
    HashNodeOA<K,V> **map;
    int tableSize;
    int currSize;
public:
    HashMapOA(int tableSize);
    int insertNode(K key, V value, bool midSquare);
    void setTableSize(int tableSize);
    void clear();
    void display();
    void MS(); // Mid Square
    void MT(); // Mod Table
    void generate(bool midSquare);
    bool isEmpty();
};

class HashMapSC
{
private:
	list<int> *map;
	int tableSize;
	int currSize;
public:
    HashMapSC(int tableSize);  // Constructor
	int insertNode(int key, bool midSquare);
	void setTableSize(int tableSize);
	void clear();
	void display();
	void MS(); // Mid Square
	void MT(); // Mod Table
	void generate(bool midSquare);
};

#endif
