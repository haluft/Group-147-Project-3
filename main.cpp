#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <chrono>
#include "Movie.h"
using namespace std;
///some info:
/* 1. so for some reason if we add any more files/classes, we have to update the Cmakefile manually.
 * 2. pls read all the comments sometimes i ask questions about how y'all would prefer to implement smth so getting
 *    feedback would be great. you guys can do the same thing i'll read any new comments/changes
 * 3. run the code on your computer! i usually only ever commit code that runs and its a good way to test as we go
 *    and see how what we already have works. right now you can see two test movies i created and some comparisons.
 */

/*
 * Pancake Sort Citation: https://www.geeksforgeeks.org/sorting-algorithms/, https://www.geeksforgeeks.org/pancake-sorting/
 * Heap Sort Citation: Module 5 lecture slides and Stepik solutions (Module6_Solution PDF)
 */

void readDataset(vector<Movie>& movies, ifstream& dataset, int maxIndex);

//sort 1 function header

//sort 2 function header
void pancakeSort(vector<Movie>& movies);

//sort 3 function header
void heapSort(vector<Movie>& movies, int size);


int main() {
//---------------------------------------------------------------------------------------------------------
//Part 1: User input
    //ask user top x movie list
    //to access super secret developer controls, use this password after typing in 147 when asked for how
    //many movies to see
    string password = "deservesAnA";
    int maxIndex;
    bool developerControls=false;

    cout << "Welcome to the Greatest Films of All Time Finder!" << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Type in how many top movies you would like to see:" << endl;
    cout << "[1-100]" << endl;
    int x;
    cin >> x;

    //check input for bounds and for secret developer access
    string inPass;
    bool correct=true;
    if(x == 147){
        cin >> inPass;
        if(inPass == password){
            developerControls = true;
            cout << "Developer Mode Activated" << endl;
            cout << "Welcome, Group 147" << endl;
        }
        else{
            correct = false;
        }
    }
    if(x != 147 || !correct){
        //check if within bounds
        while(x<1 || x>100){
            cout << "Try again, this time with a number between 1 and 100:" << endl;
            cin >> x;
        }
        maxIndex = 100000;
    }

    /* if you typed in 147, then the password "deservesAnA", you now have access to developer controls
     * which give you more control over how many movies to display and how many rows to read.
     * 2106 rows=100 movies for the first time, min if you want at least 100 movies.
     * 100th movie is Violet-only 1 review at that point(more later in set)
     */
    if(developerControls) {
        cout << endl;
        cout << "How many top movies would you like to see?" << endl;
        cout << "[1-9366]" << endl;
        cin >> x;
        cout << "How many rows should I parse through?" << endl;
        cout << "[100-400000 or 0 for all]" << endl;
        cin >> maxIndex;
        if (maxIndex == 0) {
            maxIndex = 999999;
        }
        else {
            while (maxIndex < 100 || maxIndex > 400000) {
                cout << "Try again, this time with a number between 100 and 40000:" << endl;
                cin >> maxIndex;
                if (maxIndex == 0) {
                    maxIndex = 999999;
                    break;
                }
            }
        }
    }

//---------------------------------------------------------------------------------------------------------
//Part 2
    //read through the dataset to create the movie objects and put them in a vector.
    //Note:  this takes a while to run through all 421492 reviews so be patient. To reduce time use developer
    //       mode
    //Testing: there is a test section you can uncomment that is real simple. If you do that, comment out the
    //       section where it reads the dataset so testing can run a lot faster, otherwise you'll be sitting at
    //       your computer waiting for it to go through the entire dataset every time.

    vector<Movie> movies;
    //reading dataset:
    //in order to open this on your computer make sure clion knows what directory to find it in on your computer
    //!!!if you comment out this section, you also have to comment out the line at the bottom that prints the time for this

    //open csv
    ifstream dataset;
    dataset.open("rottentomatoes-400k.csv");
    if(!dataset.is_open()){
        cout << "It failed to open." << endl;
    }

    //read it
    auto start = chrono::high_resolution_clock::now();
    readDataset(movies, dataset, maxIndex);
    auto stop = chrono::high_resolution_clock::now();
    auto readDuration = chrono::duration_cast<chrono::microseconds>(stop-start);

    //close csv
    dataset.close();

    /*
    //testing functionality. un-comment this and comment the reading the dataset section to test faster
    Movie test1("Movie", 100.0);
    Movie test2("bad movie", 25.0);
    Movie test3("Movie", 78.0);
    Movie test4("PRECIOUS: BASED ON THE NOVEL \"PUSH\" BY SAPPHIRE", 67.5);
    test1.updateScore(37.0);
    movies.push_back(test1);
    movies.push_back(test2);
    movies.push_back(test3);
    movies.push_back(test4);

    if(test1>test2){
        cout << test1.getTitle() << " is better than " << test2.getTitle() << endl;
    }
    else if(test1 < test2){
        cout << test2.getTitle() << " is better than " << test1.getTitle() << endl;
    }
    if(test1 == test3){
        cout << test1.getTitle() << " is the same movie as " << test2.getTitle() << endl;
    }*/



//---------------------------------------------------------------------------------------------------------
//Part 3
    //clone vector and perform 2 different sorts. time them

    vector<Movie> moviescopy = movies;

    auto startSort2 = chrono::high_resolution_clock::now();
    pancakeSort(movies);
    auto stopSort2 = chrono::high_resolution_clock::now();
    auto sort2Duration = chrono::duration_cast<chrono::microseconds>(stopSort2-startSort2);

    auto startSort3 = chrono::high_resolution_clock::now();
    heapSort(moviescopy, movies.size());
    auto stopSort3 = chrono::high_resolution_clock::now();
    auto sort3Duration = chrono::duration_cast<chrono::microseconds>(stopSort3-startSort3);


//---------------------------------------------------------------------------------------------------------
//Part 4
    //print out top x based on user input
    cout << fixed << setprecision(2);
    cout << "-------------------------------------------------" << endl;
    cout << "                 Top " << x << " Best Films" << endl;
    cout << "-------------------------------------------------" << endl;
    for(int i=0; i<x; i++){
        //need this for just in case asked for more than in vector
        if(i == movies.size()){
            break;
        }
        //print movie title and rating
        string num = to_string(i+1);
        num+=".";
        cout << setw(4)<< left << num;
        if(movies.at(i).getTitle().size() > 35){
            cout << movies.at(i).getTitle().substr(0,35) << "-" << endl;
            string second = movies.at(i).getTitle().substr(35);
            if(second.size() > 35){
                cout << "    " << second.substr(0,35) << "-" << endl;
                cout << "    " << setw(40) << left << second.substr(35);
            }
            else{
                cout << "    " << setw(40) << left << movies.at(i).getTitle().substr(35);
            }
        }
        else{
            cout << setw(40) << left << movies.at(i).getTitle();
        }
        cout << setw(8) << left << movies.at(i).getAvgScore() << endl;
    }

    /*
    //TEMPORARY PRINTING TO CHECK HEAPSORT
    cout << fixed << setprecision(2);
    cout << "-------------------------------------------------" << endl;
    cout << "                 Top " << x << " Best Films" << endl;
    cout << "-------------------------------------------------" << endl;
    //print 1st sort
    for(int i=0; i<x; i++){
        //need this for test... shouldn't be necessary when considering the full vector is 9366 values
        if(i == moviescopy.size()){
            break;
        }
        //print movie title and rating
        string num = to_string(i+1);
        num+=".";
        cout << setw(4)<< left << num;
        if(moviescopy.at(i).getTitle().size() > 35){
            cout << moviescopy.at(i).getTitle().substr(0,35) << "-" << endl;
            cout << "    " << setw(40) << left << moviescopy.at(i).getTitle().substr(35);
        }
        else{
            cout << setw(40) << left << moviescopy.at(i).getTitle();
        }
        cout << setw(8) << left << moviescopy.at(i).getAvgScore() << endl;


    }
    cout << endl;*/

    cout << endl;
    cout << "Time to read: " << readDuration.count() << " microseconds" << endl;
    cout << endl;
    cout << "Time for Merge Sort: " << endl;
    cout << "Time for Pancake Sort: " << sort2Duration.count() << " microseconds" << endl;
    cout << "Time for Heap Sort: " << sort3Duration.count() << " microseconds" << endl;
    cout << endl;

    cout << "Number of movies: " << movies.size() << endl; //gives 9366 for full dataset

    return 0;
}

