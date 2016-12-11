//12/2/2016
//Christian Hill
//Replace quiz 1
// Friendster
#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <algorithm>
#include "Graph.hpp"
using namespace std;
Graph::Graph() 
{ 
	// better do something here or seg faults await!
		for (int i = 0; i < HASHMAP_SIZE; i++)
            {
				hobbies[i] = NULL;
            }
  
}

Graph::~Graph() 
{ 
	// Free hash table
	  for (int i = 0; i < HASHMAP_SIZE; i++)
            {      
                    delete hobbies[i];
            }
}

void Graph::addEdge(string v1, string v2)
{
	if(v1 == v2){ 	// don't add self 
		return;
	}
	else
	{
	vertex *vertex1 = findVertex(v1);
	vertex *vertex2 = findVertex(v2);
	// make sure not already in the list
	
	bool found = false;
	for(unsigned int i=0;i<vertex1->friends.size();i++)
	{
	if(vertex1->friends[i].v->id==v2)
	found=true;
	}
	if(!found)	// add edge to both vertices
	{
             adjVertex av;
             av.v = vertex2;
             vertex1->friends.push_back(av);
             adjVertex bc;
             bc.v = vertex1;
             vertex2->friends.push_back(bc);
	}
}

}

/* add the person to the graph */
void Graph::addVertex(string id)
{ 	
	if(!id.empty())
	{
	vertex v;
	v.id=id;
	vertices.push_back(v);
	}
}

void Graph::displayEdges()
{
	// very much like previous homework
	
	 for(unsigned int i = 0; i<vertices.size(); i++)
	{
        cout << vertices[i].networkID << ": [" << vertices[i].id << "] " << vertices[i].name << "-->";
        for(unsigned int j = 0; j < vertices[i].friends.size(); j++)
		{
            cout << vertices[i].friends[j].v->name;
            if (j != vertices[i].friends.size()-1)
               cout << "***";
        }
        cout << endl;
    }
}

int Graph::addUserToHobby(std::string hobby, std::string id)
{
	//cout << "Adding to hobby: " << hobby << " user: " << id << endl;
	vertex *user = findVertex(id);
	int key = (hobby[0] + hobby[1]) % HASHMAP_SIZE;
	//cout << " initial hashmap key " << key << endl;
	int collisions = 0;
	while(hobbies[key] != NULL && hobbies[key]->hobby != hobby )  
	{
		key=(key+1)%71;
		collisions++;
	}
	//cout << " final hashmap key " << key << endl;
	if(hobbies[key] == NULL)
	{
		hobbies[key] = new hobbylist;
		hobbies[key]->hobby = hobby;
		hobbies[key]->list.push_back(user);
	}
	else
	{
		hobbies[key]->list.push_back(user);
	}
	return collisions;
}

void Graph::displayHobbies()
{
	cout << "========================================\n";
	cout << "DISPLAYING HOBBY INTERESTS =============" << endl;
	for( int i=0; i<HASHMAP_SIZE; i++)
	{
		if(hobbies[i]!=NULL)
		{
		cout<<hobbies[i]->hobby<<": ";
		for(unsigned int j=0;j<hobbies[i]->list.size()-1;j++)
		 {
	     cout<<hobbies[i]->list[j]->name<<", ";
	     if(j%10==0)
	     cout<<'\n';
	     
		 }
		cout<<hobbies[i]->list[hobbies[i]->list.size()-1]->name<<'\n';
		cout<<'\n';
		}
	
	}
	}


/* return pointer to the correct vertex (person)  */
vertex * Graph::findVertex(std::string id)
{
	// very much like previous homework
	
	 for(unsigned int j = 0; j < vertices.size(); j++)
   {
      if (vertices[j].id == id)
      {
		  return &vertices[j];
	  }
   }
return NULL;
}

void Graph::assignSocialCircles()
{
	for(unsigned int j=0;j<vertices.size();j++)
	{
		vertices[j].networkID=0;
	}
	// very much like previous homework
	
	// Starting district numbers at 1
    int networkID = 1;

    // For each of the vertices
    for(unsigned int i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if(vertices[i].networkID==0)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].id,networkID);
           
        }
        networkID++;
		}

	
}

void Graph::BFTraversalLabel(std::string userid, int groupID)
{
	// very much like previous homework
	
	queue<vertex*> q;
  // Label all as unvisited.
  for(unsigned int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
  // Find the starting node and enqueue it.
  vertex* v1=findVertex(userid);
          // set current vertex to be visited.
			v1->visited=true;
		  // add code here
		    v1->networkID=groupID;
			q.push(v1);
 // Now do the rest of the search.
 while (q.empty() != true)
 {
     vertex * u = q.front();		// get the next one from the queue
     q.pop();					// remove that one from the queue
	for(unsigned int i=0;i < u->friends.size(); i++)
        {
            if(!u->friends[i].v->visited)
            {	
                u->friends[i].v->visited = true;
                u->friends[i].v->networkID=groupID;
                q.push(u->friends[i].v);
            }
        }
       }
}

