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
private:
    V value;
    K key;
public:
    HashNode(K key, V value);
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
    int hashCode(K key);
    void insertNode(K key, V value);
    V get(K key);
    int mapSize();
    bool isEmpty();
    void display();
};

#endif
