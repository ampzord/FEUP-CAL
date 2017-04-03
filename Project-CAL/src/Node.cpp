/*
 * Node.cpp
 *
 *  Created on: 03/04/2017
 *      Author: Morango
 */

#include "Node.h"

using namespace std;

Node::Node() {
	// TODO Auto-generated constructor stub

}

Node::Node(unsigned long long node_id, string type, float latitude_in_degrees, float longitude_in_degrees,
		float longitude_in_radians, float latitude_in_radians) {
	this->node_id = node_id;
	this->type = type;
	this->latitude_in_degrees = latitude_in_degrees;
	this->longitude_in_degrees = longitude_in_degrees;
	this->longitude_in_radians = longitude_in_radians;
	this->latitude_in_radians = latitude_in_radians;
}

Node::~Node() {
	// TODO Auto-generated destructor stub
}

bool Node::operator ==(const Node & b) const {
	return node_id == b.node_id;
}

