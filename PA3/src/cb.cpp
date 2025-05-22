#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Reference 1 start: https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/
class DSU
{
    private:
        int* parent;
        int* rank;
    public:
        DSU(int n)
        {
            parent = new int[n];
            rank = new int[n];
            for(int i = 0 ; i < n ; i++)
            {
                parent[i] = -1;
                rank[i] = 1;
            }
        }

        int find(int i)
        {
            if(parent[i] == -1)
                return i;
            
            return parent[i] = find(parent[i]);
        }

        void unite(int x, int y)
        {
            int s1 = find(x);
            int s2 = find(y);

            if(s1 != s2)
            {
                if(rank[s1] < rank[s2])
                {
                    parent[s1] = s2;
                }
                else if(rank[s1] > rank[s2])
                {
                    parent[s2] = s1;
                }
                else
                {
                    parent[s2] = s1;
                    rank[s1] += 1;
                }
            }
        }
};
// Reference 1 End

class edge
{
    public:
        void set_start(int s){start = s;}
        int get_start(){return start;}
        void set_end(int des){end = des;}
        int get_end(){return end;}
        void set_weight(int w){weight = w;}
        int get_weight(){return weight;}

    private:
        int start;
        int end;
        int weight = 1;
};

bool operator>(edge e1, edge e2)
{
    return e1.get_weight() > e2.get_weight();
}

bool operator<(edge e1, edge e2)
{
    return e1.get_weight() < e2.get_weight();
}

class graph
{
    private:
        int V; // vertices
        vector <edge> edges; // edges
    public:
        graph(int num_vertices, vector <edge> graph_edge)
        {
            this->V = num_vertices;
            this->edges = graph_edge;
        }
        void edge_add(edge newedge)
        {
            edges.push_back(newedge);
        }
        vector <edge> kruskal_maxst()
        {
            vector <edge> MaxSpanTree;
            sort(edges.begin(), edges.end(), std::greater<edge>());
            DSU s(V);

            for(int i = 0 ; i < edges.size() ; i++)
            {
                if(s.find(edges[i].get_start()) != s.find(edges[i].get_end()))
                {
                    MaxSpanTree.push_back(edges[i]);
                    s.unite(edges[i].get_start(), edges[i].get_end());
                }
            }

            return MaxSpanTree;
        }
	
	vector <vector <int> > get_adj_list()
	{
	    vector <vector <int> > graph_adj_list;
	    for(int i = 0 ; i < V ; i++)
	    {
	    	vector <int> row;
		graph_adj_list.push_back(row);
	    }
	    
	    for(int i = 0 ; i < edges.size() ; i++)
	    {
	    	graph_adj_list[edges[i].get_start()].push_back(edges[i].get_end());
	    }

	    return graph_adj_list;
	}

	// Reference 2 Start : https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
	bool pre_cyc_tool(vector <vector <int> >& graph_adj_list, int u, vector <bool>& visited, vector<bool>& recStack)
	{
	    if(!visited[u])
	    {
	    	visited[u] = true;
		recStack[u] = true;
	    
		for(int x : graph_adj_list[u])
		{
		    if(!visited[x] && pre_cyc_tool(graph_adj_list, x, visited, recStack))
			return true;
		    else if (recStack[x])
			return true;
		}

	    }

	    recStack[u] = false;
	    return false;
		
	}

	bool detect_cycle()
	{
	    vector <vector <int> > graph_adj_list = this->get_adj_list();
	    vector <bool> visited(this->V, false);
	    vector <bool> recStack(this->V, false);

	    for(int i = 0 ; i < this->V ; i++)
	    {
	    	if(!visited[i] && pre_cyc_tool(graph_adj_list, i, visited, recStack))
		    return true;
	    }

	    return false;
	}

	// Reference 2 End
};

