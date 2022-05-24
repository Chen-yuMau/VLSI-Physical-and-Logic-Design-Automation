#include<stdio.h> 
#include<stdlib.h>
#include<limits.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <Windows.h>
#include <queue>
using namespace std;

int dx[4]={-1,0,1,0},dy[4]={0,-1,0,1};
#define LOCKED 1
#define UNLOCKED 0

//built node .... node = (data and pointer)
class cord
{
	public:
		int x;
		int y;
		cord(int a,int b)
		{
			x = a;
			y = b;
		}
};

struct node	 //node or link
{
	int data;   //data item
	int data2;
	node* next; //pointer to next node
};

class map
{
	public:
		int rep[16][16];
		int x;
		int y;
		map(int a)
		{
			for(int i=0;i<16;i++)
			{
				for(int j=0;j<16;j++)
				{
					rep[i][j] = (-1);
				}
			}
		}
		void display()
		{
            cout<<"-------------------------------------------------"<<endl;
			for(int i=0;i<16;i++)
			{
                cout<<"|";
				for(int j=0;j<16;j++)
				{
					if(rep[i][j]<10)
					{
						cout<<" ";
					}
					if(rep[i][j]==(-1))
					{
						cout<<" |";
					}
					else
					{
						cout<<rep[i][j]<<"|";
					}
				}
				cout<<endl;
				cout<<"-------------------------------------------------"<<endl;
			}
			cout<<endl;
			return;
		}
		int mapref(int a)
		{
			for(int i=0;i<16;i++)
			{
				for(int j=0;j<16;j++)
				{
					if(rep[i][j]==a)
					{
						x = i;
						y = j;
						return(1);
					}
				}
			}
			return(0);
		}
};


class charmap
{
	public:
		char rep[24][24];
		int x;
		int y;
		charmap(int a)
		{
			for(int i=0;i<24;i++)
			{
				for(int j=0;j<24;j++)
				{
					rep[i][j] = (-1);
				}
			}
		}
		void display()
		{
            cout<<"-------------------------------------------------"<<endl;
			for(int i=0;i<24;i++)
			{
                cout<<"|";
				for(int j=0;j<24;j++)
				{
					if(rep[i][j]=='*')
					{
						cout<<" "<<rep[i][j]<<"|";
					}
					else
					{
						cout<<rep[i][j]<<"|";
					}
				}
				cout<<endl;
				cout<<"-------------------------------------------------"<<endl;
			}
			cout<<endl;
			return;
		}
		int mapref(char a)
		{
			for(int i=0;i<24;i++)
			{
				for(int j=0;j<24;j++)
				{
					if(rep[i][j]==a)
					{
						x = i;
						y = j;
						return(1);
					}
				}
			}
			return(0);
		}
};

//built linked list
class linkedlist
{
	private:
		node* head; //head or first ... pointer to the first node

	public:
		linkedlist()	//constructor
		{
			head=NULL;  //head pointer points to null in the beginning == empty list

		}

		//declaration
		void addElement(int d);			  //add element (one node)
		void delElement(int d);
		void clear();
		int refELement(int d);
		int pop();
		int count();
		int exist(int i);
		void display();						 //display all nodes
};

int indextogain(int i)
{
	if(i%2==0)
	{
		return(i/2);
	}
	else
	{
		return(-((i+1)/2));
	}
}
int gaintoindex(int i)
{
	if(i>=0)
	{
		return(2*i);
	}
	else
	{
		return((-2)*i-1);
	}
}

