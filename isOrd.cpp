#include <iostream>
using namespace std;

struct Node
{
	int data;
	Node *left,
	     *right;
};
class Tree 
{
	Node* root;
	void copyTree(const Tree& t)
	{
		copy(root, t.root);
	}
	void copy(Node*& pos , Node* const & t)const
	{
		pos = 0;
		if(t)
		{
			pos = new Node;
			pos ->data = t->data;
			copy(pos->left,t->left);
			copy(pos->right,t->right);
		}
	}
	void deleteTree(Node* p)
	{
		if(p)
		{
			deleteTree(p->right);
			deleteTree(p->left);
			delete p;
			p=0;
		}
	}
	void createTree(Node*& pos)
	{
		int x;
		char c;
		cout<< "root: ";
		cin>>x;
		pos = new Node;
		pos->data = x;
		pos->left=0;
		pos->right=0;
		cout<<"Left Tree of: "<<x<<" y/n? ";
		cin>>c;
		if(c=='y') createTree(pos->left);
		cout<< "Right Tree of: "<<x<< " y/n? ";
		cin>>c;
		if(c=='y') createTree(pos->right);
	}
	void pr(const Node* p) const 
	{
		if(p)
		{
			pr(p->left);
			cout<< p->data<<" ";
			pr(p->right);
		}
	}

    bool Left(Node* n, int min ,int max)
	{
		if(n)
		{
			if(n->data > max || n->data < min)return false;
			else return Left(n->left, min, n->data) &&
				        Right(n->right, n->data, max);
		}
		else return true;
	}
    bool Right(Node* n, int min, int max)
	{
		if(n)
		{
			if(n->data > max || n->data < min)return false;
			else return Left(n->left, min, n->data) &&
						Right(n->right, n->data, max);
		}
		else return true;
	}
	int size(Tree& t)
	{
		if(!t.empty())return size(t.leftTree()) + size(t.rightTree()) + 1;
		else return 0;
	}
public:
	Tree()
	{
		root = 0;
	}
	~Tree()
	{
		deleteTree(root);
	}
	Tree(const Tree& t)
	{
		copyTree(t);
	}
	Tree& operator=(const Tree& t)
	{
		if(this != &t)
		{
			deleteTree(root);
			copyTree(t);
		}
		return *this;
	}

	bool empty()
	{
		return root == 0;
	}
	Node* getRoot()
	{
		return root;
	}
	int rootTree() const
	{
		return root->data;
	}
	Tree leftTree() const
	{
		Tree t;
		copy(t.root,root->left);
		return t;
	}
	Tree rightTree() const
	{
		Tree t;
		copy(t.root,root->right);
		return t;
	}
	void create3(const int& x, const Tree& t1, const Tree& t2)
	{
		if(root)
		{
			deleteTree(root);
			root=0;
		}
		root = new Node;
		root->data=x;
		copy(root->left,t1.root);
		copy(root->right,t2.root);
	}
	void print()
	{
		pr(root);
		cout<<endl;
	}
	void create()
	{
		createTree(root);
	}

	bool isOrd(Tree& t)
	{
		Node* temp=t.getRoot();
		if(temp)
		{
			if(temp->left || temp->right)
			{
				bool flag = false;
				if(temp->left)
				{
					if(temp->left->data > temp->data)return false;
					else flag = flag || Left(temp->left, INT_MIN, temp->data);
				}
				if(temp->right)
				{
					if(temp->right->data < temp->data)return false;
					else flag = flag && Right(temp->right, temp->data, INT_MAX);
				}
				return flag;
			}
			else return true;
		}
		else return true;
	}
	bool isOrd2(Tree& t,int min = INT_MIN,int max = INT_MAX,int c = 0)
	{
		if(!t.empty())
			switch (c){
			case 1:
				if(t.rootTree()>max||t.rootTree()<min)return false;
				else return isOrd2(t.leftTree(),min,t.rootTree(),1) &&
							isOrd2(t.rightTree(),t.rootTree(),max,2);
				break;
			case 2:
				if(t.rootTree()>max||t.rootTree()<min)return false;
				else return isOrd2(t.leftTree(),min,t.rootTree(),1) &&
							isOrd2(t.rightTree(),t.rootTree(),max,2);
				break;
			default:
				return isOrd2(t.leftTree(), min, t.rootTree(),1) &&
					   isOrd2(t.rightTree(),t.rootTree(),max,2);
				break;
			}
		else return true;
	}
	bool isBalanced(Tree& t)
	{
		if(!t.empty())return (2 > abs(size(t.leftTree()) - size(t.rightTree()))) &&
							isBalanced(t.leftTree()) &&
							isBalanced(t.rightTree());
		else return true;
	}
};

int main()
{
	return 0;
}
