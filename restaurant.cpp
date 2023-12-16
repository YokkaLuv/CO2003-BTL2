#include "main.h"
class Restaurant;
class HuffmanTree;
class Hashing;
class MinHeap;
int MAXSIZE;
//GOJO RESTAURANT ################################################################################################################

class Hash {
public:
    int value;
    Hash* left;
    Hash* right;
    Hash(int val) :value(val),left(nullptr),right(nullptr) {}
};

class BST {
public:
    Hash* root;
    queue<int> datalog;
    BST() {
        root = nullptr;
    }
    ~BST() {
        destructBST(root);
    }

    void destructBST(Hash* node) {
        if (node) {
            destructBST(node->left);
            destructBST(node->right);
            delete node;
        }
    }   
    Hash* insertHash(Hash* node,int x) {
        if (!node)
            return new Hash(x);
        if (x < node->value)
            node->left = insertHash(node->left, x);
        else 
            node->right = insertHash(node->right, x);

        return node;
    }

    void insertBST(int value) {
        datalog.push(value);
        root = insertHash(root,value);
    }
    Hash* delRecur(Hash* a, int x) {
        if (a == nullptr) {
            return a;
        }

        if (x < a->value) {
            a->left = delRecur(a->left, x);
        } else if (x > a->value) {
            a->right = delRecur(a->right, x);
        } else {
            if (!a->left ) {
                Hash* tmp = a->right;
                delete a;
                return tmp;
            } else if (!a->right) {
                Hash* tmp = a->left;
                delete a;
                return tmp;
            }

            Hash* tmp = minValueNode(a->right);
            a->value = tmp->value;
            a->right = delRecur(a->right, tmp->value);
        }
        return a;
    }

    Hash* minValueNode(Hash* root) {
        Hash* current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void deleteBST(){
        if(!datalog.empty()){
            int x=datalog.front();
            datalog.pop();
            root = delRecur(root,x);
        }
    }
    void printInOrder(Hash * root) {
        if (root != nullptr) {
            printInOrder(root->left);
            cout << root->value << endl;
            printInOrder(root->right);
        }
    }

};

class Hashing {
public:
    vector<BST> zone;
    Hashing() {
        zone.resize(MAXSIZE);
    }

    void insertHash(int value,int index) {
       if(index < 0 || index >= MAXSIZE)
            return ;
        zone[index].insertBST(value);
    }

    void PrintBST(int index) {
        if (index >= static_cast<int>(zone.size()) ||index < 0) {
            cerr << "Index out of range" << endl;
            return;
        }
        zone[index].printInOrder(zone[index].root);

    }
};

//END GOJO RESTAURANT ############################################################################################################

//SUKUNA RESTAURANT ##############################################################################################################

class ListNode {
    public:
    int data;
    ListNode* next;
    ListNode(int val) : data(val), next(nullptr) {}
};

class MinHeap {
    private:

    void reHeapUp(int index) {
        while (index > 0 && countNodes(heap[(index - 1) / 2].first) > countNodes(heap[index].first)) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    void reHeapDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < static_cast<int>(heap.size()) && countNodes(heap[left].first) < countNodes(heap[smallest].first)) {
            smallest = left;
        }

