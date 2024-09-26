#include "Map.h"
#include "MapIterator.h"
#include <utility>

Map::Map() {
    headOfList = nullptr;
    tailOfList = nullptr;
    totalElemsLL = 0;
}

Map::~Map() {
    while (headOfList != nullptr) {
        NodeStruct * temp = headOfList;
        headOfList = headOfList->nextAddress;
        delete temp;
    }
}

TValue Map::add(TKey c, TValue v){
    //traveling node
    NodeStruct * nomadNode = headOfList;
    //travel through the list
    while (nomadNode != nullptr) {
        //if element found overwrite old value
        if (nomadNode->dataPair.first == c) {
            TValue oldValue = nomadNode->dataPair.second;
            nomadNode->dataPair.second = v;
            return oldValue;
        }
        nomadNode = nomadNode->nextAddress;
    }
    
    
    TElem newElem = std::make_pair(c, v);
    NodeStruct * newNode = new NodeStruct(newElem);
    newNode->nextAddress = headOfList;
    newNode->prevAddress = nullptr;
    
    if (headOfList != nullptr) {
        headOfList->prevAddress = newNode;
    }
    
    headOfList = newNode;
    
    if (tailOfList == nullptr) {
        tailOfList = newNode;
    }
    
    totalElemsLL++;
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//empty list
    if (headOfList == nullptr) {
        return NULL_TVALUE;
    }
    //search and move nomad to elem
    NodeStruct * nomadNode = headOfList; // <<<------------------------------------------------||
    //                                                                                         ||
    while (nomadNode != nullptr && nomadNode->dataPair.first != c) { //                        ||
        nomadNode = nomadNode->nextAddress;//                                                  ||
    }//  <<<-------- at the end of this loop nomdaNode is set to the pair we are looking for --||
    //element not found                                                                        ||
    if (headOfList == nullptr) { //                                                            ||
        return  NULL_TVALUE; //                                                                ||
    } //                                                                                       ||
    //                                                                                         ||
    
    //TValue oldValue = nomadNode->dataPair.second; //  <<<-----------save the old value --------||
    
    //element found - case1: first element of the list
    //case1: subcases
    if (nomadNode->prevAddress == nullptr) {
        headOfList = headOfList->nextAddress; //skip head (set head to [head+1] address)
        //entering subcase checks (more elements present - tail is not null , one element present - tail needs to be null also)
        if (headOfList != nullptr) {
            //c1-subcase a. List contains more than head element >1 elem (tail is some other elem x)
            headOfList->prevAddress = nullptr;
        } else {
            //c1-subcase b. That was the only one element in the list (head = tail = removeable node)
            tailOfList = nullptr;
        }
    //element found - case2: element is the last element in the list
    //case2:
    } else if (nomadNode == tailOfList) {
    //element is the tail of the list
        tailOfList = tailOfList->prevAddress;
        tailOfList->nextAddress = nullptr;
    } else {
    //element is in between - case3
    //case3:
        nomadNode->nextAddress->prevAddress = nomadNode->prevAddress;
        nomadNode->prevAddress->nextAddress = nomadNode->nextAddress;
    }
    delete nomadNode;
    totalElemsLL--;
    return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
    NodeStruct * nomadNode = headOfList;
    while (nomadNode != nullptr) {
        if (nomadNode->dataPair.first == c) {
            return nomadNode->dataPair.second;
        }
        nomadNode = nomadNode->nextAddress;
    }
    //not found
    return NULL_TVALUE;
}

int Map::size() const {
	return totalElemsLL;
}

bool Map::isEmpty() const{
	return totalElemsLL == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



