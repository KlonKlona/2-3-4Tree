#ifndef CTree_h
#define CTree_h
#include <iostream>
#include <vector>
#include <algorithm>


template <class T> class TwoThreeFourTree;


/// klasa templatkowa z nodem
/// bedzie przechowywac dwie tablice dynamiczne
/// dodatkowo bedzie zawierala informacje o ilosci obecnych kluczy
/// oraz informacje o stanie (lisc czy nie)
template <class T> class Node
    {
        T *Values; ///tablica przechowywanych wartosci-kluczy
        Node **Children; ///tablica przechowywanych wskaznikow na kolejne nody
        int ile; ///aktualna liczba wartosci-kluczy w nodzie
        bool IsLeaf; ///zmienna informujaca o tym, czy dany nod jest lisciem czy nie
    public:
        Node(bool _leaf); ///Konstruktor
        void GoThrough(); ///funkcja sluzaca do wyswietlania drzewa
        Node *search(T k); ///funkcja do poszukiwania konkretnej wartosci-klucza
        int findKey(T k); /// funkcja pomocnicza, zwraca indeks pierwszej wartosci wiekszej lub rownej k
        int findNode(Node<T>* node); ///funkcja pomocnicza, zwraca indeks dziecka w wezle
        void insertNonFull(T k); ///funkcja sluzaca dodawaniu nowej wartosci
                                 ///warunkiem użycia jest to, ze nod nie jest pełny
        void splitChild(int i, Node<T> *y); ///funkcja pomocnicza to wyrownowazania drzewa
                                            ///rozdziela ono wezel pod warunkiem, ze jest pelen
        void remove(T k); ///funkcja do usuwania wartosci-klucza
        void remove(Node<T>* node); ///funkcja do usuwania calego noda
        void removeFromLeaf(int indeks); ///jedna z funkcji usuwajacych, usuwajaca z LISCIA
        void removeFromNonLeaf(int indeks); ///jedna z funkcji usuwajacych, usuwa NIE Z LISCIA
        T GetPrevious(int indeks);
        T GetNext(int indeks);
        void fill(int indeks);
        void borrowFromPrev(int indeks); ///funkcja kopiujaca wartosc-klucz z dziecka indeks-1 do indeks
        void borrowFromNext(int indeks); ///funkcja kopiujaca wartosc-klucz z dziecka indeks+1 do indeks
        void merge(int indeks); ///funkcja sluzaca scaleniu dzieci noda o indeksach indeks i indeks+1
        friend class TwoThreeFourTree<T>;
    };


template <class T> class TwoThreeFourTree
{
        Node<T> *root;
    public:
        TwoThreeFourTree() ///konstruktor
        {
            root = NULL;
        }

        void GoThrough() ///funkcja sluzaca wyswietlaniu drzewa
        {
            if (root != NULL) root->GoThrough();
        }

        Node<T>* search(T k) ///funkcja sluzaca poszukiwaniu klucza w drzewie
        {
            return (root == NULL)? NULL : root->search(k);
        }

        void insert(T k); ///funkcja sluzaca wsadzeniu wartosci-klucza w drzewo
        void remove(T k); ///funkcja sluzaca usunieciu danej wartosci-klucza
        void remove(Node<T>* node); ///funkcja sluzaca usunieciu noda z drzewa

        bool operator== (TwoThreeFourTree &tree) ///przeciazenie operatora porownywania drzew
        {
            return TwoThreeFourTree_compare(this->root, tree.root);
        }

        bool operator!= (TwoThreeFourTree &tree) ///przeciazenie operatora porownywania drzew
        {
            return !(TwoThreeFourTree_compare(this->root, tree.root));
        }

        void clear(Node <T> *node) /// pomoc dla destruktora
        {
            if(node==NULL)
                return;
            if (!node->IsLeaf)
                {
                for (int i = 0; i < node->ile; i++)
                    if (node->Children[i] != NULL)
                        clear(node->Children[i]);
                }
            delete [] node->Children;
            delete [] node->Values;
        }

        ~TwoThreeFourTree() /// destruktor
        {
            clear(this->root);
        }

        void TwoThreeFourTree_copy(Node<T> *&node, Node<T> *&source); ///funkcja pomocnicza do konstruktor kopiujacego
        bool TwoThreeFourTree_compare(Node<T> *&node, Node<T> *&source); ///funkcja pomocnicza do przeciazania operatora ==

        TwoThreeFourTree(TwoThreeFourTree &source) ///konstruktor kopiujacy
        {
            if(source.root==NULL)
                root=NULL;
            else
                TwoThreeFourTree_copy(this->root,source.root);
        }

    void addNode(TwoThreeFourTree<T> *tree, const Node<T> *node) /// dodawanie noda
    {
            if (node != NULL)
            {
                for (int i = 0; i < node->ile; i++)
                    tree->insert(node->Values[i]);

                if (!node->IsLeaf) {
                    for (int i = 0; i < node->ile+1; i++) {
                        addNode(tree, node->Children[i]);
                    }
                }
            }
    }
    void removeNode(TwoThreeFourTree<T> *tree, const Node<T> *node) ///usuwanie noda
    {
            if (node != NULL) {
                for (int i = 0; i < node->ile; i++)
                    tree->remove(node->Values[i]);

                if (!node->IsLeaf) {
                    for (int i = 0; i < node->ile+1; i++) {
                        removeNode(tree, node->Children[i]);
                    }
                }
            }
    }

        TwoThreeFourTree& operator+ ( TwoThreeFourTree &tr) /// przeciazenie operatora dodawania
        {
            TwoThreeFourTree<T> result = *this;
            addNode(&result, tr.root);
            return result;
        }

        TwoThreeFourTree& operator- ( TwoThreeFourTree &tr) /// przeciazenie operatora odejmowania
        {
            TwoThreeFourTree<T> result = *this;
            removeNode(&result, tr.root);
            return result;
        }

		int size(Node <T> *node) /// pomocnicza funkcja do sprawdzania wielkosci drzewa
		{
			int k = 0;
			k+=node->ile;
			if (!node->IsLeaf) {
				for (int i = 0; i < node->ile+1; i++) {
					k += size(node->Children[i]);
				}
			}
			return k;
		}

		int size() ///funkcja sprawdzajaca wielkosc drzewa
		{
			return size(this->root);
		}

    };

