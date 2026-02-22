#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
    
    double num = 0;
    if(argc <= 1){
        cout << "Please input numbers to find average.\n";
    }else{
        cout << "---------------------------------" << endl;
        for(int i = 1; i < argc; i++){
            num += atof(argv[i]);
        }
        num /= (argc-1);
        cout << "Average of " << argc-1 << " numbers = " << num << endl;
        cout << "---------------------------------" << endl;
    }


    return 0;   
}
