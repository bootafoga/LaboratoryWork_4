//
// Created by Мария on 27.02.2019.
//
#pragma once
#include "List.h"
#include <iostream>
using namespace std;

template <typename T, typename T1>
class MapNode{
public:
    MapNode();
    MapNode(T key, T1 value);
    ~MapNode();
    T key;
    T1 value;
    bool color;     //if 0 it's black, if 1 it's red
    string code = "";
    MapNode *left;
    MapNode *right;
    MapNode *parent;
};

template<typename T, typename T1>
MapNode<T, T1>::MapNode() {
    this->key = (T)nullptr;
    this->value = (T1)nullptr;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = true;
}

template<typename T, typename T1>
MapNode<T, T1>::MapNode(T key, T1 value) {
    this->key = key;
    this->value = value;
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = true;
}

template<typename T, typename T1>
MapNode<T, T1>::~MapNode() {
    left = nullptr;
    right = nullptr;
    parent = nullptr;
}

template <typename T, typename T1>
class Map {
public:

    Map();
    ~Map();

    void insert(T key, T1 value);
    void remove(T key);
    MapNode<T, T1>* find(T key);
    string findVal(T1 val);
    void clear();
    List<T> get_keys();
    List<T1> get_values();
    void Show();

    MapNode<T, T1> getRootCopy(){
        MapNode<T,T1> copy = *root;
        return copy;
    }
    short int getSize(){ return size;}
    MapNode<T, T1> *root;
private:
    void leftRotation(MapNode<T,T1> *elemX);
    void rightRotation(MapNode<T,T1> *elemX);
    void fixTreeAfterInsert(MapNode<T,T1> *currentElem);
    void fixTreeAfterRemove(MapNode<T,T1> *elem);
    void helpClear(MapNode<T, T1> *currentNode);
    void creatingListOfKeys(MapNode<T, T1> *currentNode, List<T> &list);
    void creatingListOfValues(MapNode<T, T1> *currentNode, List<T1> &list);
    short int size = 0;
};

template<typename T, typename T1>
Map<T, T1>::Map() {
    root = nullptr;
}

template<typename T, typename T1>
Map<T, T1>::~Map() {
   // clear();
}

template<typename T, typename T1>
void Map<T, T1>::insert(T key1, T1 value1) {

    MapNode<T, T1> *newElem = new MapNode<T, T1>(key1, value1);

    if (root == nullptr){
        root = newElem;
    } else {
        MapNode<T, T1> *current = root;
        MapNode<T, T1> *parent = nullptr;

        while (current!= nullptr){
            parent = current;
            if (current->key == newElem->key) return;
            current =  (current->key < newElem->key)? current->right : current->left;
        }

        // now we have found the place where new ell will be added

        newElem->parent = parent;
        newElem->color = true;

        if (parent->key < newElem->key)
            parent->right = newElem;
        else
            parent->left = newElem;
    }
    fixTreeAfterInsert(newElem);
    size++;
}

template<typename T, typename T1>
void Map<T, T1>::leftRotation(MapNode<T, T1> *elemX) {

    MapNode<T, T1> *elemY = elemX->right;

    elemX->right = elemY->left;
    if (elemY->left != nullptr) elemY->left->parent = elemX;

    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->left)
            elemX->parent->left = elemY;
        else
            elemX->parent->right = elemY;
    } else {
        root = elemY;
    }

    elemY->left = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}

template<typename T, typename T1>
void Map<T, T1>::rightRotation(MapNode<T, T1> *elemX) {

    MapNode<T, T1> *elemY = elemX->left;

    elemX->left = elemY->right;
    if (elemY->right != nullptr) elemY->right->parent = elemX;


    if (elemY != nullptr) elemY->parent = elemX->parent;
    if (elemX->parent) {
        if (elemX == elemX->parent->right)
            elemX->parent->right = elemY;
        else
            elemX->parent->left= elemY;
    } else {
        root = elemY;
    }

    elemY->right = elemX;
    if (elemX != nullptr) elemX->parent = elemY;
}