template <class T> bool TwoThreeFourTree<T>::TwoThreeFourTree_compare(Node<T> *& node, Node<T> *& source)
{
    int w=0;
            if(node==source==NULL && node->IsLeaf && source->IsLeaf)
              return true;
            if(node!=NULL && source==NULL)
                return false;
            if(node==NULL && source!=NULL)
                return false;
            if(node->ile!=source->ile)
                return false;
            if(node->ile==source->ile)
            {
                for(int i = 0 ; i < node->ile ; i++)
                {
                    if(node->Values[i]==source->Values[i])
                    {
                        w++;
                    }
                }
                if(w!=node->ile)
                    return false;
                if(w==node->ile)
                {
                    if(w==1)
                    {
                        if(TwoThreeFourTree_compare(node->Children[0],source->Children[0]))
                        {
                            if(TwoThreeFourTree_compare(node->Children[1],source->Children[1]))
                                return true;
                        }
                        return false;
                    }
                    if(w==2)
                    {
                        if(TwoThreeFourTree_compare(node->Children[0],source->Children[0]))
                        {
                            if(TwoThreeFourTree_compare(node->Children[1],source->Children[1]))
                            {
                                if(TwoThreeFourTree_compare(node->Children[2],source->Children[2]))
                                    return true;
                            }
                        }
                        return false;
                    }
                    if(w==3)
                    {
                        if( TwoThreeFourTree_compare(node->Children[0],source->Children[0]))
                        {
                            if(TwoThreeFourTree_compare(node->Children[1],source->Children[1]))
                            {
                                if(TwoThreeFourTree_compare(node->Children[2],source->Children[2]))
                                {
                                    if(TwoThreeFourTree_compare(node->Children[3],source->Children[3]))
                                        return true;
                                }
                            }
                        }
                        return false;
                    }
                }
            }

}

template <class T> void TwoThreeFourTree<T>::TwoThreeFourTree_copy(Node<T> *& node, Node<T> *& source)
{
if (source == NULL)
    node = NULL;
else
{
    node=new Node<T> (source->IsLeaf);
    node->ile=source->ile;
    for(int i = 0 ; i < source->ile ; i++)
    {
        node->Values[i]=source->Values[i];
    }
    if(!(node->IsLeaf))
    {
        if(node->ile==1)
        {
        TwoThreeFourTree_copy(node->Children[0],source->Children[0]);
        TwoThreeFourTree_copy(node->Children[1],source->Children[1]);
        return;
        }
        if(node->ile==2)
        {
        TwoThreeFourTree_copy(node->Children[0],source->Children[0]);
        TwoThreeFourTree_copy(node->Children[1],source->Children[1]);
        TwoThreeFourTree_copy(node->Children[2],source->Children[2]);
        return;
        }
        if(node->ile==3)
        {
        TwoThreeFourTree_copy(node->Children[0],source->Children[0]);
        TwoThreeFourTree_copy(node->Children[1],source->Children[1]);
        TwoThreeFourTree_copy(node->Children[2],source->Children[2]);
        TwoThreeFourTree_copy(node->Children[3],source->Children[3]);
        return;
        }
    }
    }
    return;
}

