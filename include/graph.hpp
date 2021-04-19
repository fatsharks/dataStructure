#include <iostream>
#include <global.hpp>
#include <queue>
#include <algorithm>

#define MAX_COUNT_VERTEX 100
#define INFINITY 65535

//https://blog.csdn.net/Real_Fool_/article/details/114141377?ops_request_misc=&request_id=&biz_id=102&utm_term=114141377&utm_medium=distribute.pc_search_result.none-task-blog-2~all~sobaiduweb~default-0-114141377.first_rank_v2_pc_rank_v29#t30
namespace myDataStructure
{
    class Edge
    {
    public:
        float wight_;
        bool isSelect_;

        size_t tailvex_, headvex_;
        Edge *headLink_;
        Edge *tailLink_;

        Edge(size_t tailvex = 0, size_t headvex = 0, Edge *headlink = NULL, Edge *taillink = NULL, float wight = 1, bool boolean = false) : tailvex_(tailvex), headvex_(headvex), headLink_(headlink), tailLink_(taillink), wight_(wight), isSelect_(boolean)
        {
        }
        Edge(const Edge &src)
        {
            if (this == &src)
            {
                return;
            }
            else
            {
                this->wight_ = src.wight_;
                this->tailvex_ = src.tailvex_;
                this->headvex_ = src.headvex_;
                this->headLink_ = new Edge;
                this->tailLink_ = new Edge;
                *(this->headLink_) = *(src.headLink_);
                *(this->tailLink_) = *(src.tailLink_);
                this->wight_ = src.wight_;
                this->isSelect_ = src.isSelect_;
            }
        }
        Edge &operator=(const Edge &src)
        {
            if (this == &src)
            {
                return *this;
            }
            else
            {
                this->wight_ = src.wight_;
                this->tailvex_ = src.tailvex_;
                this->headvex_ = src.headvex_;
                *(this->headLink_) = *(src.headLink_);
                *(this->tailLink_) = *(src.tailLink_);
                this->wight_ = src.wight_;
                this->isSelect_ = src.isSelect_;
            }
        }
        ~Edge()
        {
            if (!headLink_)
            {
                delete headLink_;
                headLink_ = NULL;
            }
            else if (!tailLink_)
            {
                delete tailLink_;
                tailLink_ = NULL;
            }
        }
    };

    template <typename Value>
    class Vertex
    {
    public:
        Value data_;
        Edge *firstin_;
        Edge *firstout_;

        Vertex(Value *value, Edge *in = NULL, Edge *out = NULL) : data_(value), firstin_(NULL), firstout_(NULL)
        {
        }
        Vertex(const Vertex &src)
        {
            if (this == &src)
            {
                return *this;
            }
            else
            {
                this->data_ = src.data_;
                this->firstin_ = new Edge;
                this->firstout_ = new Edge;
                *(this->firstin_) = *(src.firstin_);
                *(this->firstout_) = *(src.firstout_);
            }
        }
        Vertex &operator=(const Vertex &src)
        {
            if (this == &src)
            {
                return *this;
            }
            this->data_ = src.data_;
            *(this->firstin_) = *(src.firstin_);
            *(this->firstout_) = *(src.firstout_);
            return *this;
        }
        ~Vertex()
        {
            if (!firstin_)
            {
                delete firstin_;
                firstin_ = NULL;
            }
            else if (!firstout_)
            {
                delete firstout_;
                firstout_ = NULL;
            }
        }
    };

    typedef struct estruct
    {
        int begin_;
        int end_;
        float wight_;
    } EStruct;

    template <typename Vertex, typename Edge, typename Value>
    class Graph
    {
    private:
        myDataStructure::Vertex<Value> *verList[MAX_COUNT_VERTEX];
        size_t vertexNum_, arcNum_;
        float arc[MAX_COUNT_VERTEX][MAX_COUNT_VERTEX];
        EStruct Elist[MAX_COUNT_VERTEX * (MAX_COUNT_VERTEX - 1)];
        bool visit[MAX_COUNT_VERTEX];

        int locateVertex(const Value &value);
        int firstNeighbor(int src);
        int nextNeighbor(int src, int except);
        void DFS(int index = 0);

