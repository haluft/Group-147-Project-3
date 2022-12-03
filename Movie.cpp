#include "Movie.h"

Movie::Movie(string movTitle, double score){
    title=movTitle;
    totalScores=score;
    numReviews=1;
    avgScore = totalScores/numReviews;
}

void Movie::updateScore(double score) {
    totalScores+=score;
    numReviews++;
    avgScore = totalScores/numReviews;
}

double Movie::getAvgScore() const{ //this should be const but i forget correct place to put it
    return avgScore;
}

string Movie::getTitle() const {
    return title;
}

bool Movie::isEqual(const Movie &rhs) {
    if(this->avgScore == rhs.avgScore){
        return true;
    }
    return false;
}
bool Movie::operator==(const Movie &rhs) {
    //two movies are equal if they have the same title... might have to have two equal functions, 1 for title and 1 for ratings
    if(this->title == rhs.title){
        return true;
    }
    return false;
}

bool Movie::operator>(const Movie &rhs) {
    //a movie is greater than another if it has a higher rating. If ratings are equal, go by alphabetical order
    if(this->avgScore > rhs.avgScore){
        return true;
    }
    else if(this->avgScore < rhs.avgScore){
        return false;
    }
   /* else{
        //avg ratings are equal, check for alphebetical order.
        int index=0;
        while(index != this->title.size() && index != rhs.title.size()){
            if(this->title[index] < rhs.title[index]){
                return true;
            }
            else if(this->title[index] > rhs.title[index]){
                return false;
            }
            else{
                index++;
            }
        }
        if(this->title.size() < rhs.title.size()){
            return true; //this is when one is like "Home" and the other is "Home Alone", "Home" should go first
        }
        else{
            return false;
        }
    }*/
}

bool Movie::operator<(const Movie &rhs) {
    //a movie is less than another if it has a lower rating. If ratings are equal, go by alphabetical order
    if(this->avgScore < rhs.avgScore){
        return true;
    }
    else if(this->avgScore > rhs.avgScore){
        return false;
    }
    /*else{
        //avg ratings are equal, check for alphabetical order. (later in alphabet will be the greater one)
        int index=0;
        while(index != this->title.size() && index != rhs.title.size()){
            if(this->title[index] < rhs.title[index]){
                return false;
            }
            else if(this->title[index] > rhs.title[index]){
                return true;
            }
            else{
                index++;
            }
        }
        if(this->title.size() < rhs.title.size()){
            return false; //this is when one is like "Home" and the other is "Home Alone", "Home" should go first(as greater than)
        }
        else{
            return true;
        }
    }*/
}