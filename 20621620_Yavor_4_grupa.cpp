#include<iostream>          
#include<cmath>              
#include <cstring>           
#include<string>
#include <iomanip>
#include<fstream>
#include<stdio.h>
#include<array>

using namespace std;
const int N = 100;  //limits the array
const char Filename[] = "TURNIR.dat"; //file const for name

typedef struct competitors //defining structure
{   //using char to leave fields empty when information is missing in adding competitors
    int numInTournament;        //number in the current tournament
    char name[30];              //first name
    char surname[30];           //last name
    char country[30];           //country
    int numWorldRank;     //number in the World rank list
    int currentPoints;   //points in the current tournament
    int firstPlaces;      //won trophies ( 1st places only )
}competitor;

fstream fp; //file variable
//ifstram, ofstream

//prototypes of the functions used
competitor input();                                                     //structure for adding competitors
competitor inputUpdated(competitor arr[], int i);                       //structure for editing competitors information
void display(competitor arr[], int i);                                  //displays the entered data
void sortNumInTournament(competitor arr[], int n);                      //sorts by size according to the place in the tournament
void sortNumWorldRank(competitor arr[], int n);                         //sorts by size according to the place in the World rank list 
void sortFirstPlaces(competitor arr[], int n);                          //sorts by size according to the 1st places / won trophies 
void sortName(competitor arr[], int n);                                 //sorts by name 
int loadFile(competitor arr[]);                                         //loads binary file
void saveInFile(competitor arr[], int n);                               //saves binary file 
void addOneCompetitor(competitor arr[], int n);                         //adding ONE competitor in the tournament and append it
void addManyCompetitors(competitor arr[], int n);                       //adding N number competitors in the tournament and appends them       
void showAllcompetitors(competitor arr[], int n);                       //showing all competitors in the tournament sorted by number in the tournament
void lessTrophies(competitors arr[], int n);                            //showing the competitor with less won trophies ( 1st places )
void specificCountry(competitor arr[], int n);                          //shows all competitor from wanted specific country
void editCompetitor(competitor arr[], int numInTournament, int n);      //edits competitor info by number in the tournament
int duel(competitor arr[], int n);                                      //duel ONE vs ONE by number in the tournament
int duelTest();                                                         //duel ONE vs ONE ( sample of simple comparison with if, not on assignment)
void auditWorldrank(competitor arr[], int n);                           //shows all competitors sorted by number in the World Rankings
void auditAlphabeticalOrd(competitor arr[], int n);                     //show all competitors from a watned country, sorted alphabetically
void auditFirstPlaces(competitor arr[], int n);                         //show all competitors from a wanted country, sorted by number of cups won in descending order
void submenuAudit(competitor arr[], int n);                              //sub menu with functions for audit
int saveTXT();                                                          //saves file with all competitors in txt
int saveBINARY();                                                       //saves file with all competitors in binary from existing txt file     
void saveReadableTXT(competitor arr[], int n);                          //saves readable txt file with all competitors

int menu()
{
    short int c; //choice
    cout << "\n  \t### Tennis tournament ## Menu ### ";
    cout << "\n ";
    cout << "\n === Adding competitors in the tournament: === ";
    cout << "\n 1. Adding a competitor  ";
    cout << "\n 2. Adding a list of competitors ";
    cout << "\n === Showing competitors: === ";
    cout << "\n 3. Show all competitors: ";
    cout << "\n 4. Competitors with less won trophies (1st places) ";
    cout << "\n 5. Competitors from specific country ";
    cout << "\n === Edit === ";
    cout << "\n 6. Edit competitor data by number in the tournament";
    cout << "\n === Audit - sub menu === ";
    cout << "\n 7. Audit";
    cout << "\n === Duel === ";
    cout << "\n 8. Duel Demo ( in progress ... )";
    cout << "\n 9. Duel Test ( if )";
    cout << "\n === Additional === ";
    cout << "\n 10. Save file in binary";
    cout << "\n 11. Save file from binary to text file (1) ";
    cout << "\n 12  Save file from text to binary file (2) ";
    cout << "\n 13. Save file in readable text file";
    cout << "\n 14. Exit ";
    cout << "\n !!! Follow the instructions or ERRORS may occur !!! ";
    cout << "\n ";
    do {
        cout << "\n Your choice: ";
        cin >> c;
    } while (c < 1 || c > 14);
    return c;
}

