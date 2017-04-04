/*
 * FakeEdge.cpp
 *
 *  Created on: 03/04/2017
 *      Author: Morango
 */

#include "FakeEdge.h"

namespace std {

FakeEdge::FakeEdge() {
	// TODO Auto-generated constructor stub
}

FakeEdge::FakeEdge(unsigned long long id, unsigned long long v1, unsigned long long v2){

	this->edgeId = id;
	this->v1Id = v1;
	this->v2Id = v2;
	this->twoWay = false;
}

FakeEdge::~FakeEdge() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