    public:
        int inDegree[MAX_COUNT_VERTEX];
        int outDegree[MAX_COUNT_VERTEX];

    public:
        Graph();
        Graph(const Graph &src);
        Graph &operator=(const Graph &src);

        void getInDegree();
        void getOutDegree();

        bool insertVertex(Value &value);
        bool insertEdge(Value &tailValue, Value &headValue, float wight = 1);
        bool removeVertex(Value &value);
        bool removeEdge(Value &tailValue, Value &headValue, float wight = 1);
        void DFSTravel();
        void BFSTravel();
        void MinimumSpanningTreePrime(Value &value);
        void MinimumSpanningTreeKruskal();
        void Dijsktra(Value &value);
        void Floyd();
        bool TopologicalSort();
        ~Graph();
    };

    template <typename Vertex, typename Edge, typename Value>
    Graph<Vertex, Edge, Value>::Graph() : vertexNum_(0), arcNum_(0)
    {
        for (size_t i = 0; i < MAX_COUNT_VERTEX; i++)
        {
            verList[i] = NULL;
        }
        for (size_t i = 0; i < MAX_COUNT_VERTEX; i++)
        {
            visit[i] = false;
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    Graph<Vertex, Edge, Value>::~Graph()
    {
        for (size_t i = 0; i < MAX_COUNT_VERTEX; i++)
        {
            if (!verList[i])
            {
                delete verList[i];
                verList[i] = NULL;
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    Graph<Vertex, Edge, Value>::Graph(const Graph<Vertex, Edge, Value> &src)
    {
        if (this == &src)
        {
            return;
        }
        else
        {
            this->arcNum_ = src.arcNum_;
            this->vertexNum_ = src.vertexNum_;
            this->verList = new myDataStructure::Vertex<Value> *[MAX_COUNT_VERTEX];
            for (size_t i = 0; i < src.vertexNum_; i++)
            {
                *(this->verList[i]) = *(src.verList[i]);
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    Graph<Vertex, Edge, Value> &Graph<Vertex, Edge, Value>::operator=(const Graph<Vertex, Edge, Value> &src)
    {
        if (this == &src)
        {
            return *this;
        }
        else
        {
            this->arcNum_ = src.arcNum_;
            this->vertexNum_ = src.vertexNum_;
            for (size_t i = 0; i < src.vertexNum_; i++)
            {
                *(this->verList[i]) = *(src.verList[i]);
            }
        }
        return *this;
    }
    template <typename Vertex, typename Edge, typename Value>
    int Graph<Vertex, Edge, Value>::locateVertex(const Value &value)
    {
        int index = -1;
        for (size_t i = 0; i < vertexNum_; i++)
        {
            if (verList[i]->data_)
            {
                index = i;
            }
        }
        return index;
    }
    template <typename Vertex, typename Edge, typename Value>
    int Graph<Vertex, Edge, Value>::firstNeighbor(int src)
    {
        int index = -1;
        myDataStructure::Edge *temp = verList[src]->firstout_;
        if (temp)
        {
            index = temp->headvex_;
        }
        return index;
    }
    template <typename Vertex, typename Edge, typename Value>
    int Graph<Vertex, Edge, Value>::nextNeighbor(int src, int except)
    {
        int index = -1;
        myDataStructure::Edge *temp = verList[src]->firstout_;
        while (temp)
        {
            temp = temp->tailLink_;
            if (temp && temp->headvex_ != except)
            {
                index = temp->headvex_;
                break;
            }
        }
        return index;
    }
    template <typename Vertex, typename Edge, typename Value>
    bool Graph<Vertex, Edge, Value>::insertVertex(Value &value)
    {
        if (vertexNum_ == MAX_COUNT_VERTEX)
        {
            return false;
        }
        else
        {
            myDataStructure::Vertex<Value> *newVer = new myDataStructure::Vertex<Vertex>;
            newVer->data_ = value;
            verList[vertexNum_] = newVer;
            vertexNum_++;
            return true;
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    bool Graph<Vertex, Edge, Value>::insertEdge(Value &tailValue, Value &headValue, float wight = 1)
    {
        int tailvex = locateVertex(tailValue);
        int headvex = locateVertex(headValue);
        if (tailvex == -1 || headvex == -1 || tailvex == headvex)
        {
            return false;
        }
        else
        {
            myDataStructure::Vertex<Value> *tailV = verList[tailvex];
            myDataStructure::Vertex<Value> *headV = verList[headvex];
            myDataStructure::Edge *newEdge = new myDataStructure::Edge;
            myDataStructure::Edge *temp = NULL;
            if (tailV->firstout_)
            {
                temp = tailV->firstout_;
                while (temp->tailLink_)
                {
                    temp = temp->tailLink_;
                }
                temp->tailLink_ = newEdge;
            }
            else
            {
                tailV->firstout_ = newEdge;
            }
            if (headV->firstin_)
            {
                temp = headV->firstin_;
                while (temp->headLink_)
                {
                    temp = temp->headLink_;
                }
                temp->headLink_ = newEdge;
            }
            else
            {
                headV->firstin_ = newEdge;
            }
            newEdge->tailvex_ = tailvex;
            newEdge->headvex_ = headvex;
            newEdge->wight_ = wight;
            arcNum_++;
            return true;
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::getOutDegree()
    {
        for (size_t i = 0; i < vertexNum_; i++)
        {
            int count = 0;
            for (size_t j = 0; j < vertexNum_; j++)
            {
                if (arc[i][j] != 0 && arc[i][j] < INFINITY)
                {
                    count++;
                }
            }
            outDegree[i] = count;
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::getInDegree()
    {
        for (size_t i = 0; i < vertexNum_; i++)
        {
            int count = 0;
            for (size_t j = 0; j < vertexNum_; j++)
            {
                if (arc[j][i] != 0 && arc[j][i] < INFINITY)
                {
                    count++;
                }
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::DFSTravel()
    {
        for (size_t i = 0; i < vertexNum_; i++)
        {
            visit[i] = false;
        }
        for (size_t index = 0; index < vertexNum_; index++)
        {
            if (!visit[index])
            {
                visit[index] = true;
                DFS(index);
            }
        }
        for (size_t i = 0; i < vertexNum_; i++)
        {
            visit[i] = false;
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::DFS(int index = 0)
    {
        std::cout << "Vertex number: " << index << " "
                  << "data: " << verList[index]->data_ << std::endl;
        for (size_t i = firstNeighbor(index); i >= 0; i = nextNeighbor(index, i))
        {
            if (!visit[i])
            {
                DFSTravel(i);
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::BFSTravel()
    {
        std::queue<int> que;
        int neighbor;
        myDataStructure::Edge *tempEdge = NULL;
        myDataStructure::Vertex<Value> *tempVer = NULL;
        for (size_t i = 0; i < vertexNum_; i++)
        {
            visit[i] = false;
        }
        for (size_t index = 0; index < vertexNum_; index++)
        {
            tempVer = verList[index];
            tempEdge = tempVer->firstout_;
            if (!visit[index])
            {
                que.push(index);
                while (!que.empty())
                {
                    visit[que.front()] = true;
                    std::cout << verList[que.front()]->data_ << endl;
                    que.pop();
                    while (tempEdge)
                    {
                        if (!visit[tempEdge->headvex_])
                        {
                            que.push(tempEdge->headvex_);
                        }
                        tempEdge = tempEdge->tailLink_;
                    }
                }
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::MinimumSpanningTreePrime(Value &value)
    {
        int start = locateVertex(value);
        int weightSum = 0;
        float min;
        int select[vertexNum_] = {-1}; //已选顶点集合S
        int lowcost[vertexNum_] = {0}; //从集合S出发的最短路径集合

        //随机选一个顶点，初始化顶点集合，最短路径集合
        for (size_t i = 1; i < vertexNum_; i++)
        {
            select[i] = -1;
            lowcost[i] = arc[start][i];
        }

        //循环遍历每个可能存在的连通分量，完成整个图的最小生成树
        for (size_t i = 1; i < vertexNum_; i++)
        {
            min = INFINITY;
            int k = -1;
            //选定离集合S最近的顶点
            for (size_t j = 1; j < vertexNum_; i++)
            {
                if (select[j] != -1 && lowcost[j] < min)
                {
                    min = lowcost[j];
                    k = j;
                }
            }
            //更新顶点集合S，更新最短路径集合
            if (k != -1)
            {
                select[k] = 0;
                weightSum += lowcost[k];
                for (size_t j = 1; j < vertexNum_; j++)
                {
                    if (select[j] == -1 && arc[j][k] < lowcost[j])
                    {
                        lowcost[j] = arc[j][k];
                    }
                }
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::MinimumSpanningTreeKruskal()
    {
        int begin, end;
        int adjvex[vertexNum_];
        float weightSum = 0;
        int k = 0;
        for (size_t i = 0; i < vertexNum_; i++)
        {
            adjvex[i] = -1;
            for (size_t j = 0; j < vertexNum_; j++)
            {
                if (arc[i][j] != 0 && arc[i][j] != INFINITY)
                {
                    Elist[k].begin_ = i;
                    Elist[k].end_ = j;
                    Elist[k].wight_ = arc[i][j];
                    k++;
                }
            }
        }
        heapsort(E, k, sizeof(E[0])); //对边集数组按照权值进行排序
        for (size_t i = 0; i < ++k; i++)
        {
            begin = Elist[i].begin_;
            end = Elist[i].end_;
            if (adjvex[begin] != -1 || adjvex[end] != -1)
            {
                adjvex[begin] = adjvex[end] = 0;
                weightSum += Elist[i].wight_;
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::Dijsktra(Value &value)
    {
        int start = locateVertex(value);
        bool select[vertexNum_];
        int dist[vertexNum_];
        int min;
        //初始化顶点集合S和dist[]数组
        for (size_t i = 0; i < vertexNum_; i++)
        {
            select[i] = false;
            dist[i] = arc[start][i];
        }
        select[start] = true;
        dist[start] = 0;
        for (size_t i = 0; i < vertexNum_; i++)
        {
            min = INFINITY;
            int k = -1;
            //选择dist[]数组最小的顶点k，加入顶点集合S
            for (size_t j = 0; j < vertexNum_; j++)
            {
                if (dist[j] != 0 && dist[j] < min && select[j] == false)
                {
                    min = dist[j];
                    k = j;
                }
            }
            if (k != -1)
            {
                select[k] = true;
                min = INFINITY;
                //以新加入的顶点k为出发点，比较dist[k]+arc[k][j]与dist[j]的大小，更新dist[]数组
                for (size_t j = 0; j < vertexNum_; j++)
                {
                    if (arc[k][j] != 0 && arc[k][j] < min && (dist[k] + arc[k][j]) < dist[j] && select[j] == false)
                    {
                        dist[j] = dist[k] + arc[k][j];
                    }
                }
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    void Graph<Vertex, Edge, Value>::Floyd()
    {
        float A[vertexNum_][vertexNum_];
        int path[vertexNum_][vertexNum_];
        for (size_t i = 0; i < vertexNum_; i++)
        {
            for (size_t j = 0; j < vertexNum_; j++)
            {
                A[i][j] = arc[i][j];
                path[i][j] = -1;
            }
        }
        for (size_t k = 0; k < vertexNum_; k++)
        {
            for (size_t i = 0; i < vertexNum_; i++)
            {
                for (size_t j = 0; j < vertexNum_; j++)
                {
                    if ((A[i][j] > A[i][k] + A[k][j]))
                    {
                        A[i][j] = A[i][k] + A[k][j];
                        path[i][j] = k;
                    }
                }
            }
        }
    }
    template <typename Vertex, typename Edge, typename Value>
    bool Graph<Vertex, Edge, Value>::TopologicalSort()
    {
        std::queue<int> que;
        for (size_t i = 0; i < vertexNum_; i++)
        {
            if (!inDegree[i])
            {
                que.push(i);
            }
        }
        int count = 0;
        while (!que.empty())
        {
            int index = que.front();
            count++;
            que.pop();
            myDataStructure::Vertex<Value> *tempVer = verList[index];
            for (myDataStructure::Edge *tempEdge = tempVer->firstout_; tempEdge; tempEdge = tempEdge->tailLink_)
            {
                inDegree[tempEdge->headvex_]--;
                if (inDegree[tempEdge->headvex_] == 0)
                {
                    que.push(tempEdge->headvex_);
                }
            }
        }
        if (count != vertexNum_)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

} // namespace myDataStructure
