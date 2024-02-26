// Author: Aayush Keshari
// Email: kesharah@mail.uc.edu
// ------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>

const int MAX_MOVIES = 10; // Global constant for the maximum number of movies

class Movie {
public:
    std::string title;
    int year;

    Movie(const std::string& t, int y) : title(t), year(y) {}
};

class MovieShelf {
private:
    Movie* movies[MAX_MOVIES];
    int numMovies;

public:
    MovieShelf() : numMovies(0) {
        for (int i = 0; i < MAX_MOVIES; ++i) {
            movies[i] = nullptr;
        }
    }

    void add(Movie* movie) {
        if (numMovies < MAX_MOVIES) {
            movies[numMovies++] = movie;
            std::cout << "Movie added: " << movie->title << " (" << movie->year << ")" << std::endl;
        }
        else {
            throw FullShelf();
        }
    }

    Movie* remove() {
        if (numMovies > 0) {
            Movie* removedMovie = movies[--numMovies];
            movies[numMovies] = nullptr;
            std::cout << "Movie removed: " << removedMovie->title << " (" << removedMovie->year << ")" << std::endl;
            return removedMovie;
        }
        else {
            throw EmptyShelf();
        }
    }

    int getNumMovies() const {
        return numMovies;
    }

    class FullShelf {}; // Exception class for full shelf
    class EmptyShelf {}; // Exception class for empty shelf
};

int main() {
    MovieShelf shelf;

    while (true) {
        std::cout << "Press 1 to add a movie to the shelf." << std::endl;
        std::cout << "Press 2 to remove a movie from the shelf." << std::endl;
        std::cout << "Press 3 to see how many movies are currently on the shelf." << std::endl;
        std::cout << "Press 4 to quit." << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string title;
            int year;
            std::cout << "Enter the movie title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter the release year: ";
            std::cin >> year;
            Movie* newMovie = new Movie(title, year);
            try {
                shelf.add(newMovie);
            }
            catch (const MovieShelf::FullShelf&) {
                std::cerr << "Error: Shelf is full. Cannot add more movies." << std::endl;
            }
            break;
        }
        case 2: {
            try {
                Movie* removedMovie = shelf.remove();
                delete removedMovie; // Free the memory of the removed movie
            }
            catch (const MovieShelf::EmptyShelf&) {
                std::cerr << "Error: Shelf is empty. Cannot remove a movie." << std::endl;
            }
            break;
        }
        case 3:
            std::cout << "Number of movies on the shelf: " << shelf.getNumMovies() << std::endl;
            break;
        case 4:
            return 0;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}