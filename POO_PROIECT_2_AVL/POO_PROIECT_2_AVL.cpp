#include <iostream>
#include <algorithm>
using namespace std;

class nod
{
protected:
	int info;
	nod* left, * right;

public:

	nod()
	{
		cout << "Constructor simplu baza nod" << endl;
		left = NULL;
		right = NULL;
		info = 0;
	}
	nod(int val)
	{
		cout << "Constructor param baza nod" << endl;
		info = val;
		left = NULL;
		right = NULL;
	}
	virtual ~nod()
	{
		cout << "Destructor baza nod" << endl;
	}


	friend class Arbore;
	friend class ABC;
	friend class Arbore_AVL;
};

class nod_avl : public nod
{
protected:
	int h;
public:

	nod_avl() :nod{}, h{ 1 }
	{
		cout << "Constructor simplu deriv nod" << endl;
	}

	nod_avl(int val) : nod{ val }, h{ 1 }
	{
		cout << "Constructor param deriv nod" << endl;
	}

	~nod_avl()
	{
		cout << "Destructor nod deriv" << endl;
	}


	friend class Arbore;
	friend class ABC;
	friend class Arbore_AVL;
};

class Arbore
{
protected:
	int nr_noduri;
public:

	Arbore()
	{
		cout << "Constructor Arbore simplu" << endl;
		nr_noduri = 0;
	}
	Arbore(int nr)
	{
		cout << "Constructor param Arbore baza" << endl;
		nr_noduri = nr;
	}
	virtual ~Arbore() = 0;
};
inline Arbore::~Arbore(){ cout << "Destructor Arbore" << endl; }

class ABC : public Arbore
{
protected:
	nod* rad;
public:

	friend istream& operator>>(istream& in, ABC& a)
	{
		int val;
		in >> val;
		a.inserare(a.rad, val);
		return in;
	}

	friend ostream& operator<<(ostream& os, ABC& a)
	{
		a.preordine(a.rad);
		return os;
	}

	ABC(const ABC& a)
	{
		if (a.rad->info == 0)
			cout << "Arborele este NULL";
		else
		{
			rad = new nod;
			rad = inserare(rad, a.rad->info);
			//Am nevoie de parcurgere pentru inserare - adancime sau latime
		}
	}

	/*ABC& operator=(ABC& a)
	{
		if (this == &a)
		{
			cout << "Se incearca copierea aceluiasi obiect ";
			return *this;
		}
		//DELETE TREE AICI
		nod* p = new nod;
		p->info = a.rad->info;
		p->left = a.rad->left;
		p->right = a.rad->right;
	}*/


	ABC()
	{
		cout << "Constructor ABC simplu" << endl;
		rad = new nod;
	
	}
	ABC(int val):Arbore{val}
	{
		cout << "Constructor ABC param" << endl;
		rad = new nod;
	}
	~ABC()
	{
		cout << "Destructor ABC" << endl;
	}

	nod* creareNod(int val)
	{
		nod* p = new nod();
		p->info = val;
		p->left = NULL;
		p->right = NULL;
		return p;
	}

	nod* inserare(nod* p, int val)
	{
		if (p == NULL)
			return creareNod(val);

		if (val < p->info)
			p->left = inserare(p->left, val);
		else if (val > p->info)
			p->right = inserare(p->right, val);
		else
			return p;

		return p;
	}

	nod* minim(nod* p)
	{
		nod* temp = p;
		while (temp && temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	nod* stergere(nod* p, int val)
	{
		if (p == NULL)
			return p;
		if (val < p->info)
			p->left = stergere(p->left, val);
		else if (val > p->info)
			p->right = stergere(p->right, val);
		else
		{
			if (p->left == NULL)
			{
				nod* temp = p->right;
				free(p);
				return temp;
			}
			else if (p->right == NULL)
			{
				nod* temp = p->left;
				free(p);
				return temp;
			}

			nod* temp = minim(p->right);
			p->info = temp->info;
			p->right = stergere(p->right, temp->info);
		}
		return p;
	}

	void preordine(nod* p)
	{

		if (p != NULL)
		{
			cout << p->info << " ";
			preordine(p->left);
			preordine(p->right);
		}
	}

	nod* get_root()
	{
		return rad;
	}

	void afis(nod* p)
	{
		//cout << p->right->info << endl;
		cout << rad->info << endl;
	}

	void setter(int val)
	{
		rad->info=val;
	}

	void citire(ABC& a)
	{
		int val;
		cout << "Introduceti valoarea din radacina: ";
		cin >> val;
		a.setter(val);
		int n;
		cout << endl;
		cout << "Introduceti numarul de elemente inserate: ";
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a;
		}
		cout << a;
	}

	void deleteABC(nod* p)
	{
		if (p == NULL)return;
		if (p->left != NULL)
			deleteABC(p->left);
		if (p->right != NULL)
			deleteABC(p->right);
		delete p;
	}

};

class Arbore_AVL : public Arbore
{
protected:
	nod_avl* rad;
public:

	friend istream& operator>>(istream& in, Arbore_AVL& a)
	{
		
		int val;
		in >> val;
		a.rad=dynamic_cast<nod_avl*>(a.inserare(a.rad, val));
		return in;
	}

	friend ostream& operator<<(ostream& os, Arbore_AVL& a)
	{
		a.preordine(a.rad);
		return os;
	}
	

