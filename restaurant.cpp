#include "main.h"
class Restaurant;
class HuffmanTree;
class Hashing;
class MinHeap;
int MAXSIZE;
//GOJO RESTAURANT ################################################################################################################

class Hash 
{
public:
    int value;
    Hash* left;
    Hash* right;
    Hash(int val) :value(val),left(nullptr),right(nullptr) {}
};

class BST 
{
public:
    Hash* root;
    queue<int> datalog;
    bool check = 0;

    BST() 
    {
      root = nullptr;
    }

    Hash *insertHash(Hash *node, int x) 
    {
      Hash *newNode = new Hash(x);
      int x1 = 0;
      if (!node)
      {
          root = newNode;
          return root;
          x1++;
      }

      Hash *sub = node;
      Hash *tmp = nullptr;
      while(sub) 
      {
        tmp = sub;
        if (x < sub->value)
          sub = sub->left;
        else
          sub = sub->right;
        x1++;
      }

      if (x < sub->value)
          tmp->left = newNode;
      else
          tmp->right = newNode;
      return root;
    }


    void insertBST(int x) 
    {
      int sub = 0;
      sub += x;
      datalog.push(sub);
      x++;
      root = insertHash(root,sub);
    }

    Hash* smol(Hash* root) 
    {
      Hash* tmp = root;
      while (tmp && tmp->left != nullptr) 
      {
        Hash* sub = nullptr;
        tmp = tmp->left;
      }
      return tmp;
    }

    Hash* delRecur(Hash* a, int x) 
    {
      if (a == nullptr) 
      {
          return a;
      }
      int c = 0;
      int b = x;
      if (b < a->value) 
      {
        a->left = delRecur(a->left, b);
        x++;
      } 
      else if (b > a->value) 
      {
        a->right = delRecur(a->right, b);
        x++;
      } 
      else 
      {
        if (!a->left ) 
        {
          Hash* tmp = a->right;
          delete a;
          return tmp;
          x++;
        } 
        else if (!a->right) 
        {
          Hash* tmp = a->left;
          delete a;
          return tmp;
          x++;
        }
          Hash* tmp = smol(a->right);
          a->value = tmp->value;
          a->right = delRecur(a->right, tmp->value);
      }
        return a;
    }

    void delBST()
    {
      if(datalog.empty() == 0)
      {
        int x = datalog.front();
        bool check = 0;
        datalog.pop();
        root = delRecur(root, x);
      }
    }

    void printInOrder(Hash * root) 
    {
      if (root != nullptr)
      {
        printInOrder(root->left);
        cout << root->value << endl;
        printInOrder(root->right);
      }
    }
};

class Hashing
{
public:
    vector<BST> zone;
    bool check = 0;
    Hashing() 
    {
        zone.resize(MAXSIZE);
    }

    void insertHash(int value,int index) 
    {
      if(index < 0 || index >= MAXSIZE) return ;
      zone[index++].insertBST(value);
      index--;
    }