void readDataset(vector<Movie>& movies, ifstream& dataset, int maxIndex){
    string header;
    getline(dataset, header);
    int index=0;
    while(!dataset.eof() && index<maxIndex){ //421492 reviews
        //read line and store the movie's title and rating. check the movie vector for if the movie is already in there
        //if movie already is in there, simply update the rating

        //index. just an int
        string discard;
        getline(dataset, discard, ',');

        /* This dataset has some annoying qualities. It only puts quotes around an element if there's something
         * odd inside it, which could be another comma, quotation marks in it, or a new line in it. I got it to work,
         * but there are some things that... aren't perfect
         */
        string title; //title in the dataset is in all caps... kinda annoying but changing it would add so much time
        getline(dataset, title, ',');
        if(title[0]=='"'){ //this means there's commas OR quotes. terrible
            //there were quotes which means there is a comma in the title. remove it, add the comma back, and keep going to next quote
            //quote culprits: "THE BIG SCARY ""S"" WORD" -> THE BIG SCARY ""S"" WORD",Jeffrey M. Anderson,Common Sense Media,
            //"J.R. ""BOB"" DOBBS & THE CHURCH OF THE SUBGENIUS"->J.R. ""BOB"" DOBBS & THE CHURCH OF THE SUBGENIUS",Steve Davis,Austin Chronicle,
            //"PRECIOUS: BASED ON THE NOVEL ""PUSH"" BY SAPPHIRE"->PRECIOUS: BASED ON THE NOVEL ""PUSH"" BY SAPPHIRE",Linda Cook,

            title = title.substr(1);
            title += ",";
            string secondhalf;
            getline(dataset, secondhalf, '"');
            title += secondhalf;
            //now grab that commma
            getline(dataset, discard, ',');

            if(title.find("\"\"") != string::npos){
                //this is one of the three quote culprits
                size_t found = title.find(',');
                title = title.substr(0, found-1);
            }
        }

        //these are the troublesome reviews that have new lines in them. I just hardcoded them in.
        getline(dataset, discard);
        if(index==3523 || index==70757 || index == 280972 || index == 291141 || index==300779 || index==323169 || index==354625 || index==396929 || index==402883){
            //these are "Full Reviews", 3523 is "uncut gems", 70757 is "lu over the wall", 280972 is "wreck it ralph", 291141 is "lawless"(291770 real), 300779 is "the hunger games"(301530 real), 323169 is "one day"(324239), 354625 is "best worst movie"(356225), 396929 is "the spirit"(400458 real), 402883 is "amal"(406713)
            getline(dataset, discard);
            getline(dataset, discard);
        }
        if(index==408785 || index==413332){
            //408785 is "the happening"(412866), 413332 is "the duchess of langeais"(417625). they have one new line
            getline(dataset, discard);
        }

        string score;
        //go backwards til find a comma
        int commaIndex=discard.size()-1;
        while(discard[commaIndex] != ','){
            commaIndex--;
        }
        score = discard.substr(commaIndex+1);

        //have all we need, put it in the vector:
        Movie test(title, stod(score));
        //check if already in the vector:
        auto iter = find(movies.begin(), movies.end(), test);
        if(iter != movies.end()){
            iter->updateScore(test.getAvgScore()); //this works because the default avg score will be the 1 review
        }
        else{
            movies.push_back(test);
        }

        if(index==417010){
            //(real index=421492). looks like there's an empty line at the bottom of the dataset, so it doesn't realize it reached the end
            break;
        }
        index++;
    }
    //The last index does not correspond to the index it says because there are actually ~416000 unique reviews, but
    //about 421000 lines. It does add every movie,as confirmed by checking the vector size(9366, which is the number
    //of unique movies in the dataset), and that's what's important.
}

