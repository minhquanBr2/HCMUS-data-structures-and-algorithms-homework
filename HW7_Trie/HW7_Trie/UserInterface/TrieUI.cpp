#include "TrieUI.h"
#include "OperationEnum.h"

using std::cin;
using std::cout;
using std::string;

TrieUI::TrieUI()
{
    _fileHandle = new FileHandle;
}

TrieUI::~TrieUI() 
{
    _fileHandle->~FileHandle();
}

void TrieUI::readfile()
{
    string inputfile;

    bool success = 0;
    do
    {
        cout << "Enter input filename: ";
        cin >> inputfile;

        success = _fileHandle->read(inputfile);
        if (success)
            cout << "Read file successfully!\n";
        else
            cout << "File not found!\n";
    } while (!success);
}

void TrieUI::writefile()
{
    string outputfile;

    cout << "Enter output filename: ";
    cin >> outputfile;

    bool success = _fileHandle->write(outputfile);
    if (success)
        cout << "Write file successfully!\n";
    else
        cout << "Failed to write file!\n";
}

void TrieUI::lookUp()
{
    string word;
    cout << "Enter word to look up: ";
    cin >> word;

    int id = _fileHandle->_trieHandle->lookUp(word);
    if (id == DEFAULT_ID)
        cout << "Word not found!\n";
    else
        cout << word << "'s ID in the dictionary: " << id << "\n";
}

void TrieUI::lookUpPrefix()
{
    string prefix;
    cout << "Enter prefix to look up: ";
    cin >> prefix;

    vector<string> words 
        = _fileHandle->_trieHandle->lookUpPrefix(prefix);
    
    if (words.size() == 0)
        cout << "No word found!\n";
    else
    {
        cout << "Words found: ";
        for (string word : words)
            cout << word << " ";
    }
    cout << "\n";
}

void TrieUI::insert()
{
    string insertee;
    int id = 0;

    cout << "Enter word to insert: ";
    cin >> insertee;
    cout << "Enter ID: ";
    cin >> id;

    bool inserted = _fileHandle->_trieHandle->insert(insertee, id);
    if (inserted)
        cout << "Successful insertion.\n";
    else
        cout << "Failed to insert!\n";
}

void TrieUI::remove()
{
    string removee;

    cout << "Enter word to remove: ";
    cin >> removee;

    bool removed = _fileHandle->_trieHandle->remove(removee);
    if (removed)
        cout << "Successful removal.\n";
    else
        cout << "Word not found!\n";
}

void TrieUI::print()
{
    cout << "\t------ Dictionary ------\t\n";
    cout << *_fileHandle->_trieHandle;
}

// Menu
void TrieUI::showMenu()
{
    int option = EXIT;

    while (true)
    {
        cout << "Processing menu:\n\t"
                  << Operation::INSERT << " - Insert\n\t"
                  << Operation::REMOVE << " - Remove\n\t"
                  << Operation::LOOKUP << " - Look up\n\t"
                  << Operation::PREFIX << " - Look up with prefix\n\t"
                  << Operation::PRINT << " - Print dictionary on screen\n\t"
                  << Operation::WRITE_FILE << " - Save dictionary to file\n\t"
                  << Operation::EXIT << " - Exit\n";

        cout << "Your option: ";
        cin >> option;

        switch (option)
        {
        case Operation::INSERT:
            this->insert();
            break;
        case Operation::REMOVE:
            this->remove();
            break;
        case Operation::LOOKUP:
            this->lookUp();
            break;
        case Operation::PREFIX:
            this->lookUpPrefix();
            break;
        case Operation::PRINT:
            this->print();
            break;
        case Operation::WRITE_FILE:
            this->writefile();
            break;
        default:
            return;
        }
        cout << "\t------------------------\n";
    };
}
