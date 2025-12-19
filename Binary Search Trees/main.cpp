/** 
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2025. 5. 26
  *
  */
  
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <algorithm>
#include <vector>
#include <random>

#include <iostream>
 
using namespace std;

	//ADD will be the 'variable' more like a function, the more accurate terminology. And we want ADD to be a funciton to do complicated

	int ADD(int x = 2, int y = 12, int z = 43){

		int ADDITION = x+y+z;

	}

	

	//now that we created a function called ADD, it can do 2 instructions that does addition and printing.



int main()
{
	typedef Entry<int, float> EntryType;

	LinkedBinaryTree<EntryType> t;
	
	std::cout << "Initial size : " << t.size() << std::endl;
	
	t.addRoot();
	
	std::cout << "Now size with root : " << t.size() << std::endl;
	
	
	//
	//
	//
	SearchTree<EntryType>	st;
	
	std::cout << "Size before insertions : " << st.size() << std::endl;
	st.insert(1, 2.5);
	st.insert(3, 4.5);
	st.insert(7, 5.5);
	st.insert(2, 1.5);
	st.insert(3, 8.5);
	std::cout << "Size after insertions : " << st.size() << std::endl;

	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}
		
	st.erase(3);
	std::cout << "Size after deleting an element : " << st.size() << std::endl;
	for(SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it)
	{
			std::cout << (*it).key() << " , " << (*it).value() << std::endl;
	}	
	
	std::cout << "------------AVL" << std::endl;
	
	//
	//
	//
	AVLTree<EntryType>	avl;

	avl.insert(10, 1.0);
	avl.insert(20, 2.0);
	avl.insert(30, 3.0);
	avl.insert(25, 2.5);
	avl.insert(5, 0.5);
	avl.insert(3, 0.3);
	avl.insert(8, 0.8);

	std::cout << "Size of rebalanced tree: " << avl.size() << std::endl;
	avl.erase(10);
	std::cout << "After erase(10) size: " << avl.size() << std::endl;

// Print all nodes to check structure
for (auto it = avl.begin(); it != avl.end(); ++it)
    std::cout << (*it).key() << " , " << (*it).value() << std::endl;

	
	// random test
	int nElem = 100000; //100000000;
	
	int *key = new int[nElem*2];
	float *val = new float[nElem*2];
	
	std::srand(std::time(0)); // use current time as seed for random generator
   
		  
	// initialize
	for(int i=0; i<nElem*2; i++)
	{
		key[i] = std::rand();
		val[i] = (float) std::rand()/RAND_MAX * 20000;
	}
		

    //
    // AVL tree Insert test
    //	
	clock_t tm;
    tm = clock();
	for(int i=0; i<nElem; i++)
	{
		if ((i+1)% (nElem/10) == 0){
			std::cout << "Inserting key[" << i << "] = " << key[i] << std::endl;}
		avl.insert(key[i], val[i]);
	}
	tm = clock() - tm;
	printf ("It took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	

    //
    // AVL tree Find test
    //	
    // This example is finding keys (i=nElem~2*nElem-1) different from the 
	// inserted keys (i=0~nElem-1), but the design of the experiment is 
	// your own choice. No need to follow this example.
	//
	tm = clock();
	for(int i=nElem; i<nElem*2; i++) 
	{
		avl.find(key[i]);
	}
	tm = clock() - tm;
	printf ("It took me %f seconds.\n",((float)tm)/(float)CLOCKS_PER_SEC);
	
	

	//stuffs
	std::cout<<"\n\n\n";

	typedef unsigned   K;
    typedef float      V;
    std::srand((unsigned)std::time(NULL));
	const unsigned sizes[] = {100, 10000, 1000000};

	std::cout<<"Test: number of keys; tree; operation type; time\n\n";
    for (unsigned tsize : sizes) {
		//not counting time for key generation
        std::vector<K> keys(tsize);
        for (unsigned i = 0; i < tsize; ++i) keys[i] = i;
        std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(keys.begin(), keys.end(), g);

        //insert timing
		std::cout<<"Timing of Inserts:\n";
        {
            SearchTree<EntryType> bst;
            clock_t t0 = clock();
            for (auto k : keys) bst.insert(k, V(k));
            double dt = double(clock()-t0)/CLOCKS_PER_SEC;
            std::printf("%u, BST, insert, %.6f\n", tsize, dt);
        }
        {
            AVLTree<EntryType> avl;
            clock_t t0 = clock();
            for (auto k : keys) avl.insert(k, V(k));
            double dt = double(clock()-t0)/CLOCKS_PER_SEC;
            std::printf("%u, AVL, insert, %.6f\n\n", tsize, dt);
        }

        //find timing reusing trees
		std::cout<<"Timing of Find (reused trees):\n";
        {
            SearchTree<EntryType> bst;
            for (auto k : keys) bst.insert(k, V(k));

            clock_t t0 = clock();
            for (auto k : keys) bst.find(k);
            double dt = double(clock()-t0)/CLOCKS_PER_SEC;
            std::printf("%u, BST, find, %.6f\n", tsize, dt);
        }
        {
            AVLTree<EntryType> avl;
            for (auto k : keys) avl.insert(k, V(k));
			
			clock_t t0 = clock();
            for (auto k : keys) avl.find(k);
            double dt = double(clock()-t0)/CLOCKS_PER_SEC;
            std::printf("%u, AVL, find, %.6f\n\n", tsize, dt);
        }


    }



	std::cout<<ADDITION<<"\n";

	return 0;
}