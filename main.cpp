// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include "book.h"


#include "simpleLinkedListTemplate.h"
#include "StackAndQueue.h"
#include "Graph.h"

using namespace std;

///////////////////////////////////////////////////////////////////
// Submission Zone: You should submit your code after this line
///////////////////////////////////////////////////////////////////


template <class T>
bool List<T>::exist(T n) {
    start();
    while (_current->_next) {
        if (_current->_item == n) {
            return true;
        }
        next();
    }
    return false;
}

template <class T>
void List<T>::removeTail() { // assume not empty
	if (_size > 1) {
        start(); // current is at head
        for (int i = 0; i < _size - 2; i++) { // iterate until second last pointer
            next();
        }
        delete _current->_next;
        _tail = _current;
        _current->_next = nullptr; // set second last pointer as last
    } else {
        start();
        delete _current;
        _tail = nullptr;
        _head = nullptr;
    }
    _size--;
    return;
 }

// You should modify the following and submit

template <class T>
void List<T>::insertTail(T n) // cannot assume empty
{
    ListNode<T> *aNewNode = new ListNode<T>(n); // make new node
    aNewNode->_next = nullptr; // new node points to null
    // if size more than 0, go to last node, point it to new node
    if (_size > 0) {
        start();
        while (_current->_next) { // while next exists
            next();
        }
        _current->_next = aNewNode; // update last node
    }
    _tail = aNewNode; // update tail
    if (_size == 0) {
        _head = aNewNode;
    }
    _size++;
    return;
};

template <class T>
void Stack<T>::push(T item) { // insert head
    _l.insertHead(item);
    return;
}

template <class T>
T Stack<T>::pop() { // remove head of _l and return it
    if (_l.size() == 0) {
        throw std::out_of_range("empty queue");
    }
    _l.start(); // current is head
    T temp = _l.current();
    _l.removeHead();
    return temp;
}

template <class T>
void Queue<T>::enqueue(T item) { // insert tail of _l
    _l.insertTail(item);
    return;
}

template <class T>
T Queue<T>::dequeue() { // remove head of _l and return it
    if (_l.size() == 0) {
        throw std::out_of_range("empty queue");
    }
    _l.start(); // current is head
    T temp = _l.current();
    _l.removeHead();
    return temp;
}

int qBalancedBrackets(string exp) {
    int norm_op = 0;
    int curly_op = 0;

    for (unsigned int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
          norm_op++;
        } else if (exp[i] == '{') {
          curly_op++;
        } else if (exp[i] == ')') {
          norm_op--;
          if (norm_op < 0) {
            return 0;
          }
        } else if (exp[i] == '}') {
          curly_op--;
          if (curly_op < 0) {
            return 0;
          }
        }
    }
    return (norm_op == 0 && curly_op == 0);
};

void Graph::DFS(int s, List<int>& output, bool resetVisited) // start from s, dfs all connected
{
    if (resetVisited) {
        _resetVisited();
    }
    output.insertTail(s); // output item
    _setVisited(s); // mark item as visited

    _al[s].start();
    for (int n = 0; n < _al[s].size(); n++) { // for number of items in linked list
        if (!_isVisited(_al[s].current())) { // if head item of s linked list is not visited, 
          DFS(_al[s].current(), output, false); // dfs down current node
        }
        _al[s].next();
    }
};

void Graph::BFS(int s, List<int>& output, bool resetVisited)
{
    if (resetVisited) {
        _resetVisited();
    }
    List<int> frontier;
    frontier.insertTail(s); // add starting node to frontier
    _setVisited(s); // mark item as visited
    output.insertTail(s);
    while (!frontier.empty()) { // While there are nodes in the frontier
        int current = frontier.headItem(); // Get the current node from the frontier
        frontier.removeHead(); // Remove the current node from the frontier
        
        // Traverse the linked list corresponding to the current node's neighbors
        _al[current].start();
        while (!_al[current].end()) {
            int neighbor = _al[current].current();
            if (!_isVisited(neighbor)) {
                _setVisited(neighbor); // Mark neighbor as visited
                output.insertTail(neighbor); // Output neighbor
                frontier.insertTail(neighbor); // Add neighbor to the frontier
            }
            _al[current].next(); // Move to the next neighbor in the linked list
        }
    }
};

int Graph::nComponents() {
    // Task 7
    return 0;
};
///////////////////////////////////////////////////////////////////
// Submission Zone Ended: You should submit your code above this line
///////////////////////////////////////////////////////////////////



void insertTailTest();
void stackTest();
void queueTest();
void bookStackTest();
void bookQueueTest();
int BFSTest(string,bool printGraph=true);
int DFSTest(string, bool printGraph = true);
int nComponentTest(string filename, bool printGraph = true);
void balancedBracketsTest(string exp);


int main()
{
    // All test cases
    //Task 1
    insertTailTest();

    // Task 2
    //stackTest();
    //bookStackTest();
    // For the book test, you need to uncomment the function with body below

    // Task 3
    //queueTest();
    //bookQueueTest();
    
    // Task 4
    //balancedBracketsTest("((a+b)+{e-(a-b)})");
    //balancedBracketsTest("(((a+b)+{e-(a-b)})");
    //balancedBracketsTest("(){}(){}(()){{}}");
    //balancedBracketsTest(")(");

    cout << endl;

    // Task 5
    //DFSTest("graphTraveralexample1.txt");
    //DFSTest("graphTraveralexample2.txt");
    //DFSTest("graphTraveralexample3.txt");


    // Task 6
    //BFSTest("graphTraveralexample1.txt");
    //BFSTest("graphTraveralexample2.txt");
    //BFSTest("graphTraveralexample3.txt");


    // Task 7
    //nComponentTest("cexample1.txt");
    //nComponentTest("cexample2.txt");
    //nComponentTest("cexample3.txt");

    return 0;
}

