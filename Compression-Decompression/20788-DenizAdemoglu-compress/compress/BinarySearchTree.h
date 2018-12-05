#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
using namespace std;

template <typename Comparable>
struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;

		BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
			: element(theElement), left(lt), right(rt){}


		BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
			: element(move (theElement)), left(lt), right(rt){}

	};

template <typename Comparable>
class BinarySearchTree
{
public:

	~BinarySearchTree( ){
		makeEmpty(root);
	}

	
	BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const{
		if( t == nullptr )
			return nullptr;
		if( t->left == nullptr )
			return t;
		return findMin( t->left );
	}
	BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const{
		if( t != nullptr )
			while( t->right != nullptr )
				t = t->right;
		return t;
	}
	bool contains( const Comparable & x, BinaryNode<Comparable> *t ) const	{
		if( t == nullptr )
			return false;
		else if( x < t->element )
			return contains( x, t->left );
		else if( t->element < x )
			return contains( x, t->right ); else
			return true; // Match
	}
	BinaryNode<Comparable> * find( const Comparable & x, BinaryNode<Comparable> *t ) const	{
		if( t == NULL )
			return NULL;
		else if( x < t->element )
			return find( x, t->left );
		else if( t->element < x )
			return find( x, t->right ); 
		else
			return t; // Match
	}

	void printTree( BinaryNode<Comparable> *t ) const{
		if( t != nullptr )
		{
			printTree( t->left);
			cout << t->element << endl;
			printTree( t->right);
		}


	}

	void makeEmpty( BinaryNode<Comparable> * & t )	{
		if( t != nullptr )
		{
			makeEmpty( t->left );
			makeEmpty( t->right );
			delete t;
		}
		t = nullptr;
	}

	void insert( const Comparable & x, BinaryNode<Comparable> * & t ){
		if( t == nullptr )
			t = new BinaryNode<Comparable>( x, nullptr, nullptr );
		else if( x < t->element )
			insert( x, t->left );
		else if( t->element < x )
			insert( x, t->right );
		else
			; // Duplicate; do nothing
	}
	void insert( Comparable && x, BinaryNode<Comparable> * & t ){
		if( t == nullptr )
			t = new BinaryNode<Comparable>( move( x ), nullptr, nullptr );
		else if( x < t->element )
			insert( move( x ), t->left );
		else if( t->element < x )
			insert( move( x ), t->right );
		else
			; // Duplicate; do nothing
	}
	void remove( const Comparable & x, BinaryNode<Comparable> * & t ){
		if( t == nullptr )
			return; // Item not found; do nothing
		if( x < t->element )
			remove( x, t->left );
		else if( t->element < x )
			remove( x, t->right );
		else if( t->left != nullptr && t->right != nullptr ) // Two children
		{
			t->element = findMin( t->right )->element;
			remove( t->element, t->right );
		}
		else
		{
			BinaryNode<Comparable> *oldNode = t;
			t = ( t->left != nullptr ) ? t->left : t->right;
			delete oldNode;
		}
	}

	BinaryNode<Comparable> *root;

private:
	



	BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const{
		if( t == nullptr )
			return nullptr;
		else
			return new BinaryNode<Comparable>{ t->element, clone( t->left ), clone( t->right ) };
	}


};
#endif