template <class T> Node<T>::Node(bool _leaf)
{
    IsLeaf = _leaf;
    Values = new T[3]; ///od razu rezerwuje miejsce na mozliwe wartosci-klucze
    Children = new Node<T> *[4]; ///od razu rezerwuje miejsce na wskazniki do dzieci
    for( int i = 0 ; i < 4 ; i++)
        Children[i]=NULL;
    ile = 0; ///poczatkowa liczba kluczy to oczywiscie zero
}

/// funkcja pomocnicza
/// wskazuje indeks na  PIERWSZA wartosc ktora jest wieksza lub rowna k
template <class T> int Node<T>::findKey(T k)
{
    int indeks=0;
    while (indeks<ile && Values[indeks] < k)
        ++indeks;
    return indeks;
}

/// znajduje indeks noda w tablicy dzieci danego noda
template <class T> int Node<T>::findNode(Node<T> *node)
{
    int indeks=0;
    while (indeks<ile+1 && Children[indeks] != node)
        ++indeks;
    return indeks;
}

template <class T> void Node<T>::remove(T k)
{
    int indeks = findKey(k); ///poszukuje indeksu klucza do usuniecia
    if (indeks < ile && Values[indeks] == k)
    {
        if (IsLeaf)
            removeFromLeaf(indeks);
        else
            removeFromNonLeaf(indeks);
    }
    else
    {
        if (IsLeaf)
        {
            std::cout << "Wartosc "<< k <<" nie zostala znaleziona w drzewie!\n";
            return;
        }
        bool flag = ( (indeks==ile)? true : false );

        if (Children[indeks]->ile < 2)
            fill(indeks);

        if (flag && indeks > ile)
            Children[indeks-1]->remove(k);
        else
            Children[indeks]->remove(k);
    }
    return;
}

template <class T> void Node<T>::remove(Node<T> *node)
{
    T *k = new T[node->ile];
    int n_k = node->ile;
    for (int i = 0; i < n_k; i++ )
        k[i] = node->Values[i];

    for (int i = 0; i < n_k; i++)  {
        node->remove(k[i]);
    }
    delete [] k;
}

template <class T> void Node<T>::removeFromLeaf (int indeks)
{
    for (int i=indeks+1; i<ile; ++i)
        Values[i-1] = Values[i];

    ile--;

    return;
}

template <class T> void Node<T>::removeFromNonLeaf(int indeks)
{

    T k = Values[indeks];
    if (Children[indeks]->ile >= 2)
    {
        T pred = GetPrevious(indeks);
        Values[indeks] = pred;
        Children[indeks]->remove(pred);
    }

    else if  (Children[indeks+1]->ile >= 2)
    {
        T succ = GetNext(indeks);
        Values[indeks] = succ;
        Children[indeks+1]->remove(succ);
    }

    else
    {
        merge(indeks);
        Children[indeks]->remove(k);
    }
    return;
}

template <class T> T Node<T>::GetPrevious(int indeks)
{
    Node<T> *cur=Children[indeks];
    while (!cur->IsLeaf)
        cur = cur->Children[cur->ile];

    return cur->Values[cur->ile-1];
}

template <class T> T Node<T>::GetNext(int indeks)
{
    Node<T> *cur = Children[indeks+1];
    while (!cur->IsLeaf)
        cur = cur->Children[0];
    return cur->Values[0];
}

template <class T> void Node<T>::fill(int indeks)
{
    if (indeks!=0 && Children[indeks-1]->ile >= 2)
        borrowFromPrev(indeks);

    else if (indeks!=ile && Children[indeks+1]->ile >= 2)
        borrowFromNext(indeks);

    else
    {
        if (indeks != ile)
            merge(indeks);
        else
            merge(indeks-1);
    }
    return;
}

template <class T> void Node<T>::borrowFromPrev(int indeks)
{

    Node<T> *child=Children[indeks];
    Node<T> *sibling=Children[indeks-1];

    for (int i=child->ile-1; i>=0; --i)
        child->Values[i+1] = child->Values[i];

    if (!child->IsLeaf)
    {
        for(int i=child->ile; i>=0; --i)
            child->Children[i+1] = child->Children[i];
    }

    child->Values[0] = Values[indeks-1];

    if (!IsLeaf)
        child->Children[0] = sibling->Children[sibling->ile];

    Values[indeks-1] = sibling->Values[sibling->ile-1];

    child->ile += 1;
    sibling->ile -= 1;

    return;
}

