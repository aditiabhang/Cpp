#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

struct Song {
    string id;                          //unique id of the song
    string title;                       //title name of the song
    string artist;                      //artist name of the song
    float size;                         //song size in MB
    int plays;                          //number of times the song played
    int ratings;                        //rating of the song
};

const int max_library_size = 100;       //size of the library

//functions declaration
void openLibrary(Song[], int &size);
void displayLibrary(Song[], int size);
int searchById(Song[], int size, string id);
int searchByTitleArtist(Song[], int size, string title, string artist);
void sortBytitle(Song[], int size);
void sortByRating(Song[], int size);
void sortById(Song[], int size);


// Driver program
int main() {
    Song library[max_library_size];
    int size;

    openLibrary(library, size);

    int choice;     //menu choice asked from user
    int index;      //index in the library
    string title;   //input title asked from user
    string artist;  //input artist asked from user
    string id;      //input id asked from user

    do{
        //displaying the menu to the user and asking for the choice of option
        cout << "\nMenu\n\n";
        cout << "1. Display songs sorted by song title.\n";
        cout << "2. Display songs sorted by song/'s ratings.\n";
        cout << "3. Find song/'s title and artist name using ID.\n";
        cout << "4. Find song/'s ID using song title and artist name.\n";
        cout << "5. Exit from the music library.\n\n";
        cout << "Enter your choice. ";
        cin >> choice;

        //validate the menu selection
        while(choice < 1 || choice > 5) {
            cout << "Please select a valid option from above. ";
            cin >> choice;
        }

        //respond to the user's selection
        switch (choice)
        {
        case 1:
            sortBytitle(library, size);
            displayLibrary(library, size);
            break;
        case 2:
            sortByRating(library, size);
            displayLibrary(library, size);
            break;
        case 3:
            cout << "Please enter the ID for the song you wish to find: ";
            cin >> choice;
            cout << endl;
            index = searchById(library, size, id);
            if(index != 1){
                cout << "The song with the ID " << id << " is: " << endl;
                cout << library[index].title << " performed by " << library[index].artist << endl;
            }
            else 
                cout << "No song with given ID was found in the music library." << endl;
            break;
        case 4:
            cout << "Enter the song Title you wish to search: ";
            cin >> ws;
            getline(cin, title);
            cout << "What is the artist name of this song?";
            getline(cin, artist);
            cout << endl;

            index = searchByTitleArtist(library, size, title, artist);
            if(index != 1){
                cout << "The ID of " << title << " performed by " << artist << " is " << library[index].id << endl;
            }
            else 
                cout << "No song with given title and artist found in the music library. " << endl;
            break;
        case 5:
            cout << "Exiting the program.." << endl;
            cout << "Bye." << endl;
            break;
        }
    } while(choice != 5);
}
//*************************************************************************//
// openLibrary() - reads all the songs from the file library.txt. into the 
// array. Assigns the number of songs to size parameter. Assumes there are no
// more than 100 songs in the file, and the id, title, artist are on the 
// separate lines. 
// lib - array of songs.
// size - number of elements in the array.
//*************************************************************************//
void openLibrary(Song lib[], int &size) {
    size = 0;
    ifstream in("Library.txt.rtf");
    Song song;                      //to store the next song read from the file

    //get the next unread Song from the file
    while(in >> song.id) {
        in >> ws;
        getline(in, song.title);
        in >> ws;
        getline(in, song.artist);
        in >> song.size >> song.plays >> song.ratings;
        //put the song into the array at the next free place
        lib[size] = song;
        ++size;
    }
    in.close();
}

//*************************************************************************//
// displayLibrary() - Displays the library of songs to the user in a table
// form. 
// lib - array of songs
// size - number of songs in the library
//*************************************************************************//
void displayLibrary(Song lib[], int size) {
    cout << endl;
    for(int i = 0; i < size; ++i) {
        cout << left << setw(25) << lib[i].title << " " << setw(20) <<
        lib[i].artist << right << setw(6) << lib[i].size << " MB" << 
        setw(6) << lib[i].plays << setw(6) << lib[i].ratings << endl;
    }
}
//*************************************************************************//
// searchById() - searching a particular song using ID. Implemented using
// binary search algorithm.
// lib - the array to search in
// size - number of elements in the array
// id - the particular id to search the song
// returns - the array's subscript in the id/value is found. Otherwise, returns
// -1 indicating that value/ id not found. 
//*************************************************************************//
int searchById(Song lib[], int size, string id) {
    //first make sure the array is in sorted order
    sortById(lib, size);

    int first = 0, last = size - 1, mid, position = -1;
    bool found = false;

    while(!found && first <= last) {
        mid = first + (last - first)/ 2;
        if(lib[mid].id == id){
            found = true;
            position = mid;
        }
        else if(id < lib[mid].id)       //continue to search to the left of the mid
            last = mid - 1;
        else                            //continue to search to the right of the mid
            last = mid + 1;
    }
    return position;
}
//*************************************************************************//
// searchByTitleArtist() - search a particular song on given song title
// and artist name. Implemented using linear search algorithm. 
// lib - array of songs
// size - size of the array of songs
// title - target title to find in the library array
// artist - target artist to find in the library array
// returns - the song which is found under the given title and artist,
// otherwise, returns -1.
//*************************************************************************//
int searchByTitleArtist(Song lib[], int size, string title, string artist) {
    for(int i = 0; i < size; i++)
        if(lib[i].title == title && lib[i].artist == artist)
        return i;
    return -1;
}
//*************************************************************************//
// sortByTitle() - sorts the library of songs by title. Implemented using bubble
// sort. 
// lib - array of songs library
// size - size of the song library array
//*************************************************************************//
void sortByTitle(Song lib[], int size){
    bool swap;
    do {
        swap = false;
        for(int i = 0; i < size; ++i){
            if(lib[i].title > lib[i+1].title){
                Song temp = lib[i];
                lib[i] = lib[i+1];
                lib[i+1] = temp;
                swap = true;
            }
        }
    }
    while(swap);
}
//*************************************************************************//
// sortByRating() - Sorts the library of songs based on the Ratings field.
// implemented using bubble sort algorithm.
// lib - array of library songs
// size - size of the library array
//*************************************************************************//
void sortByRating(Song lib[], int size){
    bool swap;
    do {
        swap = false;
        for (int i = 0; i < size; ++i){
            if(lib[i].ratings < lib[i+1].ratings){
                Song temp = lib[i];
                lib[i] = lib[i+1];
                lib[i+1] = temp;
                swap = true;
            }
        }
        
    } while(swap);
}
//*************************************************************************//
// sortById() - sorts the library array of songs on its ID's. Implemented 
// using bubble sort algorithm.
// lib - array of library songs
// size - size of the library array
//*************************************************************************//
void sortById(Song lib[], int size){
    bool swap;
    do {
        swap = false;
        for (int i = 0; i < size; ++i){
            if(lib[i].id < lib[i+1].id){
                Song temp = lib[i];
                lib[i] = lib[i+1];
                lib[i+1] = temp;
                swap = true;
            }
        }
        
    } while(swap);
}