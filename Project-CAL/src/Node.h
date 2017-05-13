#ifndef PROJECT_CAL_SRC_NODE_H_
#define PROJECT_CAL_SRC_NODE_H_

#include <string>
#include <cstdlib>

/** \brief class Node that stores nodeID, latitude and longitude in degrees and radians. */

class Node {
private:
	unsigned long long node_id;
	float latitude_in_degrees, longitude_in_degrees,
		longitude_in_radians, latitude_in_radians;
	std::string type;
	std::string name;

public:

	/**
	 * \brief Constructor of class Node.
	 * \param node_id ID of node.
	 * \param type Type of node ("Market", "User", "Default").
	 * \param latitude_in_degrees Latitude of node in degrees.
	 * \param longitude_in_degrees Longitude of node in degrees.
	 * \param longitude_in_radians Longitude of node in radians.
	 * \param latitude_in_radians Latitude of node in radians. */
	Node(unsigned long long node_id, std::string type, float latitude_in_degrees, float longitude_in_degrees,
			float longitude_in_radians, float latitude_in_radians);

	/** \brief Destructor for class Node. */
	virtual ~Node();

	/**
	 * \brief Compare two nodes.
	 * \details Two nodes can't have same ID. */
	bool operator ==(const Node & b) const;

	/** \brief Returns latitude in degrees. */
	float getLatitudeInDegrees() const;

	/** \brief Returns latitude in radians. */
	float getLatitudeInRadians() const;

	/** \brief Returns longitude in degrees. */
	float getLongitudeInDegrees() const;

	/** \brief Returns longitude in radians. */
	float getLongitudeInRadians() const;

	/** \brief Returns node ID. */
	unsigned long long getNodeId() const;

	/** \brief Returns type of node ("Market", "User", "Default"). */
	const std::string& getType() const;

	std::string getName() const;
};

#endif /* PROJECT_CAL_SRC_NODE_H_ */
