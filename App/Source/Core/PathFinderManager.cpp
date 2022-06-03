#include "pch.h"
#include "PathFinderManager.h"

void PathFinderManager::RemoveUnreachableConnections(std::vector<std::vector<Node*>>& grid)
{
	for (int i = 0; i < static_cast<int>(grid.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(grid.size()); j++)
		{
			// Check for unreachable neighbors
			if (HasAUnreachableNeighbor(grid.at(i).at(j)))
			{
				// assign it new neighbors without diagonal connections
				std::vector<Node*> neighbors;
				Vector2 pos = { static_cast<float>(i),static_cast<float>(j) };
				const Node* node = grid.at(i).at(j);
				for (int newX = -1; newX <= 1; newX++)
				{
					for (int newY = -1; newY <= 1; newY++)
					{
						if (static_cast<int>(node->position.x) + newX >= grid.size() || static_cast<int>(node->position.z) + newY >= grid.size()
							|| static_cast<int>(node->position.x) + newX < 0 || static_cast<int>(node->position.z) + newY < 0)
							continue;

						if (newX == 0 && newY == 0 || newX != 0 && newY != 0)
						{
							continue;
						}

						if (grid[static_cast<int>(node->position.x) + newX][static_cast<int>(node->position.z) + newY]->reachable)
							neighbors.push_back(grid[static_cast<int>(node->position.x) + newX][static_cast<int>(node->position.z) + newY]);
					}
				}
				// Assign the updated connections
				grid.at(i).at(j)->connections = neighbors;
			}
		}
	}
}

void PathFinderManager::UpdateConnections(std::vector<std::vector<Node*>>& grid)
{
	// Set up connections
	for (int i = 0; i < static_cast<int>(grid.size()); i++)
	{

		for (int j = 0; j < static_cast<int>(grid.size()); j++)
		{
			if(grid.at(i).at(j)->reachable)
				grid.at(i).at(j)->connections = GetNeighbors(grid.at(i).at(j), grid);
		}
	}
	// Remove all unreachable nodes and also the diagonal ones close to them
	RemoveUnreachableConnections(grid);
}

std::vector<std::vector<Node*>> PathFinderManager::InitializeGrid(int size, int spacing = 1)
{
	std::vector<std::vector<Node*>> grid;
	for(int i = 0; i < size; i++)
	{
		grid.emplace_back();

		for(int j = 0; j < size; j++)
		{
			Node* newNode = new Node;
			newNode->position = { static_cast<float>(i * spacing), 0.f, static_cast<float>(j * spacing) };
			grid.at(i).push_back(newNode);
		}
	}

	UpdateConnections(grid);

	return grid;
}

std::vector<Node*> PathFinderManager::AStar(Node* startNode, Node* goalNode)
{
	std::vector<Node*> openList, closedList, generatedPath;
	if(startNode == nullptr || goalNode == nullptr || !startNode->reachable || !goalNode->reachable)
	{
		std::cout << "Error in PathFinderManager::AStar(StartNode or GoalNode is null)" << std::endl;
		return generatedPath;
	}

	// Initialize start
	Node* startingNode = startNode;
	startingNode->f = 0.0f;
	openList.push_back(startingNode);

	while (!openList.empty())
	{
		Node* currentNode = openList.at(0);
		int ind = 0;

		for (int i = 1; i < openList.size(); i++)
		{
			if (openList[i]->f < currentNode->f)
			{
				currentNode = openList[i];
				ind = i;
			}
		}
		openList.erase(openList.begin() + ind);
		closedList.emplace_back(currentNode);

		if (currentNode == goalNode)
		{
			// Trace the path back
			if (goalNode->parent)
			{
				while (currentNode != startingNode)
				{
					generatedPath.push_back(currentNode);
					currentNode = currentNode->parent;
				}
			}
			for (Node* node : openList)
			{
				node->ResetFGH();
				node->parent = nullptr;
			}
			for (Node* node : closedList)
			{
				node->ResetFGH();
				node->parent = nullptr;
			}

			return generatedPath;
		}

		for (Node* neighbor : currentNode->connections)
		{
			if (IsInVector(closedList, neighbor))
			{
				continue;
			}

			const float gNew = currentNode->g + Vector3Distance(neighbor->position, currentNode->position);
			const float hNew = Vector3Distance(goalNode->position, neighbor->position);
			const float fNew = gNew + hNew;

			if (neighbor->reachable && gNew < currentNode->g || neighbor->reachable && !IsInVector(openList, neighbor))
			{
				neighbor->g = gNew;
				neighbor->h = hNew;
				neighbor->f = fNew;

				neighbor->parent = currentNode;

				openList.emplace_back(neighbor);
			}
		}
	}

	return generatedPath;
}

bool PathFinderManager::IsInVector(const std::vector<Node*>& vector, Node* node)
{
	for (Node* current : vector)
	{
		if (current == node)
		{
			return true;
		}
	}
	return false;
}

std::vector<Node*> PathFinderManager::GetNeighbors(const Node* node, const std::vector<std::vector<Node*>>& grid)
{
		std::vector<Node*> neighbors;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				if (static_cast<int>(node->position.x) + newX >= grid.size() || static_cast<int>(node->position.z) + newY >= grid.size()
					|| static_cast<int>(node->position.x) + newX < 0 || static_cast<int>(node->position.z) + newY < 0)
					continue;

				if (newX == 0 && newY == 0)
				{
					continue;
				}

				neighbors.push_back(grid[static_cast<int>(node->position.x) + newX][static_cast<int>(node->position.z) + newY]);
			}
		}

		return neighbors;
}

Node* PathFinderManager::GetClosestNode(Vector3 position, const std::vector<std::vector<Node*>>& grid)
{
	int posX = static_cast<int>(roundf(position.x));
	int posY = static_cast<int>(roundf(position.z));

	if (posX >= static_cast<int>(grid.size()))
		posX = static_cast<int>(grid.size()) - 1;
	if (posY >= static_cast<int>(grid.size()))
		posY = static_cast<int>(grid.size()) - 1;
	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;

	if(!grid.at(posX).at(posY)->reachable)
	{
		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				if (posX + newX < grid.size() && posY + newY < grid.size()
					&& posX + newX >= 0 && posY + newY >= 0 && grid.at(posX + newX).at(posY+newY)->reachable)
				{
					return grid.at(posX + newX).at(posY + newY);
				}
			}
		}
	}
	else
	{
		return grid.at(posX).at(posY);
	}

	return nullptr;
}

bool PathFinderManager::HasAUnreachableNeighbor(const Node* node)
{
	for (const auto connect : node->connections)
	{
		if (!connect->reachable)
			return true;
	}

	return false;
}
