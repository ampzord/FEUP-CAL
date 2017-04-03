/*
 * Node.h
 *
 *  Created on: 03/04/2017
 *      Author: Morango
 */

#ifndef PROJECT_CAL_SRC_NODE_H_
#define PROJECT_CAL_SRC_NODE_H_

#include <string>

class Node {
private:
	int node_id;
	float latitude_in_degrees, longitude_in_degrees, longitude_in_radians,
			latitude_in_radians;
	std::string type;

public:
	Node();
	Node(int node_id, std::string type, float latitude_in_degrees, float longitude_in_degrees,
			float longitude_in_radians, float latitude_in_radians);
	virtual ~Node();

	bool operator ==(const Node & b) const;

	float getLatitudeInDegrees() const {
		return latitude_in_degrees;
	}

	float getLatitudeInRadians() const {
		return latitude_in_radians;
	}

	float getLongitudeInDegrees() const {
		return longitude_in_degrees;
	}

	float getLongitudeInRadians() const {
		return longitude_in_radians;
	}

	int getNodeId() const {
		return node_id;
	}

	const std::string& getType() const {
		return type;
	}
};

#endif /* PROJECT_CAL_SRC_NODE_H_ */