class gain
{
	public:
		linkedlist bucket[100];
		int max;
		int num;
	gain(int i)
	{
		num = 0;
	}
	void clear()
	{
		for(int i=0;i<100;i++)
		{
			bucket[i].clear();
		}
		num = 0;
	}
	void save(int d,int gain)
	{
		bucket[gaintoindex(gain)].addElement(d);
		if (num==0||gain>max)
		{
			max = gain;
		}
		num++;
	}
	int bucketpop(int gain)
	{
		num--;
		for(int i= 49;i>=-49;i--)
		{
			if(bucket[gaintoindex(i)].count()!=0)
			{
				max = i;
				break;
			}
		}
		return(bucket[gaintoindex(max)].pop());
	}
	void remove(int d,int gain)
	{
		int n;
		if(gain>=0)
		{
			bucket[2*gain].delElement(d);
			n = 2*gain;
		}
		else
		{
			bucket[(-2)*gain-1].delElement(d);
			n = (-2)*gain-1;
		}
		num--;
		if (bucket[n].count()==0&&num>0)
		{
			while(bucket[n].count()==0)
			{
				if(n>0)
				{
					n-=2;
				}
				else if(n==0)
				{
					n+=1;
				}
				else
				{
					n+=2;
				}
			}
			if(n%2==0)
			{
				max = n/2;
			}
			else
			{
				max = -((n+1)/2);
			}
		}
		else if(num==0)
		{
			max = 0;
		}
	}
	void show()
	{
		int n = num;
		int i;
		int gain;
		i=gaintoindex(max);
		for(;(i>=0)&&(n>0);i-=2)
		{
			//cout<<indextogain(i)<<" : ";
			bucket[i].display();
			n-=bucket[i].count();
		}
		i=1;
		while(n>0)
		{
			//cout<<indextogain(i)<<" : ";
			bucket[i].display();
			n-=bucket[i].count();
			i+=2;
		}
		//cout<<endl;
	}
};


class connections
{
	public:
		int matrix[100][100];
		int vertex;
		int net;
		int limit_min;
		int limit_max;
		connections(int v,int n)
		{
			vertex = v;
			net = n;
			for(int i=0;i<100;i++)
			{
				for(int j=0;j<100;j++)
				{
					matrix[i][j]=(-1);
				}
			}
		}
};

//definition

//1-Push back code
connections copycon(connections a)
{
	return(a);
}
linkedlist copylist(linkedlist a)
{
	return(a);
}

void linkedlist::addElement(int x)
{
	node* newNode=new node;	 //newNode is the pointer of the new node
	node* temp=new node;		//temp or fromStartToEnd is the pointer must be pointer to the same as head points
	temp=head;				  //fromStartToEnd is the pointer must be pointer to the same as head points
	newNode->data=x;			//in newNode in data put x
	if(temp==NULL)			  //means if linked list is empty
	{
		newNode->next=NULL;
		head=newNode;
		return;				 //to end function

	}

	//if not,if there end(head in first then called end) points to node
	while(temp->next!=NULL)
	{
		temp=temp->next;		//make end pointer points to the next node

	}
	newNode->next=NULL;		 //make put pointer points to null
	temp->next=newNode;		 //then make end pointer points to the new node (put)

}

void linkedlist::delElement(int d)
{
	node* del;  //del is pointer points to node
	del=head;   //first we make del points to where the head points

	if(del==NULL)   //means if linked list is empty
	{
		//cout<<"Linked list is empty"<<endl;
		return;	 //return to main

	}

	if(del->data==d)	//if first element in linked list is the element that we want to delete ... or one element is what we want
	{
		head=del->next; //make head points to the next to del
		return;
	}

	//if(del->data!=d) .... the same
	if(del->next==NULL) //if first element in linked list is not the element that we want to delete ... or one element is not what we want
	{
		//cout<<"Is not here, So not deleted."<<endl;
		return;
	}

	//if here more one nodes...one node points to another node ... bigger than 2 nodes .. at least 2 nodes
	while(del->next!=NULL)
	{
		if(del->next->data==d)
		{
			del->next=del->next->next;
			return;

		}
		//else
		del=del->next;

	}
	//cout<<"Is not here, So not deleted."<<endl;

}

void linkedlist::clear()
{
	while(head!=NULL)
	{
		head = head->next;
	}
	return;
}

