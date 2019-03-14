#ifndef test_h
#define test_h

#include "TwoThreeFourTree.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Testowa
{
private:
TwoThreeFourTree <string> *tree1;
TwoThreeFourTree <string> *tree2;
TwoThreeFourTree <string> *tree3;
TwoThreeFourTree <int> *tree4;
TwoThreeFourTree <int> *tree5;
TwoThreeFourTree <int> *tree6;
public:
    Testowa()
    {
        cout << "Dodawanie elementow przetestuje za pomoca plikow tekstowych" << endl;
        tree1=new TwoThreeFourTree<string>;
        tree2=new TwoThreeFourTree<string>;
        tree3=new TwoThreeFourTree<string>;
        tree4=new TwoThreeFourTree<int>;
        tree5=new TwoThreeFourTree<int>;
        tree6=new TwoThreeFourTree<int>;
        ifstream plik;
        string bufor;
        int bufor1;
        plik.open( "test1.txt" );
        while(!plik.eof())
        {
            plik >> bufor;
            tree1->insert(bufor);
        }
        plik.close();
        plik.open( "test2.txt" );
        while(!plik.eof())
        {
            plik >> bufor;
            tree2->insert(bufor);
        }
        plik.close();
        plik.open( "testint1.txt" );
        while(!plik.eof())
        {
            plik >> bufor1;
            tree4->insert(bufor1);
        }
        plik.close();
        plik.open( "testint2.txt" );
        while(!plik.eof())
        {
            plik >> bufor1;
            tree5->insert(bufor1);
        }
        plik.close();
    }
    void Show()
    {
        tree1->GoThrough();
        cout << endl;
        tree2->GoThrough();
        cout << endl;
        tree3->GoThrough();
        cout << endl;
        tree4->GoThrough();
        cout << endl;
        tree5->GoThrough();
        cout << endl;
        tree6->GoThrough();
        cout << endl;

    }

    void Usun()
    {
        cout << "Teraz przetestuje usuwanie usuwajac wyrazy 'magna' oraz 'accumsan' z pierwszego drzewa stringow " << endl;
        cout << "z drugiego usune 'sem' oraz 'quis' natomiast z drzew intow usune liczby 5 oraz 767" << endl;
        tree1->remove("magna");
        tree1->remove("accumsan");
        tree2->remove("sem");
        tree2->remove("quis");
        tree4->remove(5);
        tree5->remove(767);
        this->Show();
        (*tree3)=(*tree1)-(*tree2);
        cout << endl;
    }

    void Skopiuj()
    {
        TwoThreeFourTree <string> pierwotne1;
        TwoThreeFourTree <int> pierwotne2;
        ifstream plik;
        string bufor;
        int bufor1;
        plik.open( "test1.txt" );
        while(!plik.eof())
        {
            plik >> bufor;
            pierwotne1.insert(bufor);
        }
        plik.close();
        plik.open( "testint1.txt" );
        while(!plik.eof())
        {
            plik >> bufor1;
            pierwotne2.insert(bufor1);
        }
        plik.close();
        cout << "Teraz skopiuje te drzewa do innych" << endl;
        pierwotne1.GoThrough();
        cout <<  endl;
        pierwotne2.GoThrough();
        cout << endl;
        cout << "a to kopie" << endl;
        TwoThreeFourTree <string> kopia1(pierwotne1);
        TwoThreeFourTree <int> kopia2(pierwotne2);
        kopia1.GoThrough();
        cout << endl;
        kopia2.GoThrough();
        cout << endl;
        cout << "Dodatkowo przetestuje sprawdzanie wielkosci drzewa" << endl;
        int wielkosc=kopia1.size();
        cout << "wielkosc pierwszej kopii to " << wielkosc << endl;
        wielkosc = kopia2.size();
        cout << "wielkosc drugiej kopii to " << wielkosc << endl;
        cout << endl;
    }

    void porownaj()
    {
        cout << "Teraz przetestuje porownywanie drzew" << endl;
        TwoThreeFourTree <string> pierwotnestring1;
        TwoThreeFourTree <string> pierwotnestring2;
        TwoThreeFourTree <int> pierwotneint1;
        TwoThreeFourTree <int> pierwotneint2;
        pierwotnestring1.insert("smiechy");
        pierwotnestring1.insert("tutaj");
        pierwotnestring1.insert("mam");
        pierwotnestring2.insert("mam");
        pierwotnestring2.insert("tutaj");
        pierwotnestring2.insert("smiechy");
        pierwotneint1.insert(3);
        pierwotneint1.insert(5);
        pierwotneint1.insert(2);
        pierwotneint1.insert(1);
        pierwotneint2.insert(4);
        pierwotneint2.insert(48);
        pierwotneint2.insert(33);
        pierwotneint2.insert(322);
        pierwotnestring1.GoThrough();
        cout << endl;
        pierwotnestring2.GoThrough();
        cout << endl;
        pierwotneint1.GoThrough();
        cout << endl;
        pierwotneint2.GoThrough();
        cout << endl;
        if(pierwotnestring1==pierwotnestring2)
            cout << "drzewa stringow sa takie same!" << endl;
        else
            cout << "drzewa stringow sa rozne!" << endl;

        if(pierwotneint1==pierwotneint2)
            cout << "drzewa intow sa takie same!" << endl;
        else
            cout << "drzewa intow sa rozne!" << endl;

        if(pierwotneint1.search(5)==NULL)
            cout << "Nie ma w pierwszym drzewie intow liczby 5" <<endl;
        else
            cout << "Jest 5 w pierwszym drzewie intow" << endl;
        cout << endl;
        if(pierwotnestring1.search("sadwa")==NULL)
            cout << "Nie ma w pierwszym drzewie stringow wyrazu 'sadwa'" <<endl;
        else
            cout << "Jest wyraz 'sadwa' w pierwszym drzewie stringow" << endl;
        cout << endl;


    }


};


#endif // test_h
