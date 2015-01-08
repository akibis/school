#include <iostream>
using namespace std;

int x[10] = {0};
int pos[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int d[10] = {73, 47, 23, 26, 67, 99, 13, 53, 1, 97};
int main() {

  int count = 0;
  int key = 24;
  for (int i=0; i<10; i++) {
    if (d[i] >= key) {
      pos[count] = i;
      x[count] = d[i];
      count++;
    }
  }

  for (int i=0; i<10; i++) {
    if (pos[i] < 0)
      break;
    cout << pos[i] << " " << x[i] << endl;
  }

}
