#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Please input numbers to find average.\n";
        return 0;
    }

    int sum = 0, count = argc - 1;
    for (int i = 1; i < argc; ++i) {
        int num = atoi(argv[i]);
        sum += num;
    }

    double average = (double)sum / count;
    
    cout << "---------------------------------\n";
    cout << "Average of " << count << " numbers = " << average << "\n";
    cout << "---------------------------------\n";

    return 0;
}