	Arbore_AVL()
	{
		cout << "Constructor AVL simplu" << endl;
		rad = new nod_avl;
	}
	Arbore_AVL(int val) :Arbore{val}
	{
		cout << "Constructor AVL param" << endl;
		rad = new nod_avl;
	}
	~Arbore_AVL()
	{
		cout << "Destructor AVL" << endl;
	}

	int height(nod* p)
	{
		if (p == NULL)
			return 0;
		return dynamic_cast<nod_avl*>(p)->h;
	}

	nod_avl* creareNod(int val)
	{
		nod_avl* p = new nod_avl();
		p->info = val;
		p->left = NULL;
		p->right = NULL;
		p->h = 1;
		return p;
	}

	nod* rotatie_dreapta(nod* p)
	{
		nod* x = p->left;
		nod* y = p->right;

		x->right = p;
		p->left = y;

		dynamic_cast<nod_avl*>(p)->h = max(height(p->left), height(p->right)) + 1;
		dynamic_cast<nod_avl*>(x)->h = max(height(x->left), height(x->right)) + 1;
		
		return x;
	}

	nod* rotatie_stanga(nod* p)
	{
		nod *x = p->right;
		nod *y = x->left;

		x->left = p;
		p->right = y;

		dynamic_cast<nod_avl*>(p)->h = max(height(p->left), height(p->right)) + 1;
		dynamic_cast<nod_avl*>(x)->h = max(height(x->left), height(x->right)) + 1;

		return x;
	}

	int getBalance(nod* p)
	{
		if (p == NULL)
			return 0;
		return height(p->left) - height(p->right);
	}

	nod* minim(nod* p)
	{
		nod* temp = p;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	nod* inserare(nod* p, int val)
	{
		if (p == NULL)
			return(creareNod(val));

		if (val < p->info)
			p->left = inserare(p->left, val);
		else if (val > p->info)
			p->right = inserare(p->right, val);
		else
			return p;

		dynamic_cast<nod_avl*>(p)->h = max(height(p->left), height(p->right)) + 1;

		int balance = getBalance(p);

		if (balance > 1 && val < p->left->info)
			return rotatie_dreapta(p);

		if (balance <-1 && val>p->right->info)
			return rotatie_stanga(p);

		if (balance > 1 && val > p->left->info)
		{
			p->left = rotatie_stanga(p->left);
			return rotatie_dreapta(p);
		}

		if (balance < -1 && val < p->right->info)
		{
			p->right = rotatie_dreapta(p);
			return rotatie_stanga(p);
		}

		return p;
	}

	nod* stergere(nod* p, int val)
	{
		if (p == NULL)
			return p;

		if (val < p->info)
			p->left = stergere(p->left, val);
		else if (val > p->info)
			p->right = stergere(p->right, val);
		else
		{
			if ((p->left == NULL) || (p->right == NULL))
			{
				nod* temp = p->left ?
					p->left :
					p->right;

				if (temp == NULL)
				{
					temp = p;
					p = NULL;
				}
				else
					*p = *temp;
				free(temp);
			}
			else
			{
				nod* temp = minim(p->right);
				p->info = temp->info;
				p->right = stergere(p->right, temp->info);
			}
		}

		if (p == NULL)
			return p;

		dynamic_cast<nod_avl*>(p)->h = max(height(p->left), height(p->right)) + 1;

		int balance = getBalance(p);

		if (balance > 1 && val < p->left->info)
			return rotatie_dreapta(p);

		if (balance <-1 && val>p->right->info)
			return rotatie_stanga(p);

		if (balance > 1 && val > p->left->info)
		{
			p->left = rotatie_stanga(p->left);
			return rotatie_dreapta(p);
		}

		if (balance < -1 && val < p->right->info)
		{
			p->right = rotatie_dreapta(p);
			return rotatie_stanga(p);
		}

		return p;
	}


	void preordine(nod* p)
	{
		if (p != NULL)
		{
			int bal = getBalance(p);
			cout << p->info <<"("<<bal<<")"<<" ";
			preordine(p->left);
			preordine(p->right);
		}
	}

	nod_avl* get_root_avl()
	{
		return rad;
	}

	void setter_avl(int val)
	{
		rad->info = val;
	}

	void citire(Arbore_AVL& a)
	{
		int val;
		cout << "Introduceti valoarea din radacina: ";
		cin >> val;
		a.setter_avl(val);
		int n;
		cout << endl;
		cout << "Introduceti numarul de elemente inserate: ";
		cin >> n;
		for (int i = 1; i <= n; i++)
		{
			cin >> a;
		}
		cout << a << endl;
	}
	void deleteAVL(nod* p)
	{
		if (p == NULL)return;
		if (p->left != NULL)
			deleteAVL(p->left);
		if (p->right != NULL)
			deleteAVL(p->right);
		delete p;
	}

};

int main()
{
	
	/*Arbore_AVL a;
	nod* root = a.get_root_avl();
	//a.setter_avl(10);                      //Pentru Arbore AVL
	//cin >> a;
	//cin >> a;
	//cin >> a;
	a.citire(a);
	a.stergere(root,20);
	cout << a;
	//cout << a;*/


	/*ABC a;
	nod* root = a.get_root();
	//a.setter(10);
	//a.afis(root);                             //Pentru Arbore ABC
	a.citire(a);
	cout << endl;
	//cin >> a;
	//cin >> a;
	//cin >> a;
	//a.inserare(root, 50);
	//a.inserare(root, 30);
	//a.inserare(root, 5);
	//a.preordine(root);
	//cout << a;
	//cout << endl;
	//a.afis(root);
	//a.stergere(root,20);
	//cout << a;
	//cout << endl;*/
	
	return 0;
}
