#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <stack>
#include  "time.h"
#include <bits/stdc++.h>
using namespace std;
class State {
public:
	int puzzle[9];
	State() {}
	void generate() // generate the 8-puzzle problem to solve 
	{
		for (int i = 0; i < 9; i++)
		{
			cout << "enter the num: " << i << endl;
			cin >> puzzle[i];
		}
	}

	void print() 
	{
		cout << "-----------------" << endl;
		for (int i = 0; i < 9; i++) {
			if (i > 0 && i % 3 == 0) cout << endl;
			cout << puzzle[i] << "\t";
		}
		cout << endl << "-----------------" << endl;
	}
	int findzero() //find the index of the space (to move it in order to solve the problem)
	{
		for (int i = 0; i < 9; i++) {
			if (puzzle[i] == 0)
				return i;
		}
		return 0;
	}
	State exchange(int i, int j) 
	{ //exchange the two numbers in the Node 
		State b;
		for (int k = 0; k < 9; k++)
			b.puzzle[k] = puzzle[k];
		int t = b.puzzle[i];
		b.puzzle[i] = b.puzzle[j];
		b.puzzle[j] = t;
		return b;
	}


	int equal(State s) 
	{
		for (int i = 0; i < 9; i++) {
			if (puzzle[i] != s.puzzle[i]) return 0;
		}
		return 1;
	}
	int goal() 
	{ 
	/*
	The Goal is:
	0	1	2
	4	4	5
	5	7	8
	*/
		int goalstate[9] = { 0,1,2,4,4,5,5,7,8 };

		for (int i = 0; i < 9; i++) {
			if (puzzle[i] != goalstate[i]) return 0;
		}
		return 1;
	}
};


class Node 
{
public:
	State s;
	Node* startnode;
	int action, cost, depth;
	Node() 
	{ //default constructor the root node has no startnode and no action
		State s;
		startnode = NULL;
		action = -1;
		cost = 1;
		depth = 0;
	}
	Node(State _s, Node* _startnode, int _action, int _depth) 
	{
		s = _s;
		startnode = _startnode;
		action = _action;
		depth = _depth;
	}
	Node copy() 
	{ //copy the node 
		Node copynode;
		for (int i = 0; i < 9; i++)
			copynode.s.puzzle[i] = s.puzzle[i];
		copynode.startnode = startnode;
		copynode.action = action;
		copynode.depth = depth;

		return copynode;
	}
	void print() 
	{
		
		cout << "Cost: \t" << cost << endl;
		cout << "Depth: \t" << depth << endl;
	}
	void expand(deque<Node>* deque) 
	{
		int p = s.findzero();
		up(deque, p);
		down(deque, p);
		right(deque, p);
		left(deque, p);
	}
	int expanded(deque<State>* deque) 
	{  
		int max = (*deque).size() > depth ? depth : (*deque).size();
		for (int i = 0; i < max; i++) {
			if (s.equal((*deque)[i])) {
				return 1;
			}
		}
		return 0;
	}
	void up(deque<Node>* deque, int p)
	{
		//moveup    (0)
		if ((p != 0 && p != 1 && p != 2) && action != 1) {
			Node n(s.exchange(p, p - 3), this, 0, depth + 1);
			(*deque).push_back(n);
			//cout<<"UP"<<endl;
			//n.s.print();
		}
		
	}
	void down(deque<Node>* deque, int p)
	{
		//movedown     (1)
		if ((p != 6 && p != 7 && p != 8) && action != 0) {
			Node n(s.exchange(p, p + 3), this, 1, depth + 1);
			(*deque).push_back(n);
			//cout<<"DOWN"<<endl;
			//n.s.print();
		}
		
	}

	void right(deque<Node>* deque, int p)
	{
		//moveright (2)
		if ((p != 2 && p != 5 && p != 8) && action != 3) {
			Node n(s.exchange(p, p + 1), this, 2, depth + 1);
			(*deque).push_back(n);
			//cout<<"RIGHT"<<endl;
			//n.s.print();
		}
		
	}
	void left(deque<Node>* deque, int p)
	{
		//moveleft     (3)
		if ((p != 0 && p != 3 && p != 6) && action != 2) {
			Node n(s.exchange(p, p - 1), this, 3, depth + 1);
			(*deque).push_back(n);
			//cout<<"LEFT"<<endl;
			//n.s.print();
		}
		
	}
	int bfs()
	{
		deque<Node> toexpand;
		deque<State> expanded;
		toexpand.push_back(*this);
		while (!toexpand.empty()) 
		{
			if (toexpand.front().s.goal() == 1) 
			{
				cout << "------|BFS|------" << endl;
				cout << "Solution found!" << endl;
				toexpand.front().print();
				cost = toexpand.front().cost;
				toexpand.clear();
				return cost;
			}
			else {
				if (!(toexpand.front().expanded(&expanded))) {
					toexpand.front().expand(&toexpand);
					expanded.push_front(toexpand.front().s);
					toexpand[1].cost = toexpand[0].cost + 1;
				}
				toexpand.pop_front();
			}
		}
		if (toexpand.empty())
			cout << endl << "Solution NOT found!" << endl;
		return 0;
	}
};
int main(int argc, char* argv[]) 
{
	clock_t start, end;
	start = clock();
	int bfscost = 0;
	int bfsfail = 0;
	
		int _bfs = 0;
		cout << "The Problem is:" << endl;
		Node n;
		n.s.generate();
		n.s.print();
		_bfs = n.bfs();
		if (_bfs > 0)
			bfscost += _bfs;
		else
			bfsfail += 1;
    	end = clock();
    	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    	cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
    	cout << " sec " << endl;
	return 0;
}
