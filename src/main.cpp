#include <iostream>
#include <regex>
using namespace std;
//MAKE SURE UR USING c++ 14!!!!!!!!!!!!


/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

/*
remove ID
    Find and remove the account with the specified ID from the tree.
    [Optional: Balance the tree automatically if necessary. We will test your code only on cases where the tree will be balanced before and after the deletion. So you can implement a BST deletion and still get full credit]
    If deletion is successful, print “successful”.
    If the ID does not exist within the tree, print “unsuccessful”.
    You must prioritize replacing a removed node with its inorder successor for the case where the deleted node has two children.

search ID
    Search for the student with the specified ID from the tree.
    If the ID was found, print out their NAME.
    If the ID does not exist within the tree, print “unsuccessful”.

search NAME
    Search for the student with the specified name, NAME in the tree.
    If the student name was found, print the associated ID.
    If the tree has more than one object with the same NAME, print each ID on a new line with no other spaces and in the same relative order as a pre-order traversal.
    If the name does not exist within the tree, print “unsuccessful”.
    NAME identifier will be surrounded by double quotes for parsing, e.g. "Josh Smith".

printInorder
    Print out a comma separated inorder traversal of the names in the tree.

printPreorder
    Print out a comma separated preorder traversal of the names in the tree.

printPostorder
    Print out a comma separated postorder traversal of the names in the tree.

printLevelCount
    Prints the number of levels that exist in the tree.
    Prints 0 if the head of the tree is null. For example, the tree in Fig. 1 has 4 levels.

removeInorder N
    Remove the Nth GatorID from the inorder traversal of the tree (N = 0 for the first item, etc).
    If removal is successful, print “successful”.
    [Optional: Balance the tree automatically if necessary. We will test your code only on cases where the tree will be balanced before and after the deletion. So you can implement a BST deletion and still get full credit]
    If the Nth GatorID does not exist within the tree, print “unsuccessful”.

*/


class BST
{
private:
    struct TreeNode
    {
        ///review here
        TreeNode(string id, string name) {
            gatorId = id;
            intId = stoi(gatorId);
            Name = name;
        }


        int val;
        int height; // Or Balance Factor
        int bfactor;

        //Add a Student object into the tree with the specified name, NAMEand GatorID number, ID.
        string gatorId;
        int intId;
        string Name;
        TreeNode* left;
        TreeNode* right;
        
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        /*
        TreeNode(int x) {
            val = x;
            left = nullptr;
            right = nullptr;
        }*/
        TreeNode(int x, TreeNode* l, TreeNode* r) {
            val = x;
            left = l;
            right = r;
        }
        
    };

    TreeNode* root = nullptr;
    BST::TreeNode* helperInsert(TreeNode* helpRoot, int key);
    void helperInorder(TreeNode* helpRoot);

public:
    void inorder();
    void insert(int key);
};




void BST::helperInorder(BST::TreeNode* helpRoot)
{
    if (helpRoot == NULL)
        std::cout << "";
    else
    {
        helperInorder(helpRoot->left);
        std::cout << helpRoot->val << " ";
        helperInorder(helpRoot->right);
    }
}


BST::TreeNode* BST::helperInsert(TreeNode* helpRoot, int key)
{
    if (helpRoot == nullptr)
        return new TreeNode(key);
    else if (key < helpRoot->val)
        helpRoot->left = helperInsert(helpRoot->left, key);
    else
        helpRoot->right = helperInsert(helpRoot->right, key);

    return helpRoot;
}


void BST::inorder()
{
    helperInorder(this->root);
}

void BST::insert(int key)
{
    this->root = helperInsert(this->root, key);

}


////////////////////////////////////////



TreeNode* insert(string name, string id) {  //TreeNode* root, int key
    /*insert NAME ID
        Add a Student object into the tree with the specified name, NAMEand GatorID number, ID.
        Balance the tree automatically if necessary.
        The ID must be unique.
        The IDand NAME must satisfy the constraints stated below.
        Also, prints “successful” if insertion is successfuland prints “unsuccessful” otherwise.
        NAME identifier will be separated by double inverted commas for parsing, e.g. "Josh Smith". */

    if (root == nullptr)
		return new TreeNode(key);
	else if (key < root->val)
		root->left = insert(root->left, key);
	else
		root->right = insert(root->right, key);

	//find height

	return root;
}




cmdRead(int i, BST& myBST) {
    //int i = 1;
    while (i !=0) {
        string str;
        cin >> str;
        
        //regex obj = regex("^[0-9]$");
        //bool name = regex_search(input, obj);
        //////////

        regex insertCheck("insert \"([^\"]+)\" (\\d{8})");
        regex removeCheck("remove (\\d{8})");

        //("insert\\s+\"([^\"]+)\"\\s+(\\d{8})");
        if (regex_match(str, insertCheck)) { //execute insert
            myBST.insert(id, );
        }
        /*
        if (str.substr(0, 7) == "insert " && ) {
            
        }*/
        else if(regex_match(str, removeCheck)){
            //(str.substr(0, 7) == "remove ") {

        }
        else if (str.substr(0, 7) == "search ") {

        }
        else if (str.substr(0, 12) == "printInorder") {
            myBST.inorder();
        }
        else if (str.substr(0, 13) == "printPreorder") {

        }
        else if (str.substr(0, 14) == "printPostorder") {

        }
        else if (str.substr(0, 15) == "printLevelCount") {

        }
        else if (str.substr(0, 13) == "printInorder ") {

        }
        else {
            cout << "unsuccessful\n";
        }
        i--;
    }

    //insert NAME ID
    //remove ID
    //search ID
    //search NAME
    //printInorder
    //printPreorder
    //printPostorder
    //printLevelCount
    //removeInorder N
}


int main(){
    BST tree;
    
    string input;
    cin >> input;
    regex obj = regex("^[1-1000]$");
    bool myTextContainsRegex = regex_search(input, obj);

    if (myTextContainsRegex) {
        cmdRead(stoi(input), tree);
    }


	return 0;
}


//////////// bullshit, look later
/*
void balanceCheck(TreeNode* root) {
    //
}
rotateLeft(node)
{
    grandchild = node->right->left;
    newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}

rotateLeft(node)
{
    grandchild = node->right->left;
    newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent;
}

*/