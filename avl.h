// An AVL tree node 
struct Node { 
  string data; 
  Node *kiri; 
  Node *kanan; 
  int tinggi; 

  Node(const string &k) { 
    data = k; 
    kiri = nullptr; 
    kanan = nullptr; 
    tinggi = 1; 
  }
}; 

// A utility function to 
// get the tinggi of the tree 
int getTinggi(Node *N) { 
  if (N == nullptr) 
    return 0; 
  return N->tinggi; 
} 

// A utility function to kanan 
// rotate subtree rooted with y 
Node *rotasiKanan(Node *y) { 
  Node *x = y->kiri; 
  Node *T2 = x->kanan; 

  // Perform rotation 
  x->kanan = y; 
  y->kiri = T2; 

  // Update heights 
  y->tinggi = 1 + max(getTinggi(y->kiri), getTinggi(y->kanan)); 
  x->tinggi = 1 + max(getTinggi(x->kiri), getTinggi(x->kanan)); 

  // Return new root 
  return x; 
} 

// A utility function to kiri rotate 
// subtree rooted with x 
Node *rotasiKiri(Node *x) { 
  Node *y = x->kanan; 
  Node *T2 = y->kiri; 

  // Perform rotation 
  y->kiri = x; 
  x->kanan = T2; 

  // Update heights 
  x->tinggi = 1 + max(getTinggi(x->kiri), getTinggi(x->kanan)); 
  y->tinggi = 1 + max(getTinggi(y->kiri), getTinggi(y->kanan)); 

  // Return new root 
  return y; 
} 

// Get balance factor of node N 
int seimbang(Node *N) { 
  if (N == nullptr) 
    return 0; 
  return getTinggi(N->kiri) - getTinggi(N->kanan); 
} 

// Recursive function to insert a data in 
// the subtree rooted with node 
Node* insert(Node* node, const string &data) { 
  
  // Perform the normal BST insertion
  if (node == nullptr) 
    return new Node(data); 

  if (data < node->data) 
    node->kiri = insert(node->kiri, data); 
  else if (data > node->data) 
    node->kanan = insert(node->kanan, data); 
  else // Equal datas are not allowed in BST 
    return node; 

  // Update tinggi of this ancestor node 
  node->tinggi = 1 + max(getTinggi(node->kiri), getTinggi(node->kanan)); 

  // Get the balance factor of this ancestor node 
  int balance = seimbang(node); 

  // If this node becomes unbalanced, 
  // then there are 4 cases 

  // Left Left Case 
  if (balance > 1 && data < node->kiri->data) 
    return rotasiKanan(node); 

  // Right Right Case 
  if (balance < -1 && data > node->kanan->data) 
    return rotasiKiri(node); 

  // Left Right Case 
  if (balance > 1 && data > node->kiri->data) { 
    node->kiri = rotasiKiri(node->kiri); 
    return rotasiKanan(node); 
  } 

  // Right Left Case 
  if (balance < -1 && data < node->kanan->data) { 
    node->kanan = rotasiKanan(node->kanan); 
    return rotasiKiri(node); 
  } 

  // Return the (unchanged) node pointer 
  return node; 
} 

// A utility function to print 
void inorder(Node* root) {
  if (root != nullptr) {
  inorder(root->kiri);
  cout <<"|-"<< root->data << endl;
  inorder(root->kanan);
  }
}

void preorder(Node *root){
  if(root != nullptr){
  cout<<"|-"<<root->data<<endl;
  preorder(root->kiri);
  preorder(root->kanan);
  }
}

void postorder(Node *root){
  if(root != nullptr){
  postorder(root->kiri);
  postorder(root->kanan);
  cout<<"|-"<<root->data<<endl;
  }
}