template<typename T, typename T1>
void Map<T, T1>::fixTreeAfterInsert(MapNode<T, T1> *currentElem){
    while (currentElem!= root && currentElem->parent->color){ // while parent red
        // if parent node is left son
        if (currentElem->parent == currentElem->parent->parent->left){
            MapNode<T, T1> *uncle = currentElem->parent->parent->right;
            if (uncle!= nullptr && uncle->color){ //uncle red
                currentElem->parent->color = false;
                uncle->color = false;
                currentElem->parent->parent->color = true;
                currentElem = currentElem->parent->parent;
            } else { //uncle black or don't exist
                if (currentElem == currentElem->parent->right){
                    currentElem = currentElem->parent;

                    leftRotation(currentElem);
                }

                currentElem->parent->color = false;
                currentElem->parent->parent->color = true;
                rightRotation(currentElem->parent->parent);
            }

        } else {

            MapNode<T, T1> *uncle = currentElem->parent->parent->left;
            if (uncle!= nullptr && uncle->color) { //uncle red
                currentElem->parent->color = false;
                uncle->color = false;
                currentElem->parent->parent->color = true;
                currentElem = currentElem->parent->parent;
            } else {
                if (currentElem == currentElem->parent->left){
                    currentElem = currentElem->parent;
                    rightRotation(currentElem);
                }
                currentElem->parent->color = false;
                currentElem->parent->parent->color = true;
                leftRotation(currentElem->parent->parent);
            }
        }
    }
    root->color = false;
}


template<typename T, typename T1>
MapNode<T, T1> *Map<T, T1>::find(T key) {
    MapNode<T, T1> *current = root;

    while (current != nullptr){
        if (current->key == key){
            return current;
        }
        else {
            current =  (current->key < key)? current->right : current->left;
        }
    }
    throw invalid_argument("The city entered is not in the existing paths.");
    return nullptr;
}

template<typename T, typename T1>
string Map<T, T1>::findVal(T1 val) {
    if (root == nullptr) {
        cout << "Empty map\n";
        return nullptr;
    }
    MapNode<T, T1> *currentNode = root;
    string answer = "";
    return helpFind(currentNode, val, answer);
    //return foundNode;
}

template<typename T, typename T1>
string helpFind(MapNode<T, T1> *current, T1 val, string answer) {
    if (current) {
        if (current->value == val){

            answer += current->key;
            //cout << answer;
            return answer;
        }
         else {
             string check = helpFind(current->right, val, answer);
             if (check != "") answer = check;

             check = helpFind(current->left, val, answer);
             if (check != "") answer = check;

         }
    }
    return answer;
}


template<typename T, typename T1>
void Map<T, T1>::remove(T key) {

    MapNode<T, T1> *deletedNode = find(key);
    if (deletedNode == nullptr) throw invalid_argument("Item with this key not found");

    // if its list
    if ((deletedNode->left == nullptr)&&(deletedNode->right == nullptr)){
        if (deletedNode == root) {
            root = nullptr;
            delete deletedNode;
        } else {

            if (deletedNode == deletedNode->parent->left)
                deletedNode->parent->left = nullptr;
            else
                deletedNode->parent->right = nullptr;

            if (!deletedNode->color) fixTreeAfterRemove(deletedNode->parent);
            delete deletedNode;
        }
    }

    //if one son
    if ((deletedNode->left == nullptr) != (deletedNode->right == nullptr)){

        if (deletedNode == root){
            if (deletedNode->left != nullptr)
                root = deletedNode->left;
            else if (deletedNode->right != nullptr)
                root = deletedNode->right;
        } else {
            MapNode<T, T1> *sonOfDeleted;

            if (deletedNode->left != nullptr)
                sonOfDeleted = deletedNode->left;
            else
                sonOfDeleted = deletedNode->right;

            sonOfDeleted->parent = deletedNode->parent;

            if (deletedNode == deletedNode->parent->left)
                deletedNode->parent->left = sonOfDeleted;
            else
                deletedNode->parent->right = sonOfDeleted;

            if (!deletedNode->color) fixTreeAfterRemove(sonOfDeleted);
            delete deletedNode;

        }
    }

    //if two sons
    if ((deletedNode->left != nullptr) && (deletedNode->right != nullptr)){
        MapNode<T, T1> *temporaryNode = deletedNode->right;
        while (temporaryNode->left != nullptr) temporaryNode = temporaryNode->left;

        if (temporaryNode->right == nullptr){
            if (temporaryNode == temporaryNode->parent->left)
                temporaryNode->parent->left = nullptr;
            else
                temporaryNode->parent->right = nullptr;

            deletedNode->key = temporaryNode->key;
            deletedNode->value = temporaryNode->value;
            if (!temporaryNode->color) fixTreeAfterRemove (temporaryNode->parent);
        } else {
            MapNode<T, T1> *sonOfTemporary = temporaryNode->right;
            temporaryNode->parent->left = sonOfTemporary;
            sonOfTemporary->parent = temporaryNode->parent;
            deletedNode->key = temporaryNode->key;
            deletedNode->value = temporaryNode->value;
            if (!temporaryNode->color) fixTreeAfterRemove (sonOfTemporary);
        }
        delete temporaryNode;
    }
    size--;
}

