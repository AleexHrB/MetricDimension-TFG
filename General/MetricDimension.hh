#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <ilcplex/ilocplex.h>
#include <iostream>
#include <list>
#include <cmath>
#include <queue>
#include <string>
#include <vector>
#include <unistd.h>
#include <omp.h>
using namespace std;
#ifndef METRICDIMENSION_HH
#define METRICDIMENSION_HH

class MetricDimension {

public:
  MetricDimension();

  // Number of nodes
  MetricDimension(int n);

  // Digraph without two edges between two nodes
  void generate_tournament(const string &s);

  // Undirected graph
  void generate_normal(const string &s);

  void solve();

  void print_solution();

  void generate_typeIII(unsigned int r, unsigned int s, unsigned int t);

  double getElapsedTime();

  int getDimension();

  void generate_circulant(int n, const vector<int> &generators);

  void print_matrix();

  void print_distance();

  void generate_file_graph(const string &file_name);

private:
  // Adjacency Matrix
  vector<vector<int>> m;

  // Resolving set nodes
  list <int> l;

  // Distance Matrix
  vector<vector<int>> dist;

  double elapsedTime = 0;


  void bfs(int node, vector<int> &dist);

  bool check_solution();

  bool circulant = false;
};

#endif