int linkedlist::refELement(int d)
{
	node* del;  //del is pointer points to node
	del=head;   //first we make del points to where the head points

	if(del==NULL)   //means if linked list is empty
	{
		return(-1);	 //return to main

	}
	for(int i=0;i<d;i++)
	{
		if(del->next!=NULL)
		{
			del=del->next;
		}
		else
		{
			return(-1);
		}
	}
	return(del->data);
}

int linkedlist::exist(int d)
{
	node* del;  //del is pointer points to node
	del=head;   //first we make del points to where the head points

	if(del==NULL)   //means if linked list is empty
	{
		return(0);	 //return to main

	}

	if(del->data==d)	//if first element in linked list is the element that we want to delete ... or one element is what we want
	{
		return(1);
	}

	//if(del->data!=d) .... the same
	if(del->next==NULL) //if first element in linked list is not the element that we want to delete ... or one element is not what we want
	{
		return(0);
	}

	//if here more one nodes...one node points to another node ... bigger than 2 nodes .. at least 2 nodes
	while(del->next!=NULL)
	{
		if(del->next->data==d)
		{
			return(1);
		}
		//else
		del=del->next;

	}
	return(0);
}

int linkedlist::pop()
{
	node* del;  //del is pointer points to node
	del=head;   //first we make del points to where the head points

	if(this->count()<1)
	{
		return(-1);
	}
	int num = del->data;
	head=del->next; //make head points to the next to del
	return(num);
}

//void linkedlist::display(node *head)
void linkedlist::display()
{
	int n=0;						//counter for number of node
	node* current=head;			 //current is pointer points to where head point .... same as node* current=new node; current=head;

	//if linked list is empty
	if (current==NULL)
		cout<<"/";

	//if linked list has nodes
	while(current!=NULL)			//until current reach to null (last element)
	{
		cout<<current->data<<"->";  //print data
		current=current->next;	  //move to next node

	}
	cout<<endl;

}

int linkedlist::count()
{
	int n=0;						//counter for number of node
	node* current=head;			 //current is pointer points to where head point .... same as node* current=new node; current=head;
	while(current!=NULL)			//until current reach to null (last element)
	{
		n++;
		current=current->next;	  //move to next node

	}
	return(n);
}


