#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Movie.h"
using namespace std;
///some info:
/* 1. so for some reason if we add any more files/classes, we have to update the Cmakefile manually.
 * 2. pls read all the comments sometimes i ask questions about how y'all would prefer to implement smth so getting
 *    feedback would be great. you guys can do the same thing i'll read any new comments/changes
 * 3. run the code on your computer! i usually only ever commit code that runs and its a good way to test as we go
 *    and see how what we already have works. right now you can see two test movies i created and some comparisons.
 */

void readDataset(vector<Movie>& movies, ifstream& dataset);

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
    //read through the dataset to create the movie objects and put them in a vector.
    //Note:  this takes a while to run through all 421492 reviews so be patient. To reduce time we could
    //       tell it to stop after it read through 100,000 lines just because that still meets the requirement.
    //Idea: we take an input of how many lines of the dataset we want to run through. would reduce time when
    //      we want but can still show that it can handle all 400,000 tuples
    //Testing: there is a test section you can uncomment that is real simple. If you do that, comment out the
    //       section where it reads the dataset so testing can run a lot faster, otherwise you'll be sitting at
    //       your computer waiting for it to go through the entire dataset every time.


    ///important!! read this!!
    //if you guys think this is fair we could divide this project up like 1 person does part2(finding averages,
    //making the movie class), 1 person does sort1, and 1 person does sort2. I'm not sure how even that would be
    //but it might be a good division.


    vector<Movie> movies;
    //reading dataset:
    //in order to open this on your computer make sure clion knows what directory to find it in on your computer


    //open csv
    ifstream dataset;
    dataset.open("rottentomatoes-400k.csv");
    if(!dataset.is_open()){
        cout << "It failed to open." << endl;
    }

    //read it
    readDataset(movies, dataset);

    //close csv
    dataset.close();

    //testing functionality. un-comment this and comment the reading the dataset section to test faster
    /*Movie test1("Movie", 100.0);
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
    //clone vector and perform 2 different sorts. time them(gotta figure out how to do that)


//---------------------------------------------------------------------------------------------------------
//Part 4
    //print out top x based on user input(speaking of, should we ask for this before going through the set
    //or after? i think if we ask at the beginning, it would work better because any possible pause while
    //sifting through the dataset would happen after the prompt rather than before it.)

    cout << fixed << setprecision(2);
    cout << "-------------------------------------------------" << endl;
    cout << "                 Top " << x << " Best Films" << endl;
    cout << "-------------------------------------------------" << endl;
    //print 1st sort
    for(int i=0; i<x; i++){
        //need this for test... shouldn't be necessary when considering the full vector is 9366 values
        if(i == movies.size()){
            break;
        }
        //print movie title and rating
        string num = to_string(i+1);
        num+=".";
        cout << setw(4)<< left << num;
        if(movies.at(i).getTitle().size() > 35){
            cout << movies.at(i).getTitle().substr(0,35) << "-" << endl;
            cout << "    " << setw(40) << left << movies.at(i).getTitle().substr(35);
        }
        else{
            cout << setw(40) << left << movies.at(i).getTitle();
        }
        cout << setw(8) << left << movies.at(i).getAvgScore() << endl;


    }
    cout << endl;
    cout << "Time sort 1: " << endl;
    cout << endl;
    cout << "Time sort 2: " << endl;

    //print 2nd sort... or since they should be the same, just the second sort's time(?)
    /*for(int i=0; i<x; i++){
        cout << i+1 << ". " << movies.at(i).getTitle() << " " << movies.at(i).getAvgScore() << endl; //print movie title and rating, would be i in vector
        if(i == movies.size()-1){
            break;
        }
    }*/


    cout << "Number of movies: " << movies.size() << endl; //gives 9366, which is the correct amount! the reading function works!

    return 0;
}

void readDataset(vector<Movie>& movies, ifstream& dataset){
    string header;
    getline(dataset, header);
    int index=0;
    while(!dataset.eof()){ //421492 reviews
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

        //these are the troublesome reviews that have enters in them. I just hardcoded them in I might find a better
        //way later if i have time
        getline(dataset, discard);
        if(index==3523 || index==70757 || index == 280972 || index == 291141 || index==300779 || index==323169 || index==354625 || index==396929 || index==402883){
            //these are "Full Reviews", 3523 is "uncut gems", 70757 is "lu over the wall", 280972 is "wreck it ralph", 291141 is "lawless"(291770 real), 300779 is "the hunger games"(301530 real), 323169 is "one day"(324239), 354625 is "best worst movie"(356225), 396929 is "the spirit"(400458 real), 402883 is "amal"(406713)
            getline(dataset, discard);
            getline(dataset, discard);
        }
        if(index==408785 || index==413332){
            //this one was just weird. 408785 is "the happening"(412866), 413332 is "the duchess of langeais"(417625). they have one new line
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
            //(real index=421492). looks like theres an empty line at the bottom of the dataset, so it doesn't realize it reached the end
            break;
        }
        index++;
    }
    //don't ask me why the index doesn't line up with the real index, I have no idea. It does add every movie,
    //as confirmed by checking the vector size(9366, which is the number of unique movies in the dataset), so
    //I don't know why it's different
}

//sort 1 function:

//sort 2 function: