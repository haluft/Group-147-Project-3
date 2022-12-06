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

double Movie::getAvgScore() const{
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
}

bool Movie::operator<(const Movie &rhs) {
    //a movie is less than another if it has a lower rating. If ratings are equal, go by alphabetical order
    if(this->avgScore < rhs.avgScore){
        return true;
    }
    else if(this->avgScore > rhs.avgScore){
        return false;
    }
}

// For merge sort:

bool Movie::operator<=(const Movie &rhs){
    // a movie is less or equal than another if it has a lower or equal rating.
    if(this->avgScore < rhs.avgScore || this->avgScore == rhs.avgScore){
        return true;
    }
    else if(this->avgScore > rhs.avgScore){
        return false;
    }
}

bool Movie::operator>=(const Movie &rhs) {
    //a movie is greater or equal than another if it has a higher or equal rating.
    if(this->avgScore > rhs.avgScore || this->avgScore == rhs.avgScore){
        return true;
    }
    else if(this->avgScore < rhs.avgScore){
        return false;
    }
}