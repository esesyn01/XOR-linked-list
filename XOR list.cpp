#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct Node {
    int number;
    Node* xorp;
};
Node* move_ptr(Node* l, Node* r)
{
    return (Node*)((uintptr_t)(l) ^ (uintptr_t)(r));
}
void insert_beg(int n, Node** begin, Node** end, Node** actual)
{
    Node* newn = new Node;
    newn->number = n;
    newn->xorp = move_ptr(*begin, NULL);
    if (*begin != nullptr)
    {
        (*begin)->xorp = move_ptr(newn, (*begin)->xorp);
    }
    if (*begin == nullptr)
    {
        *end = newn;
        *actual = newn;
    }
    *begin = newn;

}
void insert_bkw(int n, Node** begin, Node** end, Node** actual)
{
    Node* newn = new Node;
    newn->number = n;
    newn->xorp = move_ptr(*end, NULL);
    if (*end != nullptr)
    {
        (*end)->xorp = move_ptr(newn, (*end)->xorp);
    }
    if (*end == nullptr)
    {
        *begin = newn;
        *actual = newn;
    }
    *end = newn;

}
void set_np(Node* actual, Node* begin, Node* end, Node** prev, Node** next)
{
    Node* act = begin;      // ustawienie pomocniczych wskaznikow do podrozowania po liscie
    Node* prev1 = nullptr;
    Node* next1;
    while (act != actual)
    {
        next1 = move_ptr(prev1, act->xorp);
        prev1 = act;
        act = next1;
    }
    if (actual == begin)
    {
        *prev = end;
        next1 = move_ptr(prev1, act->xorp);
        *next = next1;
    }
    else                           // ustawienie next i prev zaleznie od warunkow
    {
        if (actual == end)
        {
            *next = begin;
            *prev = prev1;
        }
        else
        {
            if (begin == nullptr)
            {
                *prev = nullptr;
                *next = nullptr;
            }
            else
            {
                *prev = prev1;
                next1 = move_ptr(prev1, act->xorp);
                *next = next1;
            }
        }
    }
    act = nullptr;
    prev1 = nullptr;
    next1 = nullptr;
    delete act;
    delete prev1;
    delete next1;
}
void add_act(int n, Node** begin, Node** end, Node** actual, Node** prev, Node** next)
{
    Node* temp = nullptr;
    Node* newn = new Node;
    newn->number = n;
    if (*begin != nullptr)
    {
        if (*actual == *end)
        {
            temp = move_ptr((*prev)->xorp, *actual);
            newn->xorp = move_ptr((*actual), *prev);
            (*actual)->xorp = move_ptr(newn, NULL);
            (*prev)->xorp = move_ptr(temp, newn);
            *prev = newn;
            return;
        }
        if (*actual == *begin)
        {
            insert_beg(n, begin, end, actual);           // odpowiednie zachowanie dla pewnych warunkow
            *prev = *begin;
            return;
        }
        if (*prev == *begin)
        {
            newn->xorp = move_ptr((*actual), *prev);
            (*actual)->xorp = move_ptr(newn, *next);
            (*prev)->xorp = move_ptr(NULL, newn);
            *prev = newn;
            return;
        }
        temp = move_ptr((*prev)->xorp, *actual);
        newn->xorp = move_ptr((*actual), *prev);
        (*actual)->xorp = move_ptr(newn, *next);
        (*prev)->xorp = move_ptr(temp, newn);
        *prev = newn;
        return;
    }
    else
    {
        insert_beg(n, begin, end, actual);    // w przypadku pustej listy mamy identyczne zachowanie
        return;
    }

}
void move_fwd(Node** actual, Node** prev, Node** next, Node* begin, Node* end)
{
    Node* temp = *actual;
    Node* tempp = *next;
    if (*actual == nullptr)
    {
        cout << "NULL\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*next == end)
    {
        *next = begin;
        *prev = *actual;
        *actual = end;
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*actual == end)                // wlasciwe przechodzenie wskaznikow w roznych warunkach
    {
        *actual = begin;
        *prev = end;
        (*next) = move_ptr(begin->xorp, nullptr);
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*prev == end)
    {
        (*next) = move_ptr(tempp->xorp, temp);
        *actual = tempp;
        *prev = begin;
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    *next = move_ptr(tempp->xorp, temp);
    *prev = temp;
    *actual = tempp;
    cout << (*actual)->number << "\n";
    temp = nullptr;
    tempp = nullptr;
    delete tempp;
    delete temp;
    return;
}
void move_bkw(Node** actual, Node** prev, Node** next, Node* begin, Node* end)
{
    Node* temp = *actual;
    Node* tempp = *prev;
    if (*actual == nullptr)
    {
        cout << "NULL\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*prev == begin)
    {
        *next = temp;
        *prev = end;
        *actual = begin;
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*actual == begin)             // wlasciwe zachowanie funkcji w zaleznosci od ustawien wskaznikow
    {
        (*prev) = move_ptr(end->xorp, nullptr);
        *actual = end;
        *next = begin;
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    if (*next == begin)
    {
        (*prev) = move_ptr(tempp->xorp, end);
        *actual = tempp;
        *next = end;
        cout << (*actual)->number << "\n";
        temp = nullptr;
        tempp = nullptr;
        delete tempp;
        delete temp;
        return;
    }
    (*prev) = move_ptr(tempp->xorp, temp);
    *actual = tempp;
    *next = temp;
    cout << (*actual)->number << "\n";
    temp = nullptr;
    tempp = nullptr;
    delete tempp;
    delete temp;
    return;
}
void cactual(Node* actual)
{
    if (actual != nullptr)
        cout << actual->number << "\n";
    else
    {
        cout << "NULL\n";
    }
}
void print_fwd(Node* begin)
{
    if (begin == nullptr)
    {
        cout << "NULL\n";
        return;
    }
    Node* act = begin;
    Node* prev = nullptr;
    Node* next;
    while (act != nullptr)
    {
        cout << act->number << " ";
        next = move_ptr(prev, act->xorp);
        prev = act;
        act = next;
    }
    act = nullptr;
    next = nullptr;
    prev = nullptr;
    delete act;
    delete next;
    delete prev;
}
void print_bkw(Node* end)
{
    if (end == nullptr)
    {
        cout << "NULL\n";
        return;
    }
    Node* act = end;
    Node* next = nullptr;
    Node* prev;
    while (act != nullptr)
    {
        cout << act->number << " ";
        prev = move_ptr(act->xorp, next);
        next = act;
        act = prev;
    }
    act = nullptr;
    next = nullptr;
    prev = nullptr;
    delete act;
    delete next;
    delete prev;
}
void del_beg(Node** begin, Node** end, Node** actual, Node** prev, Node** next, bool* k)
{
    if (*begin == *end)
    {
        *begin = nullptr;
        *end = nullptr;
        *actual = nullptr;
        *prev = nullptr;
        *next = nullptr;
        *k = 0;
        return;
    }
    if (*begin == nullptr)
    {
        return;
    }
    bool f = 0, p = 0;   
    Node* temp;
    if (*actual == *begin)
    {
        temp = move_ptr((*end)->xorp, NULL);
        *prev = temp;
        *actual = *end;
        f = 1;
    }
    if (*prev == *begin)    // ustawienie flag aby odpowiednio sterowac reszta wskaznikow
    {
        p = 1;
    }
    if (*next == *begin)
    {
        f = 1;
    }
    Node* beg = move_ptr((*begin)->xorp, NULL);
    beg->xorp = move_ptr(beg->xorp, *begin);
    *begin = beg;
    if (f)
    {
        *next = *begin;
    }
    if (p)
    {
        *prev = *end;
    }
    temp = nullptr;
    beg = nullptr;
    delete temp;
    delete beg;
}
void del_end(Node** begin, Node** end, Node** actual, Node** prev, Node** next, bool* k)
{
    if (*begin == *end)
    {
        *begin = nullptr;
        *end = nullptr;
        *actual = nullptr;
        *prev = nullptr;
        *next = nullptr;
        *k = 0;
        return;
    }
    if (*begin == nullptr)
    {
        return;
    }
    bool p = 0, n = 0;
    Node* temp;
    if (*actual == *end)
    {
        temp = move_ptr((*prev)->xorp, *actual);
        *actual = *prev;
        *prev = temp;
    }
    if (*prev == *end)
    {
        p = 1;
    }
    if (*next == *end)
    {
        n = 1;
    }
    Node* ed = move_ptr((*end)->xorp, NULL);
    ed->xorp = move_ptr(ed->xorp, *end);
    *end = ed;
    if (p)
    {
        *prev = *end;
    }
    temp = nullptr;
    ed = nullptr;
    delete temp;
    delete ed;
}
void del_act(Node** begin, Node** end, Node** actual, Node** prev, Node** next, bool* k)
{
    if (*begin == *end)
    {
        *begin = nullptr;
        *end = nullptr;
        *actual = nullptr;
        *prev = nullptr;
        *next = nullptr;
        *k = 0;
        return;
    }
    if (*begin == nullptr)
    {
        return;
    }
    if (*actual == *begin)
    {
        del_beg(begin, end, actual, prev, next, k);
        return;
    }
    if (*actual == *end)
    {
        del_end(begin, end, actual, prev, next, k);
        return;
    }
    Node* temp;
    if (*prev == *begin && *next == *end)    // rozpatrywanie roznych ustawien wskaznikow
    {
         temp = *prev;
        (*prev)->xorp = *next;
        (*next)->xorp = temp;
        *actual = *prev;
        *prev = *next;
        return;
    }
    Node* p = nullptr;
    Node* n = nullptr;
    if (*prev != *begin)
    {
        p = move_ptr((*prev)->xorp, *actual);
    }
    if (*next != *end)
    {
        n = move_ptr((*next)->xorp, *actual);
    }
     temp = *prev;
    (*prev)->xorp = move_ptr(p, *next);
    (*next)->xorp = move_ptr(temp, n);
    *actual = *prev;
    if (p != nullptr)
    {
        *prev = p;
    }
    else
    {
        *prev = *end;
    }
    temp = nullptr;
    p = nullptr;
    n = nullptr;
    delete temp;
    delete p;
    delete n;
}
void del_n(Node** begin, Node** end, Node** actual, Node** prev, Node** next, int n, bool* k)
{
    if (*begin == nullptr)
    {
        return;
    }
    if (*begin == *end && (*begin)->number == n)
    {
        *begin = nullptr;
        *end = nullptr;
        *actual = nullptr;
        *prev = nullptr;
        *next = nullptr;
        *k = 0;
        return;
    }
    Node* act = *begin;
    Node* prv = nullptr;
    Node* nxt = nullptr;
    Node* temp;
    if ((*actual)->number != n)
    {
        temp = *actual;
    }
    else
    {
        Node* hp = *prev;
        Node* ha = *actual;
        Node* hn = *next;              
        while (ha->number == n)
        {
            hp = move_ptr(ha->xorp, hn);
            hn = ha;
            ha = hp;
        }
        temp = ha;          // ustalenie, na co wksazywal bedzie actual po wykonaniu usuwania elementow
        hp = nullptr;
        ha = nullptr;
        hn = nullptr;
        delete hp;
        delete ha;
        delete hn;
    }
    while (act != nullptr)
    {
        if (act->number == n)
        {
            *actual = act;
            set_np(*actual, *begin, *end, prev, next);   // ustawianie actual na wartosc usuwanego elementu
            del_act(begin, end, actual, prev, next, k);  // wywolanie wczesniej zaimplementowanej logiki, oszczednosc kodu
            if (*actual != *end)
            {
                act = *actual;
                if (*actual != *begin)
                {
                    prv = *prev;
                }
                else
                {
                    prv = nullptr;
                }

            }
            else
            {
                act = *begin;
                prv = nullptr;
            }
        }
        nxt = move_ptr(act->xorp, prv);
        prv = act;
        act = nxt;
    }
    *actual = temp;
    set_np(*actual, *begin, *end, prev, next);   // ustawienie actual oraz prev i next na odpowiednie pola
    temp = nullptr;
    act = nullptr;
    nxt = nullptr;
    prv = nullptr;
    delete temp;
    delete act;
    delete nxt;
    delete prv;
}
int main()
{
    Node* begin = nullptr;
    Node* prev = nullptr;
    Node* actual = nullptr;
    Node* next = nullptr;
    Node* end = nullptr;
    string cmd;
    int n;
    bool k = 0;
    while (cin >> cmd)
    {
        if (cmd == "ACTUAL")
        {
            cactual(actual);
        }
        if (cmd == "NEXT")
        {
            if (actual != nullptr && k == 0)
            {
                set_np(actual, begin, end, &prev, &next);
                k = 1;
            }
            move_fwd(&actual, &prev, &next, begin, end);
        }
        if (cmd == "PREV")
        {
            if (actual != nullptr && k == 0)
            {
                set_np(actual, begin, end, &prev, &next);
                k = 1;
            }
            move_bkw(&actual, &prev, &next, begin, end);
        }
        if (cmd == "ADD_BEG")
        {
            cin >> n;
            insert_beg(n, &begin, &end, &actual);
        }
        if (cmd == "ADD_END")
        {
            cin >> n;
            insert_bkw(n, &begin, &end, &actual);
        }
        if (cmd == "ADD_ACT")
        {
            if (actual != nullptr && k == 0)
            {
                set_np(actual, begin, end, &prev, &next);
                k = 1;
            }
            cin >> n;
            add_act(n, &begin, &end, &actual, &prev, &next);
        }
        if (cmd == "DEL_BEG")
        {
            del_beg(&begin, &end, &actual, &prev, &next, &k);
        }
        if (cmd == "DEL_END")
        {
            del_end(&begin, &end, &actual, &prev, &next, &k);
        }
        if (cmd == "DEL_VAL")
        {
            if (actual != nullptr && k == 0)
            {
                set_np(actual, begin, end, &prev, &next);
                k = 1;
            }
            cin >> n;
            del_n(&begin, &end, &actual, &prev, &next, n, &k);
        }
        if (cmd == "DEL_ACT")
        {
            if (actual != nullptr && k == 0)
            {
                set_np(actual, begin, end, &prev, &next);
                k = 1;
            }
            del_act(&begin, &end, &actual, &prev, &next, &k);
        }
        if (cmd == "PRINT_FORWARD")
        {
            print_fwd(begin);
            cout << "\n";
        }
        if (cmd == "PRINT_BACKWARD")
        {
            print_bkw(end);
            cout << "\n";
        }
    }
    actual = nullptr;
    begin = nullptr;
    end = nullptr;
    next = nullptr;
    prev = nullptr;
    delete actual;
    delete begin;
    delete end;
    delete next;
    delete prev;
    return 0;
}