connections input_from_file(char file_name[])
{
	int v,n;
	FILE* file = fopen (file_name, "r");
	fscanf (file, "%d", &v);
	fscanf (file, "%d", &n);
	connections con(v,n);
	for(int i=0;i<con.net;i++)
	{
		fscanf (file, "%d", &con.matrix[i][0]);
		for(int j=0;j<con.matrix[i][0];j++)
		{
			fscanf (file, "%d", &con.matrix[i][j+1]);
		}
	}
	fscanf (file, "%d", &con.limit_min);
	fscanf (file, "%d", &con.limit_max);

	int tempv=v;
	if(tempv%2==1)
	{
		tempv--;
		tempv/=2;
	}
	else
	{
		tempv/=2;
		tempv--;
	}
	con.limit_min = tempv;
	fclose (file);
	return(con);

}
int whichlist(int i,linkedlist l,linkedlist r)
{
	int list;
	if(l.exist(i)==1)
	{
		list = 0;
	}
	else if(r.exist(i)==1)
	{
		list = 1;
	}
	else
	{
		// cout<<"error1: "<<i<<" not in list"<<endl;
		// cout<<"L:"<<endl;
		// l.display();
		// cout<<"R:"<<endl;
		// r.display();
		return(-1);
	}
	return(list);
}
int calgain(int ii,linkedlist l,linkedlist r,connections con)
{
	int FS = 0;
	int TE = 0;
	// ////cout<<"node = "<<ii<<endl;
	for(int i=0;i<con.net;i++)
	{
		int samelist = 0;
		int diflist = 0;
		int nodeinnet = 0;
		// ////cout<<endl<<"net #"<<i<<endl;
		for(int j=1;j<=con.matrix[i][0];j++)
		{	
			// ////cout<<con.matrix[i][j]<<"is in "<<whichlist(con.matrix[i][j],l,r);
			if((whichlist(con.matrix[i][j],l,r)==whichlist(ii,l,r))&&(ii!=(con.matrix[i][j])))
			{
				// ////cout<<"same"<<endl;
				samelist++;
			}
			else if((whichlist(con.matrix[i][j],l,r)!=whichlist(ii,l,r))&&(ii!=(con.matrix[i][j])))
			{
				// ////cout<<"different"<<endl;
				diflist++;
			}
			else if(ii==(con.matrix[i][j]))
			{
				// ////cout<<"self"<<endl;
				nodeinnet = 1;
			}
		}
		if(nodeinnet==1)
		{
			if(samelist!=0)
			{
				// ////cout<<"FS++"<<endl;
				FS++;
			}
			if(diflist!=0)
			{
				// ////cout<<"TE++"<<endl;
				TE++;
			}
		}
	}
	// ////cout<<" TE"<<TE<<" FS"<<FS<<endl;
	return(TE-FS);
}
map partition(linkedlist o,connections con,int pass, map grid, int level)
{
	cout<<"level:"<<level<<endl;
	cout<<"O:"<<endl;
	o.display();
	linkedlist lo,ro;
	if(level==8)
	{
		int nonode = o.pop();
		// cout<<nonode<<endl;
		grid.rep[grid.x][grid.y] = nonode;
		if(o.count()!=0)
		{
			cout<<"error3"<<endl;
		}
		// grid.display();
		return(grid);
	}
	else if(o.count()==2)
	{
		lo.addElement(o.pop());
		ro.addElement(o.pop());
	}
	else
	{
		linkedlist l,r;
		linkedlist lg,rg;
		linkedlist oo = o;

		int temp;
		while(oo.count()!=0)
		{
			temp = oo.pop();
			if(temp!=-1)
			{
				l.addElement(temp);
				lo.addElement(temp);
				lg.addElement(temp);
			}
			temp = oo.pop();
			if(temp!=-1)
			{
				r.addElement(temp);
				ro.addElement(temp);
				rg.addElement(temp);
			}
		}
		// ////cout<<endl;
		// for(int i = 0;i<con.vertex;i++)
		// {
			// ////cout<<o.refELement(i)<<" gain:"<<calgain(o.refELement(i),l,r,con)<<endl;
		// }
		// ////cout<<endl;
		gain LL(0);
		gain RR(0);


		// for(int i=0;i<l.count();i++)
		// {
		// 	LL.save(l.refELement(i),calgain(l.refELement(i),l,r,con));
		// }
		// for(int i=0;i<r.count();i++)
		// {
		// 	RR.save(r.refELement(i),calgain(r.refELement(i),l,r,con));
		// }

		// ////cout<<"LL:"<<endl;
		// LL.show();
		// ////cout<<"RR:"<<endl;
		// RR.show();
		for(int p = 0;p<pass;p++)
		{
			int movefrom = 0;
			linkedlist lock;
			lock.clear();
			int gained[100] = {0};
			int numingained = 0;
			int times = 0;
			while(lock.count()<(lo.count()+ro.count()))
			{
				//cout<<endl<<endl<<"times:"<<times<<"//////////////////////////"<<endl;
				times++;
				LL.clear();
				for(int i=0;i<l.count();i++)
				{
					LL.save(l.refELement(i),calgain(l.refELement(i),lg,rg,con));/////////lg rg problem
				}
				RR.clear();
				for(int i=0;i<r.count();i++)
				{
					RR.save(r.refELement(i),calgain(r.refELement(i),lg,rg,con));////////
				}
				//cout<<"lg:"<<endl;
				// lg.display();
				//cout<<"rg:"<<endl;
				// rg.display();
				//cout<<endl;
				//cout<<"l:"<<endl;
				// l.display();
				//cout<<"r:"<<endl;
				// r.display();
				//cout<<endl;
				//cout<<"LL:"<<endl;
				// LL.show();
				//cout<<"RR:"<<endl;
				// RR.show();
				//cout<<"lock:"<<endl;
				// lock.display();
				for(int h=0;h<numingained;h++)
				{
					//cout<<gained[h]<<"  ";
				}
				//cout<<endl;
				if(LL.max>RR.max)
				{
					//cout<<"LL has higher gain";
					//cout<<"	 "<<LL.max<<"/"<<RR.max<<endl;
					movefrom = 0;
				}
				else if(LL.max<RR.max)
				{
					//cout<<"RR has higher gain";
					//cout<<"	 "<<LL.max<<"/"<<RR.max<<endl;
					movefrom = 1;
				}
				else
				{}
				// ////cout<<"a"<<endl;
				if(lg.count()<=con.limit_min)
				{
					//cout<<"l has less than min"<<"	 "<<lg.count()<<endl;
					movefrom=1;
				}
				else if(rg.count()<=con.limit_min)
				{
					//cout<<"r has less than min"<<"	 "<<rg.count()<<endl;
					movefrom=0;
				}
				// ////cout<<"b"<<endl;
				if((LL.num<=0)&&(RR.num<=0))
				{
					//cout<<"LL and RR empty"<<endl;
					break;
				}
				else if(LL.num<=0)
				{
					//cout<<"No more in LL"<<endl;
					movefrom = 1;
				}
				else if(RR.num<=0)
				{
					//cout<<"No more in RR"<<endl;
					movefrom = 0;
				}
				else
				{}
				// ////cout<<"c"<<endl;
				if(movefrom == 0)
				{
					int ogain = LL.max;
					int num = LL.bucketpop(LL.max);
					//cout<<"move "<<num<<" from l"<<endl;
					l.delElement(num);
					lock.addElement(num);
					lg.delElement(num);
					rg.addElement(num);
					if(numingained>0)
					{
						gained[numingained] = ogain+ gained[numingained-1];
					}
					else
					{
						gained[numingained] = ogain;
					}
					numingained++;
				}
				else if(movefrom == 1)
				{
					int ogain = RR.max;
					int num = RR.bucketpop(RR.max);
					//cout<<"move "<<num<<" from r"<<endl;
					r.delElement(num);
					lock.addElement(num);
					rg.delElement(num);
					lg.addElement(num);
					if(numingained>0)
					{
						gained[numingained] = ogain+ gained[numingained-1];
					}
					else
					{
						gained[numingained] = ogain;
					}
					numingained++;
				}
				// ////cout<<"d"<<endl;
			}
			//cout<<endl<<"result:"<<endl;
			//cout<<"lock:"<<endl;
			// lock.display();
			for(int h=0;h<numingained;h++)
			{
				//cout<<gained[h]<<"  ";
			}
			//cout<<endl;
			int maxgain = 0;
			int maxgainstep = -1;
			int m;
			for(m = 0;m<numingained;m++)
			{
				if(gained[m]>maxgain)
				{
					maxgain = gained[m];
					maxgainstep = m;
				}
			}
			//cout<<endl<<"maxgain: "<<maxgain<<endl;
			//cout<<endl<<"maxgainstep: "<<maxgainstep<<endl;

			for(int n = 0;n<=maxgainstep;n++)
			{
				int num = lock.pop();
			// ////cout<<"move "<<num<<endl;
				if(lo.exist(num)==1)
				{
					lo.delElement(num);
					ro.addElement(num);
			// ////cout<<"L:"<<endl;
			// lo.display();
			// ////cout<<"R:"<<endl;
			// ro.display();
				}
				else if(ro.exist(num)==1)
				{
					ro.delElement(num);
					lo.addElement(num);
			// ////cout<<"L:"<<endl;
			// lo.display();
			// ////cout<<"R:"<<endl;
			// ro.display();
				}
				else
				{
					cout<<"error2"<<endl;
				}
			// ////cout<<endl;
			}


			//cout<<"Final partition of pass #"<<p+1<<" :"<<endl;
			// cout<<"L:"<<endl;
			// lo.display();
			// cout<<"R:"<<endl;
			// ro.display();
			// cout<<endl;
			//cout<<"gain:"<<maxgain<<endl;
			//cout<<"|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
			l = copylist(lo);
			lg = copylist(lo);
			r = copylist(ro);
			rg = copylist(ro);
		}
	}
	// cout<<"Final partition :"<<endl;
	cout<<"L:"<<endl;
	lo.display();
	cout<<"R:"<<endl;
	ro.display();
	cout<<"|||||||||||||||||||||||||||||||||||||||||"<<endl;
	int cordtemp;
	if(level%2 == 0)
	{
		grid.x *=2;
		cordtemp = grid.x;
		connections lcon(con.vertex,con.net);
		connections rcon(con.vertex,con.net);
		lcon = copycon(con);
		int tempv = lo.count();
		if(tempv%2==1)
		{
			tempv--;
			tempv/=2;
		}
		else
		{
			tempv/=2;
			tempv--;
		}
		lcon.limit_min = tempv;

		rcon = copycon(con);
		tempv = ro.count();
		if(tempv%2==1)
		{
			tempv--;
			tempv/=2;
		}
		else
		{
			tempv/=2;
			tempv--;
		}
		rcon.limit_min = tempv;

		int xxx = grid.x;
		int yyy = grid.y;
		grid = partition(lo,lcon,pass, grid, level+1);
		grid.y = yyy;
		grid.x = cordtemp+1;
		grid = partition(ro,rcon,pass, grid, level+1);
	}
	else
	{
		grid.y *=2;
		cordtemp = grid.y;
		connections lcon(con.vertex,con.net);
		connections rcon(con.vertex,con.net);
		lcon = copycon(con);
		int tempv = lo.count();
		if(tempv%2==1)
		{
			tempv--;
			tempv/=2;
		}
		else
		{
			tempv/=2;
			tempv--;
		}
		lcon.limit_min = tempv;

		rcon = copycon(con);
		tempv = ro.count();
		if(tempv%2==1)
		{
			tempv--;
			tempv/=2;
		}
		else
		{
			tempv/=2;
			tempv--;
		}
		rcon.limit_min = tempv;
		
		int xxx = grid.x;
		int yyy = grid.y;
		grid = partition(lo,lcon,pass, grid, level+1);
		grid.y = cordtemp+1;
		grid.x = xxx;
		grid = partition(ro,rcon,pass, grid, level+1);
	}
	return(grid);
}
int main(int argc, char *argv[])
{

	connections con(0,0);
	con = input_from_file(argv[1]);
	//cout<<"vertex num:"<<con.vertex<<endl;

	linkedlist o;
	//cout<<"bro"<<endl;
	for(int i=0;i<con.net;i++)
	{
		for(int j = 1;j <= con.matrix[i][0];j++)
		{
			//cout<<con.matrix[i][j]<<" ";
			if(o.exist(con.matrix[i][j])==0)
			{
				o.addElement(con.matrix[i][j]);
			}
		}
		//cout<<endl;
	}

	o.display();
	map grid(0);

	grid.x = 0;
	grid.y = 0;
	int pass;
	pass = 1;

	grid = partition(o,con,pass,grid,0);
	grid.display();

    charmap cgrid(0);

    for(int t = 0;t<con.vertex;t++)
    {
    	int n = o.pop();
    	grid.mapref(n);
    	cgrid.rep[grid.x][grid.y] = '*';
    }
    queue <cord> que;
	for(int i=0;i<con.net;i++)
	{
		que = queue<cord>();
    	int fail = 0;
		grid.mapref(con.matrix[i][1]);
		cord start(grid.x,grid.y);
		grid.mapref(con.matrix[i][2]);
		cord end(grid.x,grid.y);
		// cord start(0,0);
		// cord end(10,10);
		int connected = 0;
	    charmap temp(0);
	    temp.rep[start.x][start.y]=0;
		que.push(start);
	    while(connected == 0)
	    {
			// system("cls");
			// temp.display();
			if(que.size()==0)
			{
				fail=1;
				break;
			}
	    	cord point = que.front();
	    	que.pop();
	    	for(int i = 0;i<4;i++)
	    	{
	    		cord pointpd(point.x+dx[i],point.y+dy[i]);
	    		if (pointpd.x == end.x && pointpd.y == end.y)
	    		{
	    			temp.rep[pointpd.x][pointpd.y] = temp.rep[point.x][point.y]+1;
	    			connected = 1;
	    			break;
	    		}
	    		else if(temp.rep[pointpd.x][pointpd.y]==(-1)&&cgrid.rep[pointpd.x][pointpd.y]!='*'&&pointpd.x>=0&&pointpd.x<24&&pointpd.y>=0&&pointpd.y<24)/////////////////////edge condition
	    		{
	    			temp.rep[pointpd.x][pointpd.y] = temp.rep[point.x][point.y]+1;
					que.push(pointpd);
	    		}
	    	}
	    }
	    connected = 0;
	    int direction = 0;
	    cord point = end;
	    while(connected == 0 && fail!=1)
	    {
	    	cord pointpd(point.x+dx[direction],point.y+dy[direction]);
	    	while((temp.rep[pointpd.x][pointpd.y]!=temp.rep[point.x][point.y]-1)||pointpd.x<0||pointpd.x>=24||pointpd.y<0||pointpd.y>=24)/////////////////sometimes doesn't go in just misses and continues putting down "*" also goes up to 16 sometimes 
	    	{
	    		// cout<<"b"<<endl;
	    			direction++;
		    		if(direction==4)
		    		{
		    			direction = 0;
		    		}
		    		pointpd.x = point.x+dx[direction];
		    		pointpd.y = point.y+dy[direction];
	    		// cout<<"point = ("<<point.x<<","<<point.y<<") "<<endl<<"pointpd = ("<<pointpd.x<<","<<pointpd.y<<")"<<endl;
	    	}
	    	if(pointpd.x == start.x && pointpd.y == start.y)
	    	{
	    		break;
	    	}
	    	else
	    	{
	    		cgrid.rep[pointpd.x][pointpd.y] = '*';
	    		point = pointpd;
	    	}

			// system("cls");
			// cgrid.display();
	    }
	    if(fail==1)
	    {
	    	cout<<"node "<<grid.rep[start.x][start.y]<<" can't connect to "<<"node "<<grid.rep[end.x][end.y]<<endl;
	    }
	}

	cout<<"-------------------------------------------------------------------------"<<endl;
	for(int i=0;i<24;i++)
	{
        cout<<"|";
		for(int j=0;j<24;j++)
		{
			if(grid.rep[i][j]==(-1)&&(i<16)&&(j<16))
			{
				if(cgrid.rep[i][j]=='*')
				{
					cout<<" "<<cgrid.rep[i][j]<<"|";
				}
				else
				{
					cout<<cgrid.rep[i][j]<<"|";
				}
			}
			else if((i>=16)||(j>=16))
			{
				if(cgrid.rep[i][j]=='*')
				{
					cout<<" "<<cgrid.rep[i][j]<<"|";
				}
				else
				{
					cout<<cgrid.rep[i][j]<<"|";
				}
			}
			else
			{
				if(grid.rep[i][j]<10)
				{
					cout<<" ";
				}
				cout<<grid.rep[i][j]<<"|";
			}
		}
		cout<<endl;
		cout<<"-------------------------------------------------------------------------"<<endl;
	}
	cout<<endl;


	return 0;
}

// added

// added
// exist()
// need to write
// gain[] exist