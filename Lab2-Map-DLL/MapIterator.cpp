#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    currentElement = map.headOfList;
}


void MapIterator::first() {
    currentElement = map.headOfList;
}


void MapIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentElement = currentElement->nextAddress;
}


TElem MapIterator::getCurrent(){
    if (!valid()) {
        throw exception();
    }
    return currentElement->dataPair;
}


bool MapIterator::valid() const {
	return currentElement != nullptr;
}



