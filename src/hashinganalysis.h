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
    int capacity;
    int size;
public:
    HashMap(int capacity, int size);
    int midSquareHash(K key);
    int keyModTableSize(K key);
    int insertNodeOpenAddressing(K key, V value);
    V get(K key);
    int mapSize();
    bool isEmpty();
    void display();
    void generate();
};

#endif
