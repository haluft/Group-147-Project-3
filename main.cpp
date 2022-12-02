#include <iostream>
using namespace std;

int main() {
//---------------------------------------------------------------------------------------------------------
//Part 1: User input
    //(maybe) ask user top x movie list
    cout << "Type in how many movies you would like to see: [1-100]" << endl;
    int x;
    cin >> x;
    //check for bounds validity

//---------------------------------------------------------------------------------------------------------
//Part 2
    //read through the dataset and create the movie, avg rating pairs- we could create a movie class so we
    //could overload the comparator operators, which may make sorting easier.


//---------------------------------------------------------------------------------------------------------
//Part 3
    //clone vector and perform 2 different sorts. time them(gotta figure out how to do that)


//---------------------------------------------------------------------------------------------------------
//Part 4
    //print out top x based on user input(speaking of, should we ask for this before going through the set
    //or after? i think if we ask at the beginning, it would work better because any possible pause while
    //sifting through the dataset would happen after the prompt rather than before it.
    for(int i=0; i<x; i++){ //print 1st sort
        cout << i+1 << ". " << "movieTitle " << "rating" << endl; //print movie title and rating, would be i-1 in vector
    }
    cout << "Time sort 1: " << endl;
    cout << endl;

    //print 2nd sort... or since they should be the same, just the second sort's time(?)
    for(int i=0; i<x; i++){
        cout << i+1 << ". " << "movieTitle " << "rating" << endl; //print movie title and rating, would be i in vector
    }
    cout << "Time sort 2: " << endl;



    return 0;
}
