  template <typename E>					// constructor
  SearchTree<E>::SearchTree() : T(), n(0)
    { T.addRoot(); T.expandExternal(T.root()); }	// create the super root
  
  template <typename E>					// get virtual root
  typename SearchTree<E>::TPos SearchTree<E>::root() const
    { return T.root().left(); }				// left child of super root
  
   template <typename E>					// iterator to first entry
  typename SearchTree<E>::Iterator SearchTree<E>::begin() {
    TPos v = root();					// start at virtual root
    while (v.isInternal()) v = v.left();		// find leftmost node
    return Iterator(v.parent());
  }
  
  template <typename E>					// iterator to end entry
  typename SearchTree<E>::Iterator SearchTree<E>::end()
    { return Iterator(T.root()); }			// return the super root
    
  template <typename E>					// remove key k entry
  void SearchTree<E>::erase(const K& k) { //throw(NonexistentElement) {
    TPos v = finder(k, root());				// search from virtual root
    if (v.isExternal())					// not found?
      throw "Erase of nonexistent";//NonexistentElement("Erase of nonexistent");
    eraser(v);						// remove it
  }
  
  template <typename E>					// erase entry at p
  void SearchTree<E>::erase(const Iterator& p)
    { eraser(p.v); }
    
  template <typename E>					// find entry with key k
  typename SearchTree<E>::Iterator SearchTree<E>::find(const K& k) {
    TPos v = finder(k, root());				// search from virtual root
    if (v.isInternal()) return Iterator(v);		// found it
    else return end();					// didn't find it
  }  
  
  template <typename E>					// insert (k,x)
  typename SearchTree<E>::Iterator SearchTree<E>::insert(const K& k, const V& x)
    { TPos v = inserter(k, x); return Iterator(v); }  
 
  template <typename E>
  int SearchTree<E>::size() const { return n; }  
    
    
//
// ToDo
//    
 
  template <typename E>					// inorder successor
  typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
   
   // ToDo
    TPos v = this->v;
    if (v.isExternal()) return *this;
    if (v.right().isInternal()) {
      v = v.right();
      while (v.isInternal()) v = v.left();
      this->v = v.parent();
    } else {
      TPos w = v.parent();
      while (w.isInternal() && v == w.right()) {
        v = w;
        w = w.parent();
      }
      this->v = w;
    }
    return *this;
  }
     
    
    
  template <typename E>					// remove utility
  typename SearchTree<E>::TPos SearchTree<E>::eraser(TPos& v) {
       
    // ToDo
    TPos w;
    if (v.left().isExternal()) {
      w = v.right();
      T.removeAboveExternal(v.left());
      n--;
    }
    else if (v.right().isExternal()) {
      w = v.left();
      T.removeAboveExternal(v.right());
      n--;
    }
    else {
      TPos u = v.right();
      while (u.isInternal()) u = u.left();
      TPos w = u.parent();
      (*v).setKey((*w).key());
      (*v).setValue((*w).value());
      T.removeAboveExternal(u);
      n--;
      return w;
    }
    return w.parent();
  }
      
  template <typename E>					// find utility
  typename SearchTree<E>::TPos SearchTree<E>::finder(const K& k, const TPos& v) {
    if (v.isExternal()) return v;
    if (k == (*v).key()) return v;
    else if (k < (*v).key()) return finder(k, v.left());
    else return finder(k, v.right());
  
  }
  
  template <typename E>					// insert utility
  typename SearchTree<E>::TPos SearchTree<E>::inserter(const K& k, const V& x) {
    
    // ToDo
    TPos v = finder(k, root());
    if (v.isInternal()) {
      (*v).setValue(x);
      return v;
    }
    T.expandExternal(v);
    (*v).setKey(k);
    (*v).setValue(x);
    n++;
    return v;
    
  }
  