Includes & Namespaces

<iostream> for console I/O
<string> for std::string
<ctime> for timestamps

using namespace std; for brevity

Hex Conversion Helper (to_hex)
Takes an unsigned long and builds a hex string manually (nibble by nibble), prefixing with "0x".

Hash Function (hash_function)
Implements a simple polynomial rolling hash: starts from 0, for each character multiplies current hash by 31 and adds the character’s ASCII code.
Calls to_hex to turn that numeric hash into a hex‑formatted string.

Block Class
Members:
int index – block number in the chain

time_t timestamp – creation time

string data – payload (transaction/message)

string prevHash – the previous block’s hash

string hash – this block’s own hash

Block* next – pointer to the next block

Constructor
Uses an initializer list to set index, data, prevHash, and next
In the body, captures the current time, concatenates index, timestamp, data, and prevHash into one string, and computes hash = hash_function(...).

Blockchain Class
Member: Block* head points to the first (genesis) block.

Constructor
Creates the genesis block with index 0, data “Genesis Block”, and a dummy prevHash of "0x0".

addBlock(data)
Traverses from head to the last block, then allocates a new Block whose index is last’s index +1, data is the passed string, and prevHash is the last block’s hash.

display()
Iterates the linked list, printing each block’s index, human‑readable timestamp (ctime), data, previous hash, and current hash.

validate()
Walks the chain pairwise: for each block curr and its successor nxt, checks

nxt->prevHash == curr->hash

Recomputes hash_function(...) on nxt’s stored contents and compares to nxt->hash

Returns false on any mismatch, true otherwise.

Destructor
Deletes every block in sequence to free memory.

main() Logic
Instantiates a Blockchain (auto‐creates the genesis block).
Prompts the user in a loop to enter transaction data lines until they type exit. Each non‑empty line calls chain.addBlock(data).

After exit, prints the full chain via chain.display(), then runs chain.validate() and reports “Blockchain valid.” or “Blockchain invalid!”