void insertTailTest() {
    cout << "Insert Tail Test:" << endl;
    List<int> li;
    for (int i = 1; i < 5; i++)
    {
        li.insertHead(i);
        li.insertTail(i);
    }
    cout << "List after inserting head and tails" << endl;
    cout << "Your list:" << endl;
    li.print();
    cout << "List after more deletion and insertion" << endl;
    for (int i = 0; i < 8; i++)
    {
        li.removeHead();
    }
    for (int i = 100; i < 104; i++)
    {
        li.insertHead(i);
        li.insertTail(i);
    }
    li.removeHead();
    cout << "Your list:" << endl;
    li.print();
    cout << endl;
}


void stackTest()
{

    Stack<int> si;


    cout << "Stack Test:" << endl;

    for (int i = 0; i < 10; i++)
        si.push(i);
    for (int i = 0; i < 3; i++)
        si.pop();
    for (int i = 90; i < 100; i++)
        si.push(i);
    cout << "Your output" << endl;
    si.print();
    cout << endl;
}

void queueTest() {

    Queue<int> qi;
    cout << "Queue Test:" << endl;
    for (int i = 0; i < 10; i++)
        qi.enqueue(i);
    for (int i = 0; i < 3; i++)
        qi.dequeue();
    for (int i = 90; i < 100; i++)
        qi.enqueue(i);
    cout << "Your output" << endl;
    qi.print();
    cout << endl;

}

/*
void bookStackTest()
{

    Stack<Book> sb;


    cout << "Book Stack Test:" << endl;

    for (int i = 0; i < 5; i++)
    {
        string series("Hairy Border ");
        Book b(series + to_string(i+1),100+i);
        sb.push(b);
    }
    
    for (int i = 0; i < 3; i++)
        sb.pop();
    for (int i = 0; i < 2; i++)
    {
        string series("Bravo Super Hero Comics ");
        Book b(series + to_string(i+1),23+i);
        sb.push(b);
    }

    sb.print(true);
}

void bookQueueTest()
{

    Queue<Book> qb;


    cout << "Book Queue Test:" << endl;

    for (int i = 0; i < 5; i++)
    {
        string series("Hairy Border ");
        Book b(series + to_string(i+1),100+i);
        qb.enqueue(b);
    }
    
    for (int i = 0; i < 3; i++)
        qb.dequeue();
    for (int i = 0; i < 2; i++)
    {
        string series("Bravo Super Hero Comics ");
        Book b(series + to_string(i+1),23+i);
        qb.enqueue(b);
    }

    qb.print(true);
}
*/

void balancedBracketsTest(string exp)
{
    cout << "The expression \"" << exp << "\" is " << (qBalancedBrackets(exp) ? "balanced" : "not balanced" )<< endl;
}

int DFSTest(string filename, bool printGraph) {
    cout << "DFS Test with file: " << filename << endl;
    ifstream myfile(filename);
    int v; // number of vertices
    int e; // number of edges
    int q; // number of queries
    
    if (myfile.fail()){
        cout << "File not found" << endl;
        return -1;
    }
    
    myfile >> v;
    myfile >> e;
    myfile >> q;
    

    Graph G(v); // create a graph with nv nodes
    int s, d;

    // read in all the edges and add into the graph
    for (int i = 0; i < e; i++)
    {
        myfile >> s;
        myfile >> d;
        G.addEdge(s, d);
        G.addEdge(d, s);
    }
    
    if (printGraph)
        G.printGraph(); 

    for (int i = 0; i < q; i++)
    {
        myfile >> s;
        cout << "Starting from Node " << s << ":" << endl;
        List<int> li;
        G.DFS(s, li);
        li.print();

    }
    myfile.close();
    cout << endl;
    return 0;
}

int BFSTest(string filename, bool printGraph) {
    cout << "BFS Test with file: " << filename << endl;
    ifstream myfile(filename);
    int v; // number of vertices
    int e; // number of edges
    int q; // number of queries

    if (myfile.fail()) {
        cout << "File not found" << endl;
        return -1;
    }

    myfile >> v;
    myfile >> e;
    myfile >> q;


    Graph G(v); // create a graph with nv nodes
    int s, d;

    // read in all the edges and add into the graph
    for (int i = 0; i < e; i++)
    {
        myfile >> s;
        myfile >> d;
        G.addEdge(s, d);
        G.addEdge(d, s);
    }

    if (printGraph)
        G.printGraph();


    for (int i = 0; i < q; i++)
    {
        
        myfile >> s;
        cout << "Starting from Node " << s << ":" << endl;
        List<int> li;
        G.BFS(s, li);
        li.print();
    }
    myfile.close();
    cout << endl;
    return 0;
}

int nComponentTest(string filename,bool printGraph) {
    cout << "Number of Component Test with file: " << filename << endl;
    ifstream myfile(filename);
    int v; // number of vertices
    int e; // number of edges
    int q; // number of queries

    if (myfile.fail()) {
        cout << "File not found" << endl;
        return -1;
    }



    myfile >> v;
    myfile >> e;
    myfile >> q;


    Graph G(v); // create a graph with nv nodes
    int s, d;

    // read in all the edges and add into the graph
    for (int i = 0; i < e; i++)
    {
        myfile >> s;
        myfile >> d;
        G.addEdge(s, d);
        G.addEdge(d, s);
    }

    if (printGraph)
        G.printGraph();


    cout << "No. of components = " << G.nComponents() << endl;

    myfile.close();
    cout << endl;
    return 0;
}
