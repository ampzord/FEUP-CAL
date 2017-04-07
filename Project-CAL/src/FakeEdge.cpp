#include "FakeEdge.h"

FakeEdge::FakeEdge(unsigned long long edgeId, unsigned long long v1Id,
		unsigned long long v2Id) {

	this->edgeId = edgeId;
	this->v1Id = v1Id;
	this->v2Id = v2Id;
	this->twoWay = false;
}

FakeEdge::~FakeEdge() {
}

unsigned long long FakeEdge::getEdgeId() const {
	return edgeId;
}

unsigned long long FakeEdge::getV1Id() const {
	return v1Id;
}

unsigned long long FakeEdge::getV2Id() const {
	return v2Id;
}

bool FakeEdge::isTwoWay() const {
	return twoWay;
}

void FakeEdge::setTwoWay(bool twoWay) {
	this->twoWay = twoWay;
}
