#include "MetricDimension.hh"

bool MetricDimension::check_solution() {

    vector<vector<int>> tuples (m.size(), vector<int>(l.size()));

    for (int i = 0; i < m.size(); ++i) {

        int j = 0;

        for (int x : l) {
            tuples[i][j] = dist[x][i];
            ++j;
        }
    }

    
/*
    for (auto& v: tuples) {

        for (int x : v) cout << x << " ";

        cout << endl;

    }

    */
    
    

    for (int i = 0; i < m.size(); ++i) {

        for (int j = i + 1; j < m.size(); ++j) if (tuples[i] == tuples[j]) return false;

    }

    return true;

}

void MetricDimension::generate_typeIII(unsigned int r, unsigned int s, unsigned int t) {
    unsigned int n = r + s + t + 2;
    m = vector<vector<int>>(n, vector<int>(n, 0));

    for (unsigned int i = 2; i <= r; ++i) m[i][i-1] = m[i-1][i] = 1;
    for (unsigned int i = r+2; i <= r+s; ++i) m[i][i-1] = m[i-1][i] = 1;
    for (unsigned int i = r+s+2; i <= r+s+t; ++i) m[i][i-1] = m[i-1][i] = 1;

    m[n-1][r] = m[r][n-1] = 1;
    m[n-1][r+s] = m[r+s][n-1] = 1;
    m[n-1][r+s+t] = m[r+s+t][n-1] = 1;


    m[0][1] = m[1][0] = 1;
    m[0][r+1] = m[r+1][0] = 1;
    m[0][r+s+1] = m[r+s+1][0] = 1;
    
}

void MetricDimension::print_solution() {

  for (int x : l)
    cout << x << " ";
  cout << endl;
}

MetricDimension::MetricDimension(int n) {

  m = vector<vector<int>>(n, vector<int>(n));
}

MetricDimension::MetricDimension() {}

void MetricDimension::generate_tournament(const string &s) {

  circulant = false;

  int n = m.size();

  for (int i = 0; i < n; ++i)
    m[i][i] = 0;

  int k = 0;

  for (int i = 0; i < n; ++i) {

    for (int j = i + 1; j < n; ++j) {

      m[i][j] = s[k] - '0';
      m[j][i] = not m[i][j];
      ++k;
    }
  }
}

void MetricDimension::generate_normal(const string &s) {

  int n = m.size();

  circulant = false;

  for (int i = 0; i < n; ++i)
    m[i][i] = 0;

  int k = 0;

  for (int i = 0; i < n; ++i) {

    for (int j = i + 1; j < n; ++j) {

      m[i][j] = s[k] - '0';
      m[j][i] = m[i][j];
      ++k;
    }
  }
}

double MetricDimension::getElapsedTime() { return elapsedTime; }

int MetricDimension::getDimension() { return l.size(); }

void MetricDimension::solve() {

    l.clear();
    IloEnv env;
    IloModel model(env);

    int n = m.size();

    IloBoolVarArray vars(env, n);
    IloExpr exp(env);

    dist = vector<vector<int>>(n, vector<int>(n, n));

    for (int i = 0; i < n; ++i) {

        model.add(vars[i]);
        exp += vars[i];


    }

    #pragma omp parallel
    #pragma omp single
    #pragma omp taskloop nogroup
    for (int i = 0; i < n; ++i) bfs(i, dist[i]);

    model.add(IloMinimize(env, exp));
    exp.end();

    //Constraints

    for (int i = 0; i < n; ++i) {

        for (int j = i + 1; j < n; ++j) {

            IloExpr constr(env);

            for (int k = 0; k < n; ++k) {

                if (dist[k][i] != dist[k][j]) constr += vars[k];
            }

            model.add(constr >= 1);

            constr.end();

        }

    }
    

    IloCplex cplex(model);
    cplex.setOut(env.getNullStream());
    cplex.solve();


    for (int i = 0; i < n; ++i) if(round(cplex.getValue(vars[i])) == 1) l.push_back(i);

    if (not check_solution()) {

        cerr << "ERROR !!" << endl;

        for (int i = 0; i < n; ++i) {

            for (int j = i + 1; j < n; ++j) cerr << m[i][j];

        }

        cerr << endl;
    }

    cplex.end();
    model.end();
    vars.end();
    env.end();
}



void MetricDimension::generate_file_graph(const string &file_name) {

  int n = m.size();

  dist = vector<vector<int>>(n, vector<int>(n, n));
  for (int i = 0; i < n; ++i)
    bfs(i, dist[i]);

  ofstream f(file_name);

  f << "Minimize" << endl;

  f << " obj: ";

  for (int i = 1; i < n; ++i)
    f << "x" + to_string(i) + " + ";

  f << "x0" << endl;

  f << "Subject To" << endl;


  for (int i = 0; i < n; ++i) {

      for (int j = i + 1; j < n; ++j) {

              bool plus = false;

              for (int k = 0; k < n; ++k) {

                  if (dist[k][i] != dist[k][j]) {

                      if (plus) f << " + ";
                      f << "x" << k;
                      plus = true;
                  }

              }

              f << " >= 1 " << endl;
          
      }

  }


  f << "Binary" << endl;

  for (int i = 0; i < n; ++i)
    f << " x" + to_string(i);

  f << endl;

  f << "End" << endl;
}

void MetricDimension::generate_circulant(int n, const vector<int> &v) {
  m = vector<vector<int>>(n, vector<int>(n));

  circulant = true;

  for (int i = 0; i < m.size(); ++i)
    m[0][i] = 0;

  for (int i = 0; i < v.size(); ++i) {
    //(0 + j)
    int res = v[i] % n;
    if (res != 0)
      m[0][res] = 1;
    //(0 - j)
    res = (n + ((-v[i]) % n)) % n;
    if (res != 0)
      m[0][res] = 1;
  }

  for (int i = 1; i < m.size(); ++i) {

    int end = m.size() + i;

    for (int j = i; j < end; ++j)
      m[i][j % m.size()] = m[i - 1][(j - 1) % m.size()];
  }
}

void MetricDimension::print_matrix() {

  for (const vector<int> &v : m) {

    for (int x : v)
      cout << x << " ";

    cout << endl;
  }
}

void MetricDimension::bfs(int node, vector<int> &dist) {

  int n = m.size();

  queue<int> q;

  dist[node] = 0;

  q.push(node);

  while (not q.empty()) {

    int act = q.front();
    q.pop();

    for (int i = 0; i < n; ++i) {

      if (dist[i] == dist.size() and m[act][i]) {

        q.push(i);
        dist[i] = dist[act] + 1;

      }
    }
  }
}


void MetricDimension::print_distance() {

    for (auto& v: dist) {

        for (int x: v) cout << x << " ";

        cout << endl;

    }

}