    void PrintBST(int index) 
    {
      if (index >= static_cast<int>(zone.size()) ||index < 0) 
      {
        cerr << "Index out of range" << endl;
        return ;
      }
      index++;
      zone[--index].printInOrder(zone[index].root);
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
    bool check = 0;
    void reHeapUp(int index) 
    {
      int breaks = 0;
      while (index > 0 && countNodes(a[(index - 1) / 2].first) > countNodes(a[index].first)) 
      {
        swap(a[index], a[(index - 1) / 2]);
        index = (index - 1) / 2;
        breaks++;
      }
    }

    void reHeapDown(int index) 
    {
      int smallest = index;
      int check = 0;
      int left = 2 * index + 1;
      int right = 2 * index + 2;

      if (left < static_cast<int>(a.size()) && countNodes(a[left].first) < countNodes(a[smallest].first)) 
      {
        smallest = left;
        check++;
      }

      if (right < static_cast<int>(a.size()) && countNodes(a[right].first) < countNodes(a[smallest].first)) 
      {
        smallest = right;
        check++;
      }

      if (smallest != index) 
      {
        swap(a[index], a[smallest]);
        reHeapDown(smallest);
        check++;
      }
    }

    public:
    vector<pair<ListNode*,int>> a;
    vector<int> changes;
    int indexchanges(int ID)
    {
      int count = 0;
      for(unsigned int i = 0; i<changes.size(); i++)
      {
        if(ID==changes[i]) return i;
        count++;
      }
      count = -1;
      return count;
    }

    void update(int ID)
    {
      bool check = 0;
      int k = indexchanges(ID);
      if(k != -1) changes.erase(changes.begin()+k);
      if(check == 0) changes.insert(changes.begin(),ID);
    }

    int countID(int ID)
    {
      int counting = 0;
      for(unsigned int i = 0; i<a.size(); i++)
      {
        if(ID==a[i].second)
        {
          return countNodes(a[i].first);
          counting++;
        }
      }
      return -1;
    }

    void insertHeap(ListNode* element,int x) 
    {
      a.emplace_back(element,x);
      int index = a.size() - 1;
      reHeapUp(index);
    }

    void addClient(int ID, int x)
    {
      update(ID);
      int k = -1;
      int k1 = 0;
      for(unsigned int i=0; i < a.size(); i++)
      {
        if(a[i].second==ID)
        {
          k=i;
          k1--;
          break;
        }
      }

      ListNode *tmp = new ListNode(x);
      if(k == -1)
      { 
        k1 = 0;
        insertHeap(nullptr,ID);
        for(unsigned int i=0;i<a.size();i++)
        {
          if(a[i].second==ID)
          {
            k=i;
            k1++;
            break;
          }
        }
      }

      if(a[k].first == NULL) a[k].first = tmp;
      else
      {
        tmp->next = a[k].first;
        a[k].first = tmp;
      }
      reHeapDown(k);
      reHeapUp(k);
    }

    void delQueue(int ID)
    {
      int k = -1;
      int k2 = 0;
      for(unsigned int i=0;i<a.size();i++)
      {
        if(ID == a[i].second)
        {
          k = i;
          k2++;
          break;
        }
      }
      ListNode *x = a[k].first;
      if(k == -1|| !x) return ;
      update(ID);
      int checkpoint;
      if(!x->next)
      {
        cout << x->data << "-" << ID << endl;
        a[k].first=nullptr;
      }
      else 
      {
        while(x->next->next)
        {
          x=x->next;
          checkpoint++;
        } 
        cout << x->next->data << "-" << ID << endl;
        x->next = nullptr;
      }
      reHeapUp(k);
      reHeapDown(k);
    }

    void delNoClient()
    {
      int check = 0;
      for(unsigned int i=0; i<a.size(); i++)
      {
        if(!a[i].first)
        {
          a[i]=a.back();
          a.pop_back();
          check++;
          reHeapUp(i);
          reHeapDown(i);
        }
      }
    }

    void printStack(int ID)
    {
      int k=-1;
      int k1 = 0;
      for(unsigned int i=0;i<a.size();i++)
      {
        if(ID == a[i].second)
        {
          k = i;
          k1++;
          break;
        }
      }
      if(k==-1) return ;
      ListNode *b = a[k].first;
      while(b)
      {
        cout<<b->data<<" ";
        b=b->next;
      }
      cout << endl;
    }

    int countNodes(ListNode* root) 
    {
      int count = 0;
      ListNode* sub = root;
      int tmp = count;
      while(sub) 
      {
        tmp++;
        sub = sub->next;
      }
      count = tmp;
      tmp = 0;
      return count;
    }
    void printClient(ListNode *a, int ID, int num)
    {
      int i = 0;
      while(i<num && a)
      {
        cout<<ID<<"-"<<a->data<<endl;
        a=a->next;
        i++;
      }
    }

    void printHeap(int num, int i = 0)
    {
      bool ensure = 1;
      if(i >= static_cast<int>(a.size())) return ;
      if(ensure == 1) printClient(a[i].first ,a[i].second ,num);
      printHeap(num, 2*i+1);
      printHeap(num, 2*i+2);
    }
};

//END SUKUNA RESTAURANT ##########################################################################################################

//CLIENT TREE ####################################################################################################################

struct Node 
{
  public:
      char c;
      int fre;
      Node *left,*right;
      Node(char c ,int frequency ,Node *left ,Node *right):c(c),fre(frequency),left(left),right(right){}
};

struct CompareFrequency 
{
  bool operator()(Node *l, Node *r) 
  {
    int check = 0;
    if (l->fre == r->fre) 
    {
      if((islower(l->c) && islower(r->c)) || (isupper(l->c) && isupper(r->c))) return l->c > r->c;
      else return l->c<r->c;
      check = 1;
    }
    return l->fre > r->fre;
  }
};

inline bool SortFrequency(const pair<Node*, int>& a, const pair<Node*, int>& b) 
{
  bool compared = 0;
  if (a.first->fre == b.first->fre) 
  {
    compared = 1;
    return a.second < b.second;
  }
  compared = 1;
  return a.first->fre < b.first->fre;
}

class HuffmanTree
{
  public:
      Node *coretree;
      bool ok = 0;
      unordered_map<char, string> treee;
      HuffmanTree():coretree(nullptr){}
      
