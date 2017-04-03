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
	int edgeId, v1Id, v2Id;
public:
	FakeEdge();
	FakeEdge(int id, int v1, int v2);
	virtual ~FakeEdge();

	int getEdgeId() const {
		return edgeId;
	}

	int getV1Id() const {
		return v1Id;
	}

	int getV2Id() const {
		return v2Id;
	}
};

} /* namespace std */

#endif /* PROJECT_CAL_SRC_FAKEEDGE_H_ */
