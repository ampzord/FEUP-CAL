#ifndef PROJECT_CAL_SRC_FAKEEDGE_H_
#define PROJECT_CAL_SRC_FAKEEDGE_H_

/** \brief a class to hold edge information such as it's ID, start node and end node. */

class FakeEdge {
private:
	unsigned long long edgeId, v1Id, v2Id;
	bool twoWay;
public:

	/** \brief Builds an edge.
	 * \param id ID of edge.
	 * \param v1 ID of source node.
	 * \param v2 ID of destiny node. */
	FakeEdge(unsigned long long edgeId, unsigned long long v1Id, unsigned long long v2Id);

	/** \brief Destroys a FakeEdge. */
	virtual ~FakeEdge();

	/** \brief Returns edge ID. */
	unsigned long long getEdgeId() const;

	/** \brief Returns ID of origin source node. */
	unsigned long long getV1Id() const;

	/** \brief Returns ID of destiny node. */
	unsigned long long getV2Id() const;

	/** \brief Returns information about the street.
	 *  \return True if road is a two way street.
	 *  \return False if road is only one way street. */
	bool isTwoWay() const;

	/** \brief Method to change a roads way.  */
	void setTwoWay(bool twoWay);

};

#endif /* PROJECT_CAL_SRC_FAKEEDGE_H_ */
