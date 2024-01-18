#include "MetricDimension.hh"

void solve_tournaments() {

  int n;
  cin >> n;

  string s;
  MetricDimension md(n);

  vector<int> v(n + 1, 0);

  while (cin >> s) {

    md.generate_tournament(s);


    

    md.solve();

    ++v[md.getDimension()];

    cout << s << " -> ";
    md.print_solution();
    //md.print_distance(); 

  }

  for (int i = 1; i < v.size(); ++i)
    cout << i << " " << v[i] << endl;
}

bool check_bound(int dim, int n) {

  switch (n % 8) {

  case 0:
    if (dim != 6)
      return false;
    break;
  case 1:
    if (dim != 6)
      return false;
    break;
  case 2:
    if (dim != 5)
      return false;
    break;

  case 3:
    if (dim != 5)
      return false;
    break;

  case 4:
    if (dim != 4)
      return false;
    break;

  case 5:
    if (dim != 5)
      return false;
    break;

  case 6:
    if (dim != 5)
      return false;
    break;

  case 7:
    if (dim != 6)
      return false;
    break;
  }

  return true;
}

void solve_circulants() {

  MetricDimension md;

  for (int n = 7; n <= 900; n += 8) {

    vector<int> gen = {1, 2, 3, 4};

    md.generate_circulant(n, gen);

    cout << "Solving circular for n = " << n << endl;
    md.solve();

    cout << n << " mod " << 8 << " = " << n % 8 << endl;
    cout << "Metric Dimension: " << md.getDimension() << endl;
    cout << "Resolving Set: ";
    md.print_solution();

    if (not check_bound(md.getDimension(), n)) {
      cout << "Error en n = " << n << endl;
      return;
    }
  }
}

void solve_typeIII() {

    const unsigned int MAX_ITER = 100;

    MetricDimension md;

    for (unsigned int i = 1; i < MAX_ITER; ++i) {

        md.generate_typeIII(1,i+1,i+1);
        md.solve();
        cout << "Metric Dimension: " << md.getDimension() << endl;
        cout << "Resolving Set: ";
        md.print_solution();
    }
}

int main() { 
    solve_typeIII();
}