int main()
{
    competitor arr[N]; //array of structs with limit N = 100
    int choice;
    int n = 0;   //n = 0 = empty tournament
    n = loadFile(arr);
    do {
        choice = menu();
        switch (choice) {
        case 1: addOneCompetitor(arr, n); n++; break;
        case 2: { system("cls"); } addManyCompetitors(arr, n); break;
        case 3: {system("cls"); } {n = loadFile(arr); showAllcompetitors(arr, n); }; break;
        case 4: {system("cls"); } {n = loadFile(arr); lessTrophies(arr, n); }; break;
        case 5: {system("cls"); } { n = loadFile(arr); specificCountry(arr, n); }; break;
        case 6: {system("cls"); } {  n = loadFile(arr); showAllcompetitors(arr, n);
            cout << "\n Edit by number in the tournament: ";
            int numInTournament;
            cin >> numInTournament;
            cout << endl;
            editCompetitor(arr, numInTournament, n);
            saveInFile(arr, n);
        };
              break;
        case 7: {system("cls"); } n = loadFile(arr); submenuAudit(arr, n); break;
        case 8: {system("cls"); }
        { cout << "\n \t ONEvsONE duel - Demo / future function";
        n = loadFile(arr);
        showAllcompetitors(arr, n);
        duel(arr, n);
        };
        break;
        case 9: {system("cls"); } duelTest(); break;
        case 10: saveInFile(arr, n);
        {
            cout << "\n File saved as TURNIR.dat as binary \n";
        }
        break;
        case 11: saveTXT();
        {
            cout << "\n File saved as TURNIR.txt as txt \n";
        }
        break;
        case 12: saveBINARY();
        {
            cout << "\n File saved as TURNIR_NEW.dat as binary \n";
        }
        break;
        case 13: saveReadableTXT(arr, n);
        {
            cout << "\n File saved as TURNIR_READABLE.txt as txt \n";
        }
        break;
        }
    } while (choice != 14);

    return 0;
}

competitor input()      //structure for adding competitors
{
    competitor a = { 0 };       //defines as an empty structure

    cout << "\n Confirm number in the current tournament ";
    cout << "\n Number in the current tournament: ";
    cin >> a.numInTournament;

    cout << "\n Confirm number in the World rank list ";
    cout << "\n Number in World rank list (only int number) : ";
    cin >> a.numWorldRank;

    cout << "\n First Name: ";
    cin.ignore();   //ignore or clear one or more characters from the input buffer
    cin.getline(a.name, 30);

    cout << "\n Last Name: ";
    cin.getline(a.surname, 30);

    cout << "\n Country: ";
    cin.getline(a.country, 30);

    cout << "\n Current points (only number) : ";
    cin >> a.currentPoints;

    cout << "\n Number of won 1st places (only int number) : ";
    cin >> a.firstPlaces;

    cout << "\n ################################" <<
        "\n Number in the current tournament: " << a.numInTournament <<
        "\n Number in World rank list: " << a.numWorldRank <<
        "\n First Name: " << a.name <<
        "\n Last Name: " << a.surname <<
        "\n Country: " << a.country <<
        "\n Current points: " << a.currentPoints <<
        "\n Number of won 1st places: " << a.firstPlaces <<
        "\n ################################ " << endl;
    return(a); //returning full structure
}

competitor inputUpdated(competitor arr[], int i)     //structure for editing competitors information
{
    competitor update;       //defines structure

    cout << "Confirm number in the current tournament ";
    cin >> update.numInTournament;

    cout << "\n Number in the world rank list: " << arr[i].numWorldRank;
    cout << "\n Confirm number in the number in World rank list: ";
    cin >> update.numWorldRank;

    cout << "\n First Name: ";
    cin.ignore();        //ignore or clear one or more characters from the input buffer
    cin.getline(update.name, 30);

    cout << "\n Last Name: ";
    cin.getline(update.surname, 30);

    cout << "\n Country: ";
    cin.getline(update.country, 30);

    cout << "\n Current points (only number) : ";
    cin >> update.currentPoints;

    cout << "\n Number of won 1st places (only int number) : ";
    cin >> update.firstPlaces;

    cout << "\n ########### UPDATED ############" <<
        "\n Number in the current tournament: " << update.numInTournament <<
        "\n Number in World rank list: " << update.numWorldRank <<
        "\n First Name: " << update.name <<
        "\n Last Name: " << update.surname <<
        "\n Country: " << update.country <<
        "\n Current points: " << update.currentPoints <<
        "\n Number of won 1st places: " << update.firstPlaces <<
        "\n ################################ " << endl;
    return(update);      //returning updated full structure
}

