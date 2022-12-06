#ifndef GROUP_147_PROJECT_3_MOVIE_H
#define GROUP_147_PROJECT_3_MOVIE_H
#include <string>
using namespace std;

class Movie {
    string title;
    double avgScore;
    double totalScores;
    double numReviews;
public:
    Movie(string movTitle, double score);

    void updateScore(double score);

    double getAvgScore() const;
    string getTitle() const;


    bool isEqual(const Movie& rhs);
    bool operator==(const Movie& rhs);
    bool operator<(const Movie& rhs);
    bool operator>(const Movie& rhs);

    // For merge sort:
    bool operator<=(const Movie &rhs);
    bool operator>=(const Movie &rhs);
};


#endif //GROUP_147_PROJECT_3_MOVIE_H
