/*
 * FakeEdge.h
 *
 *  Created on: 03/04/2017
 *      Author: Morango
 */

#ifndef PROJECT_CAL_SRC_FAKEEDGE_H_
#define PROJECT_CAL_SRC_FAKEEDGE_H_

namespace std {

class FakeEdge {
private:
	unsigned long long edgeId, v1Id, v2Id;
public:
	FakeEdge();
	FakeEdge(unsigned long long id, unsigned long long v1, unsigned long long v2);
	virtual ~FakeEdge();

	unsigned long long getEdgeId() const {
		return edgeId;
	}

	unsigned long long getV1Id() const {
		return v1Id;
	}

	unsigned long long getV2Id() const {
		return v2Id;
	}
};

} /* namespace std */

#endif /* PROJECT_CAL_SRC_FAKEEDGE_H_ */