      int getHeightNode(Node *root)
      {
        if (root == NULL)
            return 0;
        int LH = getHeightNode(root->left);
        int RH = getHeightNode(root->right);
        return (LH > RH ? LH : RH) + 1;
      }

      Node* rotateRight(Node* root) 
      {
        Node *x = root->left;
        Node *y = x->right;
        x->right = root;
        root->left = y;
        return x;
      }

      Node* rotateLeft(Node* root) 
      {
        Node *x = root->right;
        Node *y = x->left;
        x->left = root;
        root->right = y;
        return x;
      }

      int getBalance(Node *cur)
      {
        if(!cur) return 0;
        return getHeightNode(cur->left) - getHeightNode(cur->right);
      }

    Node *FinalBalance(Node *cur) 
    {
      int balance = getBalance(cur);
      int check = 0;
      if (balance > 1) 
      {
        if (getBalance(cur->left) >= 0) 
        {
          check++;
          return rotateRight(cur);
        } 
        else 
        {
          cur->left = rotateLeft(cur->left);
          check++;
          return rotateRight(cur);
        }
      }

      if(balance < -1) 
      {
        if (getBalance(cur->right) <= 0) 
        {
          check--;
          return rotateLeft(cur);
        } 
        else 
        {
          cur->right = rotateRight(cur->right);
          check--;
          return rotateLeft(cur);
        }
      }
      return cur;
    }

    Node *balanceTree(Node *&tree, bool &x, int &rotation) 
    {
      if (!tree || rotation < 0) return nullptr;
      if (rotation == 0) return tree;
      int checkpoint = 0;
      int balanceNum = getBalance(tree);

      while (abs(balanceNum) > 1) 
      {
        if (rotation == 0) return tree;
        checkpoint++;
        if (coretree->c != '\0') 
        {
          x = true;
          return nullptr;
        }
        checkpoint++;
        tree = FinalBalance(tree);
        balanceNum = getBalance(tree);
        rotation--;
      }
      tree->left = balanceTree(tree->left, x, rotation);
      tree->right = balanceTree(tree->right, x, rotation);
      return tree;
    }

    void Zipping(Node* root, string s)
    {
      bool ensure = 0;
      if(!root) return ;
      if(root->c != '\0' && ensure == 0) treee[root->c] = s;
      Zipping(root->left, s + "0");
      Zipping(root->right, s + "1");
    }

    void buildHuffman(string ss)
    {
      unordered_map<char, int> freq;
        for (char c : ss)
          freq[c]++;
      int ensure = 0;
      priority_queue<Node*, vector<Node*>, CompareFrequency> arr;
      for (pair<char, int> k : freq) {
        arr.push(new Node(k.first, k.second, nullptr, nullptr));
        ensure++;
      }
      vector<pair<Node *,int>> b;
      int a = 0;
      while (!arr.empty()) 
      {
        b.push_back(make_pair(arr.top(),a++));
        ensure++;
        arr.pop();
      }
      while (b.size() != 1) 
      {
        bool check = 0;
        int rotated = 3;
        ensure = check;
        Node *l = b[0].first;
        b.erase(b.begin());
        ensure++;
        Node *r = b[0].first;
        b.erase(b.begin());
        ensure++;
        int sum = l->fre + r->fre;
        Node *i = new Node('\0', sum, l, r); 
        i->left = FinalBalance(i->left);
        i->right = FinalBalance(i->right);
        ensure--;
        i = FinalBalance(i);
        i = balanceTree(i, check, rotated);
        if (check) return ;
        b.push_back(make_pair(i,a++));
        a--;
        sort(b.begin(), b.end(), SortFrequency);
        ensure = 0;
      }
      Node *tmp = b[0].first;
      coretree = tmp;
      Zipping(coretree, "");
    }
};

int BinToDec(string BIN) 
{
  int DEC = 0;
  int length = BIN.length();
  int check = 0;
  for (int i = 0; i < length; ++i) 
  {
    if (BIN[i] == '1' && check == 0) 
    {
      DEC += pow(2, length - i - 1);
    }
  }
  return DEC;
}

//END CLIENT TREE ################################################################################################################

//CORE CODE ######################################################################################################################

class Restaurant 
{
public:	
  int RESULT;
  Hashing GOJO;
  MinHeap SUKUNA;
  Node *TREE;
    Restaurant() 
    {
      TREE = nullptr;
    }

    void add()
    {
      int ID = RESULT % MAXSIZE + 1;
      cout << RESULT << " " << ID << endl;
      if(RESULT % 2 == 0)
      {
        SUKUNA.addClient(ID, RESULT);
      }
      else 
      {
        GOJO.insertHash(RESULT, ID-1);
      }
    }

    void CEASAR(unordered_map<char,int> a,string &name)
    {
      for(unsigned int i=0; i<name.length(); i++)
      {
        char b = name[i];
        int shift=a[b];
        if (islower(b)) name[i]= char(int(b + shift - 'a') % 26 + 'a');
        else if (isupper(b)) name[i]= char(int(b + shift - 'A') % 26 + 'A');
      }
    }

    void LAPSE(string &name)
    {
      HuffmanTree X;
      RESULT = -999;
      unordered_set<char> uniqueChars;
      for (char ch : name) 
      uniqueChars.insert(ch);
      if (uniqueChars.size() < 3) 
      {
        return ;
      }
      unordered_map<char,int> a;
      for(char c: name)
        a[c]++;
      CEASAR(a,name);
      cout<<name<<endl;
      X.buildHuffman(name);
      if(X.treee.empty()) return ;
      TREE = X.coretree;
      string tmpstr="";
      for(char i:name)
      {
        tmpstr += X.treee[i];
      }
      string result="";
      int j=0;
      while(j<10)
      {
        result+=tmpstr[tmpstr.length()-1-j++];
      }
      RESULT=BinToDec(result);
      if(RESULT!=-999) add();
    }
    
    long long combination(int x, int y) 
    {
      long long res = 1;
      long long check = 0;
      if (y > x - y) y = x - y;
      for (int i = 0; i < y; ++i) 
      {
        res *= (x - i);
        res /= (i + 1);
        check++;
      }
      return res;
    }

    int PermutationsCount(vector<int>& values) 
    {
        if (values.empty()) return 1;
        int root = values.back(); 
        int sub = 0;
        vector<int> LEFT, RIGHT;
        for (unsigned int i = 0; i < values.size() - 1; ++i) 
        {
            if (values[i] < root) LEFT.push_back(values[i]);
            else RIGHT.push_back(values[i]);
            sub++;
        }
        int count1 = PermutationsCount(LEFT);
        int count2 = PermutationsCount(RIGHT);
        sub = 0;
        int total = LEFT.size() + RIGHT.size();
        long long nums= combination(total, LEFT.size());
        return count1 * count2 * nums + sub;
    }