void display(competitor arr[], int i)       //displays the entered data
{
    cout << "\n ################################" <<
        "\n Number in the current tournament: " << arr[i].numInTournament <<
        "\n Number in World rank list: " << arr[i].numWorldRank <<
        "\n First Name: " << arr[i].name <<
        "\n Last Name: " << arr[i].surname <<
        "\n Country: " << arr[i].country <<
        "\n Current points: " << arr[i].currentPoints <<
        "\n Number of won 1st places: " << arr[i].firstPlaces <<
        "\n  ################################" << endl;
}

void sortNumInTournament(competitor arr[], int n)      //sorts by size according to the place in the tournament
{
    competitor temp;    //defines structure / holding variable
    //int flag = 1;
    int i, j;
    for (i = 0; i < n - 1; i++)     // element to be compared
    {
      /*  if(!flag)
        {
            break;
        }
        else { flag = false; }
        */
        for (j = i + 1; j < n; j++) // rest of the elements
        {
            if (arr[i].numInTournament > arr[j].numInTournament)    //Ascending Order
            {
                temp = arr[i];      //swap
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortNumWorldRank(competitor arr[], int n)     //sorts by size according to the place in the World rank list 
{
    competitor temp;    //defines structure / holding variable
    //int flag = 1;
    int i, j;
    for (i = 0; i < n - 1; i++)     // element to be compared
    {
        /*  if(!flag)
        {
            break;
        }
        else { flag = false; }
        */
        for (j = i + 1; j < n; j++) // rest of the elements
        {
            if (arr[i].numWorldRank > arr[j].numWorldRank)      //Ascending Order
            {
                temp = arr[i];      //swap
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortFirstPlaces(competitor arr[], int n)      //sorts by size according to the 1st places / won trophies 
{
    competitor temp;    //defines structure / holding variable
    //flag = 1;
    int i, j;
    for (i = 0; i < n - 1; i++)      // element to be compared
    {
        /*  if(!flag)
        {
            break;
        }
        else { flag = false; }
        */
        for (j = i + 1; j < n; j++)  // rest of the elements
        {
            if (arr[i].firstPlaces < arr[j].firstPlaces)        //descending Order
            {
                temp = arr[i];      //swap
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void sortName(competitor arr[], int n)         //sorts by name
{
    competitor temp;        //defines structure / holding variable
    int i, j;
    for (i = 0; i < n - 1; i++)      // element to be compared
    {
        for (j = i + 1; j < n; j++) // rest of the elements
        {
            /*starts comparing the first character of each string.
            If they are equal to each other,
            it continues with the following pairs
            until the characters differ or until a
            terminating null-character is reached*/

            if (strcmp(arr[i].name, arr[j].name) > 0)
            {
                temp = arr[i];       //swap
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int loadFile(competitor arr[])      //loads binary file
{
    long pos;     //position
    int n = 0, i; //n = 0 = empty tournament
    competitors b; //defines structure 

    //open the binary file for reading
    fp.open(Filename, ios::binary | ios::in);

    //in case of a problem it returns back to main()
    if (!fp) { cout << "\n TURNIR.dat file not exist\n"; return n; }

    //take the number of bytes and closes it
    fp.seekg(0l, ios::end); //ukazatelq v nachaloto , sprqmo  kraq na faila
    pos = fp.tellg(); //current position |
    fp.close();
    n = pos / (sizeof(competitor));

    //open the file for reading again
    fp.open(Filename, ios::binary | ios::in);
    //checks for error
    if (!fp) { cout << "\n Error in file \n"; exit(1); }

    //read structure by structure people and put them in an array
    for (i = 0; i < n; i++)
    {
        fp.read((char*)&b, sizeof(competitor));
        arr[i] = b;
    }
    fp.close(); //closing file 
    return n;   //with return, I return n to the calling function
}

void saveInFile(competitor arr[], int n)    //saving binary file 
{
    //opens a file named Filename ( file constanta ) as a binary for writing
    fp.open(Filename, ios::binary | ios::out);

    //interrupts in case of a problem
    if (!fp) { cout << "\n Error in file \n"; exit(1); }

    //writes down the whole tournament program data which has n number competitors * (multiplied) by one competitor structure
    fp.write((char*)arr, sizeof(competitor) * n);
    fp.close(); //closing file 
}

void addOneCompetitor(competitor arr[], int n)      //adding ONE competitor in the tournament and append it
{
    competitor b;   //defines structure
    cout << "\n Number in the current tournament (cheks if the number is free or it is taken): ";
    cin >> b.numInTournament;
    cout << endl;
    if (b.numInTournament < 101)
    {
        //check for unique number in the tournament
        for (int i = 0; i < n; i++)
        {
            if (arr[i].numInTournament == b.numInTournament)
            {
                cout << "Number in the current tournament is taken \n";
                return;
            }
        }


        cout << "\n Number in the world rank list (cheks if the number is free or it is taken): ";
        cin >> b.numWorldRank;
        cout << endl;
        //check for unique number in the tournament
        for (int i = 0; i < n; i++)
        {
            if (arr[i].numWorldRank == b.numWorldRank)
            {
                cout << "Number in the world rank list is taken \n";
                return;
            }
        }

        //opens binary file for appending
        fp.open(Filename, ios::binary | ios::app);
        //checks for error
        if (!fp) { cout << "\n Error in file \n"; exit(1); }
        cout << "\n Append new competitor to the tournament";
        b = input();
        //writting and appending competitor in the end
        fp.write((char*)&b, sizeof(competitor));
        fp.close();
    }
    else if (b.numInTournament > 100)
    {
        cout << "\n Maximum number is 100 !!! \n";
        return;
    }
}

void addManyCompetitors(competitor arr[], int n)        //adding N number competitors in the tournament and appends them
{
    int comp = 0;   //comp = competitors
    do {
        cout << "\n Enter the num of new competitors you want to add (0 < num < 100) : ";
        cin >> comp; //Add n competitors
    } while (comp < 1 || comp > 101);
    //check for free places in the tournament
    if (comp + n < 100)
    {
        for (int i = 0; i < comp; i++)
        { //Call the function below this
            cout << "\n Competitor to add No: " << i + 1;
            addOneCompetitor(arr, n); //calling function for adding each competitor
        }
    }
    else     //if the tournament is full ( 100 competitors )
    {
        cout << "\n There are no more free places in the tournament \n ";
        cout << "\n Max competitors is 100! ";
    }
}

void showAllcompetitors(competitor arr[], int n)    //showing all competitors in the tournament sorted by number in the tournament
{
    int i;
    int k = 0;
    cout << "\n All competitors: \n";
    //all available competitors
    for (i = 0; i < n; i++)
    {
        //numbered sequentially
        cout << "\n " << i + 1 << ".";
        //sorts by number in the tournament
        sortNumInTournament(arr, n);
        //displays each competitor after the sorting by num
        display(arr, i);
        k++;
    }
}

void lessTrophies(competitors arr[], int n)  //showing the competitor with less won trophies ( 1st places )
{
    cout << "\n Competitor/s with less won trophies (1st places) \n";
    int count = 0;
    int minTrophies = arr[0].firstPlaces;
    //to find the number of minimum cups
    for (int i = 0; i < n; i++)
    {
        if (minTrophies > arr[i].firstPlaces)
        {
            minTrophies = arr[i].firstPlaces;
        }
    }

    //to go around the competitors again and get those who have exactly as many cups as minTrophies
    for (int i = 0; i < n; i++)
    {
        if (minTrophies == arr[i].firstPlaces)
        {
            display(arr, i);
            count++;
        }
    }
}

void specificCountry(competitor arr[], int n)   //shows all competitor from wanted specific country
{
    char country[30];   //defines country
    int count = 0;
    cin.ignore();
    cout << "Enter wanted country: ";
    cin.getline(country, 30);

    // element to be compared
    for (int i = 0; i < n; i++)
    {
        /*starts comparing the first character of each string.
            If they are equal to each other,
            it continues with the following pairs
            until the characters differ or until a
            terminating null-character is reached*/
        if (!strcmp(country, arr[i].country))
        {
            cout << "\nFound: ";
            //displays each competitor from wanted country
            display(arr, i);
            count++;
        }
    }
    if (count > 0)  //checks how many competitors from country are found
    {
        cout << "\n Total competitors found: " << count << "\n";
    }
    else           //if there are no competitors from wanted country
    {
        cout << "\n Country not found. \n";
    }
}

void editCompetitor(competitor arr[], int numInTournament, int n)   //edits competitor info by number in the tournament
{
    int count = 0;

    //all available competitors
    for (int i = 0; i < n; i++)
    {
        // Check if someone of the elements are equal to inputed tournament number
        if (arr[i].numInTournament == numInTournament)
        {
            competitor b = inputUpdated(arr, i); // new element
            b.numInTournament = arr[i].numInTournament; //Save old tournament number
            arr[i] = b; //replace current competitor with the new one or updates information

            count++;
        }
    }
    if (count == 0)      //checks if there is not a competitor with the searched number in the tournament
    {
        cout << "\n Competitor not found. \n";
    }
}

void auditWorldrank(competitor arr[], int n)   //shows all competitors sorted by number in the World Rankings
{
    int k = 0;
    cout << "\n All competitors: \n";
    //all available competitors
    for (int i = 0; i < n; i++)
    {
        //numbered sequentially
        cout << "\n" << i + 1 << "." << "\n \t";
        //sorts by number in the world rank list
        sortNumWorldRank(arr, n);
        //displays each competitor after the sorting by world rank
        display(arr, i);
        k++;
    }
}

void auditAlphabeticalOrd(competitor arr[], int n)    //show all competitors from a watned country, sorted alphabetically
{
    char country[30];   //defines country
    int flag = 0, count = 0;
    cin.ignore();
    cout << "Enter wanted country: ";
    cin.getline(country, 30);

    // element to be compared
    for (int i = 0; i < n; i++)
    {
        sortName(arr, n); //sorts competitors by name

        /*starts comparing the first character of each string.
            If they are equal to each other,
            it continues with the following pairs
            until the characters differ or until a
            terminating null-character is reached*/
        if (!strcmp(country, arr[i].country))
        {
            cout << "\nFound: "; flag = 1;
            //displays each competitor from wanted country
            display(arr, i);
            count++;
        }
    }
    if (count > 0)  //checks how many competitors from country are found
    {
        cout << "\n Total countries found: " << count << "\n";
    }
    else           //if there are no competitors from wanted country
    {
        cout << "\n Country not found. \n";
    }
}

void auditFirstPlaces(competitor arr[], int n)        //show all competitors from a wanted country, sorted by number of cups won in descending order
{
    char country[30];   //defines country
    int flag = 0, count = 0;
    cin.ignore();
    cout << "Enter wanted country: ";
    cin.getline(country, 30);

    // element to be compared
    for (int i = 0; i < n; i++)
    {
        sortFirstPlaces(arr, n); //sorts competitors by won trophies

        /*starts comparing the first character of each string.
            If they are equal to each other,
            it continues with the following pairs
            until the characters differ or until a
            terminating null-character is reached*/
        if (!strcmp(country, arr[i].country))
        {
            cout << "\nFound: "; flag = 1;
            //displays each competitor from wanted country
            display(arr, i);
            count++;
        }
    }
    if (count > 0)  //checks how many competitors from country are found
    {
        cout << "\n Total countries found: " << count << "\n";
    }
    else           //if there are no competitors from wanted country
    {
        cout << "\n Country not found. \n";
    }
}

void submenuAudit(competitor arr[], int n)
{
    int ch;
    do {
        cout << "\n \t #### SUB MENU #####";
        cout << "\n 1. Competitors sorted by World rank ";
        cout << "\n 2. Competitors from specific country sorted in alphabetical order";
        cout << "\n 3. Competitors from specific country sorted by first places ";
        cout << "\n 4. Back to main menu";
        cout << "\n Your choice: ";
        cin >> ch;
    } while (ch < 1 || ch > 4);
    switch (ch) {
    case 1: auditWorldrank(arr, n); break;
    case 2: auditAlphabeticalOrd(arr, n); break;
    case 3: auditFirstPlaces(arr, n); break;
    }
}

int saveTXT()   //saves file with all competitors in txt
{
    /* this function gets the data from already existing
       binary file and copy it in a new txt file*/

    ifstream fin; //only for reading fin
    fin.open("TURNIR.dat"); //opens binary file
    ofstream fout; //only writting fout
    fout.open("TURNIR.txt"); //opens txt file

    char ch;

    //reading all the way to the last symbol from the binary file
    while (!fin.eof())  //check if all the data is written to the file
    {
        fin.get(ch);  //reads 1 symbol and saves it in char
        fout << ch;
    }
    //closing both files
    fin.close();
    fout.close();
    return 0;
}

int saveBINARY()    //saves file with all competitors in binary from existing txt file
{
    /* this function gets the data from already existing
       txt file and copy it in a new binary file*/

    ifstream fin; //only for reading fin
    fin.open("TURNIR.txt"); //opens txt file
    ofstream fout; //only writting fout
    fout.open("TURNIR_NEW.dat"); //opens binary file

    char ch;

    //reading all the way to the last symbol from the binary file
    while (!fin.eof())  //check if all the data is written to the file
    {
        fin.get(ch);  //reads 1 symbol and saves it in char
        fout << ch;
    }
    //closing both files
    fin.close();
    fout.close();
    return 0;
}

void saveReadableTXT(competitor arr[], int n)
{
    fstream file;
    file.open("TURNIR_READABLE.txt", ios::out);

    for (int i = 0; i < n; i++)
    {
        file << arr[i].numInTournament << endl;
        file << arr[i].numWorldRank << endl;
        file << arr[i].name << endl;
        file << arr[i].surname << endl;
        file << arr[i].country << endl;
        file << arr[i].currentPoints << endl;
        file << arr[i].firstPlaces << endl;
    }

    file.close();
}

int duel(competitor arr[], int n)
{
    // in progress ...
    int powerOne, powerTwo;
    int i, j;
    cout << "\n Enter competitor 1 by number in the tournament: ";
    cin >> powerOne;

    for (i = 0; i < n; i++)
    {
        // Check if someone of the elements are equal to inputed tournament number
        if (arr[i].numInTournament == powerOne)
        {
            display(arr, i);
        }
    }

    cout << "\n Enter competitor 2 by number in the tournament: ";
    cin >> powerTwo;

    for (j = 0; j < n; j++)
    {
        // Check if someone of the elements are equal to inputed tournament number
        if (arr[j].numInTournament == powerTwo)
        {
            display(arr, i);
        }
    }


    if (arr[i].currentPoints > arr[j].currentPoints)
    {
        cout << "\n Competitor 1 wins \n ";
    }
    else  if (arr[i].currentPoints < arr[j].currentPoints)
    {
        cout << "\n Competitor 2 wins \n ";
    }
    else if (arr[i].currentPoints == arr[j].currentPoints)
    {
        cout << "\n No winner \n ";
    }

    return 0;
}

int duelTest()
{
    int powerOne, powerTwo;

    cout << "\n \t ONEvsONE duel - Demo / future function";
    cout << "\n Enter competitor 1 power (int): ";
    cin >> powerOne;

    cout << "\n Enter competitor 2 power (int):: ";
    cin >> powerTwo;

    if (powerOne > powerTwo)
    {
        cout << "\n Competitor 1 wins \n ";
    }
    else  if (powerOne < powerTwo)
    {
        cout << "\n Competitor 2 wins \n ";
    }
    else if (powerOne == powerTwo)
    {
        cout << "\n No winner \n ";
    }

    return 0;
}


//  fp.seekg(5l, ios::);
//  double p = 2.5789345;
//  cout<< setpercision(4)<< p ;
//  cout<< precision(4, p); --  