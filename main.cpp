#include <iostream>

#include <stdlib.h>
#include <utility>
#include <stdio.h>


using namespace std;
template <class T,int order>
class Node{
public:
        T *key;
        Node **children;
        bool isLeaf;
        int counter;
        Node(){
            key= new T[order-1];
            children=new Node*[order];
            counter=0;
            for(int i=0;i<order;i++){
                children[i]=NULL;
            }

        }
        void insertkeys(T x){
            int index=0;
            for (index = counter; index > 0 && (x < key[index - 1]); index--) {
                key[index] =key[index - 1];
                children[index + 1] = children[index];
            }


            children[index + 1] = children[index];
            key[index] = x;
            counter++;

        }


            void split(int i){
                int degree=order-1;
                Node<T,order> *toSplit =children[i];
                Node<T,order> *newNode = new Node();
                newNode->isLeaf = toSplit->isLeaf;
                newNode->counter = degree - 1;
                for (int j = 0; j < degree - 1; j++) {
                    newNode->key[j] = toSplit->key[j + degree-1];
                }
                if (!toSplit->isLeaf) {
                    for (int j = 0; j < order; j++) {
                        newNode->children[j] = toSplit->children[j + degree-1];
                    }
                }
                toSplit->counter = degree -1-1;
                insertkeys(toSplit->key[degree - 1-1]);
                children[i + 1] = newNode;

            }


            void printNodes(int i){

                for(int index=0;index<counter;index++){
                    cout<<key[index]<<" ";
                }
                if(isLeaf==false){
                    i++;
                    for(int j=0;j<=counter;j++){

                        cout<<endl;
                        cout<<" "<<"";
                        children[j]->printNodes(i);


                }
            }}




};



template <class T,int order>
class BTree{
public:
    Node<T,order> *root;
    BTree(){root=NULL;}
    void Insert(T);
    void Print();

};

template <class T,int order>
void BTree<T,order>::Insert(T value)
{
    if(root==NULL){
        root = new Node<T,order>();
        root->isLeaf=true;
        root->key[0] = value;
        root->counter = 1;
    }
    else{
	if (root->counter == order - 1&&root->isLeaf==true) {
		Node<T,order> *newRoot= new Node<T,order>();
		newRoot->isLeaf = false;
		newRoot->children[0] = root;
		root = newRoot;
		newRoot->split(0);
	}


	Node<T,order> *curr = root;
	while (!curr->isLeaf) {


		int index = curr->counter - 1;
		while (index >= 0 && value <curr->key[index]) {
			index--;
		}
		index++;


		if (curr->children[index]->counter == order - 1) {
			curr->split(index);
			if (curr->key[index]<value) {
				index++;
			}
		}
		root=curr;
		curr = root->children[index];

	}

	curr->insertkeys(value);


    }
}

template <class T,int order>
void BTree<T,order>::Print()
{
    if(root!=NULL){
        root->printNodes(0);
    }
}

int main()
{

    BTree<int,3> t1;

    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);

    t1.Print();





    return 0;
}
