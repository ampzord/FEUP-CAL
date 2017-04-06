#ifndef PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_
#define PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_

#include "graphviewer.h"
#include "Graph.h"
#include "Node.h"
#include "FakeEdge.h"

#define PI 3.14159265358979323846

class SupermarketNetwork {
private :
    std::string name;
    GraphViewer* gv;
    Graph<Node> fake_graph;
    int marketId;
    std::vector<Node> nodes;
    std::vector<FakeEdge> edges;
public:

    /**
     * \brief Constructor of class SupermarketNetwork
     * \param name name of the Supermarket */
	SupermarketNetwork(std::string name);
	void manage();
	void addSupermarket(std::string name);
	bool handleRequest();
	void performOperation(std::string operation);
	/**
	 * \brief Faz load dos nodes em txt, adicionando-lhes um Random Type.
	 * \details Para cada node em txt é criado um objeto Node e inserido em nodes[].
	 * \details O Random Type usado serve para criar Markets, Users e Default Points. */
	void loadNodesRandom();

	/**
	 * \brief Faz load das Ruas em txt atualizando o atributo TwoWays de cada uma.
	 * \details Para cada Rua em txt,"True" ou "False" definem o atributo de cada objeto.
	 * \details True torna possivel a Rua ter 2 sentidos.
	 * \details False garante que a Rua so tem um sentido. */
	void loadStreetInformation();
	/**
	 * \brief Faz load das edges em txt e adiciona-as ao vector de edges.
	 * \details Para cada edge em txt cria objeto FakeEdge com parametros lidos.
	 * \details edges.txt */
	void loadEdgeInformation();

	/**
	 * \brief Insere no Grafo os nós e edges e pinta-os tambem no GraphViewr.
	 * \details Os nos e edges encontram-se nos vectores atributo nodes[] e edges[]. */
	void paintLoaded();

	/**
	 * \brief Retorna a posicao de uma edge no vector atraves do seu Id.
	 * \details Usado para localizar Ruas lidas e sincronizadas com edges.
	 * \param id Id da Rua a encontrar. */
	int getEdgePosById(unsigned long long id);
	/**
	 * \brief Verifica se existe alguma edge com o Id forncido.
	 * \details Usado para verificar a existencia de Ruas lidas no vector edges.
	 * \param id Id da Rua a verificar */
	bool isEdgePosById(unsigned long long id);

	/**
	 * \brief Escreve no ficheiro os resultado da aplicacao dos algoritmos.
	 * \details results.txt */
	void printResults(map<int, vector<int> > res);
	void printResults(vector<pair<int, vector<int> > > res);
	/**
	 * \brief Calcula a distância entre dois nos.
	 * \param lat1 Latitude do no de origem.
	 * \param lat2 Latitude do no de destino.
	 * \param long1 Longitude do no de origem.
	 * \param long2 Longitude do no de destino. */
	double distanceBetween2Nodes(double lat1, double lat2, double long1, double long2);
	void mainMenu();
	void chooseAlgorithmFromOpenStreetMapsGraph();
	void chooseAlgorithmFromSimpleGraph();
	void loadInformationOpenStreetMapsGraph();
};

#endif /* PROJECT_CAL_SRC_SUPERMARKETNETWORK_H_ */
