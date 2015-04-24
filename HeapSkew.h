#if !defined (HEAPSKEW_H)
#define HEAPSKEW_H

#include "BinaryTree.h"

template < class T >
class HeapSkew : public Drawable
{

   private:
      BinaryTree<T>* bt;
      int sze;
      BinaryTree<T>* merge(BinaryTree<T>* left, BinaryTree<T>* right);

      int (*compare_items) (T* item_1, T* item_2);

   public:
      HeapSkew(int (*comp_items) (T* item_1, T* item_2));
      virtual ~HeapSkew();

      bool heapIsEmpty();
      void heapInsert(T* item);
      T* heapRemove();

      void draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height);
      void mouseClicked(int x, int y);

};

// this is a MAXHEAP (largest items to top alphabetical order)
template < class T >
HeapSkew<T>::HeapSkew(int (*comp_items) (T* item_1, T* item_2)) : Drawable()
{ 
   bt = new BinaryTree<T>();
   sze = 0;

   compare_items = comp_items;
}

template < class T >
HeapSkew<T>::~HeapSkew() 
{ 
   delete bt;
}  

template < class T >
bool HeapSkew<T>::heapIsEmpty()
{
   return sze == 0;
}

template < class T >
BinaryTree<T>* HeapSkew<T>::merge(BinaryTree<T>* left, BinaryTree<T>* right)
{
	//DO THIS
	//rule 1
	if (!left || left->isEmpty())
	{
		delete left;
		return right;
	}
	if (!right || right->isEmpty())
	{
		delete right;
		return left;
	}
   
   //rule 2
   int comp = compare_items (left->getRootItem(), right->getRootItem());
   
   if (comp < 0)
	   return merge(right, left);
   
   //rule 3
   BinaryTree<T>* LL = left->detachLeftSubtree();
   BinaryTree<T>* LR = left->detachRightSubtree();
   
   //rule 4
   left->attachRightSubtree(LL);
   delete LL;
   
   //rule 5
   if (LR->isEmpty())
   {
	   left->attachLeftSubtree(right);
	   delete LR;
	   delete right;
	   return left;
   }
   
   //rule 6
   else
   {
	   BinaryTree<T>* mergedTrees = merge(LR, right);
	   left->attachLeftSubtree(mergedTrees);
	   delete LR;
	   delete mergedTrees;
	   return left;
   } 
}

template < class T >
void HeapSkew<T>::heapInsert(T* item)
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* right = new BinaryTree<T>(item);
   bt = merge(bt, right);
   sze++;
}

template < class T >
T* HeapSkew<T>::heapRemove()
{
   //DO THIS (calls merge, should be short)
   BinaryTree<T>* left_sub = bt->detachLeftSubtree();
   BinaryTree<T>* right_sub = bt->detachRightSubtree();
   
   T* result = bt->getRootItem();

   BinaryTree<T>* merged = merge(left_sub, right_sub);
   delete bt;
   
   bt = merged;
   
   sze--;
   return result;
}

template < class T >
void HeapSkew<T>::draw(Cairo::RefPtr<Cairo::Context> cr, int width, int height)
{
   bt->draw(cr, width, height);
}

template < class T >
void HeapSkew<T>::mouseClicked(int x, int y) {bt->mouseClicked(x, y);}

#endif