        if (right < static_cast<int>(heap.size()) && countNodes(heap[right].first) < countNodes(heap[smallest].first)) {
            smallest = right;
        }

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            reHeapDown(smallest);
        }
    }

    public:
    ~MinHeap() {
        for (auto& pair : heap) {
            ListNode* current = pair.first;
            while (current != nullptr) {
                ListNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }
    vector<pair<ListNode*,int>> heap;
    vector<int> change;
    int checkchange(int ID){
        for(size_t i=0;i<change.size();i++){
            if(ID==change[i])
                return i;
        }
        return -1;
    }
    void updatechange(int ID){
        int k=checkchange(ID);
        if(k!=-1)
            change.erase(change.begin()+k);
        change.insert(change.begin(),ID);
    }
    int countNodeID(int ID){
        for(size_t i=0;i<heap.size();i++){
            if(ID==heap[i].second){
                return countNodes(heap[i].first);
            }
        }
        return -1;
    }
    void addkhach(int ID,int val){
        updatechange(ID);
        int k=-1;
        for(size_t i=0;i<heap.size();i++){
            if(heap[i].second==ID){
                k=i;
                break;
            }
        }
        ListNode *tmp=new ListNode(val);
        if(k==-1){ //chua co khu vuc ID
           insertHeap(nullptr,ID);
           for(size_t i=0;i<heap.size();i++){
            if(heap[i].second==ID){
                k=i;
                break;
            }
        }
        }

        if(heap[k].first==NULL)
            heap[k].first=tmp;
        else {
            tmp->next=heap[k].first;
            heap[k].first=tmp;
        }
        reHeapDown(k);
        reHeapUp(k);
    }
    void deleteFIFO(int ID){
        int k=-1;
        for(size_t i=0;i<heap.size();i++){
            if(ID==heap[i].second){
                k=i;
                break;
            }
        }
        ListNode *ys=heap[k].first;
        if(k==-1 || !ys) return ;

        updatechange(ID);
        if(!ys->next){
            cout<<ys->data<<"-"<<ID<<endl;
            heap[k].first=nullptr;
        }
        else {
        while(ys->next->next)
            ys=ys->next;
        cout<<ys->next->data<<"-"<<ID<<endl;
        ys->next=nullptr;
        }
        reHeapUp(k);
        reHeapDown(k);
    }
    void delNoClient(){
        for(size_t i=0;i<heap.size();i++){
            if(!heap[i].first){
                heap[i]=heap.back();
                heap.pop_back();
                reHeapUp(i);
                reHeapDown(i);
            }
        }
    }
    void printLIFO(int ID){
        int k=-1;
        for(size_t i=0;i<heap.size();i++){
            if(ID==heap[i].second){
                k=i;
                break;
            }
        }
        if(k==-1) return ;
        ListNode *a=heap[k].first;
        while(a){
            cout<<a->data<<" ";
            a=a->next;
        }
        cout<<endl;
    }
    void insertHeap(ListNode* element,int k) {
        heap.emplace_back(element,k);
        int index = heap.size() - 1;
        reHeapUp(index);
    }
    int countNodes(ListNode* head) {
        int count = 0;
        ListNode* sub = head;
        while (sub) {
            count++;
            sub = sub->next;
        }
        return count;
    }
    void printNumCus(ListNode *a,int ID,int num){
        int i=0;
        while(i<num && a){
            cout<<ID<<"-"<<a->data<<endl;
            a=a->next;
            i++;
        }
    }
    void printHeap(int num,int i = 0){
            if(i >= static_cast<int>(heap.size()))
                return ;
            printNumCus(heap[i].first ,heap[i].second ,num);
            printHeap(num, 2*i+1);
            printHeap(num, 2*i+2);
    }
};

//END SUKUNA RESTAURANT ##########################################################################################################

//CLIENT TREE ####################################################################################################################

struct Node {
  public:
  char c;
  int fre;
  Node *l,*r;
  Node(char c ,int fre ,Node *left ,Node *right):c(c),fre(fre),l(left),r(right){}
};

struct CompareFrequency {
    bool operator()(Node *left, Node *right) {
        if (left->fre == right->fre) {
            if((islower(left->c) && islower(right->c))|| (isupper(left->c) && isupper(right->c)))
            return left->c > right->c;
            else return left->c<right->c;
        }
        return left->fre > right->fre;
    }
};

inline bool SortFrequency(const pair<Node*, int>& a, const pair<Node*, int>& b) {
    if (a.first->fre == b.first->fre) {
        return a.second < b.second;
    }
    return a.first->fre < b.first->fre;
}

class HuffmanTree{
    public:
    Node *treeH;
    unordered_map<char, string> huffhuff;
    HuffmanTree():treeH(nullptr){}
    ~HuffmanTree() {
            destructHuff(treeH);
        }
        void destructHuff(Node* node) {
            if (node) {
                destructHuff(node->l);
                destructHuff(node->r);
                delete node;
            }
        }
    int getHeightNode(Node *node){
        if (node == NULL)
            return 0;
        int lh = getHeightNode(node->l);
        int rh = getHeightNode(node->r);
        return (lh > rh ? lh : rh) + 1;
    }
    Node* rotateRight(Node* root) {
        //TODO: Rotate and return new root after rotate
        Node *x=root->l;
        Node *y=x->r;
        x->r=root;
        root->l=y;
        return x;
    }

    Node* rotateLeft(Node* root) {
        //TODO: Rotate and return new root after rotate
        Node *x=root->r;
        Node *y=x->l;
        x->l=root;
        root->r=y;
        return x;
    }
    int getBalance(Node *cur){
        if(!cur) return 0;
        return getHeightNode(cur->l)-getHeightNode(cur->r);
    }
  Node *balancevip(Node *cur) {
    int balance = getBalance(cur);
    if (balance > 1) {
      if (getBalance(cur->l) >= 0) {
       
        return rotateRight(cur);
      } else {
        cur->l = rotateLeft(cur->l);
        return rotateRight(cur);
      }
    }
    if (balance < -1) {
      if (getBalance(cur->r) <= 0) {
        return rotateLeft(cur);
      } else {
        cur->r = rotateRight(cur->r);
        return rotateLeft(cur);
      }
    }
    return cur;
  }
  Node *balanceTree(Node *&tree, int &rotate, bool &xxx) {
    if (!tree || rotate < 0)
      return nullptr;
    if (rotate == 0)
      return tree;
    int balanceNum = getBalance(tree);

    while (abs(balanceNum) > 1) {
      if (rotate == 0)
        return tree;
      if (treeH->c != '\0') {
        xxx = true;
        return nullptr;
      }
      tree = balancevip(tree);
      
      balanceNum = getBalance(tree);
      rotate--;
    }

    tree->l = balanceTree(tree->l, rotate, xxx);
    tree->r = balanceTree(tree->r, rotate, xxx);
    return tree;
  }
    void encodetree(Node* root, string str){
        if(!root)
            return ;
        if(root->c!='\0')
            huffhuff[root->c]=str;
        encodetree(root->l,str+"0");
        encodetree(root->r,str+"1");
    }
void printqueue(priority_queue<Node *,vector<Node *>,CompareFrequency> ys){
  while(!ys.empty()){
    cout<<ys.top()->c<<" "<<ys.top()->fre<<endl;
    ys.pop();
  }
}
void buildHuffman(string ss){
  unordered_map<char, int> freq;
    for (char c : ss)
      freq[c]++;
    
    priority_queue<Node *, vector<Node *>, CompareFrequency> arr;
   
    for (pair<char, int> k : freq) {
      arr.push(new Node(k.first, k.second, nullptr, nullptr));
    }

    vector<pair<Node *,int>> ys;
    int thutu=0;
    while (!arr.empty()) {
      ys.push_back(make_pair(arr.top(),thutu++));
      arr.pop();
    }
    while (ys.size() != 1) {

      Node *left = ys[0].first;
      ys.erase(ys.begin());
      Node *right = ys[0].first;
      ys.erase(ys.begin());
      int sum = left->fre + right->fre;
      Node *k = new Node('\0', sum, left, right); 
      k->l=balancevip(k->l);
      k->r=balancevip(k->r);
      k=balancevip(k);
      bool ok = 0;
      int rot=3;
      k=balanceTree(k,rot,ok);
      if (ok)
        return;
      ys.push_back(make_pair(k,thutu++));
      sort(ys.begin(), ys.end(), SortFrequency); 
      
    }

    Node *tmp = ys[0].first;
    treeH = tmp;


    encodetree(treeH, "");
      }
};

int BinToDec(string binaryString) {
    int decimalValue = 0;
    int length = binaryString.length();

    for (int i = 0; i < length; ++i) {
        if (binaryString[i] == '1') {
            decimalValue += pow(2, length - i - 1);
        }
    }

    return decimalValue;
}

//END CLIENT TREE ################################################################################################################

//CORE CODE ######################################################################################################################

class Restaurant {
  public:	
  int RESULT;
  Hashing GOJO;
  MinHeap SUKUNA;
  Node *treeHand;
    Restaurant() {
        treeHand=nullptr;
    }

    void add(){
        int ID=RESULT%MAXSIZE+1;
      cout<<RESULT<<" "<<ID<<endl;
        if(RESULT%2!=0){
            GOJO.insertHash(RESULT,ID-1);
        }
        else {
            SUKUNA.addkhach(ID,RESULT);
        }
    }
void  CEASAR(unordered_map<char,int> a,string &name){
    for(size_t i=0;i<name.length();i++){
        char b = name[i];
        int shift=a[b];
        if (islower(b))
            name[i]= char(int(b + shift - 'a') % 26 + 'a');
        else if (isupper(b))
            name[i]= char(int(b + shift - 'A') % 26 + 'A');
    }
}

void LAPSE(string &name){
    HuffmanTree lor;
    RESULT=-999;
    unordered_set<char> uniqueChars;
    for (char ch : name) 
    uniqueChars.insert(ch);
    if (uniqueChars.size() < 3) {
        return ;
    }
    unordered_map<char,int> a;
    for(char c: name)
        a[c]++;
    CEASAR(a,name);
    cout<<name<<endl;
    lor.buildHuffman(name);
    if(lor.huffhuff.empty()) return ;
    treeHand=lor.treeH;
    string tmpstr="";
    for(char i:name){
        tmpstr+=lor.huffhuff[i];
    }
    string result="";
    int j=0;
    while(j<10){
        result+=tmpstr[tmpstr.length()-1-j++];
    }
    RESULT=BinToDec(result);
    if(RESULT!=-999)
        add();
}
    // Function to calculate binomial coefficient
    long long tohop(int n, int k) {
        long long res = 1;
        if (k > n - k) k = n - k;
        for (int i = 0; i < k; ++i) {
            res *= (n - i);
            res /= (i + 1);
        }
        return res;
    }

    int Permutations(vector<int>& values) {
        if (values.empty()) return 1;
        int root = values.back();  // Last element is the root in post-order
        vector<int> leftSubTree, rightSubTree;
        for (size_t i = 0; i < values.size() - 1; ++i) {
            if (values[i] < root) leftSubTree.push_back(values[i]);
            else rightSubTree.push_back(values[i]);
        }
        int leftCount = Permutations(leftSubTree);
        int rightCount = Permutations(rightSubTree);
        // Calculate the number of ways to interleave left and right subtrees
        int totalNodes = leftSubTree.size() + rightSubTree.size();
        long long ways= tohop(totalNodes, leftSubTree.size());

        return leftCount * rightCount * ways;
    }

    void duyetPostOrder(Hash *root,vector<int> &ys){
        if(root){
            duyetPostOrder(root->left,ys);
            duyetPostOrder(root->right,ys);
            ys.push_back(root->value);
        }
    }

    void KOKUSEN(){
      if(GOJO.zone.empty())
          return ;
        vector<int> a;
        for(int i=0 ;i < MAXSIZE ;i++){
            if(!GOJO.zone[i].root)
                continue;
            duyetPostOrder(GOJO.zone[i].root,a);
            int Y=Permutations(a);
            Y = Y % MAXSIZE;
            a.clear();
            for(int j = 0 ;j < Y ;j++){
                if(GOJO.zone[i].root)
                    GOJO.zone[i].deleteBST();
            }
        }
    }

    void KEITEIKEN(int num){
      if(SUKUNA.heap.empty())
          return ;
        vector<int> log;
        for(size_t i=0;i<SUKUNA.heap.size();i++){
            if(!SUKUNA.heap[i].first)
                break;
            log.push_back(SUKUNA.heap[i].second);
        }
        for(size_t i=0;i<log.size()-1;i++){
            for(size_t j=i+1;j<log.size();j++){
                if((SUKUNA.countNodeID(log[i])>SUKUNA.countNodeID(log[j])) || (SUKUNA.countNodeID(log[i])==SUKUNA.countNodeID(log[j]) && SUKUNA.checkchange(log[i])<SUKUNA.checkchange(log[j])))
                    swap(log[i],log[j]);
            }
        }
        for(int i=0;i<num;i++){
            for(int j=0;j<num;j++){
                SUKUNA.deleteFIFO(log[i]);
            }
        }
        SUKUNA.delNoClient();
    }

    void printHuffman(Node* root) {
        if (root != nullptr) {
            printHuffman(root->l);
            if(root->c!='\0')cout << root->c <<"\n";
            else cout<<root->fre<<"\n";
            printHuffman(root->r);
        }
    }
    
    void HAND(){
        printHuffman(treeHand);
    }

    void LIMITLESS(int num){
        GOJO.PrintBST(num-1);
    }

    void CLEAVE(int num){
        SUKUNA.printHeap(num);
    }
};

//END CORE CODE ##################################################################################################################

//READ FILE RUN ##################################################################################################################

void simulate(string filename)
{
  ifstream ss(filename);
  string str ,NUM,maxsize,name;
  bool maxsizecheck=0;
  while(ss>>str){
      if(str=="MAXSIZE"){
          ss>>maxsize;
          MAXSIZE=stoi(maxsize);
          maxsizecheck=1;
          break;
      }
  }
  if(!maxsizecheck){
      cout<<"chua gan dc MAXSIZE\n";
      return ;
  }
  Restaurant *ys=new Restaurant();
  while(ss>> str){
      cout<<str<<endl;
      if(str=="LAPSE"){
          ss>>name;
          ys->LAPSE(name);
      }
      else if(str=="KOKUSEN"){
          ys->KOKUSEN();
      }
      else if(str=="KEITEIKEN"){
          ss>>NUM;
          ys->KEITEIKEN(stoi(NUM));
      }
      else if(str=="HAND"){
          ys->HAND();
      }
      else if(str=="LIMITLESS"){
          ss>>NUM;
          ys->LIMITLESS(stoi(NUM));
      }
      else {
          ss>>NUM;
          ys->CLEAVE(stoi(NUM));
      }
  }
}