template <class T> void Node<T>::borrowFromNext(int indeks)
{

    Node<T> *child=Children[indeks];
    Node<T> *sibling=Children[indeks+1];

    child->Values[(child->ile)] = Values[indeks];

    if (!(child->IsLeaf))
        child->Children[(child->ile)+1] = sibling->Children[0];

    Values[indeks] = sibling->Values[0];

    for (int i=1; i<sibling->ile; ++i)
        sibling->Values[i-1] = sibling->Values[i];

    if (!sibling->IsLeaf)
    {
        for(int i=1; i<=sibling->ile; ++i)
            sibling->Children[i-1] = sibling->Children[i];
    }

    child->ile += 1;
    sibling->ile -= 1;

    return;
}

template <class T> void Node<T>::merge(int indeks)
{
    Node<T> *child = Children[indeks];
    Node<T> *sibling = Children[indeks+1];

    child->Values[1] = Values[indeks];

    for (int i=0; i<sibling->ile; ++i)
        child->Values[i+2] = sibling->Values[i];

    if (!child->IsLeaf)
    {
        for(int i=0; i<=sibling->ile; ++i)
            child->Children[i+2] = sibling->Children[i];
    }

    for (int i=indeks+1; i<ile; ++i)
        Values[i-1] = Values[i];

    for (int i=indeks+2; i<=ile; ++i)
        Children[i-1] = Children[i];

    child->ile += sibling->ile+1;
    ile--;

    delete(sibling);
    return;
}

template <class T> void TwoThreeFourTree< T >::insert(T k)
{
    if (root == NULL)
    {
        root = new Node< T >(true);
        root->Values[0] = k;
        root->ile = 1;
    }
    else
    {
        if (root->ile == 3)
        {
            Node<T> *s = new Node < T >(false);

            s->Children[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->Values[0] < k)
                i++;
            s->Children[i]->insertNonFull(k);

            root = s;
        }
        else
            root->insertNonFull(k);
    }
}

template <class T> void Node<T>::insertNonFull(T k)
{
    int i = ile-1;

    if (IsLeaf == true)
    {

        while (i >= 0 && Values[i] > k)
        {
            Values[i+1] = Values[i];
            i--;
        }

        Values[i+1] = k;
        ile = ile+1;
    }
    else
    {
        while (i >= 0 && Values[i] > k)
            i--;


        if (Children[i+1]->ile == 3)
        {
            splitChild(i+1, Children[i+1]);
            if (Values[i+1] < k)
                i++;
        }
        Children[i+1]->insertNonFull(k);
    }
}

template <class T> void Node<T>::splitChild(int i, Node<T> *y)
{

    Node<T> *z = new Node<T>(y->IsLeaf);
    z->ile = 1;

    for (int j = 0; j < 2-1; j++)
        z->Values[j] = y->Values[j+2];

    if (y->IsLeaf == false)
    {
        for (int j = 0; j < 2; j++)
            z->Children[j] = y->Children[j+2];
    }

    y->ile = 2 - 1;

    for (int j = ile; j >= i+1; j--)
        Children[j+1] = Children[j];

    Children[i+1] = z;

    for (int j = ile-1; j >= i; j--)
        Values[j+1] = Values[j];

    Values[i] = y->Values[2-1];

    ile = ile + 1;
}

template <class T> void Node<T>::GoThrough() /// wyswietlenie inorder
{
    int i;
    for (i = 0; i < ile; i++)
    {
        if (IsLeaf == false)
            Children[i]->GoThrough();
        std::cout << " " << Values[i];
    }
    if (IsLeaf == false)
        Children[i]->GoThrough();
}

template <class T> Node<T> *Node<T>::search(T k)
{
    int i = 0;
    while (i < ile && k > Values[i])
        i++;
    if (Values[i] == k)
        return this;
    if (IsLeaf == true)
        return NULL;
    return Children[i]->search(k);
}

template <class T> void TwoThreeFourTree<T>::remove(T k)
{
    if (!root)
    {
        std::cout << "Drzewo jest puste!\n";
        return;
    }
    root->remove(k);
    if (root->ile==0)
    {
        Node<T> *tmp = root;
        if (root->IsLeaf)
            root = NULL;
        else
            root = root->Children[0];
        delete tmp;
    }
    return;
}

template <class T> void TwoThreeFourTree<T>::remove(Node<T>* node)
{
    if (!root)
    {
        std::cout << "Drzewo jest puste!\n";
        return;
    }
    root->remove(node);
    /// jezeli korzen nie ma wartosci-kluczy zmienia jego pierwsze dziecko w korzen
    /// albo zmien go na NULL'a
    if (root->ile==0)
    {
        Node<T> *tmp = root;
        if (root->IsLeaf)
            root = NULL;
        else
            root = root->Children[0];
        delete tmp;
    }
    return;
}

#endif
