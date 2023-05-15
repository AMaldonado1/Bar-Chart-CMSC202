/***********************************************************
 ** File:    Bar.cpp
 ** Project: CMSC 202 - Project 5
 ** Author:  Adrian Maldonado
 ** Email:   amaldon1@umbc.edu
 ** Date     4/25/2023
 ** Section: 11
 ** This file contains the definition cpp file of the Bar class
 **********************************************************/
#include "Bar.h"

// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar()
{
    m_data = new LL<string>();
    m_fileName = "test.txt";
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename)
{
    m_data = new LL<string>();
    m_fileName = filename;
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar()
{
    delete m_data;
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start()
{
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    DisplayBars();
    Export();
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile()
{
    // Makes variables for the total amount of words read
    int totalWords = 0;
    // Variables for the single word and the complete line strings
    string word;
    // Makes the stream and opens the file
    ifstream dataFile(m_fileName);
    if (dataFile.is_open())
    {
        // Loops through the stream that contains all the words
        while (dataFile >> word)
        {
            // Stops at every space or new line and removes punctuation
            RemovePunct(word);
            // Increases word count
            totalWords++;
            // Adds word to linked list
            m_data->Insert(word);
        }
        cout << totalWords << " words loaded." << endl;
        // Success on opening the file then closing it
        dataFile.close();
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
    return;
}

// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string &word)
{
    // Removes the first character if it is punctuation
    if (ispunct(word.front()))
    {
        word.erase(0, 1);
    }
    // Removes the last character if it is punctuation
    if (ispunct(word.back()))
    {
        word.pop_back();
    }
    // Loop through the string using iterators
    for (auto it = word.begin(); it != word.end(); ++it)
    {
        // Convert every character to lowercase one by one
        *it = tolower(*it);
    }
}

// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon()
{
    // Creates a flag boolean to check for user validation
    bool isValid = false;
    // Creates user input string for validation
    string remove;
    // Continue to ask user until given valid input
    while (!isValid)
    {
        cout << "Would you like to remove all common words (Only use with essays)?" << endl;
        cin >> remove;
        // If user input is yes
        if ((remove == "yes") || (remove == "y"))
        {
            remove = "y";
            isValid = true;
        }
        // If user input is no
        else if ((remove == "no") || (remove == "n"))
        {
            remove = "n";
            isValid = true;
        }
        // If user input is invalid
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
    // If user declines to remove words
    if (remove == "n")
    {
        return;
    }
    // Loops through all the excluded words
    for (vector<string>::const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); ++it)
    {
        // Loops through all the words in the linked list
        for (int i = 0; i < m_data->GetSize(); ++i)
        {
            // If any element in the linked list is in the excluded words list
            if ((*m_data)[i].first == *it)
            {
                // Removes that element from the linked list
                m_data->RemoveAt((*m_data)[i].first);
            }
        }
    }
    cout << "All common words removed." << endl;
}

// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles()
{
    // Creates a flag boolean to check for user validation
    bool isValid = false;
    // Creates user input string for validation
    string remove;
    // Continue to ask user until given valid input
    while (!isValid)
    {
        cout << "Would you like to remove all words with a frequency of 1?" << endl;
        cin >> remove;
        // If user input is yes
        if ((remove == "yes") || (remove == "y") || (remove == "Y") || (remove == "YES"))
        {
            remove = "y";
            isValid = true;
        }
        // If user input is no
        else if ((remove == "no") || (remove == "n"))
        {
            remove = "n";
            isValid = true;
        }
        // If user input is invalid
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
    // If user declines to remove words
    if (remove == "n")
    {
        return;
    }
    int wordsRemoved = 0;
    // Loops through all the words in the linked list
    for (int i = 0; i < m_data->GetSize();)
    {
        // If the frequency of the words is only 1
        if ((*m_data)[i].second == 1)
        {
            // Removes that element from the linked list
            m_data->RemoveAt((*m_data)[i].first);
            wordsRemoved++;
            // Sets i to 0 to not skip any more words
            i = 0;
        }
        // If the frequency of the words is not 1 then i is increased to check the next ones
        else
        {
            i++;
        }
    }
    cout << wordsRemoved << " words removed." << endl;
}

// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData()
{
    // Loops through all items in m_data
    for (int i = 0; i < m_data->GetSize(); i++)
    {
        // Makes a new pair with number as the key and word as the value
        pair<int, string> sortPair = make_pair((*m_data)[i].second, ((*m_data)[i].first));
        // Puts that new key into the multi map
        m_dataSorted.insert(sortPair);
    }
}

// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars()
{
    int largestWord = 0;
    // Loop through all items in the linked list
    for (int i = 0; i < m_data->GetSize(); i++)
    {
        // Looks for the longest word and sets its length to largestWord
        if ((int)(*m_data)[i].first.size() > largestWord)
        {
            largestWord = (*m_data)[i].first.size();
        }
    }
    // Sets the column width to largest word plus 2 more spaces
    int columnSpace = largestWord + 2;
    // Loops through all the elements in the multi-map reversed
    for (multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); it++)
    {
        // Prints out space and the word
        cout << setw(columnSpace) << right << it->second << ": ";
        // Loops through all the word frequency and prints out * for each one
        for (int i = 0; i < (int)it->first; i++)
        {
            cout << barChar;
        }
        cout << endl;
    }
}

// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export()
{
    // Declaring the name of the file and the stream name
    string fileName;
    ofstream fileOut;
    // Asks user what name the export file should be called
    cout << "What would you like to call the export file?" << endl;
    cin >> fileName;
    cout << "Output to exportFile " << fileName << endl;
    // Makes the new file with the file name
    fileOut.open(fileName);
    // Does same as Display Bars but adds it to the fstream to export
    int largestWord = 0;
    // Loop through all items in the linked list
    for (int i = 0; i < m_data->GetSize(); i++)
    {
        // Looks for the longest word and sets its length to largestWord
        if ((int)(*m_data)[i].first.size() > largestWord)
        {
            largestWord = (*m_data)[i].first.size();
        }
    }
    // Sets the column width to largest word plus 2 more spaces
    int columnSpace = largestWord + 2;
    // Loops through all the elements in the multi-map reversed
    for (multimap<int, string>::reverse_iterator it = m_dataSorted.rbegin(); it != m_dataSorted.rend(); it++)
    {
        // Prints out space and the word
        fileOut << setw(columnSpace) << right << it->second << ": ";
        // Loops through all the word frequency and prints out * for each one
        for (int i = 0; i < (int)it->first; i++)
        {
            fileOut << barChar;
        }
        fileOut << endl;
    }
}
