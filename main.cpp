#include <iostream>
#include "Movie.h"
using namespace std;

//sort 1 function header
//sort 2 function header

int main() {
//---------------------------------------------------------------------------------------------------------
//Part 1: User input
    //(maybe) ask user top x movie list
    cout << "Welcome to the Greatest Films of All Time Finder!" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Type in how many top movies you would like to see: [1-100]" << endl;
    int x;
    cin >> x;
    //check for bounds validity
    while(x<0 || x>100){
        cout << "Try again, this time with a number between 1 and 100:" << endl;
        cin >> x;
    }

//---------------------------------------------------------------------------------------------------------
//Part 2
    //read through the dataset and create the movie, avg rating pairs- we could create a movie class so we
    //could overload the comparator operators, which may make sorting easier.
    //oooh you know if we did that class we could store a "totalRatings" and "numRatings" so that the average
    //is just totalRatings/numRatings, and this way if there's a rating for a movie in a non-concecutive part
    //of the dataset, we can still find the average pretty quickly.
    Movie test1("Movie", 100.0);
    Movie test2("bad movie", 25.0);
    /*if(test1>test2){
        cout << test1.getTitle() << " is better than " << test2.getTitle() << endl;
    }
    else if(test1 < test2){
        cout << test2.getTitle() << " is better than " << test1.getTitle() << endl;
    }
    else if(test1 == test2){
        cout << test1.getTitle() << " is the same movie as " << test2.getTitle() << endl;
    }*/


    ///important!! read this!!
    //if you guys think this is fair we could divide this project up like 1 person does part2(finding averages,
    //making the movie class), 1 person does sort1, and 1 person does sort2. I'm not sure how even that would be
    //but it might be a good division.


//---------------------------------------------------------------------------------------------------------
//Part 3
    //clone vector and perform 2 different sorts. time them(gotta figure out how to do that)


//---------------------------------------------------------------------------------------------------------
//Part 4
    //print out top x based on user input(speaking of, should we ask for this before going through the set
    //or after? i think if we ask at the beginning, it would work better because any possible pause while
    //sifting through the dataset would happen after the prompt rather than before it.

    cout << "Top " << x << " Best Films" << endl;
    //print 1st sort
    for(int i=0; i<x; i++){
        cout << i+1 << ". " << "movieTitle " << "rating" << endl; //print movie title and rating, would be i in vector
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


//sort 1 function:

//sort 2 function: