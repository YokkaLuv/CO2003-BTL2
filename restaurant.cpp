#include "main.h"


int MAXSIZE;

class HashNode {
public:
  int value;
  HashNode *left;
  HashNode *right;
  HashNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
  HashNode *root;
  queue<int> FIFO;
  BST() { root = nullptr; }

  HashNode *insertNode(HashNode *node, int value) {
    if (!node)
      return new HashNode(value);

    if (value < node->value)
      node->left = insertNode(node->left, value);
    else
      node->right = insertNode(node->right, value);

    return node;
  }

  void insertBST(int value) {
    FIFO.push(value);
    root = insertNode(root, value);
  }
  HashNode *delRecur(HashNode *cur, int x) {
    if (cur == nullptr) {
      return cur;
    }

    if (x < cur->value) {
      cur->left = delRecur(cur->left, x);
    } else if (x > cur->value) {
      cur->right = delRecur(cur->right, x);
    } else {
      if (!cur->left) {
        HashNode *temp = cur->right;
        delete cur;
        return temp;
      } else if (!cur->right) {
        HashNode *temp = cur->left;
        delete cur;
        return temp;
      }

      HashNode *tmp = minValueNode(cur->right);
      cur->value = tmp->value;
      cur->right = delRecur(cur->right, tmp->value);
    }
    return cur;
  }

  HashNode *minValueNode(HashNode *node) {
    HashNode *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }
  void deleteBST() {
    if (!FIFO.empty()) {
      int x = FIFO.front();
      FIFO.pop();
      root = delRecur(root, x);
    }
  }
  void printInOrder(HashNode *node) {
    if (node != nullptr) {
      printInOrder(node->left);
      cout << node->value << " ";
      printInOrder(node->right);
    }
  }
};

class HashTable {

public:
  vector<BST> table;
  HashTable() { table.resize(MAXSIZE); }

  void insertHash(int value, int index) {
    // size_t index = hashFunction(value);
    if (index < 0 || index >= MAXSIZE)
      return;
    table[index].insertBST(value);
  }
  void PrintBST(int index) {
    if (index >= table.size() || index < 0) {
      cerr << "Index out of range" << endl;
      return;
    }
    table[index].printInOrder(table[index].root);
    cout << endl;
  }
};
class ListNode {
public:
  int data;
  ListNode *next;
  ListNode(int val) : data(val), next(nullptr) {}
};

class MinHeap {
private:
  void reHeapUp(int index) {
    while (index > 0 && countNodes(heap[(index - 1) / 2].first) >
                            countNodes(heap[index].first)) {
      swap(heap[index], heap[(index - 1) / 2]);
      index = (index - 1) / 2;
    }
  }

  void reHeapDown(int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap.size() &&
        countNodes(heap[left].first) < countNodes(heap[smallest].first)) {
      smallest = left;
    }

    if (right < heap.size() &&
        countNodes(heap[right].first) < countNodes(heap[smallest].first)) {
      smallest = right;
    }

    if (smallest != index) {
      swap(heap[index], heap[smallest]);
      reHeapDown(smallest);
    }
  }

public:
  vector<pair<ListNode *, int>> heap;
  vector<int> change;
  int checkchange(int ID) {
    for (int i = 0; i < change.size(); i++) {
      if (ID == change[i])
        return i;
    }
    return -1;
  }
  void updatechange(int ID) {
    int k = checkchange(ID);
    if (k != -1)
      change.erase(change.begin() + k);
    change.insert(change.begin(), ID);
  }
  int countNodeID(int ID) {
    int k = 0;
    for (int i = 0; i < heap.size(); i++) {
      if (ID == heap[i].second) {
        k = i;
        break;
      }
    }
    return countNodes(heap[k].first);
  }
  void addkhach(int ID, int val) {
    updatechange(ID);
    int k = -1;
    for (int i = 0; i < heap.size(); i++) {
      if (heap[i].second == ID) {
        k = i;
        break;
      }
    }
    ListNode *tmp = new ListNode(val);
    if (k == -1) { // chua co khu vuc ID
      insertHeap(nullptr, ID);
      for (int i = 0; i < heap.size(); i++) {
        if (heap[i].second == ID) {
          k = i;
          break;
        }
      }
    }

    if (heap[k].first == NULL)
      heap[k].first = tmp;
    else {
      tmp->next = heap[k].first;
      heap[k].first = tmp;
    }
    reHeapDown(k);
    reHeapUp(k);
  }
  void deleteFIFO(int ID) {
    int k = -1;
    for (int i = 0; i < heap.size(); i++) {
      if (ID == heap[i].second) {
        k = i;
        break;
      }
    }
    ListNode *ys = heap[k].first;
    if (k == -1 || !ys)
      return;

    updatechange(ID);
    if (!ys->next) {
      cout << ys->data << "-" << ID << endl;
      heap[k].first = nullptr;
    } else {
      while (ys->next->next)
        ys = ys->next;
      cout << ys->next->data << "-" << ID << endl;
      ys->next = nullptr;
    }
    reHeapUp(k);
    reHeapDown(k);
  }
  void deleteKhuvuc() {
    for (int i = 0; i < heap.size(); i++) {
      if (!heap[i].first) {
        heap[i] = heap.back();
        heap.pop_back();
        reHeapUp(i);
        reHeapDown(i);
      }
    }
  }
  void printLIFO(int ID) {
    int k = -1;
    for (int i = 0; i < heap.size(); i++) {
      if (ID == heap[i].second) {
        k = i;
        break;
      }
    }
    if (k == -1)
      return;
    ListNode *a = heap[k].first;
    while (a) {
      cout << a->data << " ";
      a = a->next;
    }
    cout << endl;
  }
  void insertHeap(ListNode *element, int k) {
    heap.emplace_back(element, k);
    int index = heap.size() - 1;
    reHeapUp(index);
  }
  int countNodes(ListNode *head) {
    int count = 0;
    ListNode *current = head;
    while (current) {
      count++;
      current = current->next;
    }
    return count;
  }
  void printNumCus(ListNode *a, int ID, int num) {
    int i = 0;
    while (i < num && a) {
      cout << ID << "-" << a->data << endl;
      a = a->next;
      i++;
    }
  }
  void CLEAVEfake(int num, int j = 0) {
    if (j >= heap.size())
      return;
    printNumCus(heap[j].first, heap[j].second, num);
    CLEAVEfake(num, 2 * j + 1);
    CLEAVEfake(num, 2 * j + 2);
  }
};
class Node {
public:
  char c;
  int fre;
  Node *l, *r;
  Node(char c, int fre, Node *left, Node *right)
      : c(c), fre(fre), l(left), r(right) {}
};
bool compareNode(const Node *a, const Node *b) { return a->fre < b->fre; }
class HuffmanTree {

public:
  Node *treeH;
  unordered_map<char, string> huffhuff;
  HuffmanTree() : treeH(nullptr) {}

  int getHeightNode(Node *node) {
    if (node == NULL)
      return 0;
    int lh = getHeightNode(node->l);
    int rh = getHeightNode(node->r);
    return (lh > rh ? lh : rh) + 1;
  }
  Node *rotateRight(Node *root) {
    // TODO: Rotate and return new root after rotate
    Node *x = root->l;
    Node *y = x->r;
    x->r = root;
    root->l = y;
    return x;
  }

  Node *rotateLeft(Node *root) {
    // TODO: Rotate and return new root after rotate
    Node *x = root->r;
    Node *y = x->l;
    x->l = root;
    root->r = y;
    return x;
  }
  int getBalance(Node *cur) {
    if (!cur)
      return 0;
    return getHeightNode(cur->l) - getHeightNode(cur->r);
  }
  Node *balancevip(Node *cur, int &rotate) {
    int balance = getBalance(cur);
    if (balance > 1) {
      rotate--;
      if (getBalance(cur->l) >= 0) {
        return rotateRight(cur);
      } else {
        cur->l = rotateLeft(cur->l);
        return rotateRight(cur);
      }
    }
    if (rotate <= 0)
      return cur;
    if (balance < -1) {
      rotate--;
      if (getBalance(cur->r) <= 0) {
        return rotateLeft(cur);
      } else {

        cur->r = rotateRight(cur->r);
        return rotateLeft(cur);
      }
    }
    return cur;
  }
  void balanceTree(Node *&tree, int &rotate, bool &xxx) {
    if (!tree || rotate <= 0)
      return;

    queue<Node *> q;
    q.push(tree);
    int first = 0;
    while (!q.empty()) {
      if (rotate <= 0)
        return;
      Node *cur = q.front();
      q.pop();
      int balance = getBalance(cur);
      while (abs(balance) > 1) {
        if (rotate <= 0)
          return;

        cur = balancevip(cur, rotate);
        if (first == 0) {
          treeH = cur;
          if (treeH->c != '\0') {
            xxx = 1;
            return;
          }
        }
        // cout<<"sau khi rotate: "<<cur->c<<" "<<cur->fre<<endl;
        balance = getBalance(cur);
      }
      if (cur->l)
        q.push(cur->l);
      if (cur->r)
        q.push(cur->r);
      first++;
    }
  }
  void encodetree(Node *root, string str) {
    if (!root)
      return;
    if (root->c != '\0')
      huffhuff[root->c] = str;
    encodetree(root->l, str + "0");
    encodetree(root->r, str + "1");
  }

  void buildHuffman(vector<pair<char, int>> ys) {
    int rot = 3;
    vector<Node *> arr;
    for (auto k : ys)
      arr.push_back(new Node(k.first, k.second, nullptr, nullptr));
    while (arr.size() != 1) {
      Node *left = arr.front();
      arr.erase(arr.begin());
      Node *right = arr.front();
      arr.erase(arr.begin());
      int sum = left->fre + right->fre;
      arr.push_back(new Node('\0', sum, left, right));
      sort(arr.begin(), arr.end(), compareNode);
    }

    Node *tmp = arr.front();
    treeH = tmp;
    bool xxx = 0;
    balanceTree(tmp, rot, xxx);
    if (xxx)
      return;
    encodetree(treeH, "");
    cout << "Huffman Codes are :\n" << endl;
    for (auto pair : huffhuff) {
      cout << pair.first << " " << pair.second << "\n";
    }
  }
};

class Restaurant {

public:
  int RESULT;
  HashTable gojo;
  MinHeap sukuna;
  Node *treeHand;
  Restaurant() {}

  void add() {
    int ID = RESULT % MAXSIZE + 1;
    if (RESULT % 2 != 0) {
      gojo.insertHash(RESULT, ID - 1);
    } else {
      sukuna.addkhach(ID, RESULT);
    }
  }

  bool check(char a, char b) {
    // support cho sortLap
    if ((islower(a) && islower(b)) || (isupper(a) && isupper(b)))
      return a > b ? true : false;
    if (islower(a))
      return false;
    else
      return true; // Neu a upper b lower thi doi vi tri b vs a
  }
  void sortLap(vector<pair<char, int>> &ys) {
    for (int i = 1; i < ys.size(); i++) {
      int tmp2 = ys[i].second;
      char tmp1 = ys[i].first;
      int j;
      for (j = i; j > 0 &&
                  (ys[j - 1].second > tmp2 ||
                   (ys[j - 1].second == tmp2 && check(ys[j - 1].first, tmp1)));
           j--) {
        ys[j].first = ys[j - 1].first;
        ys[j].second = ys[j - 1].second;
      }
      ys[j].first = tmp1;
      ys[j].second = tmp2;
    }
  }
  int checklap(vector<pair<char, int>> ys, char c) {
    for (int i = 0; i < ys.size(); i++) {
      if (c == ys[i].first)
        return i;
    }
    return -1;
  }
  string caesar(vector<pair<char, int>> &ys) {
    string result = "";
    for (int i = 0; i < ys.size(); i++) {
      char c = ys[i].first;
      int shift = ys[i].second;
      if (islower(c))
        c = char(int(c + shift - 'a') % 26 + 'a');
      else if (isupper(c))
        c = char(int(c + shift - 'A') % 26 + 'A');
      while (ys[i].second > 0) {
        result += c;
        ys[i].second--;
      }
    }

    return result;
  }

  int binaryToDecimal(string binaryString) {
    int decimalValue = 0;
    int length = binaryString.length();

    for (int i = 0; i < length; ++i) {
      if (binaryString[i] == '1') {
        decimalValue += pow(2, length - i - 1);
      }
    }

    return decimalValue;
  }
  void LAPSE(string &name) {
    HuffmanTree lor;
    RESULT = -999;
    unordered_set<char> uniqueChars;
    for (char ch : name)
      uniqueChars.insert(ch);

    if (uniqueChars.size() < 3) {
      return;
    }

    vector<pair<char, int>> ys;
    ys.emplace_back(name[0], 1);
    for (int i = 1; i < name.length(); i++) {
      int k = checklap(ys, name[i]);
      if (k == -1) {
        ys.emplace_back(name[i], 1);
      } else {
        ys[k].second++;
      }
    }
    name = caesar(ys);
    cout << name << endl;
    ys.clear();
    ys.emplace_back(name[0], 1);
    for (int i = 1; i < name.length(); i++) {
      int k = checklap(ys, name[i]);
      if (k == -1) {
        ys.emplace_back(name[i], 1);
      } else {
        ys[k].second++;
      }
    }
    sortLap(ys);

    lor.buildHuffman(ys);
    if (lor.huffhuff.empty())
      return;
    treeHand = lor.treeH;
    string tmpstr = "";
    for (int i = 0; i < name.length(); i++) {
      tmpstr += lor.huffhuff[name[i]];
    }
    string result = "";
    int j = 0;
    while (j < 10) {
      result += tmpstr[tmpstr.length() - 1 - j++];
    }
    RESULT = binaryToDecimal(result);
    cout << "RESULT la:" << RESULT << endl;

    if (RESULT != -999)
      add();
  }
  void CLEAVEold(int num) {
    cout << "num la:" << num << endl;
    sukuna.printLIFO(num);
  }
  void CLEAVE(int num) { sukuna.CLEAVEfake(num); }
  void LIMITLESS(int num) {
    cout << "num la:" << num << endl;
    gojo.PrintBST(num - 1);
  }
  void calculateFak(int fact[], int N) {
    fact[0] = 1;
    for (long long int i = 1; i < N; i++) {
      fact[i] = fact[i - 1] * i;
    }
  }

  int NCR(int fact[], int N, int R) {
    if (R > N)
      return 0;
    int res = fact[N] / fact[R];
    res /= fact[N - R];

    return res;
  }
  int countHoanVi(vector<int> &arr, int fact[]) {

    int N = arr.size();

    if (N <= 2) {
      return 1;
    }

    vector<int> leftSubTree;

    vector<int> rightSubTree;

    int root = arr[0];

    for (int i = 1; i < N; i++) {
      if (arr[i] < root) {
        leftSubTree.push_back(arr[i]);
      } else {
        rightSubTree.push_back(arr[i]);
      }
    }
    int N1 = leftSubTree.size();
    // int N2 = rightSubTree.size();
    int countLeft = countHoanVi(leftSubTree, fact);
    int countRight = countHoanVi(rightSubTree, fact);

    return NCR(fact, N - 1, N1) * countLeft * countRight;
  }
  void duyetPostOrder(HashNode *rt, vector<int> &ys) {
    if (rt) {
      // LRN
      duyetPostOrder(rt->left, ys);
      duyetPostOrder(rt->right, ys);
      ys.push_back(rt->value);
    }
  }
  void KOKUSEN() {
    vector<int> ys;
    for (int i = 0; i < MAXSIZE; i++) {
      if (!gojo.table[i].root)
        continue;
      duyetPostOrder(gojo.table[i].root, ys);
      int n = ys.size();
      int fak[n];
      calculateFak(fak, n);
      int Y = countHoanVi(ys, fak);
      cout << "Khu vuc :" << i << endl;
      Y = Y % MAXSIZE;
      cout << "Y la:" << Y << endl;
      ys.clear();
      for (int j = 0; j < Y; j++) {
        if (gojo.table[i].root)
          gojo.table[i].deleteBST();
      }
    }
  }

  void KEITEIKEN(int num) {
    vector<int> vlad;
    for (int i = 0; i < MAXSIZE; i++) {
      if (sukuna.heap[i].first)
        vlad.push_back(sukuna.heap[i].second);
    }

    for (int i = 0; i < vlad.size() - 1; i++) {
      for (int j = i + 1; j < vlad.size(); j++) {
        if ((sukuna.countNodeID(vlad[i]) > sukuna.countNodeID(vlad[j])) ||
            (sukuna.countNodeID(vlad[i]) == sukuna.countNodeID(vlad[j]) &&
             sukuna.checkchange(vlad[i]) < sukuna.checkchange(vlad[j])))
          swap(vlad[i], vlad[j]);
      }
    }
    cout << "Vlad la:";
    for (auto k : vlad)
      cout << k << " ";
    cout << endl;
    for (int i = 0; i < num; i++) {
      for (int j = 0; j < num; j++) {
        sukuna.deleteFIFO(vlad[i]);
      }
    }
    sukuna.deleteKhuvuc();
  }
  void printHuffman(Node *node) {
    if (node != nullptr) {
      printHuffman(node->l);
      if (node->c != '\0')
        cout << node->c << "\n";
      else
        cout << node->fre << "\n";
      printHuffman(node->r);
    }
  }
  void HAND() { printHuffman(treeHand); }
};

void simulate(string filename) {
  ifstream ss(filename);
  string str, NUM, maxsize, name;
  Restaurant *ys = new Restaurant();
  while (ss >> str) {
    if (str == "MAXSIZE") {
      ss >> maxsize;
      MAXSIZE = stoi(maxsize);
    } else if (str == "LAPSE") {
      ss >> name;
      ys->LAPSE(name);
    } else if (str == "KOKUSEN") {
      ys->KOKUSEN();
    } else if (str == "KEITEIKEN") {
      ss >> NUM;
      ys->KEITEIKEN(stoi(NUM));
    } else if (str == "HAND") {
      ys->HAND();
    } else if (str == "LIMITLESS") {
      ss >> NUM;
      ys->LIMITLESS(stoi(NUM));
    } else if (str == "CLEAVE") {
      ss >> NUM;
      ys->CLEAVE(stoi(NUM));
    }
  }
}

