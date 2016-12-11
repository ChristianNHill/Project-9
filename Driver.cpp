//12/2/2016
//Christian Hill
//Replace quiz 1
// Friendster

#include <iostream>
#include <fstream>  //allows istream/ostream
#include <string>
#include <cstdlib> 
#include <vector>
#include <array>
#include <queue>
#include <sstream>      // std::stringstream, std::stringbuf
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include "Graph.hpp"
#include "Graph.cpp"

using namespace std;

void readUsersIntoGraph(Graph &g, char* fileName);
void readFilesIntoGraph(Graph & g, char* directoryName);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Usage: " << argv[0] << " datasetDirectoryName idlistFilename" << endl;
		return -1;
	}

    // Create a graph
    Graph graph;

    // Read file into graph
	readUsersIntoGraph(graph, argv[2]);	// file is just a list of all userids
    readFilesIntoGraph(graph, argv[1]); // each userid's detailed info

	graph.assignSocialCircles();

	cout << "========================================\n";
	cout << "GRAPH CONNECTIONS ====================== " << endl;
	graph.displayEdges();
	graph.displayHobbies();

    return 0;
}

/* Function to read in all the ids in the social network.
  Does not have access to their name and hobbies, just a list of ids
  Reads in from the filename listed in command-line arguments
  @param network the graph data structure of the social network
  @param fileName is the file with a list of IDs in the social network
*/
void readUsersIntoGraph(Graph & network, char* fileName)
{
	cout << "Creating graph of social network ids from file: " << fileName << endl;
	ifstream in_stream;
    in_stream.open(fileName);
    if (!in_stream)
    {
        cout << "Could not open file\n";
        return;
    }
    string userid;
    string line;
    while(getline(in_stream,line))
    {
	network.addVertex(line);
	}
	in_stream.close();
}

/*
 * reads all files (one at a time) from the dataset into the graph
 * @param directoryName name of the directory with all the dataset files
 * @param fileName name of file with a list of IDs needed to process in directory
 */
void readFilesIntoGraph(Graph & g, char* directoryName)
{
	// loop through each vertex and read in its detailed information
	//	each vertex in the graph has the userid which you can create the filename to read
	// hint: create a string with directoryname/userid.txt to open each file
	/*string dir = string(directoryName);
	vector<string> files = vector<string>();
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(dir.c_str())) == NULL) 
	{
		cout << "Error(" << errno << ") opening " << dir << endl;
	}
	while ((dirp = readdir(dp)) != NULL) 
	{
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);*/
	int numCollisions = 0;
	for (unsigned int i = 0;i < g.vertices.size();i++) 
	{
		ifstream in_stream;
		string file=string(directoryName);
		file.append("/");
		file.append(g.vertices[i].id);
		file.append(".txt");
		//cout<<g.vertices[i].id<<endl
		in_stream.open(file);
		if(!in_stream.is_open())
		{
		cout<<"file not opened"<<endl;
		}
		string data;
		getline(in_stream,data);
		string user=data;
		getline(in_stream,data);
		g.vertices[i].name=data;
		getline(in_stream,data);
		stringstream ss(data);
		while(getline(ss,data,','))
		{
			numCollisions+=g.addUserToHobby(data,user);
		}
		while(getline(in_stream,data))
		{
			g.addEdge(user,data);
		}
		in_stream.close();
	}
	 cout << "Processing dataset: " << directoryName << " (" << g.vertices.size() << " files)" << endl;
	cout << "========================================\n";
	cout << " NUMBER OF COLLISIONS ON ADDING HOBBIES: " << numCollisions << endl;
}