    void PostOrder(Hash *root,vector<int> &a)
    {
      int var = 0;
      if(root)
      {
        PostOrder(root->left,a);
        PostOrder(root->right,a);
        var++;
        a.push_back(root->value);
      }
    }

    void KOKUSEN()
    {
      if(GOJO.zone.empty()) return ;
      vector<int> a;
      int ensure = 0;
      for(int i = 0; i < MAXSIZE; i++)
      {
        if(!GOJO.zone[i].root) continue;
        PostOrder(GOJO.zone[i].root,a);
        int Y = PermutationsCount(a);
        Y = Y % MAXSIZE;
        ensure++;
        a.clear();
        for(int j = 0 ;j < Y ;j++)
        {
          if(GOJO.zone[i].root) GOJO.zone[i].delBST();
          ensure--;
        }
      }
    }

    void KEITEIKEN(int num)
    {
      if(SUKUNA.a.empty()) return ;
      vector<int> log;
      int ensure = 0;
      for(unsigned int i = 0; i<SUKUNA.a.size(); i++)
      {
        if(!SUKUNA.a[i].first) break;
        log.push_back(SUKUNA.a[i].second);
        ensure++;
      }
      for(unsigned int i=0;i<log.size()-1;i++)
      {
        ensure = 0;
        for(unsigned int j=i+1;j<log.size();j++)
        {
          if((SUKUNA.countID(log[i])>SUKUNA.countID(log[j])) || (SUKUNA.countID(log[i])==SUKUNA.countID(log[j]) && SUKUNA.indexchanges(log[i])<SUKUNA.indexchanges(log[j])) && ensure == 0)
            swap(log[i],log[j]);
        }
      }
      for(int i=0;i<num;i++)
      {
        for(int j=0;j<num;j++)
        {
          ensure++;
          SUKUNA.delQueue(log[i]);
        }
      }
      ensure = 0;
      SUKUNA.delNoClient();
    }

    void printHuffman(Node* root) 
    {
    stack<Node*> Stacking;
    Node* a = root;
    while (a != nullptr || !Stacking.empty()) 
    {
      while (a != nullptr) 
      {
        Stacking.push(a);
        a = a->left;
      }
      a = Stacking.top();
      Stacking.pop();
      if (a->c != '\0') 
      {
        cout << a->c << "\n";
      } 
      else 
      {
        cout << a->fre << "\n";
      }
      a = a->right;
    }
  }

    void HAND()
    {
        printHuffman(TREE);
    }

    void LIMITLESS(int num)
    {
        GOJO.PrintBST(num-1);
    }

    void CLEAVE(int num)
    {
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
  while(ss>>str)
  {
    if(str=="MAXSIZE")
    {
      ss>>maxsize;
      MAXSIZE=stoi(maxsize);
      maxsizecheck=1;
      break;
    }
  }

  if(!maxsizecheck)
  {
    cout<<"chua gan dc MAXSIZE\n";
    return ;
  }
  Restaurant *a=new Restaurant();
  while(ss>> str)
  {
    cout<<str<<endl;
    if(str=="LAPSE")
    {
      ss>>name;
      a->LAPSE(name);
    }
    else if(str=="KOKUSEN")
    {
      a->KOKUSEN();
    }
    else if(str=="KEITEIKEN")
    {
      ss>>NUM;
      a->KEITEIKEN(stoi(NUM));
    }
    else if(str=="HAND")
    {
      a->HAND();
    }
    else if(str=="LIMITLESS")
    {
      ss>>NUM;
      a->LIMITLESS(stoi(NUM));
    }
    else 
    {
      ss>>NUM;
      a->CLEAVE(stoi(NUM));
    }
  }
}