int main(int argc, char *argv[])
{
    fstream fin;
    fstream fout;
    char buffer;

    fin.open(argv[1], fstream::in);

    char type; // undirected or directed
    int num_vertices, num_edges; // Number of vertices and edges
    vector <edge> graph_edge;

    fin >> type;
    fin >> num_vertices;
    fin >> num_edges;

    for(int i = 0 ; i < num_edges ; i++)
    {
        int edge_start, edge_end, weight_edge;
        fin >> edge_start >> edge_end >> weight_edge;
        //cout << "Input: " << edge_start << " " << edge_end << " " << weight_edge << endl;
        edge newedge;
        newedge.set_start(edge_start);
        newedge.set_end(edge_end);
        newedge.set_weight(weight_edge);
        //cout << "Get: " << newedge.get_end() << " " << newedge.get_weight() << endl;
        graph_edge.push_back(newedge);

    }

    //cout << "\n";
 
    graph graph_input = graph(num_vertices, graph_edge); 
    vector <edge> MaxSpanTreeEdge = graph_input.kruskal_maxst();

    //for(int i = 0 ; i < MaxSpanTreeEdge.size() ; i++)
    //{
    //    cout << MaxSpanTreeEdge[i].get_start() << " " << MaxSpanTreeEdge[i].get_end() << " " << MaxSpanTreeEdge[i].get_weight() << "\n";
    //}

    //cout << "\n";

    graph MaxSpanTree = graph(num_vertices, MaxSpanTreeEdge);

    vector <bool> IsInMaxSpanTree(num_edges, false);
    for(int i = 0 ; i < graph_edge.size() ; i++)
    {
        for(int j = 0 ; j < MaxSpanTreeEdge.size() ; j++)
        {
            if(graph_edge[i].get_start() == MaxSpanTreeEdge[j].get_start()
            && graph_edge[i].get_end() == MaxSpanTreeEdge[j].get_end())
            {
                IsInMaxSpanTree[i] = true;
            }
        }
    }

    int removed_weight = 0;
    vector <edge> RemainEdge;
    for(int i = 0 ; i < IsInMaxSpanTree.size() ; i++)
    {
        if(IsInMaxSpanTree[i] == false)
	{	
	    RemainEdge.push_back(graph_edge[i]);
	}
    }

    if(type == 'u')
    {
    	for(int i = 0 ; i < RemainEdge.size() ; i++)
	{
	    removed_weight += RemainEdge[i].get_weight();
	}
    }
    else if(type == 'd')
    {
    	sort(RemainEdge.begin(), RemainEdge.end(), std::greater<edge>());
    	vector <bool> Remain_AddBack(RemainEdge.size(), true);
	for(int i = 0 ; i < RemainEdge.size() ; i++)
	{
	    MaxSpanTreeEdge.push_back(RemainEdge[i]);
	    graph MaxSpanTree = graph(num_vertices, MaxSpanTreeEdge);
	    if(MaxSpanTree.detect_cycle() == true)
	    {
	    	Remain_AddBack[i] = false;
		MaxSpanTreeEdge.pop_back();
	    }	    
	}

	vector <edge> RemainEdge_fin;

	for(int i = 0 ; i < Remain_AddBack.size() ; i++)
	{
	    if(Remain_AddBack[i] == false)
	    {	
		RemainEdge_fin.push_back(RemainEdge[i]);
		removed_weight += RemainEdge[i].get_weight();
	    }
	}

	RemainEdge = RemainEdge_fin;
    }

    //cout << removed_weight << "\n";

    //for(int i = 0 ; i < RemainEdge.size() ; i++)
    //{
    //    cout << RemainEdge[i].get_start() << " " << RemainEdge[i].get_end() << " " << RemainEdge[i].get_weight() << "\n";
    //}

    fout.open(argv[2], fstream::out);
    fout << removed_weight << "\n";

    for(int i = 0 ; i < RemainEdge.size() ; i++)
    {
    	if(IsInMaxSpanTree[i] == false)
	fout << RemainEdge[i].get_start() << " " << RemainEdge[i].get_end() << " " << RemainEdge[i].get_weight() << "\n";
    }

    fin.close();
    fout.close();

    return 0;
}
