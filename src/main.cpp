#include <iostream>
#include <regex>
using namespace std;

/* Note:
    1. You will have to comment main() when unit testing your code because catch uses its own main().
    2. You will submit this main.cpp file and any header files you have on Gradescope.
*/

class BST { //Most of this BST class is from the sample code Project 1 wrapped BST example
private:
    struct TreeNode {
        int val; //    val is student ID
        
        string strID; //student ID in string form
        string strName; //student name
        
        TreeNode* left;
        TreeNode* right;

        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, string id, string name) : val(x), strID(id), strName(name), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;
    BST::TreeNode* helperInsert(TreeNode* helpRoot, int key, string id, string name);
    void helperInorder(TreeNode* helpRoot, int& count);
    void helperPreorder(TreeNode* helpRoot, int& count);
    void helperPostorder(TreeNode* helpRoot, TreeNode* trueRoot);
    
public:
    int nodeNum = 0;

    void inorder();
    void preorder();
    void postorder();
    void insert(int key, string id, string name);

    void searchID(string key, string& name);
    
    void printLevelCount();
    int height(TreeNode* root);
    int bFactor(TreeNode* root);

    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* balancer(TreeNode* node);

    void searchName(string name);
    void searchNameHelper(TreeNode* helpRoot, string name, bool& spotted);
    
    void removeId(int key);
    TreeNode* removeIdhelp(TreeNode* root, int& key, bool& worked);
    
    void removeInorder(int key);
    TreeNode* idInorderIterator(TreeNode* root, int& count, int& key, bool& found);
};


//Print Inorder
//Print out a comma separated inorder traversal of the names in the tree.
void BST::inorder() { //Taken from the sample code Project 1 wrapped BST example
    int count = 0;
    helperInorder(this->root, count);
    cout << endl;
}
void BST::helperInorder(BST::TreeNode* helpRoot, int& count) {
    if (helpRoot == nullptr)
        cout << "";
    else {
        helperInorder(helpRoot->left, count);
        cout << helpRoot->strName;
        count++;
        if (count < nodeNum) cout << ", ";
        helperInorder(helpRoot->right, count);
    }
}


//Print Preorder     Print out a comma separated preorder traversal of the names in the tree.
void BST::preorder() {
    int count = 0;
    helperPreorder(this->root, count);
    cout << endl;
}
void BST::helperPreorder(BST::TreeNode* helpRoot, int& count) { 
    if (helpRoot == nullptr){
        cout << "";
    }
    else {
        cout << helpRoot->strName;
        count++;
        if(count < nodeNum) cout << ", ";  //Stops printing commas when the last name displayed by comparing node count and current nodes iterated through
        helperPreorder(helpRoot->left, count);
        helperPreorder(helpRoot->right, count);
    }
}


//printPostorder      Print out a comma separated postorder traversal of the names in the tree.
void BST::postorder() {
    helperPostorder(this->root, this->root);
    cout << endl;
}
void BST::helperPostorder(BST::TreeNode* helpRoot, BST::TreeNode* trueRoot) {
    
    if (helpRoot == nullptr) {
        cout << "";
    }
    else {
        helperPostorder(helpRoot->left, trueRoot);
        helperPostorder(helpRoot->right, trueRoot);
        cout << helpRoot->strName;
        if (helpRoot->val != trueRoot->val) //Stop printing commas when the root is reached, since this will be the last node in postorder
            cout << ", ";
    }
}

//insert NAME ID
//    Add a Student object into the tree with the specified name, NAMEand GatorID number, ID.
//  Balance the tree automatically if necessary.
//The ID must be unique.
//The IDand NAME must satisfy the constraints stated below.
//Also, prints “successful” if insertion is successfuland prints “unsuccessful” otherwise.
//NAME identifier will be separated by double inverted commas for parsing, e.g. "Josh Smith".

void BST::insert(int key, string id, string name) { //Sample code Project 1 wrapped BST example
    this->root = helperInsert(this->root, key, id, name);
}
BST::TreeNode* BST::helperInsert(TreeNode* helpRoot, int key, string id, string name) {
    if (helpRoot == nullptr){
        cout << "successful" << endl;
        nodeNum++;
        return new TreeNode(key, id, name);
    }
    else if (key < helpRoot->val)
        helpRoot->left = helperInsert(helpRoot->left, key, id, name);
    else if (key > helpRoot->val)
        helpRoot->right = helperInsert(helpRoot->right, key, id, name);
    else{
        cout << "unsuccessful" << endl;
    }
    return balancer(helpRoot);
}