template<typename T, typename T1>
void Map<T, T1>::fixTreeAfterRemove(MapNode<T, T1> *currentNode) {
    while (currentNode != root && !currentNode->color) {
        if (currentNode == currentNode->parent->left) {
            MapNode<T, T1> *brotherOfCurrent = currentNode->parent->right;
            if (brotherOfCurrent->color) {
                brotherOfCurrent->color = false;
                currentNode->parent->color = true;
                leftRotation(currentNode->parent);
                brotherOfCurrent = currentNode->parent->right;
            }
            if (!brotherOfCurrent->left->color && !brotherOfCurrent->right->color) {
                brotherOfCurrent->color = true;
                currentNode = currentNode->parent;
            } else {
                if (!brotherOfCurrent->right->color) {
                    brotherOfCurrent->left->color = false;
                    brotherOfCurrent->color = false;
                    rightRotation(brotherOfCurrent);
                    brotherOfCurrent = currentNode->parent->right;
                }
                brotherOfCurrent->color = currentNode->parent->color;
                currentNode->parent->color = false;
                brotherOfCurrent->right->color = false;
                leftRotation(currentNode->parent);
                currentNode = root;
            }
        } else {
            MapNode<T, T1> *brotherOfCurrent =  currentNode->parent->left;
            if (brotherOfCurrent->color) {
                brotherOfCurrent->color = false;
                currentNode->parent->color = true;
                rightRotation(currentNode->parent);
                brotherOfCurrent = currentNode->parent->left;
            }
            if (!brotherOfCurrent->right->color && !brotherOfCurrent->left->color) {
                brotherOfCurrent->color = true;
                currentNode = currentNode->parent;
            } else {
                if (!brotherOfCurrent->left->color) {
                    brotherOfCurrent->right->color = false;
                    brotherOfCurrent->color = true;
                    leftRotation(brotherOfCurrent);
                    brotherOfCurrent = currentNode->parent->left;
                }
                brotherOfCurrent->color = currentNode->parent->color;
                currentNode->parent->color = false;
                brotherOfCurrent->left->color = false;
                rightRotation(currentNode->parent);
                currentNode = root;
            }
        }
    }
    currentNode->color = false;
}

template<typename T, typename T1>
void Map<T, T1>::Show() {
    if (root == nullptr) {
        cout << "Empty map\n";
        return;
    }
    MapNode<T, T1> *currentNode = root;
    helpShow(currentNode, 0);
}

template<typename T, typename T1>
void helpShow(MapNode<T, T1> *node, int level) {
    if (node) {
        helpShow(node->right, level+1);
        for(int i = 0; i < 3*level; i++) cout << " ";
        char color = (node->color)? 'r' : 'b';
        cout << node->key << "(" << color << ")" << node->value << "\n";
        helpShow(node->left, level+1);
    }
}

template<typename T, typename T1>
void Map<T, T1>::clear() {
    MapNode<T, T1> *currentNode = root;
    helpClear(currentNode);
}

template<typename T, typename T1>
void Map<T,T1>::helpClear(MapNode<T, T1> *currentNode){
    if (currentNode == root) root = nullptr;
    if(currentNode){
        helpClear(currentNode->left);
        helpClear(currentNode->right);
        delete currentNode;
        size--;
    }
}

template<typename T, typename T1>
List<T> Map<T, T1>::get_keys() {
    List<T> listOfKeys;
    creatingListOfKeys(root, listOfKeys);

    return listOfKeys;
}

template<typename T, typename T1>
void Map<T, T1>::creatingListOfKeys(MapNode<T, T1> *node, List<T> &listOfKeys) {
    if(node){
        creatingListOfKeys(node->left, listOfKeys);
        listOfKeys.push_back(node->key);
        creatingListOfKeys(node->right, listOfKeys);
    }
}

template<typename T, typename T1>
List<T1> Map<T, T1>::get_values() {
    List<T1> listOfValues;
    creatingListOfValues(root, listOfValues);
    return listOfValues;
}

template<typename T, typename T1>
void Map<T, T1>::creatingListOfValues(MapNode<T, T1> *node, List<T1> &listOfValues) {
    if(node){
        creatingListOfValues(node->left, listOfValues);
        listOfValues.push_back(node->value);
        creatingListOfValues(node->right, listOfValues);
    }
}


