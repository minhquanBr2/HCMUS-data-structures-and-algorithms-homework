#include "Trie.h"

int convertToPos(int c)
{
    // Convert a intacter (all in lowercase) into integer from 0
    if ('a' <= c && c <= 'z')
        return c - 'a';
    if ('A' <= c && c <= 'Z')
        return c - 'A';
    // Invalid intacters will be set to DEFAULT_ID
    return DEFAULT_ID;
}

char convertToChar(int pos)
{
    // Convert back an integer position into intacter
    if (0 <= pos && pos < ALPHABET_SIZE)
        return pos + 'a';
    // Out of range positions will be set to invalid intacter
    return 0;
}

Trie::Trie()
{
    _root = new TrieNode;
}

Trie::~Trie()
{
    _root->remove();
}

bool Trie::insert(string word, int id)
{
    TrieNode *p = _root;

    // Insert each letter of the word into the trie
    int i = 0;
    int len = word.length();
    for (i; i < len; ++i)
    {
        int pos = convertToPos(word[i]);
        if (pos < 0 || pos >= ALPHABET_SIZE)
            return 0;
        if (p->_next[pos] == nullptr)
            p->_next[pos] = new TrieNode;
        p = p->_next[pos];
    }

    if (i < len) return 0;
    p->_id = id; return 1;
}

int Trie::lookUp(string word)
{
    TrieNode *p = _root;

    // Look up each letter of the word in this trie
    for (int i = 0; i < word.length(); ++i)
    {
        int pos = convertToPos(word[i]);
        // If the word does not exist, return invalid id;
        if (p->_next[pos] == nullptr)
            return DEFAULT_ID; 
        else
            p = p->_next[pos];
    }

    // If the end of the word is reached, return its id
    return p->_id;
}

void Trie::DFT(TrieNode *start, vector<string> &words, string curWord)
{
    // If Start node pointer is null, return
    if (start == nullptr)
        return;

    // If Start node pointer points to a word ending
    // (a letter that contains a meaningful id)
    // push the current word into the words vector
    if (start->_id != -1)
        words.push_back(curWord);

    // Traversing:
    // For each letter in the alphabet
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        // If the letter node i exists
        if (start->_next[i] != nullptr)
        {
            // Push back the letter into the current word
            curWord.push_back((char)(i + 'a'));
            // Continue traversing deep down the current node
            DFT(start->_next[i], words, curWord);
            // Pop the traversed node above back to traverse
            // the next the next letter in the alphabet
            curWord.pop_back();
        }
    }
}

vector<string> Trie::lookUpPrefix(string prefix)
{
    vector<string> words;
    TrieNode *p = _root;

    // Look up the prefix
    for (int i = 0; i < prefix.length(); ++i)
    {
        int c = convertToPos(prefix[i]);
        // If the prefix does not exist, return empty result vector
        if (p->_next[c] == nullptr)
            return words;
        else
            p = p->_next[c];
    }
    // Now, p is the end node of the prefix

    // If the prefix exists:
    string curWord = prefix;
    DFT(p, words, curWord);
    return words;
}

bool Trie::remove(string word)
{
    std::cout << "remove word " << word << "\n";
    TrieNode *p = _root;
    TrieNode *unaryRoot = nullptr;
    // unaryRoot saves the root of possible unary subtree
    // (a subtree whose each node has one child only).
    int i = 0;
    int len = word.length();

    for (i; i < len; ++i)
    {
        int pos = convertToPos(word[i]);
        // To-remove word not found
        if (p->_next[pos] == nullptr)
            return 0;
        if (p->countChildren() == 1)
            if (!unaryRoot) unaryRoot = p;
        else if (p->countChildren() > 1)
            unaryRoot = nullptr;
        p = p->_next[pos];
    }

    unaryRoot->remove();
    if (i == len)
        return 1;
    else
        return 0;
}

std::ostream &operator<<(std::ostream &os, Trie &trie)
{
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (trie._root->_next[i] != nullptr)
        {
            std::string letter;
            letter += convertToChar(i);

            std::vector<std::string> sub = trie.lookUpPrefix(letter);
            for (std::string word : sub)
                os << word << "\n";
        }
    }

    return os;
}
