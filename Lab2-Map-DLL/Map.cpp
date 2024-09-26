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
    NodeStruct * nomadNode = headOfList;
    //search and move nomad to elem
    while (nomadNode != nullptr && nomadNode->dataPair.first != c) {
        nomadNode = nomadNode->nextAddress;//
    }
    //if not found
    if (nomadNode == nullptr) {
          return NULL_TVALUE;
      }
    
    //to be deleted node, bookmark this address node ?
    //NodeStruct * todeleteNode = nomadNode;
    TValue oldValue = nomadNode->dataPair.second;
    
    if (nomadNode != nullptr) {
        if (nomadNode == headOfList) {
            headOfList = headOfList->nextAddress;
            if (headOfList != nullptr) {
                headOfList->prevAddress = nullptr;
            }
        }
        else if (nomadNode == tailOfList) {
            tailOfList = tailOfList->prevAddress;
            if (tailOfList != nullptr) {
                tailOfList->nextAddress = nullptr;
            }
        }
        else {
            //WARNING!! (can you explain please?)
            //it works but this feels like a weird workaround from gpt !!!
            //why do i still need to check for null ptr if I checked above, or I didnt cover ?
            if (nomadNode->nextAddress != nullptr) {
                   nomadNode->nextAddress->prevAddress = nomadNode->prevAddress;
               }

               if (nomadNode->prevAddress != nullptr) {
                   nomadNode->prevAddress->nextAddress = nomadNode->nextAddress;
               }
        }
    }
    delete nomadNode;
    //delete todeleteNode;
    totalElemsLL--;
    return oldValue;
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



