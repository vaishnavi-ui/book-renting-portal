/*WELCOME TO OUR DS PROJECT
This is a book renting portal where users can read books on rent
The Flow of the Code is:
Header Section
Declaration of global variables and structures
class Graph
class cartMenu
displayCustomers()
displayBooks()
displayGraph()
loginAccount()
showBooksmenu()
DFS()
admin()
main()
For a simplified version of our project flow, please refer our detailed reports
Creaters:
Riya Tendulkar and Vaishnavi Rathod*/

	//Header Section
	#include<iostream>
	#include<cmath>
	#include<conio.h>
	#include <stdlib.h>
	#include <string.h>
	#include<iostream>
	#include<cstring>
	#include<stack>
	#include<queue>
	using namespace std;


	//ProtoType of the functions
	void loginAccount(void);
	void showBooksMenu(void);
	void displayBooks(void);
	void displayCustomers(void);
	void showBooksMenu(void);


	//Declaring the structures used in the code
	//This structure is used for printing the shortest path from user to seller using linked list

	struct path{
		string nextVertex;
		struct path *next;
	};

	//This structure is used for the cart class using linked list

	struct cart{
		string title;
		string customerId;
		string bookId;
		int price;
		string genre;
		struct cart *next;

	};

	//Creating databses

	/*Adding customers to the database
	Now here we have a matrix with rows=10 and coloumns=7
	Here number of rows is the number of customers and number of coloumns is the criterias for database, they are as follows:
	0->Customer Id
	1->Name
	2->Phone Number
	3->Username
	4->Password
	5->Address
	6->Locality
	*/

	string customers[10][7]={
	{"1","Diya","4653258765","diyaarora123","diyaroxx","4,Orchard Street","Kandivali"},
	{"2","Manoj","1234567890","manishere5","manojissad","12,Thakur Complex","Malad"},
	{"3","Sunny","7587465856","sunisfun","sunyybunny","20,Sunrise Building","Thane"},
	{"4","Gargi","3569687253","chefgargi","ilovevaish","604,Vasant Vihar","Powai"},
	{"5","Pranay","56748937520","kingtopper","hatemeplease","41,Riddhima Circle","Thane"},
	{"6","Monica","3434546777","cleanfreak","bestcookever","19,Pride Residency","Worli"},
	{"7","Harry","1029384756","guspowered","mypassword9","40,Top Apartments","Mulund"},
	{"8","Shivam","2346507876","ohmyfriend","shivbhakt","12,Banaras Galli","Vikhroli"},
	{"9","Sheldon","11199230577","sheldor1","notmyspot","4,Caltech Estate","Ghatkopar"},
	{"10","Jasmine","56484848454","jasmine3","iamaflower","8,Jumping Street","Dadar"}};


	/*Adding books to the database
	Now here we have a matrix with rows=15 and coloumns=5
	Here number of rows is the number of books and number of coloumns is the criterias for database, they are as follows:
	0->Customer Id of the customer who is selling the book
	1->Book Code
	2->Title of the book
	3->Genre
	4->Price
	*/

	string books[20][5]={
	{"5 ","245","The Murder On The Orient Express     ","Crime","299"},
	{"6 ","160","Much Ado About Nothing               ","Drama","159"},
	{"2 ","999","Harry Potter And Goblet Of Fire      ","Fantasy","345"},
	{"6 ","307","The Mysterious Affair At Styles      ","Crime","199"},
	{"8 ","419","Around The World In Eighty Days      ","Action","139"},
	{"7 ","118","The Haunting Of The HillHouse        ","Horror","449"},
	{"1 ","652","How To Train Your Dragon             ","Fantasy","320"},
	{"3 ","212","The Adventures Of Tom Sawyer         ","Drama","599"},
	{"4 ","456","Strange Case Of Missing Cards        ","Horror","259"},
	{"1 ","111","The Cards On The Murder Table        ","Crime","100"},
	{"1 ","529","Diary Of Madam Annie Scott           ","Fantasy","799"},
	{"9 ","379","Buddenbrooks:The Declined Call       ","Drama","320"},
	{"2 ","291","Legend Of The Sleepyhollow           ","Horror","699"},
	{"8 ","535","The Girl With The Dragon Tattoo      ","Action","199"},
	{"9 ","700","Harry Potter And Cursed Child        ","Crime","799"},
	{"5 ","167","Harry Potter And Philosopher's Stone ","Fantasy","699"},
	{"7 ","100","Harry Potter And Half Blood Prince   ","Horror","399"},
	{"9 ","200","Harry Potter And Story Continues     ","Fantasy","999"},
	{"4 ","430","How Does Netlix Make So Much Money   ","Drama ","469"},
	{"6 ","969","The Sun Outshines All Living Creatures","Action","799"}};


	/*Creating databse of cities which are used in the code
	We have 10 localities in our database: Kandivali,Malad,Thane,Powai,Vile
	Parle,Worli,Mulund,Vikhroli,Ghatkopar,Dadar*/

	string cities[10]={"Kandivali","Malad","Thane","Powai","Kurla","Worli","Mulund","Vikhroli","Ghatkopar","Dadar"};


	/*Storing the adjacency matrix for the graph
	No Of Rows=No of Columns= No of cities
	This matrix stores the distances between the places
	It a weighted graph*/

	int graphDatabase[10][10]={
	{0,8,5,3,4,2147483647,6,2,7,10},
	{8,0,7,5,6,4,1,3,2147483647,7},
	{7,3,0,8,2,8,2,9,8,2147483647},
	{3,2147483647,8,0,2,2,4,1,6,5},
	{2,3,8,10,0,2147483647,9,4,2,7},
	{10,4,5,2,6,0,2147483647,7,3,8},
	{1,1,3,4,2147483647,5,0,9,1,9},
	{9,3,4,6,5,4,9,0,2147483647,6},
	{2,1,2,1,2147483647,10,3,5,0,4},
	{10,2147483647,6,1,7,4,2,3,6,0}
		};



	//We are done with creating all databases


	//Now we will declare all the global variables
	//Note that the variable runLoop is for printing lines in the entire project for GUI
	int NoOfPlaces=10;               				   //Stores the number of cities/places
	int noOfCustomers=10;            				 //Stores the number of customers in the database
	int noOfBooks=20;               				//Stores the number of books in the databse
	struct cart *head=NULL;                        //head pointer for the linked list //ADMIN lets try to add this in the linked list cart
	string name,address,locality,userid,number;   //To store the details of the buyer
	string sellerLocality;                		//stores the locality of the seller to be later implemented in admin part


	/*We have 2 main classes in our project:Graph and cartMenu
	Graph is the class implementing Dijkstra's Algorithm
	cartMenu is the class which is the main implementation of the linked list and has all the funtions of the linked list
	*/



	//Class Graph
	class Graph
	{
			/*This is the Graph class which is the implementation of the Dijkstra's algorith
			It calculates the shortest distance and path between the seller and buyer.
			The functions of of this class are:
			setGraph()
			BFS()
			dijkstra() */

			public:
			friend void getDistance(string s, string e); //We are declaring the function getDistance from class Graph to make it as a friend function

			//This function is to set a user defined Graph, that is, if the admin wants to have another graph and not the one whichis predefined
			void setGraph()
			{
				int noOfPlaces1; //Stores number of nodes
				char choice;  //stores choice for BFS
				int m,i,j; //Variables used in the 'for' loops
				string source,dest;//to imput source and destination
				int counterSource=0,counterDest=0;//counters to check if source and destination exist
			
				//Inputing the number of nodes
				cout<<"Enter the number of places(nodes) for the graph: ";
				cin>>noOfPlaces1;
				

				//Declaring the arrays
			
				int graphByUser[10][10];
				string places[10];

				//Inputing the names of the nodes
				cout<<"Enter the places: "<<endl;
				for(m=0;m<noOfPlaces1;m++)
				{
					cout<<"PLACE "<<m<<" : ";
					cin>>places[m];
				}

				//Inputing the distances(matrix)

				cout<<"For no edge enter 0(it will be converted to infinity)"<<endl;
				cout<<"Enter the matrix: "<<endl;

				for(i=0;i<noOfPlaces1;i++)
			{
			    for(j=0;j<noOfPlaces1;j++)
				{
					cout<<"Enter value at row "<<i<<" and coloumn "<<j<<" :";
					cin>>graphByUser[i][j];
					if(graphByUser[i][j]==0&&i!=j)
					graphByUser[i][j]=2147483647;   //For the places where there is no path, the matrix value will be set as infinity
				}
			}
				
				
				cout<<endl<<"Here is the graph you just entered: "<<endl<<endl;
				for(int i=0;i<noOfPlaces1;i++)
				{
					for(int j=0;j<noOfPlaces1;j++)
					{
						if(graphByUser[i][j]==2147483647)
							cout<<"  0  ";
						else
							cout<<"  "<<graphByUser[i][j]<<"  ";
					}
					cout<<endl;
				}
				
				
			
					
					cout<<endl;
					cout<<"NOTE:The source and destination you enter must be present in the graph"<<endl;
					cout<<"Enter source: ";
					cin>>source;
					for(int check=0;check<noOfPlaces1;check++)
					{
						if(places[check]==source)
						counterSource++;
					}
					
					if(counterSource==0)
						cout<<"SOURCE DOES NOT EXIST!"<<endl;
					else
					{
						cout<<"Enter destination: ";
						cin>>dest;
						for(int check=0;check<noOfPlaces1;check++)
						{
							if(places[check]==dest)
							counterDest++;
						}
						if(counterDest==0)
							cout<<"DESTINATION DOES NOT EXIST!"<<endl;
						else	
							dijkstra(graphByUser,places,source,dest,noOfPlaces1); //Calling Dijkstra
					}

				
				
			}//function setGraph() ends here


			

			//Function to calculate the shortest distance and path
			void dijkstra(int graph[10][10],string places[10],string sourceParameter,string endParameter,int size)
			{
				//declaration of variables
				int i,j,k,c,r;//Variables used in the 'for' loops
				int vertex,n,small,source,end,counter;
				int dij[size][3];//defining the dijkstra's matrix
				path *head=NULL;//traversing the path linked list


				//Finding the index of the source and destination
				for(c=0;c<size;c++)
				{
					if(places[c]==sourceParameter)
						source=c;
					if(places[c]==endParameter)
						end=c;
				}

				//Setting the initial value of the dijkstra's matrix,i.e, visited=0,distance=infinity,parent=0
				for(i=0;i<size;i++)
				{
					dij[i][1]=2147483647;
					dij[i][0]=0;
					dij[i][2]=0;
				}
					//setting the distance of the source node as 0
					dij[source][1]=0;
				for(i=0;i<size;i++)
				{
					//Finding the smallest distance
					small=1000,counter;
					for(r=0;r<size;r++)
					{
						if(dij[r][0]==0) //does not consider the nodes which are already visited
						{
							if(dij[r][1]<=small)
							{
								small=dij[r][1];
								counter=r;
							}
						}
					}
					//Setting the node with the smallest distance as the vertex
					vertex=counter;

					//Making the visited of the vertex as 1
					dij[vertex][0]=1;

					//The following code snippet performs that part of the algorithm which compares the distances and replaces accordingly
					for(j=0;j<size;j++)
					{
						if(dij[j][0]==0) //Does not consider the nodes which are already visited
						{
						//Compares the values: goes inside the 'if' only if new value is smaller than the original value and the path exists
							if(graph[vertex][j]+dij[vertex][1]<dij[j][1]&&graph[vertex][j]!=2147483647&&j!=vertex)
							{
								dij[j][1]=graph[vertex][j]+dij[vertex][1]; //sets the new value
								dij[j][2]=vertex; //sets the parent
							}
						}
					}
				} //the algorithm for dijkstra's ends here

				//The following part is to print the shortest path and distance

				//Prints the value at the 'distance' coloumn of the matrix

				cout<<"Distance       : "<<dij[end][1]<<" kms"<<endl;
				//To print the path, we use a single linked list

				if(dij[end][1]==0)
					cout<<"You are at your destination! You do not need to travel at all!"<<endl;
				else
				{
					cout<<"Shortest Path  : ";
					k=end;
					//The following code stores the path in the linked list
					while(k!=source)
					{
						path *newNode=new path;
						newNode->nextVertex=places[k];
						newNode->next=head;
						head=newNode;
						k=dij[k][2];
					}//insert beg

					/*As we need to include the source in our path, we can use the following code snippet instead of individually printing the source
					path *newNode=new path;
					newNode->data=nodes[source];
					newNode->next=head;
					head=newNode;
					*/

					//Printng the source
					cout<<places[source]<<"-->";
					//Printing the path(i.e. the linked list)
					path *temp=head;
					while(temp!=NULL)
					{
						cout<<temp->nextVertex;
						cout<<"-->";
						temp=temp->next;
					}
					cout<<"*";
				}
			}//dijkstra() ends here

	};//class Graph ends here

	//Class cartMenu
	class cartMenu
	{
		/*The functions of the class cartMenu are:
		countNodes()
		add()
		deleteEntire()
		deleteItem()
		deleteOnBookid()
		deletDuplicate()
		display()
		totalAmount()
		sortAscending()
		sortDescending
		connectCustomer()
		getDistance()
		menu()*/

		public:

		friend void showBooksMenu();//We are declaring the function showBooksMenu() as a friend of this class so this class is accessible there

		int countNodes()
		{
			//This function will traverse till the end of the linked list and will count the total number of nodes present
			int count=0; //count variable counts the number of nodes (counter variable)
			cart *temp=head;
			while(temp!=NULL)
			{
				count++;
				temp=temp->next;
			}
			return count;
		}//Function countNodes ends here


		//Function to add an item to the cart
		void add(string cCode,string bId,string bTitle,string bGenre,int amt)
		{
			//This function adds a new node to the list like adding an element to the cart
			//The parameters are added to the struct upon creating a new node
			cart *newNode= new cart; //Creating a new node
			newNode->price=amt;
			newNode->customerId=cCode;
			newNode->bookId=bId;
			newNode->genre=bGenre;
			newNode->title=bTitle;
			newNode->next=head;
			head=newNode;
		}//Function add ends here

		//Function to delete the entire cart
		void deleteEntire()
		{
		cart *temp;
			if(head==NULL)
				cout<<"Your cart is already empty!"<<endl;
			else
			{
				while(head!=NULL)
				{
					temp=head;
					head=head->next;
					delete temp;
				}
			cout<<"Cart Deleted successfully!"<<endl;
			}
		}//deleteEntire ends here


		//Function to remove an item from the cart based on the serial number
		void deleteItem(int position)
			{
			/*This function deletes the item/node from the cart on the serial number
			The user will enter the serial number of the item which will act as the position of the node*/

			int check=1; //counter to find the position of the node
			cart *current=head; //pointer at the current node
			cart *pre=head;//pointer to track the previous node of the current

			if(head==NULL)
			cout<<endl<<"The cart is empty! You can not delete any items.";

			else if(position==1)
			{
				for(int runLoop=0;runLoop<=100;runLoop++)
				{ cout<<"-";}cout<<endl;

				cout<<"Item Deleted Successfully!!"<<endl;
				cout<<"You just deleted: "<<endl;
				cout<<"Product Name: "<<head->title<<endl;
				cout<<"Product Code: "<<head->bookId<<endl;

				for(int runLoop=0;runLoop<=100;runLoop++)
				{ cout<<"-";}

				head=head->next;
			}
			else
			{
				if(countNodes()>=position) //if to check if the position is within the limits
				{
					check=1;
					while(check!=position) //Finds the node to be deleted from the position

					{
						pre=current;
						current=current->next;
						check++;
					}
					//cout<<current->bookId<<endl;
					//Displaying the details of the item before deleting it
					for(int runLoop=0;runLoop<=100;runLoop++)
					{ cout<<"-";}

					cout<<"Item Deleted Successfully!!"<<endl;
					cout<<"You just deleted: "<<endl;
					cout<<"Product Name: "<<current->title<<endl;
					cout<<"Product Code: "<<current->bookId<<endl;

					for(int runLoop=0;runLoop<=100;runLoop++)
					{ cout<<"-";}

					//Deleting the node from the memory
					pre->next=current->next;
					current=NULL;
					delete current;
					//Linking the nodes again

				}
				else if(countNodes()<position)
					cout<<"The Number does not exist in the cart."<<endl;
			}
		}//Function deleteItem ends here


		//Function to delete the item based on the book idea
		void deleteOnBookid(string data)
		{
			cart *current=head;
			int counter=0;//counter to check if the bookId is actually present in the cart
			cart *pre=head; //tracks the previous node

			if(head==NULL)
			cout<<"Empty Cart Please Try Again!"<<endl;

			else if(head->bookId==data)
			{

				for(int runLoop=0;runLoop<=100;runLoop++)
				{ cout<<"-";}cout<<endl;

				cout<<"Item Deleted Successfully!!"<<endl;
				cout<<"You just deleted: "<<endl;
				cout<<"Product Name: "<<head->title<<endl;
				cout<<"Product Code: "<<head->bookId<<endl;

				head=head->next;

				for(int runLoop=0;runLoop<=100;runLoop++){ cout<<"-";}
			}
			else{
				while(current!=NULL)
				{
					if(current->bookId==data)
					{
						counter++; //counter increments if the bookId is in the cart
						break;
					}
					else
					{
						//Traversing the list

						pre=current;
						current=current->next;
					}
				}
				if(counter==1)
				{
					//Deleting the item
					for(int runLoop=0;runLoop<=100;runLoop++)	{ cout<<"-";}cout<<endl;

					cout<<"Item Deleted Successfully!!"<<endl;
					cout<<"You just deleted: "<<endl;
					cout<<"Product Name: "<<current->title<<endl;
					cout<<"Product Code: "<<current->bookId<<endl;

					for(int runLoop=0;runLoop<=100;runLoop++)	{ cout<<"-";}

					pre->next=current->next;
					current=NULL;
					delete current;

				}
				else if(counter==0)
					cout<<"The BookId you are trying to delete is not in the cart!"<<endl;
			}
		}//deleteOnBookId ends here

		//Function to delete duplicates in the list
		void deleteDuplicate()
		{
			cart *temp=head;cart *temp2;
			cart *temp1;
			if(head==NULL)
				cout<<"Empty Cart! No items to check for duplicates!"<<endl;

			else
			{
				while(temp!=NULL)//traversing through the entire list to check duplicates for each element
				{
					temp1=temp->next;
					while(temp1!=NULL)//traversing through the entire list to check duplicates of temp
					{
						if(temp->bookId==temp1->bookId)//checking for duplicates
						{ //deleting if duplicate found
							temp2=temp1;
							temp->next=temp1->next;
							temp2=NULL;
							delete temp2;
						}
						temp1=temp1->next;
					}
					temp=temp->next;
				}
			}
		}//deletDuplicates() ends here

		//This function is to display the items of the cart

		void display()
		{
			int serialNo=0;//Counter variable to print serial number
			cart *temp=head;

			for(int runLoop=0;runLoop<=100;runLoop++){ cout<<"~";}
            
            cout<<endl;
            
			cout<<endl<<"\t\t HI THERE! WELCOME TO YOUR CART!"<<endl;

			for(int runLoop=0;runLoop<=100;runLoop++){ cout<<"~";}

			cout<<endl<<"Here are the items of your cart: "<<endl;

			if(head==NULL)
				cout<<"OOPS! Your cart is empty!"<<endl;

			else
			{
				cout<<"NO\tBOOKCODE\tBOOK NAME\t\t\tGENRE\tPRICE\t"<<endl;
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}
				cout<<endl;

				while(temp!=NULL)
				{
					serialNo++;
					cout<<serialNo<<")\t"<<temp->bookId<<" \t "<<temp->title<<" \t"<<temp->genre<<" \t"<<temp->price<<endl;
					temp=temp->next;
				}
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;

				cout<<"Details of your cart: "<<endl;
				cout<<"Total Items : "<<countNodes()<<endl;
				cout<<"Total Amount : Rs."<<totalAmount()<<endl;

				for(int i=0;i<100;i++){cout<<"-";}
				
				cout<<endl;
			}
		}//Function Display ends here


		//Function to calculate the total amount of the cart
		int totalAmount()
		{
			int total=0;
			cart *temp=head;
			while(temp!=NULL)//traversing the entire list
			{
				total+=temp->price;//adding the amount
				temp=temp->next;
			}
			return total;
		}//Function total amount ends here


		//Function to sort the cart in ascending order
		void sortAscending()
        {
                if(head==NULL)
                	cout<<"EMPTY CART!"<<endl;
                	
				else
				{
					deleteDuplicate();
					  cart* curr = head;
				    int count = 0;
	
				    for(int i=countNodes();i>1;i--)
				    {
				        cart *temp, *swap1;
				        swap1 = head;
				        for(int j=0;j<countNodes()-1;j++)
				        {
				            if(swap1->price>swap1->next->price)
				            {
				                cart *swap2 = swap1->next;
				                swap1->next = swap2->next;
				                swap2->next = swap1;
				                if(swap1 == head)
				                {
				                    head = swap2;
				                    swap1 = swap2;
				                }
				                else
				                {
				                    swap1 = swap2;
				                    temp->next = swap2;
				                }
				            }
				            temp = swap1;
				            swap1 = swap1->next;
				        }
				    }
	            cout<<"The items in cart in ascending order of prices are:"<<endl;
				display();
			}
		} //Sort Function for ascending ends here

		void sortDescending()
        {
        	if(head==NULL)
        		cout<<"EMPTY CART!"<<endl;
        	else
			{
				deleteDuplicate();
				
				cart* curr = head;
			    int count = 0;
	
			    for(int i=countNodes();i>1;i--)
			    {
			        cart *temp, *swap1;
			        swap1 = head;
			        for(int j=0;j<countNodes()-1;j++)
			        {
			            if(swap1->price<swap1->next->price)
			            {
			                cart *swap2 = swap1->next;
			                swap1->next = swap2->next;
			                swap2->next = swap1;
			                if(swap1 == head)
			                {
			                    head = swap2;
			                    swap1 = swap2;
			                }
			                else
			                {
			                    swap1 = swap2;
			                    temp->next = swap2;
			                }
			            }
			            temp = swap1;
			            swap1 = swap1->next;
			        }
			    }
			    cout<<"The items in cart in descending order of prices are:"<<endl;
			    display();
		    }
	}//sortFunction for Descending ends here


		//This function connects the book to its seller and displays the details of the customer selling the book

		void connectCustomer()
		{
			int counter=0;
			int i,j;//'for' loops
			int seller; string buyer; //storing buyer and seller
			cout<<endl<<endl<<endl;
			for(int runLoop=0;runLoop<=100;runLoop++){cout<<"~";}cout<<endl;
			for(int runLoop=0;runLoop<=100;runLoop++){cout<<"~";}cout<<endl;
			system("CLS");
			cout<<"\tFINAL BILL"<<endl;

			for(int runLoop=0;runLoop<=100;runLoop++){cout<<"~";}cout<<endl;

			cout<<"Welcome to the check out counter!"<<endl;
			cout<<"Now we will connect you to your user from whom you want to buy the book!"<<endl;

			for(int runLoop=0;runLoop<=100;runLoop++){cout<<"-";}cout<<endl;

			//Prints details of the cutomer
			cout<<"User Name    : "<<name<<endl;
			cout<<"User Number  : "<<number<<endl;
			cout<<"User Address : "<<address<<endl;
			cout<<"User Locality: "<<locality<<endl;
			cout<<endl;
			for(int runLoop=0;runLoop<=100;runLoop++){cout<<"-";}cout<<endl;

			//Prints details of the books
			cout<<"\tBOOK AND SELLER DETAILS"<<endl<<endl;
			cart *temp2=head;

			while(temp2!=NULL)//Traversing the linked list for the cart
			{
				counter++; seller=0;
				cout<<endl<<"BOOK "<<counter<<": "<<endl;
				for(int infinite=0;infinite<1000000000;infinite++);
				for(int runLoop=0;runLoop<=30;runLoop++){cout<<"-";}cout<<endl;

				cout<<"Title          : "<<temp2->title<<endl;
				cout<<"Book Id        : "<<temp2->bookId<<endl;
				cout<<"Genre          : "<<temp2->genre<<endl;
				cout<<"Price          : Rs. "<<temp2->price<<endl;

				buyer=locality;
				//The Following code snippet is to convert the string value of the customer to integer
				for(int j=0;j<1;j++)
				{
					char c=temp2->customerId[j]; //customerId the member of the structure cart
					int n=c-48;
					seller=seller*10+n;
				}
				seller=seller-1;

				//Printing the details of the seller

				cout<<"Name of seller : "<<customers[seller][1]<<endl;
				cout<<"Phone Number   : "<<customers[seller][2]<<endl;
				cout<<"Address        : "<<customers[seller][5]<<endl;
				cout<<"Locality       : "<<customers[seller][6]<<endl;
				sellerLocality=customers[seller][6];
				//calling getDistance to display the distance and the shortest path between the seller and the buyer
				getDistance(buyer,customers[seller][6]);
				temp2=temp2->next;
				cout<<endl;

			}
		counter=0;
		cout<<endl<<"~~~~~~~~~~~"<<endl;
		cout<<"TOTAL AMOUNT YOU WILL HAVE TO PAY: "<<totalAmount()<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";} cout<<endl;

		}//connectCustomerEnds here

		//function to call dijkstra and get the distance
		void getDistance(string buy,string sell)
		{
			Graph graphObject; //Creating an object of the graph class
			graphObject.dijkstra(graphDatabase,cities,buy,sell,NoOfPlaces);
		}//function getDistance() ends here

		//Menu of the cart
		void menu()
		{
			//This functions calls all the other functions in the class according to the menu

			int choice,value;
			string bId;

			cartMenu c; //Creating object for the class cart
			
			if(countNodes()==0)
            {
				cout<<"Looks like you have no books to buy!"<<endl;
				return;
			}	
			
			else
			{
				c.display();
					
				cout<<endl;
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
	            
				cout<<endl<<"Welcome to your CART! "<<endl;
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
			
				//Printing the menu
				
				cout<<" 1)Delete item using serial number"<<endl;
				cout<<" 2)Sort items from lowest to highest(with respect to price)"<<endl;
				cout<<" 3)Sort items from highest to lowest(with respect to price)"<<endl;
				cout<<" 4)Display cart"<<endl;
				cout<<" 5)Display Total Amount and Number of items in the cart"<<endl;
				cout<<" 6)Delete book by book Id"<<endl;
				cout<<" 7)Delete entire cart"<<endl;
				cout<<" 8)Accidentally added double items?Delete Duplicates from the cart"<<endl;
				cout<<" 9)Proceed to check out counter"<<endl;
				cout<<"10)Exit from portal"<<endl;
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}
				
				for(;;)
				{
					cout<<endl<<endl<<"ENTER YOUR CHOICE FROM THE ABOVE MENU: ";
					cin>>choice;
					cout<<endl;
					if(choice==9)
					{
						c.connectCustomer();
						cout<<endl;
						break;
					}
	
					else 
					{
						switch(choice)
						{
							case 1:
								cout<<"Enter the Sr. No. of the item which you want to delete: ";
								cin>>value;
								c.deleteItem(value);
								cout<<endl;
								break;
	
							case 2:
								c.sortAscending();
								cout<<endl;
								break;
	
							case 3:
								c.sortDescending();
								cout<<endl;
								break;
	
							case 4:
								c.display();
								cout<<endl;
								break;
	
							case 5:
								if(head==NULL)
								cout<<"Looks like your cart is Empty!"<<endl;
								cout<<endl<<"---------------------------------"<<endl;
								cout<<"Details of your cart: "<<endl;
								cout<<"Total Items : "<<c.countNodes()<<endl;
								cout<<"Total Amount : Rs."<<c.totalAmount()<<endl;
								cout<<"---------------------------------"<<endl;
								break;
	
							case 6:
								cout<<"Enter the book ID of the item you wish to delete: ";
								cin>>bId;
								c.deleteDuplicate();
								deleteOnBookid(bId);
								break;
	
							case 7:
								c.deleteEntire();
								cout<<endl;
								break;
	
							case 8:
								c.deleteDuplicate();
								c.display();
								break;
							
							case 10:
								cout<<endl;
								return;
								break;
	
							default:
								cout<<"OOPS! Wrong Option! Please try again!";
								break;
						}
	
					}
					
	              }
            }
		}//menu() function ends here

	}; //Class cartMenu ends here

	//Now we have all the normal functions
	/*The Normal Functions are as follows:
	displayCustomers()
	displayBooks()
	displayGraph()
	loginAccount()
	showBooksmenu()
	DFS()
	admin()
	main()
	*/


	//This function is to display the customer database
	void displayCustomers()
	{ //This function is to display the customer database
		int i,j; //Variables for the 'for' loop

		cout<<"The database is: "<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;
		cout<<"ID\tNAME\tNUMBER\t\tUSERNAME\tPASSWORD\tADDRESS\t\t\tLOCALTIY\t"<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;

		for(i=0;i<10;i++)
		{
			for(j=0;j<7;j++)
			{
				cout<<customers[i][j]<<"\t";
			}
				cout<<endl;
		}
	}//Display Customers ends here


	//This function is to display the books database
	void displayBooks()
	{
		int i,j; //Variables for the 'for' loop
		cout<<"The database is: "<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;
		cout<<"NO\tBOOKCODE\tBOOK NAME\t\t\tGENRE\tPRICE\t"<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;

		for(i=0;i<20;i++)
		{
			for(j=0;j<5;j++)
			{
				cout<<books[i][j]<<"\t";
			}
			cout<<endl;
		}
	}//displayBooks ends here


	//This function is to print the adjacency matrix of the graph

	void displayGraph()
	{
		int i,j;
		cout<<"The cities in our graph are: "<<endl;
		for(i=0;i<NoOfPlaces;i++)
		{
			cout<<i+1<<". "<<cities[i]<<endl;
		}
		cout<<endl;
		cout<<"For the simplicity of viewing the graph,infinity is displayed as '-1'!"<<endl;
		cout<<"The adjacency matrix of graph is as follows: "<<endl;
		for(i=0;i<NoOfPlaces;i++)
		{
			for(j=0;j<NoOfPlaces;j++)
			{
				if(graphDatabase[i][j]==2147483647)
					cout<<"-1   ";
				else
					cout<<" "<<graphDatabase[i][j]<<"   ";
			}
			cout<<endl;
		}
	}//displayGraph() ends here



	//In this function we check if the user is already a customer, if not then we take his details
	void loginAccount()
		{
		string username,password;
		int counter=0;
		string loginUser; //Counter to check if the user is registered or not
		bool flag;
		int choice;
		int counter1=0,counter2=0;
		flag=false;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		cout<<"\t\t\t\tPICK-A-BOOK"<<endl;
		cout<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		cout<<endl<<"Saw that book in crossword and wanted to buy it, but the price tag seemed too heavy for you? "<<endl<<"Want to read ALOT but less pocket money?"<<endl;
		
		cout<<"THEN YOU ARE AT THE RIGHT PLACE!!"<<endl<<"PICK-A-BOOK Renting Portal will help you rent MANY books from book-lovers like you at a very low price!!!!"<<endl;
		
		cout<<"Pick a book-Add it to your cart-Meet your seller and rent the book! It's that easy!"<<endl;
		
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		
		cout<<endl<<"PLEASE NOTE: AT PICK-A-BOOK WE DO NOT PROVIDE DELIVERY SERVICE, YOU NEED TO MEET THE SELLER YOUR SELF."<<endl<<"WE ARE JUST A MEDIUM CONNECTING YOU WITH THE SELLER!"<<endl;
		
		cout<<endl<<"FOR YOUR CONVENIENCE WE WILL PROVIDE YOU WITH THE DISTANCE,PATH AND CONTACT NUMBER, WHICH YOU WILL HAVE TO TAKE TO REACH YOUR USER!"<<endl;
		
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		cout<<endl<<"\tHello dear user,Welcome to * PICK-A-BOOK * Book Renting Portal"<<endl;
		
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		
		cout<<"You can rent some really amazing books here from us and enjoy the bliss of reading in a very cost efficient way!"<<endl;
		
		cout<<"We are open now and at your service!!!!"<<endl;
		
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;

		do
		{
			
			cout<<endl<<"Are you a registered user?(enter y or n only): ";
			cin>>loginUser;
			if(loginUser=="y"||loginUser=="Y")
			{
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
				do
				{
					cout<<"HELLO USER!Enter your username and password to login to your account"<<endl;
					for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
					cout<<"Username:";
					cin>>username;
					//comparing this username with database
	
					for(int i=0;i<10;i++)
					{
						if(username==customers[i][3])
						{
							cout<<"Password:";
							cin>>password;
							//compare with this username in the database,both should match(username and password to serial no)
							if(password==customers[i][4])
							{
								cout<<endl<<"You were successful in logging in!"<<endl;
								flag=true;
								name=customers[i][1];
								address=customers[i][5];
								locality=customers[i][6];
								number=customers[i][2];
								userid=customers[i][0];
							}
						}
					}
					if(flag==false)
					{
						cout<<"Invalid username or password!Please re-enter!"<<endl;
						counter++; //after 5 failed attempts to login,the system will stop asking
					}
	
					if(counter==5)
						break;
				}while(flag==false);
			}
			else if(loginUser=="n"||loginUser=="N")
			{
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
				cout<<"Hey There! New user!Welcome to PICK-A-BOOK"<<endl;
				for(int runLoop=0;runLoop<120;runLoop++){cout<<"~";}
				cout<<endl;
				cout<<"Enter the following sign up details to create account"<<endl;
				cout<<"Name:";
				cin>>name;
				for(;;)
				{
					counter1=0;
					counter2=0;
					cout<<"Phone Number(10 digits only):";
					cin>>number;
					if(number.length()!=10)
		            {
						cout<<"Digits must be 10! Incorrect Input!"<<endl;
						counter1++;
					}
		            else
					{
						for(int run=0;run<10;run++)
		           		{
			           		if(number[run]<48||number[run]>57)
			           		{
								counter2++;
							}
				   		}
				   		if(counter2>0)
				   		{
							   	cout<<"NOT A NUMBER!Enter only digits!"<<endl;
							   	counter1++;
						}
					}
					if(counter1==0)
						break;
	           
				}
				cout<<"Address:";
				cin>>address;
	            for(;;){
				cout<<"Locality(Please Enter from the following ONLY(case sensitive): Kandivali,Malad,Thane,Powai,Kurla,Worli,Mulund,Vikhroli,Ghatkopar,Dadar):";
				cin>>locality;
				if(locality=="Kandivali"||locality=="Malad"||locality=="Thane"||locality=="Powai"||locality=="Kurla"||locality=="Worli"||locality=="Mulund"||locality=="Vikhroli"||locality=="Ghatkopar"||locality=="Dadar")
	            break;
	            }
			}
		}while(!(loginUser=="y"||loginUser=="Y"||loginUser=="n"||loginUser=="N"));
		if(counter==5)
		{
			cout<<endl;for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
			cout<<"You have entered the incorrect username/password 5 times. We can not let you proceed further!"<<endl;
			cout<<endl;for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
			return;
		}
		
		else
		{
			for(int runLoop=0;runLoop<=1000000000;runLoop++);
			system("CLS");
			showBooksMenu();
		}
		
		
		
	} //login account ends here

	void showBooksMenu()
	{
		int i,j; //'for' loop
		int counterOfBooks=0,k,amt=0,counter=0,id=0;
		string choiceOfGenre,addToCart;
		cartMenu cobj; string choice;
		cart *temp2; char c;

		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;
		cout<<"\t\tWELCOME USER! BUY A BOOK!"<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"~";}cout<<endl;

		do
		{
			addToCart="";amt=0;
			cout<<endl<<"Which Genre of books do you want buy?We have the following genres: Crime,Horror,Fantasy,Drama,Action."<<endl;
			cout<<endl<<"Enter the genre(Make sure all the entries match the ones shown above(This is a case sensitivecode)!): ";
			cin>>choiceOfGenre;
			for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;
			
			//"if" checks if the genre is actually present in the databse
			if(choiceOfGenre=="Crime"||choiceOfGenre=="Drama"||choiceOfGenre=="Fantasy"||choiceOfGenre=="Action"||choiceOfGenre=="Horror")
			{
				cout<<"|Id\t\tTitle\t\t\t\tGenre\tPrice"<<endl;
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;
				//code snippet to display the books of the entered genre
				for(i=0;i<noOfBooks;i++)
				{
					if(choiceOfGenre==books[i][3])
						{
						cout<<"|";
						for(j=1;j<5;j++)
						{
							cout<<books[i][j]<<"\t";
						}
						cout<<"|";
						cout<<endl;
					}
				}
				for(int runLoop=0;runLoop<100;runLoop++){cout<<"-";}cout<<endl;
				cout<<endl;

				cout<<"Please enter the codes of the books you want to buy and enter 'done' when you are done and 'exit' to exit the code:"<<endl; //input of the code which should be added to cart
				
	
				for(i=0;addToCart!="done";i++)
				{
					cin>>addToCart;
					
					if(addToCart=="exit")
						return;
						
					counter=0;				
					amt=0;
					id=0;
					
					for(k=0;k<noOfBooks;k++)
					{
					
						if(books[k][1]==addToCart)
						{   
							
							//The following code snippet is to convert customer id from string to int
							string convert1=books[k][0];
							for(int st=0;st<1;st++)
							{
								int n=convert1[st]-48;
								id=id*10+n;
							}
							
							//The following code snippet is to convert the amount from string to integer
							string convert=books[k][4];
							//price the member of the structure cart
							for(int t=0;t<3;t++)
							{
								int n=convert[t]-48;
								amt=amt*10+n;
							}
							if(customers[id-1][1]==name)
							{	
								cout<<"Looks like you yourself are the seller of this book! Buy it from yourself! :) Continue adding!"<<endl;
								counter++;
						    }
							else
							{
								cobj.add(books[k][0],books[k][1],books[k][2],books[k][3],amt);
								counter++;
								break;
							}
						}
					}
				
					if(counter==0&&addToCart!="done")
						cout<<"You have entered incorrect code! We will not accept this code. Please continue adding!"<<endl;
					
				}
			}
			else
			{
				cout<<"OOPS YOU ENTERED AN INCORRECT GENRE!!!! PLEASE TRY AGAIN!"<<endl;
				choice='y';
			}
            /*for(int run=0;choice!="y"||choice!="Y";run++)
			{*/
			cout<<"Do you wish to continue viewing books by genres?(Enter y to continue,any other input will be considered no):";
			cin>>choice;
			//if(choice!="n"||choice!="N"||choice!="y"||choice!="Y")
			//	break;
			//}*/
            
		}while(choice=="y"||choice=="Y");

	cobj.menu();
	}//showBooksMenu() ends here


	//function to print the preDefined graph using DFS
	void DFS(int vertex)
	{
		int visited[NoOfPlaces]={0};
		int i;//'for' loop

		    stack<int> s; //creating object of predefined stack
		    s.push(vertex);
		    while(!s.empty()) //running till stack is empty
		    {
			        vertex=s.top();
			        s.pop();
			        if(visited[vertex]==0) //checking for visited
			        {
			            visited[vertex]=1;
			            cout<<cities[vertex]<<" * ";
			            for(i=0;i<NoOfPlaces;i++)
			            {
			                if(graphDatabase[vertex][i]!=0||graphDatabase[vertex][i]!=2147483647)//checking if path exists
			                s.push(i);
			            }
			        }
		    }

	}//function DFS() ends here


	//Function to give admin options which are not available to the user
	void admin()
	{
		system("CLS");
		Graph objOfGraph;//Creating object of graph class
		char adminChoice;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
		cout<<endl<<"\t\t\tADMIN SECTION"<<endl;
		for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;

		cout<<"As an admin do you want to perform the following the operations?: "<<endl;
		cout<<endl<<"Welcome Admin!"<<endl;

		cout<<"Please take a look at the menu: "<<endl;
		cout<<"1->View Customer Database"<<endl;
		cout<<"2->View Book Database"<<endl;
		cout<<"3->View the Graph Databse"<<endl;
		cout<<"4->Display the Pre-Defined Graph"<<endl;
		cout<<"5->Enter a new Graph Database"<<endl;
		cout<<"6->Exit"<<endl;

		for(;;)
		{
			cout<<endl<<"Please enter your choice from above menu to perform admin functions: ";
			cin>>adminChoice;
			cout<<endl;
			if(adminChoice=='6')
				break;
			else{
				switch(adminChoice)
				{
					case '1':
						displayCustomers();
						break;
					case '2':
						displayBooks();
						break;
					case '3':
						displayGraph();
						break;
					case '4':
						cout<<endl;
						DFS(0);
						cout<<endl;
						break;
					case '5':
						cout<<"We will directly send you to setGraph and from there you can implement Dijkstra's algorithm"<<endl;
						cout<<"The function of Dijkstras's Algorithm is independent of the database."<<endl;
						cout<<endl;
						objOfGraph.setGraph();
						break;
					default:
						cout<<"You have entered the wrong choice! Please try again later!"<<endl;
				}
			}
		}
	}//function admin() ends here


	//Main function to call the function
	int main()
	{       string choice;
			loginAccount();
			cout<<"HOPE YOU HAD FUN USING OUR PORTAL!!!"<<endl;
			cout<<"THANK YOU FOR BEING OUR CUSTOMER!!!"<<endl;
			for(int runLoop=0;runLoop<100;runLoop++){cout<<"*";}cout<<endl;
			cout<<"Enter continue to go to the admin section: ";
			cin>>choice;
			if(choice=="continue")
				admin();
			cout<<"END OF CODE";
	}



