//
// Implementation
//
template <typename E>					// constructor
AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
int AVLTree<E>::height(const TPos& v) const
  { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
void AVLTree<E>::setHeight(TPos v) {
  int hl = height(v.left());
  int hr = height(v.right());
  (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
}

template <typename E>					// is v balanced?
  bool AVLTree<E>::isBalanced(const TPos& v) const {	
  int bal = height(v.left()) - height(v.right());
  return ((-1 <= bal) && (bal <= 1));
}

template <typename E>					// get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
  TPos zl = z.left();
  TPos zr = z.right();
  if (height(zl) >= height(zr))	{		// left child taller
    if (height(zl.left()) >= height(zl.right()))
      return zl.left();
    else
      return zl.right();
  }
   else{ 						// right child taller
    if (height(zr.right()) >= height(zr.left()))
      return zr.right();
    else
      return zr.left();
   }
  }


//
// ToDo
//

template <typename E>					// remove key k entry
void AVLTree<E>::erase(const K& k) {

    // ToDo
    TPos v = this->finder(k, this->root());
    if (v.isExternal()){
      throw "Erase of Nonexistent";
    }
    TPos w = this->eraser(v);
    rebalance(w);
    
  }

template <typename E>					// insert (k,x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
    // ToDo
    TPos v = this->inserter(k, x);
    //if (this->size() <= 2) return Iterator(this->root());
    if (v.parent().v == NULL) {
      setHeight(v);
      return Iterator(v);}
      setHeight(v);
    rebalance(v);
    return Iterator(v);
  }
  
template <typename E>					// rebalancing utility
void AVLTree<E>::rebalance(const TPos& v) {

  // ToDo
  if (v.parent().v == NULL) return;
  TPos z = v;
    while (z.parent().v != NULL) {
    setHeight(z);
    if (!isBalanced(z)){
    TPos x = tallGrandchild(z);
     z = this->restructure(x);
      setHeight(z.left());
      setHeight(z.right());
      setHeight(z);
    }
    z = z.parent();
  }
}

template <typename E>				// Binary Search Tree Rotation
typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {
  
  if (v.isExternal()) {
    return v.parent();}
  TPos c = v;
  TPos b = c.parent();
  TPos a = b.parent();

  TPos ggp; //grand grand parent
  bool aIsRoot = a.isRoot();
  if (!aIsRoot)
    ggp = a.parent();

  TPos newRoot;          // what we’ll return

  // Case 1: LL
  if ( c == b.left() && b == a.left() ) {
    // right–rotate a around b
    // 1) detach b from ggp
    if (!aIsRoot) {
      if (ggp.left() == a)      ggp.v->left  = b.v;
      else                       ggp.v->right = b.v;
      b.v->par = ggp.v;
    } else {
      // a was root → reattach via super–root’s left child
      TPos sr = this->root();  // super–root
      sr.v->left = b.v;
      b.v->par = sr.v;
    }

    // 2) perform rotation pointers
    a.v->left  = b.v->right;
    if (a.v->left) a.v->left->par = a.v;
    b.v->right = a.v;
    a.v->par   = b.v;

    newRoot = b;
  }
  // Case 2: RR
  else if ( c == b.right() && b == a.right() ) {
    // left–rotate a around b
    if (!aIsRoot) {
      if (ggp.left() == a)      ggp.v->left  = b.v;
      else                       ggp.v->right = b.v;
      b.v->par = ggp.v;
    } else {
      TPos sr = this->root();
      sr.v->left = b.v;
      b.v->par = sr.v;
    }

    a.v->right = b.v->left;
    if (a.v->right) a.v->right->par = a.v;
    b.v->left   = a.v;
    a.v->par    = b.v;

    newRoot = b;
  }
  // Case 3: LR
  else if ( c == b.right() && b == a.left() ) {
    // step 1: left–rotate b around c
    // detach c from a
    a.v->left = c.v;
    c.v->par  = a.v;
    // rotate
    b.v->right = c.v->left;
    if (b.v->right) b.v->right->par = b.v;
    c.v->left   = b.v;
    b.v->par    = c.v;

    // now treat it as LL on a–and new b==c
    TPos bb = c;
    // reattach to ggp
    if (!aIsRoot) {
      if (ggp.left() == a)      ggp.v->left  = bb.v;
      else                       ggp.v->right = bb.v;
      bb.v->par = ggp.v;
    } else {
      TPos sr = this->root();
      sr.v->left = bb.v;
      bb.v->par  = sr.v;
    }
    // right–rotate a around bb
    a.v->left  = bb.v->right;
    if (a.v->left) a.v->left->par = a.v;
    bb.v->right = a.v;
    a.v->par    = bb.v;

    newRoot = bb;
  }
  // Case 4: RL
  else {  // ( c == b.left() && b == a.right() )
    // step 1: right–rotate b around c
    a.v->right = c.v;
    c.v->par   = a.v;
    b.v->left  = c.v->right;
    if (b.v->left) b.v->left->par = b.v;
    c.v->right = b.v;
    b.v->par   = c.v;

    // now treat it as RR with new b==c
    TPos bb = c;
    if (!aIsRoot) {
      if (ggp.left() == a)      ggp.v->left  = bb.v;
      else                       ggp.v->right = bb.v;
      bb.v->par = ggp.v;
    } else {
      TPos sr = this->root();
      sr.v->left = bb.v;
      bb.v->par  = sr.v;
    }
    // left–rotate a around bb
    a.v->right = bb.v->left;
    if (a.v->right) a.v->right->par = a.v;
    bb.v->left = a.v;
    a.v->par   = bb.v;

    newRoot = bb;
  }

  return newRoot;
}

