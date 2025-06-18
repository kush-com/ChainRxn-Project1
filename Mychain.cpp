#include <iostream>
#include <string>
#include <ctime>

using namespace std;

// Helper: convert unsigned long to hex string with "0x" prefix
string to_hex(unsigned long value) {
    string hexStr = "";
    if (value == 0) return "0x0";
    while (value > 0) {
        int digit = value % 16;
        char hexChar;
        if (digit < 10) hexChar = '0' + digit;
        else hexChar = 'a' + (digit - 10);
        hexStr = hexChar + hexStr;
        value /= 16;
    }
    return "0x" + hexStr;
}

// Very basic hash function: polynomial rolling hash
string hash_function(const string& input) {
    unsigned long hash = 0;
    const unsigned long prime = 31;
    for (char c : input) {
        hash = hash * prime + static_cast<unsigned long>(c);
    }
    return to_hex(hash);
}

// Block structure
class Block {
public:
    int index;
    time_t timestamp;
    string data;
    string prevHash;
    string hash;
    Block* next;

    Block(int idx, const string& d, const string& prev)
        : index(idx), data(d), prevHash(prev), next(nullptr) {
        timestamp = time(nullptr);
        string toHash = to_string(index) + to_string(timestamp) + data + prevHash;
        hash = hash_function(toHash);
    }
};

// Blockchain class
class Blockchain {
private:
    Block* head;

public:
    Blockchain() {
        head = new Block(0, "Genesis Block", "0x0");
    }

    void addBlock(const string& data) {
        Block* curr = head;
        while (curr->next) curr = curr->next;
        curr->next = new Block(curr->index + 1, data, curr->hash);
    }

    void display() const {
        for (Block* curr = head; curr; curr = curr->next) {
            cout << "******************************************\n";
            cout << "Block No: " << curr->index << "\n";
            cout << "Timestamp: " << ctime(&curr->timestamp);
            cout << "Data: " << curr->data << "\n";
            cout << "Previous Hash: " << curr->prevHash << "\n";
            cout << "Current Hash:  " << curr->hash << "\n";
        }
    }

    bool validate() const {
        for (Block* curr = head; curr && curr->next; curr = curr->next) {
            Block* nxt = curr->next;
            if (nxt->prevHash != curr->hash) return false;
            string toHash = to_string(nxt->index) + to_string(nxt->timestamp) + nxt->data + nxt->prevHash;
            if (hash_function(toHash) != nxt->hash) return false;
        }
        return true;
    }

    ~Blockchain() {
        while (head) {
            Block* del = head;
            head = head->next;
            delete del;
        }
    }
};

int main() {
    Blockchain chain;
    cout << "Basic Blockchain Simulation\n";
    cout << "Enter transactions (type 'exit' to finish):\n";
    string data;
    while (true) {
        cout << "> ";
        if (!getline(cin, data) || data == "exit") break;
        if (!data.empty()) chain.addBlock(data);
    }
    cout << "\nDisplaying blockchain...\n";
    chain.display();
    cout << "\nValidating blockchain integrity...\n";
    cout << (chain.validate() ? "Blockchain valid.\n" : "Blockchain invalid!\n");
    return 0;
}
