#include "Node.h"

using namespace std;

Node::Node(unsigned long long node_id, string type, float latitude_in_degrees, float longitude_in_degrees,
		float longitude_in_radians, float latitude_in_radians) {
	this->node_id = node_id;
	this->type = type;
	this->latitude_in_degrees = latitude_in_degrees;
	this->longitude_in_degrees = longitude_in_degrees;
	this->longitude_in_radians = longitude_in_radians;
	this->latitude_in_radians = latitude_in_radians;
}

Node::~Node() {}

bool Node::operator ==(const Node & b) const {
	return node_id == b.node_id;
}

float Node::getLatitudeInDegrees() const {
	return latitude_in_degrees;
}

float Node::getLatitudeInRadians() const {
	return latitude_in_radians;
}

float Node::getLongitudeInDegrees() const {
	return longitude_in_degrees;
}

float Node::getLongitudeInRadians() const {
	return longitude_in_radians;
}

unsigned long long Node::getNodeId() const {
	return node_id;
}

const string& Node::getType() const {
	return type;
}
