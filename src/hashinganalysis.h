#ifndef HASHINGANALYSIS_H_
#define HASHINGANALYSIS_H_

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
	void remove(int index);
	void print();
};

template<typename K, typename V>
class HashNode {
public:
    HashNode(K key, V value);
    V value;
    K key;
};

template<typename K, typename V>
class HashMap
{
private:
    HashNode<K,V> **map;
    int tableSize;
    int currSize;
public:
    HashMap(int tableSize, int currSize);
    int midSquareHash(K key);
    int keyModTableSize(K key);
    int insertNodeOA(K key, V value, bool midSquare);
    V get(K key);
    int mapSize();
    void setTableSize(int tableSize);
    void clear();
    bool isEmpty();
    void display();
    void generateOA(bool midSquare);
};

#endif
