//#include <iostream>
//using namespace std;

int fibonacci(int n);

int main() { 
    int n = 1000000;
    int answer;

    while (true) {
        answer = fibonacci(n);
        //cout << answer;
    }

    return answer;   
}

int fibonacci(int n) {
    int array[2];

    array[0] = 0;
    array[1] = 1;
    int buffor; // sprawdzic czy jest roznica jak zadeklaruje to w petli
    for (int i = 2; i <= n; i++) {
        buffor = array[1];
        array[1] = array[0] + array[1];
        array[0] = buffor;
    }
    
    if (n == 0)
        return array[0];
    return array[1];
}