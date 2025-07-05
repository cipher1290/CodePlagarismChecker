// #include <iostream>
// using namespace std;

// bool isPrime(int n) {
//     if (n <= 1) return false;
//     for (int i = 2; i < n; i++) {
//         if (n % i == 0) return false;
//     }
//     return true;
// }

// int main() {
//     int num = 17;
//     if (isPrime(num)) {
//         cout << "Prime\n";
//     } else {
//         cout << "Not Prime\n";
//     }
//     return 0;
// }

#include <iostream>
using namespace std;

int main() {
    int c, x;
    cin >> c >> x;
    int result = c + x;
    cout << "Sum is: " << result << endl;
    return 0;
}