int BST::height(TreeNode* root) { //Sample code from Module 5 stepik solutions
    if (root == nullptr)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

int BST::bFactor(TreeNode* root) { //Sample code from Module 5 stepik solutions
    int balanceFactor;
    if (root == nullptr)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    balanceFactor = leftHeight - rightHeight; 
    return balanceFactor;
}

// Helper function to perform a left rotation on a subtree rooted at node
BST::TreeNode* BST::rotateLeft(TreeNode* node) { //Sample code from Module 5 stepik solutions
    TreeNode* rightChild = node->right;
    node->right = rightChild ->left;
    rightChild->left = node;
    return rightChild;
}

// Helper function to perform a right rotation on a subtree rooted at node
BST::TreeNode* BST::rotateRight(TreeNode* node) { //Sample code from Module 5 stepik solutions
    TreeNode* leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

// Helper function to balance a subtree rooted at node
BST::TreeNode* BST::balancer(TreeNode* node) {
    int bf = bFactor(node);
    if (bf > 1 && (bFactor(node->left) < 0)) { // Left Right rotation
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    else if (bf > 1 && !(bFactor(node->left) < 0)) { //Right rotation
        return rotateRight(node);
    }
    else if (bf < -1 && (bFactor(node->right) > 0)) { //Right Left Rotation
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    else if (bf < -1 && !(bFactor(node->right) > 0)) { //Left rotation
        return rotateLeft(node);
    }
    else {
        return node;
    }
}


// search ID
//Search for the student with the specified ID from the tree.
//If the ID was found, print out their NAME.
//If the ID does not exist within the tree, print “unsuccessful”.

void BST::searchID(string key, string& name) {
    TreeNode* iter = root;
    while (iter != nullptr) {
        if (iter->val == stoi(key)) { //Node reached
            name = iter->strName;
            iter = nullptr;
        }
        else if (stoi(key) < iter->val) { //Enter the left subtree
            iter = iter->left;
        }
        else if (stoi(key) > iter->val) { //Enter the right subtree
            iter = iter->right;
        }
        else {
            iter = nullptr;
        }
    }
}


//search NAME
void BST::searchName(string name) { 
    bool spotted = false; //Tracks if a name is found

    searchNameHelper(this->root, name, spotted);
    if (!spotted) {
        cout << "unsuccessful" << endl;
    }
}
void BST::searchNameHelper(BST::TreeNode* helpRoot, string name, bool& spotted) { //Essentially copies the preorder function to iterate through in a preorder manner
    if (helpRoot == nullptr){}    
    else {
        if (helpRoot->strName == name) { 
            cout << helpRoot->strID << endl;
            spotted = true;
        }
        searchNameHelper(helpRoot->left, name, spotted);
        searchNameHelper(helpRoot->right, name, spotted);
    }
}



//remove ID    Find and remove the account with the specified ID from the tree.

void BST::removeId(int key) { //Algorithm from binary tree lecture slides 3-Trees.pdf    p.11
    bool worked = false;
    this->root = removeIdhelp(this->root, key, worked);
    if (worked) {
        cout << "successful" << endl;
        nodeNum--; //Lowers node count, node count is used for inorder deletion.
    }
}
BST::TreeNode* BST::removeIdhelp(TreeNode* root, int& key, bool& worked) {
    if (root == nullptr) { // Key not in tree
        return nullptr;
    }
    else if (key < root->val) {   // Iterates through left subtree
        root->left = removeIdhelp(root->left, key, worked);
        return root;
    }
    else if (key > root->val) {   // Iterates through right subtree
        root->right = removeIdhelp(root->right, key, worked);
        return root;
    }
    else if (key == root->val) {    // Key is in the root
        worked = true;
        if (root->left == nullptr && root->right == nullptr) {  // Root has no children
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr || root->right == nullptr) {     // Root has one child
            TreeNode* newRoot;
            if (root->left != nullptr) { //Only has a left child
                newRoot = root->left;
            }
            else { //Only has a right child
                newRoot = root->right; 
            }
            delete root;
            return newRoot;
        }
        TreeNode* successor = root->right; // Root has two children
        while (successor->left != nullptr) { //Finds the successor
            successor = successor->left;
        }
        root->val = successor->val;
        root->strID = successor->strID;
        root->strName = successor->strName;

        
        root->right = removeIdhelp(root->right, successor->val, worked);
        return root;
    }
    else {
    }
}


// printLevelCount
// Prints the tree levels
void BST::printLevelCount() {
    cout << height(this->root) << endl;     
}


//removeInorder N
void BST::removeInorder(int key) { //Taken from the sample code Project 1 wrapped BST example
    int count = 0;
    bool found = false;
    if (key > nodeNum || key < 0)
        cout << "unsuccessful\n";
    else {
        idInorderIterator(this->root, count, key, found); 
        if(found) // If the node is found, remove it using remove function.
            removeId(key);
        else{
            cout << "unsuccessful\n";
        }
        
    }
}

BST::TreeNode* BST::idInorderIterator(TreeNode* root, int& count, int& key, bool& found) { //Finds the nth node
    if (root == nullptr) {
        return nullptr;
    }
    //Iterate through left subtree
    TreeNode* leftNode = idInorderIterator(root->left, count, key, found);
    if (leftNode != nullptr) {
        return leftNode;
    }
    //Checks the current node 
    if (count == key) {
        key = root->val;
        found = true;
        return root;
    }
    count++;
    // Iterate through right subtree
    return idInorderIterator(root->right, count, key, found);
}


//Parsing and input reading function, iterates for however many times the first number given is
void cmdRead(int i, BST& myBST) {
    
    while (i != 0) {
        
        string str;
        getline(cin, str);

        regex insertCheck("insert \"([^\"]+)\" (\\d{8})");     //Checks for insert
        regex removeCheck("remove (\\d{8})"); //Checks for remove


        if (regex_match(str, insertCheck)) { //Executes insert
            bool idBool = false, nameBool = false; //Bool stores whether the name and id are valid, both must be true for an id to be inserted
            
            string name;
            regex nameCheck("\"([a-zA-Z ]+)\"");
            smatch nameMatches;
            if (regex_search(str, nameMatches, nameCheck)) {
                name = nameMatches[1].str(); //Uses regex to isolate name from input string and then puts it in a name string
                nameBool = true;
            }

            string id;
            regex idCheck("\\b\\d{8}\\b");
            smatch idMatches;
            if (regex_search(str, idMatches, idCheck)) {
                id = idMatches[0].str(); //Uses regex to isolate id from input string and then puts it in a id string
                idBool = true;
            }

            if(nameBool && idBool)  myBST.insert(stoi(id), id, name); //If name and id are valid, they will be inserted as a node
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (str.substr(0, 7) == "search ") { //Search id and search name
            
            string id;
            regex strPattern("\\b\\d{8}\\b"); // Regex to match id
            smatch idMatch;

            string name;
            regex nameCheck("\"([a-zA-Z ]+)\""); // Regex to match name
            smatch nameMatches;

            //Search id
            if (regex_search(str, idMatch, strPattern)) {
                id = idMatch.str();
                string name = "unsuccessful";
                myBST.searchID(id, name);
                cout << name << endl; 
            }
            
            //Search name
            else if (regex_search(str, nameMatches, nameCheck)) {
                name = nameMatches[1].str();
                myBST.searchName(name);
            }

            else { //Search failed
                cout << "unsuccessful" << endl;
            } 
        }
        else if (str.substr(0, 12) == "printInorder") { //Print inorder
            myBST.inorder();
        }
        else if (str.substr(0, 13) == "printPreorder") { //Print preorder
            myBST.preorder();
        }
        else if (str.substr(0, 14) == "printPostorder") { //Print postorder
            myBST.postorder();
        }
        else if (str.substr(0, 15) == "printLevelCount") { //Print level count
            myBST.printLevelCount();
        }
        else if (str.substr(0, 7) == "remove ") { //Remove id functions
            string id;
            regex strPattern("\\b\\d{8}\\b"); // Regex to match id
            smatch idMatch;

            if (regex_search(str, idMatch, strPattern)) { // Remove id
                id = idMatch.str();
                myBST.removeId(stoi(id));
            }
            else {
                cout << "unsuccessful" << endl;
            }
        }
        else if (str.substr(0, 14) == "removeInorder ") { //Remove inorder
            int leng = str.length();
            int n = stoi(str.substr(14,str.length()-14)); //Isolates nth node to remove 
            myBST.removeInorder(n);
        }
        else {
            cout << "unsuccessful\n";
        }
        i--;
    }
}


int main() {
    BST myBST;

    string input;
    getline(cin, input);

    regex obj("\\b[1-9]\\d{0,2}\\b|1000"); //Checks if command count is valid

    
    bool myTextContainsRegex = regex_search(input, obj);
    
    if (myTextContainsRegex) {
        cmdRead(stoi(input), myBST);
    }
}
