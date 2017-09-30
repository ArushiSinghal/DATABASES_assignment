#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ios>
#include <ctime>
using namespace std;
long long int distinct_tuples, tuples_one_block, total_tuples, number_of_blocks,attributes,numAttrs;
string filenames =  "input.csv";
string output_file = "output.csv";
#define BTREE_MINDEG 20
#define LC(veca, vecb) lexicographical_compare(veca.begin(), veca.end(), \
		vecb.begin(), vecb.end())

ifstream fi;
ofstream f;
ofstream log1;

/**************************** INPUT FILE GENERATION ********************************/
int input_file_generate(int  duplicate, long long int block)
{
	int j,i;
	string A[100];
	filenames =  "input.csv";
	ofstream ofs(filenames, ios::out | ios::trunc);
	long long int count = 0;
	while(1)
	{
		ifstream in(filenames, ifstream::ate | ifstream::binary);
		long long int memory = in.tellg();
		//if(memory > 1073741824)
		//	break;
		if(memory > 1073741824)
			break;
		ofstream log(filenames, std::ios_base::app | std::ios_base::out);
		count += 1;
		for(i=0;i<(100-duplicate);i++)
		{
			int a;
			if(attributes == 1)
			{
				a = rand()%1001;
				log << a << "\n";
				A[i] = to_string(a);
			}
			else
			{
				a = rand()%1001;
				log << a << ",";
				A[i] = to_string(a) + ",";
				for(j=2;j<=attributes-1;j++)
				{
					a = rand()%1001;
					log << a << ",";
					A[i] = A[i] + to_string(a) + ",";
				}
				a = rand()%1001;
				log << a << "\n";
				A[i] = A[i] + to_string(a);
			}
		}
		for(i=0;i<duplicate;i++)
		{
			int val = rand()%(100-duplicate);
			log << A[val] << "\n";
		}
	}
	distinct_tuples = count*100- duplicate*count;
	tuples_one_block = distinct_tuples/block;
	total_tuples = count *100;
	ofs.close();
	return 0;
}

class BTreeNode {
	vector< vector<int> > keys;
	vector< BTreeNode* > children;
	bool isLeaf;
	int minDeg, numKeys;

	public:
	BTreeNode(int _minDeg, bool _isLeaf) {
		minDeg=_minDeg;
		isLeaf=_isLeaf;
		numKeys=0;
		keys.resize(2*minDeg-1);
		for(int i=0;i<2*minDeg-1;i++)
			keys[i].resize(numAttrs);
		children.resize(2*minDeg);
	}

	void insertNonFull(vector<int> k) {
		int i=numKeys-1;
		if(isLeaf==true) {
			while(i>=0 && LC(keys[i], k)!=0) {
				keys[i+1]=keys[i];
				i--;
			}
			keys[i+1]=k;
			numKeys++;
		}
		else {
			while(i>=0 && LC(keys[i], k)!=0)
				i--;
			if(children[i+1]->numKeys==2*minDeg-1) {
				splitChild(i+1, children[i+1]);
				if(LC(k, keys[i+1])!=0)
					i++;
			}
			children[i+1]->insertNonFull(k);
		}
	}

	void splitChild(int i, BTreeNode *y) {
		BTreeNode *z=new BTreeNode(y->minDeg, y->isLeaf);
		z->numKeys=minDeg-1;

		for(int j=0;j<minDeg-1;j++)	
			z->keys[j]=y->keys[j+minDeg];

		if (y->isLeaf==false) {
			for(int j=0;j<minDeg;j++)
				z->children[j]=y->children[j+minDeg];
		}

		y->numKeys=minDeg-1;

		for(int j=numKeys;j>=i+1;j--)
			children[j+1]=children[j];
		children[i+1]=z;

		for(int j=numKeys-1;j>=i;j--)
			keys[j+1]=keys[j];
		keys[i]=y->keys[minDeg-1];

		numKeys=numKeys+1;
	}

	BTreeNode *search(vector<int> k) {
		int i = 0;
		while(i<numKeys && LC(k, keys[i])!=0)
			i++;

		if(k==keys[i])
			return this;

		if(isLeaf==true)
			return NULL;

		return children[i]->search(k);
	}

	friend class BTree;
};

// A BTree
class BTree {
	BTreeNode *root;
	int minDeg;
	public:
	BTree() {
		root=NULL;
		minDeg=BTREE_MINDEG;
	}

	BTreeNode* search(vector<int> k) {
		return (root == NULL)?NULL:root->search(k);
	}

	void insert(vector<int> k) {
		if(root==NULL) {
			root = new BTreeNode(minDeg, true);
			root->keys[0]=k;
			root->numKeys=1;
		}
		else {
			if(root->numKeys==2*minDeg-1) {

				BTreeNode *s=new BTreeNode(minDeg, false);
				s->children[0]=root;
				s->splitChild(0, root);
				int i=0;
				if(LC(k, s->keys[0])!=0)
					i++;
				s->children[i]->insertNonFull(k);
				root=s;
			}
			else {
				root->insertNonFull(k);
			}
		}

	}
};

BTree tree;
void closed(ifstream fi,ofstream log)
{
	fi.close();
	log1.close();
	return;
}

void get_next_btree() {
	string line;
	while(getline(fi,line))
	{
		stringstream linestream(line);
		string curnum;
		vector<int> record;
		while(getline(linestream, curnum, ',')) {
			record.push_back(stoi(curnum));
		}
		if(tree.search(record));
		else {
			tree.insert(record);
			log1 << line << "\n";
		}
	}
	fi.close();
	log1.close();
	//closed(fi,log);
	return;
}

class HashMap {
	unordered_map<string, bool> recordPresence;
	public:
	bool search(string key) {
		if(recordPresence.find(key) == recordPresence.end()) return false;
		return true;
	}
	void insert(string key) {
		if(search(key)==false)
			recordPresence[key]=true;
	}
};

HashMap hash_[1000];
/**************  duplicacy elimination using two phase hashing **********************************************/
int get_next_hashing()
{
	string a;
	while(getline(fi,a))
	{
		if(hash_[1000].search(a));
		else {
			hash_[1000].insert(a);
			log1 << a << "\n";
		}	
	}
	fi.close();
	log1.close();
	//closed(fi,log);
	return 0;
}

int open(string a)
{
	string check1 = "hash";
	string check2 = "btree";
	if (a == check1)
	{
		fi.open(filenames);
		f.open(output_file, ios::out | ios::trunc);
		f.close();
		log1.open(output_file, ios_base::app | ios_base::out);
		get_next_hashing();
	}
	else if (a == check2)
	{
                fi.open(filenames);
                f.open(output_file, ios::out | ios::trunc);
                f.close();
                log1.open(output_file, ios_base::app | ios_base::out);
                get_next_btree();
	}
	return 0;
}

int main(int argc, char* argv[])
{
	//Attribute, duplicacy percentage, number of blocks in main memory, type_of_index
	attributes = stoi(argv[1]);
	numAttrs = attributes;
	input_file_generate(stoi(argv[2]), stoi(argv[3]));
	number_of_blocks = stoi(argv[3]);
	string index_type =  argv[4];
	open(index_type);
	return 0;
}
