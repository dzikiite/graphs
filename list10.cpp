// list11_c++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<conio.h>
#include<math.h>
#include<random>
#include<string>
#include<deque>           
#include<queue> 

using namespace std;

int *setGraph(int vertices, int edge)
{
	string answer;
	int *tab = new int[edge];
	cout << "Do u want to draw the edges? [y/n]" << endl; 
	cin >> answer;
	if (answer == "y" || answer == "Y" || answer == "yes" || answer == "YES")
	{
		for (int i = 0; i<edge; i++)
		{
			tab[i] = rand() % vertices;
			if (i % 2 == 1)
			{
				if (tab[i] == tab[i - 1])
				{
					tab[i] = tab[i] - 1;
				}
			}
		}
	} 
	else if (answer == "n" || answer == "no" || answer == "N" || answer == "NO")
	{
		for (int i = 0; i < edge; i++)
		{
			cout << "Set edge: " << endl; 
			cin >> tab[i];
		}
	}
	else
	{
		cout << "Wrong answer value.";
	}
	 
	return tab;
}

void printTab(int *tab, int n)
{
	for (int i = 0; i<n; i++)
	{
		cout << tab[i] << "|";
	}
}

void printAdjacencyList(int **tab, int vertices)
{
	for (int i = 0; i < vertices; i++)
	{
		if (tab[i][0] < 0 || tab[i][0] >= vertices) continue;
		else
		{
			int size = sizeof(tab[i]);
			cout << endl << i << " -> ";
			for (int j = 0; j < size; j++)
			{
				if (tab[i][j] >= 0 && tab[i][j] < vertices)
				{
					cout << tab[i][j] << "|";
				}
			}
		}
	}
}
int **adjacencyList(int *tab, int vertices, int edge)
{
	int **list = new int *[vertices];
	for (int i = 0; i<vertices; i++)
	{
		int a = 0;
		for (int j = 0; j < edge; j++)
		{
			if (tab[j] == i)  a++;
		}
		list[i] = new int[a];

		int k = 0;
		for (int j = 0; j < edge; j++)
		{
			if (tab[j] == i)
			{
				if (j % 2 == 0)
				{
					int f = 0;
					for (int z = 0; z<k; z++)
					{
						if (list[i][z] == tab[j + 1])
						{
							f++;
							break;
						}
					}
					if (f == 0) { list[i][k] = tab[j + 1]; k++; }
				}
				else if (j % 2 == 1)
				{
					int f = 0;
					for (int z = 0; z < k; z++)
					{
						if (list[i][z] == tab[j - 1])
						{
							f++;
							break;
						}
					}
					if (f == 0) { list[i][k] = tab[j - 1]; k++; }
				}
			}
		}
	}
	return list;
}

void BFS(int **adjacencyList, int end, int *visnr, bool *vis, int vertices)
{
	int nr = 0;
	queue <int> Q;
	Q.push(end);
	vis[end] = true;

	while (!Q.empty())
	{
		end = Q.front();
		if (vis[end] && visnr[end] == false)
		{
			nr++;
			visnr[end] = nr;
		}

		vis[end] = true;
		int d = sizeof(adjacencyList[end]);
		for (int j = 0; j < d; j++)
		{
			int k;
			if (adjacencyList[end][j] >= 0 && adjacencyList[end][j] < vertices)
			{
				k = adjacencyList[end][j];
				if (!vis[k])
				{
					Q.push(k);
					vis[k] = true;
				}
			}
		}
		Q.pop();
	}
}

int main()
{
	string answer;
	do
	{
		int vertices, edge;
		cout << "Number of vertices: ";
		cin >> vertices;
		cout << "Number of edge: ";
		cin >> edge;
		cout << endl;

		int *tab = setGraph(vertices, edge);
		printTab(tab, edge);
		cout << endl;

		int **list = adjacencyList(tab, vertices, edge);
		printAdjacencyList(list, vertices); cout << endl;

		int start, end;

		bool *vis = new bool[vertices];
		int *visnr = new int[vertices];

		do
		{
			cout << endl << "Set start for BFS algorithm: " << endl;
			cin >> start;
			cout << "Set end for BFS algorithm: " << endl;
			cin >> end;
			cout << endl;

			for (int i = 0; i < vertices; i++)  vis[i] = false;
			for (int i = 0; i < vertices; i++)  visnr[i] = 0;

			BFS(list, end, visnr, vis, vertices);

			if (visnr[start] == false)
			{
				cout << "No way" << endl;
			}
			else
			{
				cout << start;
				int i = start;
				int min = start;

				do
				{
					int a = sizeof(list[i]); int b;
					for (int j = 0; j<a; j++)
					{
						if (list[i][j] >= 0 && list[i][j] < vertices)
						{
							b = list[i][j];
							if (visnr[b] < visnr[min] && visnr[b] > 0 && b != i) { min = b; }
						}
					}
					cout << " -> " << min;
					i = min;
				} while (i != end);
			}
			cout << endl << "Do you want to looking for different way? [y/n]" << endl;
			cin >> answer;
		} while (answer == "y" | answer == "yes" | answer == "Y" | answer == "YES");

		cout << endl << endl << "Do you want to use this program again? [y/n]" << endl;
		cin >> answer;
	} while (answer == "y" | answer == "yes" | answer == "Y" | answer == "YES");
}

