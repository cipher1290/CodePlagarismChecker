// #include <iostream>
// #include <cmath>
// using namespace std;

// bool primeChecker(int x) {
//     if (x < 2) return false;
//     for (int d = 2; d*d <= x; ++d) {
//         if (x % d == 0) return false;
//     }
//     return true;
// }

// int main() {
//     int val = 17;
//     bool result = primeChecker(val);
//     cout << (result ? "Yes\n" : "No\n");
//     return 0;
// }

#include <iostream>
using namespace std;

int main() {
    int a, b;
    cin >> a >> b;
    int sum = a + b;
    cout << "Sum is: " << sum << endl;
    return 0;
}

