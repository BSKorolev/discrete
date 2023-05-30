#include <iostream>
#include <vector>
#include <iomanip>

//const int VALUE = 2000000000;

void swFloyd(const std::vector<int>& vertexes, const std::vector<std::vector<int>> graph, std::vector<std::vector<std::string>>& ways, int current)
{
	std::vector<std::vector<int>> g(vertexes.size(), std::vector<int>(vertexes.size(), 2000000));	//раздаём веса 
	for (std::vector<int> v : graph)
	{
		g[v[0]][v[1]] = v[2];
		ways[v[0]][v[1]] += ' ';
		ways[v[0]][v[1]] += v[1]+'0';
		g[v[1]][v[0]] = v[2];
		ways[v[1]][v[0]] += ' ';
		ways[v[1]][v[0]] += v[0]+'0';
		g[v[0]][v[0]] = 0;
		g[v[1]][v[1]] = 0;
	}

	std::vector<std::vector<int>> d = g;
	int n = vertexes.size();
	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n; k++)
			{
				if (d[j][k] > d[j][i - 1] + d[i - 1][k])
				{
					d[j][k] = d[j][i - 1] + d[i - 1][k];
					ways[j][k] = ways[j][i-1];
					ways[j][k] += ' ';
					ways[j][k] += k + '0';
				}
			}
		}
	}
	std::cout << "Кратчайшие пути: " << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cout << std::setw(10) << i << "-" << j << ": " << ways[i][j];
			std::cout << ((d[i][j] == 0) ? "\t\t" : "\t")<< d[i][j] << std::endl;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	std::vector<std::vector<int>> graph; 
	std::vector<int> vertexes;
	int v1, v2, weight, numOfRibs=0;

	//ВВОД ДАННЫХ(НАЧАЛО)
	std::cout << 
		"Введите данные в формате: вершина1, вершина2, вес ребра(для прекращения ввода введите любые отрицательные значения)"
		<< std::endl;
	std::cin >> v1 >> v2 >> weight;
	while ((v1 >= 0) && (v2 >= 0) && (weight >= 0))
	{
		graph.push_back(std::vector<int> {v1,v2,weight});	//регистрируем очередную запись в графе 
		numOfRibs++;	//увеличиваем счётчик рёбер
		std::cin >> v1 >> v2 >> weight;
	}
	//ВВОД ДАННЫХ(КОНЕЦ)

	//составляем список присутствующих вершин
	
	for (std::vector<int> v : graph)
	{ 
		if (std::find(vertexes.begin(), vertexes.end(), v[0]) == vertexes.end())
		{
			vertexes.push_back(v[0]);
		}
		if (std::find(vertexes.begin(), vertexes.end(), v[1]) == vertexes.end())
		{
			vertexes.push_back(v[1]);
		}
	}

	//составляем матрицу инцидентности

	std::vector<std::vector<int>> incidence(vertexes.size(), std::vector<int>(numOfRibs,0));
	for(int i =0; i < graph.size(); i++)
	{
		incidence[graph[i][0]][i] = 1;
		incidence[graph[i][1]][i] = 1;
	}

	//выводим матрицу инцидентности в консоль:
	std::cout << "Матрица инцидентности: " << std::endl;
	int temp = 0;
	for (; temp < incidence[0].size(); temp++)
	{
		std::cout << std::setw(5) << "\t" << temp  ;
	}
	std::cout << std::endl;
	temp = 0;
	for (std::vector<int> v : incidence)
	{
		std::cout << temp;
		temp++;
		for (int i : v)
		{
			std::cout << std::setw(5) << "\t" << i;
		}
		std::cout << std::endl;
	}

	//переводим матрицу инцидентности в матрицу смежности
	std::vector<std::vector<int>> adjacency(vertexes.size(), std::vector<int>(vertexes.size(),0));
	for (int i =0; i < incidence.size(); i++)
	{
		std::vector<int> v = incidence[i];
		for (int j = 0; j < v.size(); j++)
		{
			if (v[j] != 0)
			{
				for (int k = 0; k < incidence.size(); k++)
				{
					if ((k != i) && (incidence[k][j] != 0))
					{
						adjacency[i][k] = 1;
						adjacency[k][i] = 1;
					}
					
				}
			}
		}
	}

	//выводим матрицу смежности в консоль:
	std::cout << "Матрица смежности: " << std::endl;
	temp = 0;
	for (; temp < adjacency[0].size(); temp++)
	{
		std::cout << "\t" << temp  ;
	}
	std::cout << std::endl;
	temp = 0;

	for (std::vector<int> v : adjacency)
	{
		std::cout << temp;
		temp++;
		for (int i : v)
		{
			std::cout << "\t" << i;
		}
		std::cout << std::endl;
	}


	std::vector<std::vector<std::string>> ways(vertexes.size(),std::vector<std::string>(vertexes.size(), ""));
	//ищем кратчайшие пути(Алгоритм Флойда-Уоршела)
	swFloyd(vertexes, graph, ways, 0);

	/*ищем кратчайшие пути между всеми вершинами(Алгоритм Дейкстры)
	for (int i = 0; i < vertexes.size(); i++)
	{
		shortestWay(vertexes, graph, ways, i);
	}*/
	
	return 0;
}
	
/*
0 3 16
0 6 13
1 7 10
2 0 18
2 1 16
2 6 13
4 1 13
4 2 17
3 2 14
4 6 19
4 7 18
5 3 14
5 4 11
5 7 13
6 5 19
7 1 18
7 2 16
7 3 15
7 6 11
-1 -1 -1
*/