//sort 1 function:

//sort 2 functions:
//finds the minimum value of the sub-vector
int findMin(vector<Movie>& movies, int lastIndex)
{
    int min = 0;
    Movie highestRating("", 100.0);
    for (int i = 0; i <= lastIndex; i++) {
        if (movies.at(i).getAvgScore() < highestRating.getAvgScore())
        {
            min = i;
            highestRating = movies.at(i);
        }
    }
    return min;
}

//moves the smallest value to front
void pancakeFlip(vector<Movie>& movies, int index)
{
    Movie temp("", 0.0);
    while (index > 0)
    {
        temp = movies.at(index-1);
        movies.at(index-1) = movies.at(index);
        movies.at(index) = temp;
        index--;
    }
}

//flips the pancake by finding the minimum value, moving it to the front of the "pancake stack" vector, and then flipping the pancake stack by reversing the vector
void pancakeSort(vector<Movie>& movies)
{
    int firstIndex = 0;
    int lastIndex = movies.size()-1;
    while (firstIndex < lastIndex) {
        int min = findMin(movies, lastIndex);

        //pancakeFlip and reverse() together count as the "flip of the pancake stack"
        pancakeFlip(movies, min);
        reverse(movies.begin(), movies.begin()+lastIndex+1);
        lastIndex--;
    }
}

//sort 3 Functions:
//implements heap data structure in order to test merge sort against the other two sorts

void heapify(vector<Movie>& movies, int size, int i)
{
    int min = i;
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;

    if (l < size && movies.at(l).getAvgScore() < movies.at(min).getAvgScore())
    {
        min = l;
    }

    if (r < size && movies.at(r).getAvgScore() < movies.at(min).getAvgScore())
    {
        min = r;
    }

    if (min != i)
    {
        swap(movies.at(i), movies.at(min));
        heapify(movies, size, min);
    }
}

//builds the heap in-place using the movies vector and the heapify function
void buildHeap(vector<Movie>& movies, int size)
{
    for (int i = (size/2)-1; i >= 0; i--)
    {
        heapify(movies, size, i);
    }
}

//actual sort function that builds the heap and then sorts the vector into descending order
void heapSort(vector<Movie>& movies, int size)
{
    buildHeap(movies, size);
    for (int i = (size - 1); i >= 0; i--)
    {
        swap(movies.at(0), movies.at(i));
        heapify(movies, i, 0);
    }
}