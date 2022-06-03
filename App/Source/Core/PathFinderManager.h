#pragma once

struct Node
{
	float f = FLT_MAX, g = FLT_MAX, h = FLT_MAX;
	Vector3 position{};
	std::vector<Node*> connections;
	Node* parent = nullptr;
	bool reachable = true;
	void ResetFGH()
	{
		f = FLT_MAX, g = FLT_MAX, h = FLT_MAX;
	}
};

class PathFinderManager
{
public:
	// Not allowed to instantiate this class
	PathFinderManager() = delete;
	// Remove diagonal connections between nodes close to unreachable nodes and unreachable nodes
	static void RemoveUnreachableConnections(std::vector<std::vector<Node*>>& grid);
	// Set up the connections for the nodes in grid
	static void UpdateConnections(std::vector<std::vector<Node*>>& grid);
	// Set up a grid
	static std::vector<std::vector<Node*>> InitializeGrid(int size, int spacing);
	// Perform A-star search resulting in a path returned
	static std::vector<Node*> AStar(Node* startNode, Node* goalNode);
	// Check if node is in a vector
	static bool IsInVector(const std::vector<Node*>& vector, Node* node);
	// Get all neighbor nodes in proximity to the node
	static std::vector<Node*> GetNeighbors(const Node* node, const std::vector<std::vector<Node*>>& grid);
	// Get the closest node from the given position
	static Node* GetClosestNode(Vector3 position, const std::vector<std::vector<Node*>>& grid);
	// Check if node has unreachable nodes in connections
	static bool HasAUnreachableNeighbor(const Node* node);
};

