#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <deque>
#include <stack>
#include "mpi.h"
#include <string>
#include  "time.h"
#include <bits/stdc++.h>

using namespace std;


class State {
public:
	int a[9];
	State() {}

	void generate() // generate the 8-puzzle problem to solve 
	{
		for (int i = 0; i < 9; i++)
		{
			cout << "enter the num: " << i << endl;
			cin >> a[i];
		}
	}
	void set(int t[])
	{
		for (int i = 0; i < 9; i++)
		{
			a[i]=t[i];
		}
	}
	int* getMatrix()
	{
		return a;
	}
	void print() {
		cout << "-----------------" << endl;
		for (int i = 0; i < 9; i++) {
			if (i > 0 && i % 3 == 0) cout << endl;
			cout << a[i] << "\t";
		}
		cout << endl << "-----------------" << endl;
	}
	int findzero() //find the index of the space (to move it in order to solve the problem)
	{
		for (int i = 0; i < 9; i++) {
			if (a[i] == 0)
				return i;
		}
		return 0;
	}
	State exch(int i, int j) { //exchange the two numbers in the Node 
		State b;
		for (int k = 0; k < 9; k++)
			b.a[k] = a[k];
		int t = b.a[i];
		b.a[i] = b.a[j];
		b.a[j] = t;
		return b;
	}
	int equal(State s) { //check if 2 Nodes are equal
		for (int i = 0; i < 9; i++) {
			if (a[i] != s.a[i]) return 0;
		}
		return 1;
	}
	int goal() { //Check if we reach the goal 
		int g[9] = { 0,1,2,4,4,5,5,7,8 };

		for (int i = 0; i < 9; i++) {
			if (a[i] != g[i]) return 0;
		}
		return 1;
	}
};

class Node {
public:
	State s;
	Node* father;
	int action, cost, depth;
	char fchild;
	char ch='f';

