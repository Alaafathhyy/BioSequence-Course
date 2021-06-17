#include <iostream>

#define  endl  "\n"
using namespace std;
int const N = 1e3 + 5;
int Size[N]; //
int Nodes;
struct Node {
    Node *Fail{}; //the node that the current node is making the failure link with.
    int Len = 0, // The length of longest prefix that also a suffix that end at the current node
    Ids = -1; 
    Node *Child[132]{}; // Children of the current node
};

Node *Root;

Node *CreateTrieNode() // Create and Initialize Trie Node
{
    Node *node = new Node;
    node->Label = Nodes++;
    int i;
    // Initialize all the children with null
    for (i = 0; i < 132; i++) node->Child[i] = 0;
    node->Fail = 0;
    return node;
}

void AddToTrie(const char *str, int sz, int id) // Add str with size of sz and id to the trie
{
    Size[id] = sz;
    if (!Root) //init the root
        Root = CreateTrieNode();

    Node *CurNode = Root;
    int i;
    for (i = 0; i < sz; i++) // append the characters of str to the trie
    {
      
        CurNode = CurNode->Child[str[i]];
    }

    CurNode->Ids = id; //save the id of str at the current node


}

Node *GetFailNode(int &len, char ch, Node *Cur, int CurLable)  // return the node that making the Failure Link with
{
  
    while (len && Cur != Root && !Cur->Child[ch]) {
        Cur = Cur->Fail;
        len = Cur->Len;

    }

    len += (bool) (Cur->Child[ch]); 

    return (len ? Cur->Child[ch] : Root); 
}

void BuildFail(const char *str, int sz) // build the Failure links of str with length sz
{
    int len = 0, i;
    Node *CurNode = Root->Child[str[0]],
            *FailNode = Root;
    CurNode->Fail = Root; 
    CurNode->Len = 0;

    for (i = 1; i < sz; ++i) {
        CurNode = CurNode->Child[str[i]];
       
        CurNode->Fail = GetFailNode(len, str[i], FailNode, CurNode->Label);
        CurNode->Len = len;
        FailNode = CurNode->Fail;

    

    }
}

void Search(const char *Text, int sz)  // search for some patterns at text
{
    Node *FailNode = Root;
    int len = 0, i;
    for (i = 0; i < sz; ++i)// for each index find the longest suffix that also a prefix from the patterns
    {
        FailNode = GetFailNode(len, Text[i], FailNode, i);

        if (~FailNode->Ids) // if the current node is hold an id, wasn't equal -1
        {
            cout << "Rep(" << FailNode->Ids << "," << i - Size[FailNode->Ids] + 1 << ")" << endl;
        }

        if (FailNode->Fail && ~FailNode->Fail->Ids)  // if the failure node of current node is hold an id
        {
            cout << "Rep(" << FailNode->Fail->Ids << "," << i - Size[FailNode->Fail->Ids] + 1 << ")" << endl;
        }

    }
}

void DeleteTrie(Node *node)  // delete Node
{
    int i;
    node->Fail = 0;
    for (i = 0; i < 132; i++) if (node->Child[i]) DeleteTrie(node->Child[i]);


    delete node;
}

void DeleteTrie() // delete Trie
{
    DeleteTrie(Root);
}
