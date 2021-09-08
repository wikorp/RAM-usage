//#include <iostream>
//using namespace std;

int fibonacci(int n);

int main() { // jak przekazac parametr do main
    int n = 1000;
    int answer;
    int x = 1000;
    
    answer = fibonacci(n);
    //cout << answer << endl;

    return answer;
}

int fibonacci(int n) { // zabezpieczenie przed ujemnymi

    if (n == 0)
        return 0;
    if (n == 1 || n == 2)
        return 1;

    return fibonacci(n - 1) + fibonacci(n - 2);
}