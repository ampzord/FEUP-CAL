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

FakeEdge::FakeEdge(int id, int v1, int v2){

	this->edgeId = id;
	this->v1Id = v1;
	this->v2Id = v2;
}

FakeEdge::~FakeEdge() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