	Node() { //default constructor the root node has no father and no action
		State s;
		father = NULL;
		action = -1;
		cost = 1;
		depth = 0;
		fchild=' ';
	}
	Node(State _s, Node* _father, int _action, int _depth) { //parametarized constructor
		s = _s;
		father = _father;
		action = _action;
		depth = _depth;
		fchild=' ';
	}
	Node copy() { //copy the node 
		Node b;
		for (int i = 0; i < 9; i++)
			b.s.a[i] = s.a[i];
		b.father = father;
		b.action = action;
		b.depth = depth;

		return b;
	}
	void print() {
		//cout << "Cost/Generated: \t" << cost << endl;
		//cout << "Depth/Expanded: \t" << depth << endl;
	}
	void expand(deque<Node>* deque ,Node &n1, Node &n2, Node &n3, Node &n4) {
		int p = s.findzero();
		Node tempn1,tempn2,tempn3,tempn4;
		tempn1=moveup(deque, p);
		tempn2=movedown(deque, p);
		tempn3=moveright(deque, p);
		tempn4=moveleft(deque, p);
		n1=tempn1;
		n2=tempn2;
		n3=tempn3;
		n4=tempn4;		
	}
	void expand2(deque<Node>* deque) {
		int p = s.findzero();
		moveup2(deque, p);
		movedown2(deque, p);
		moveright2(deque, p);
		moveleft2(deque, p);
	}
	int expanded(deque<State>* deque) { //return 0 if the node not expanded yet >>Can be expanded  
		int max = (*deque).size() > depth ? depth : (*deque).size();
		for (int i = 0; i < max; i++) {
			if (s.equal((*deque)[i])) {
				return 1;
			}
		}
		return 0;
	}
	Node moveup(deque<Node>* deque, int p)
	{
		Node nempty;
		//moveup    (0)
		if ((p != 0 && p != 1 && p != 2) && action != 1) {
			Node n(s.exch(p, p - 3), this, 0, depth + 1);
			(*deque).push_back(n);
			n.fchild='f';
			return n;
		}
		return nempty;
	}
	Node movedown(deque<Node>* deque, int p)
	{
		Node nempty;
		//movedown     (1)
		if ((p != 6 && p != 7 && p != 8) && action != 0) {
			Node n(s.exch(p, p + 3), this, 1, depth + 1);
			(*deque).push_back(n);
			n.fchild='f';
			return n;
		}
		return nempty;
	}
	Node moveright(deque<Node>* deque, int p)
	{
		Node nempty;
		//moveright (2)
		if ((p != 2 && p != 5 && p != 8) && action != 3) {
			Node n(s.exch(p, p + 1), this, 2, depth + 1);
			(*deque).push_back(n);
			n.fchild='f';
			return n;
		}
		return nempty;
	}
	Node moveleft(deque<Node>* deque, int p)
	{
		Node nempty;
		//moveleft     (3)
		if ((p != 0 && p != 3 && p != 6) && action != 2) {
			Node n(s.exch(p, p - 1), this, 3, depth + 1);
			(*deque).push_back(n);
			n.fchild='f';
			return n;
		}
		return nempty;
	}
	void moveup2(deque<Node>* deque, int p)
	{
		//moveup    (0)
		if ((p != 0 && p != 1 && p != 2) && action != 1) {
			Node n(s.exch(p, p - 3), this, 0, depth + 1);
			(*deque).push_back(n);
		}
		
	}
	void movedown2(deque<Node>* deque, int p)
	{
		//movedown     (1)
		if ((p != 6 && p != 7 && p != 8) && action != 0) {
			Node n(s.exch(p, p + 3), this, 1, depth + 1);
			(*deque).push_back(n);
		}
		
	}
	void moveright2(deque<Node>* deque, int p)
	{
		//moveright (2)
		if ((p != 2 && p != 5 && p != 8) && action != 3) {
			Node n(s.exch(p, p + 1), this, 2, depth + 1);
			(*deque).push_back(n);
		}
		
	}
	void moveleft2(deque<Node>* deque, int p)
	{
		//moveleft     (3)
		if ((p != 0 && p != 3 && p != 6) && action != 2) {
			Node n(s.exch(p, p - 1), this, 3, depth + 1);
			(*deque).push_back(n);

		}
		
	}
	
	
	int bfs2(int &depth ,int rank,Node &n1, Node &n2, Node &n3, Node &n4)
	{
		clock_t start, end;
		start = clock();
		bool flag=true;
		MPI_Status status;
		deque<Node> toexpand;
		deque<State> expanded;
		toexpand.push_back(*this);
		bool flag2=true;
		while (!toexpand.empty() && (n1.ch=='f' && n2.ch=='f' && n3.ch=='f' &&  n4.ch=='f')) 
		{
			if (toexpand.front().s.goal() == 1 ) 
			{
				cout << "Solution found from rank: "<<rank<< endl;
				toexpand.front().print();
				cost = toexpand.front().cost;
				depth=toexpand.front().depth;
				toexpand.clear();
				cout<<"The DEPTH IS: "<<depth<<endl;
				cout<<"COST is: " << cost<<endl;
				end = clock();
			    	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
			    	cout << "Time taken by rank "<<rank<< " is : " << fixed << time_taken << setprecision(5);
			    	cout << " sec " << endl;
			    	cout<<endl;
			    	cout<<"**************************************************"<<endl;
			    	cout<<endl;
			    	n1.ch='t';
			    	n2.ch='t';
			    	n3.ch='t';
			    	n4.ch='t';
			    	
			    	MPI_Send(&ch, 1, MPI_BYTE, rank, 10, MPI_COMM_WORLD);
				return cost;
			}
			else
			{
				int flag1,flag3;
					if (!(toexpand.front().expanded(&expanded))) 
					{
						toexpand.front().expand2(&toexpand);
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
	int bfs(Node &n1, Node &n2, Node &n3, Node &n4)
	{
		deque<Node> toexpand;
		deque<State> expanded;
		toexpand.push_back(*this);
		while (!toexpand.empty()) 
		{
			if (toexpand.front().s.goal() == 1) {
				cout << "Solution found from rank 0." << endl;
				toexpand.front().print();
				cost = toexpand.front().cost;
				toexpand.clear();
				
				return cost;
			}
			else
			{
				if (!(toexpand.front().expanded(&expanded))) 
				{
					toexpand.front().expand(&toexpand , n1,n2,n3,n4);
					expanded.push_front(toexpand.front().s);
					toexpand[1].cost = toexpand[0].cost + 1;
				}
				toexpand.pop_front();
			}
			return 0;
		}
		if (toexpand.empty())
			cout << endl << "Solution NOT found!" << endl;
		
		return 0;
	}
};
int main(int argc, char *argv[]) 
{	
	clock_t start, end;
	start = clock();
	int size, rank;
	int bfscost = 0;
	int bfsdepth=0;
	int bfsfail = 0;
	int _bfs = 0;
	int _bfs2 = 0;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	//4 nodes for the childs from the initial node which is n
	Node n1,n2,n3,n4,n;
	int *a1,*a2,*a3,*a4;
	int atemp1[9];
	int atemp2[9];
	int atemp3[9];
	int atemp4[9];
	int depth1,depth2,depth3,depth4;
	char flag1,flag2,flag3,flag4;
	if(rank == 0)
	{
		cout << "The Problem is:" << endl;
		n.s.generate();
		n.s.print();
		_bfs = n.bfs(n1,n2,n3,n4);
	}
	//For synchronization
	//MPI_Barrier(MPI_COMM_WORLD);
	a1=n1.s.getMatrix();
	a2=n2.s.getMatrix();
	a3=n3.s.getMatrix();
	a4=n4.s.getMatrix();
	for(int i=0;i<9;i++)
	{
		atemp1[i]=a1[i];
		atemp2[i]=a2[i];
		atemp3[i]=a3[i];
		atemp4[i]=a4[i];
	}
	MPI_Bcast(&n1.depth, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n2.depth, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n3.depth, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n4.depth, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(&n1.fchild, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n2.fchild, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n3.fchild, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	MPI_Bcast(&n4.fchild, 1, MPI_CHAR, 0, MPI_COMM_WORLD);
	
	MPI_Bcast(&atemp1, 9, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&atemp2, 9, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&atemp3, 9, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&atemp4, 9, MPI_INT, 0, MPI_COMM_WORLD);
	char a;
	
	if(rank==1)
	{
		if(n1.fchild!=' ')
		{
			n1.s.set(atemp1);
			_bfs2 = n1.bfs2(depth1,1,n1,n2,n3,n4);
			if (_bfs2 > 0)
			{
				
				MPI_Recv(&flag1, 1, MPI_BYTE, 1, 10, MPI_COMM_WORLD, &status);
				n1.ch=flag1;
				bfscost += _bfs2;
				//send the cost and depth to rank 0
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&depth1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				
			}
			else
			{
				bfsfail += 1;
				bfscost = -1;
				bfsdepth= -1;
				//send -1 to rank 0
				MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			}
		}
		else
		{
			bfscost = -1;
			bfsdepth= -1;
			//send -1 to rank 0 if the rank did not work
			MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		
		
		
		
	}
	//MPI_Bcast(&n1.ch, 1, MPI_BYTE, 1, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==2)
	{
		if(n2.fchild!=' ')
		{
			n2.s.set(atemp2);
			_bfs2 = n2.bfs2(depth2,2,n1,n2,n3,n4);
			if (_bfs2 > 0)
			{
				MPI_Recv(&flag2, 1, MPI_BYTE, 2, 10, MPI_COMM_WORLD, &status);
				n2.ch=flag2;
				bfscost += _bfs2;
				//send the cost and depth to rank 0
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&depth2, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			}
			else
			{	
				bfsfail += 1;
				bfscost = -1;
				bfsdepth= -1;
				//send -1 to rank 0
				MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);	
			}
		}
		else
		{
			bfscost = -1;
			bfsdepth= -1;
			//send -1 to rank 0 if the rank did not work
			MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
	}
	
	//MPI_Bcast(&n2.ch, 1, MPI_BYTE, 2, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==3)
	{
		if(n3.fchild!=' ')
		{
			n3.s.set(atemp3);
			_bfs2 = n3.bfs2(depth3,3,n1,n2,n3,n4);
			if (_bfs2 > 0)
			{
				MPI_Recv(&flag3, 1, MPI_BYTE, 3, 10, MPI_COMM_WORLD, &status);
				n3.ch=flag3;
				bfscost += _bfs2;
				//send the cost and depth to rank 0
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&depth3, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			}
			else
			{

			
				bfsfail += 1;
				bfscost = -1;
				bfsdepth= -1;
				//send -1 to rank 0
				MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				
			}
		}
		else
		{
			bfscost = -1;
			bfsdepth= -1;
			//send -1 to rank 0 if the rank did not work
			MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		
	}
	
	//MPI_Bcast(&n3.ch, 1, MPI_BYTE, 3, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==4)
	{
		if(n4.fchild!=' ')
		{
			n4.s.set(atemp4);

			
			
			_bfs2 = n4.bfs2(depth4,4,n1,n2,n3,n4);
			if (_bfs2 > 0)
			{
				MPI_Recv(&flag4, 1, MPI_BYTE, 4, 10, MPI_COMM_WORLD, &status);
				n4.ch=flag4;
				bfscost += _bfs2;
				//send the cost and depth to rank 0
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&depth4, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			}
			else
			{
				bfsfail += 1;
				bfscost = -1;
				bfsdepth= -1;
				//send -1 to rank 0
				MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);	
			}
		}
		else
		{
			bfscost = -1;
			bfsdepth= -1;
			//send -1 to rank 0 if the rank did not work
			MPI_Send(&bfsdepth, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			MPI_Send(&bfscost, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		}
		
	}
	//MPI_Bcast(&n4.ch, 1, MPI_BYTE, 4, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
	if(rank==0)
	{
		//cout<<"RANK 0"<<endl;	
		int cost=0;
		int depth=0;
		int costtemp[4];
		int depthtemp[4];
		char t[4];
		//receive the cost from the 4 ranks
		MPI_Recv(&costtemp[0], 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&costtemp[1], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&costtemp[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&costtemp[3], 1, MPI_INT, 4, 1, MPI_COMM_WORLD, &status);
		//receive the depth from the 4 ranks
		MPI_Recv(&depthtemp[0], 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&depthtemp[1], 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&depthtemp[2], 1, MPI_INT, 3, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&depthtemp[3], 1, MPI_INT, 4, 1, MPI_COMM_WORLD, &status);
		int mincost=11111111;
		int index=-1;
			
		for(int i=0;i<4;i++)
		{
			if(depthtemp[i]<mincost && depthtemp[i]!=-1)
			{
				
				mincost=depthtemp[i];
				index=i;
			}
		}
		if(index!=-1)
		{
			cout<<"The optimal solution found from rank: "<<index+1<<"."<<endl;
			cout<<"The cost is: "<<costtemp[index]<<"."<<endl;
			cout<<"The depth is: "<<depthtemp[index]<<"."<<endl;
		}
		else
			cout<<"Solution not found from any ranks."<<endl;
		end = clock();
	    	double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
	    	cout << "Time taken by program is : " << fixed << time_taken << setprecision(5);
	    	cout << " sec " << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
		
	MPI_Finalize();
	return 0;
}
