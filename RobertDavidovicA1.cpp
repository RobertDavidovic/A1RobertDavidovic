/**************************************************
 Project: RobertDavidovicA1
 Date: Sunday 30th August 2020
 Author: Robert Davidovic
 Purpose: Reading in file data and converting quotes
 into cryptograms. These cryptograms can then be saved
 in a text file.
**************************************************/
#include "A1Declarations.h"

/*Clears cin buffers. This prevents overflow by the user not inputting numbers*/
void flush(){
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max( ), '\n' ); 

}

/*This function will allow the user to read information by waiting for them to press enter*/
void pressEnter(){
    cout << "\nPress enter to continue . . ." << endl;
    cout.flush();
    while ((getchar()) != '\n');
    getchar();
}

/*This function will check if the data has been loaded into the arrays quotes and cryptograms.
the dataLoaded variable is made true during in the createLists function*/
bool dataLoadedCheck(){
    if (!dataLoaded){
        cout << "ERROR: Please load in the data from files first!";
        pressEnter();
    }
    return dataLoaded;
}

/*This function converts a file into a string vector. It has three arguements; The first
is the filename of the file you want to convert, the second is the vector you want to bring the 
file values to, and the third is the character that seperates the different lines in the file.
*/
void convertFileToVector(string filename, vector<string>& collection, char newLine = '\n'){
    collection.empty();
    string quote;
    ifstream data(filename);
    while (data.eof() == false){
        getline(data, quote,newLine);
        collection.push_back(quote);
    }
    data.close();
}

/*This function reads out all the lines in a file. It takes one arguement which is the file you
want to read out*/
void readAllFileLines(string filename){
    string line;
    ifstream file(filename);
    while (file.eof() == false){
        getline(file, line);
        cout << line << "\n";
    }
    file.close();
}

/*This function creates the user interface that will allow the user to call certain functions.
There are no variables that need to be initialised here.*/
void runMenu(){
    system("clear");
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "      The Amazing Cryptogram Generator\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "[X] End Testing the Program\n";
    cout << "[I] Display ""About"" Information\n";
    cout << "[R] Read and store data from files\n";
    cout << "[G] Generate a Random Cryptogram\n";
    cout << "[S] Save a Cryptogram to a file\n";
    cout << "[D] Display saved Cryptograms from a file\n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    cout << "Which option would you like (X-D): ";
    cin >> command;
    switch (command)
        {
        case 'X':
            break;
        case 'I':
            displayText("CryptoAbout.txt");
            break;
        case 'R':
            createLists("CryptogramData.txt","savedCryptograms.txt");
            break;
        case 'G':
            generateCryptograms();
            break;
        case 'S':
            saveData();
            break;
        case 'D':
            displaySavedCryptograms();
            break;
        default:
            flush();
            command = -1;
            break;
    }
}

/*This function clears the screen and reads all the lines from a file. It takes in one arguement
which is the filename of the file wanting to be read.*/
void displayText(string fileName){
    ifstream file;
    file.open(fileName);
    if (file.fail()){
        cout << "Sorry about file could not be found.";
        pressEnter();
        return;
    }
    system("clear");
    readAllFileLines(fileName);
    pressEnter();
}

/*This function creates two vectors that will be filled containing everything contained in two files.
It has two arguements which are the names of the two files. One container will be quotes another
will be the cryptograms. The collection variables are correctly initialised in the header file.*/
void createLists(string filename, string savedCypto){
    convertFileToVector(filename, quotes,';');
    convertFileToVector(savedCypto, cryptograms, '\n');
    cout << "Data has been loaded from CryptogramData.txt";
    dataLoaded = true;
    pressEnter();
}

/*This function will create a cryptogram using a random quote taken from the vector quotes.
It will do this by asking the user for a number then adding that number to each letter
of the selected quote.*/
void generateCryptograms(){
    if (!dataLoadedCheck()){
        return;
    }
    cryptogram = "";
    int cryptokey;
    int randomIndex;
    string randomQuote;
    do {
        flush();
        cout << "Choose a number from (1-25): ";
        cin >> cryptokey;
        cout << "\n";
    } while (cryptokey < 1 || cryptokey >25);
    randomIndex = rand() % quotes.size();
    randomQuote = quotes[randomIndex];
    for (int i = 0; i <= randomQuote.size();i++){
        char letter;
        if (randomQuote[i] > 47){
            letter = randomQuote[i] + cryptokey;
        }
        else{
            letter = randomQuote[i];
        }
        cryptogram = cryptogram + letter;
    }
    cout << cryptogram;
    pressEnter();
}

/*This function will append data to a file. It takes in a filename of the file and the data
that you want to append*/
void writeDataToFile(string filename, string data){
    ofstream savedFile;
    savedFile.open(filename, ios::app);
    savedFile << data << endl;
    savedFile.close();
}

/*This function will ask the user if they want to save the last generated cryptogram. It will loop
until the user selects 'y' or 'n'*/
void saveData(){
    if (!dataLoadedCheck()){
        return;
    }
    string response = "";
    cout << "\n" + cryptogram;
    cout << "\nDo you want to save this Cryptogram? (y/n) ";
    do{
        cin >> response;
        if (response == "y"){
            writeDataToFile("savedCryptograms.txt", cryptogram);
            cout << "\nThis Cryptogram is now saved.\n";
            pressEnter();
            return;
        }
        else if (response == "n")
        {
            return;
        }
        else
        {
            cout << "Please respond with a ""y"" or ""n"": ";
        }
    } while (response != "");
    
}

/*This function will read all of the saved cryptograms by calling the readAllFileLines function*/
void displaySavedCryptograms(){ 
    readAllFileLines("savedCryptograms.txt");
    pressEnter();
}

/*This is the main section of the program. It will keep calling runMenu() until the command is changed
to X*/
int main()
{
    while (command != 'X'){
        runMenu();
        }
    return 0;
}
