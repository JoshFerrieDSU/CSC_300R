#include "graph.h"

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    visited = new bool[maxVertices] {false};

    adjMatrix = new int*[maxVertices]; // a pointer of rows
    // each int* stores a row
    for(int i = 0; i < maxVertices; i++){
        adjMatrix[i] = new int[maxVertices];
        for (int j = 0; j < maxVertices; j++)
            adjMatrix[i][j] = 0;
    }
}

Graph::~Graph()
{
    delete[] visited;

    for(int i = 0; i < maxVertices; i++)
        delete[] adjMatrix[i];

    delete[] adjMatrix;

    vertex* tempVertex;
    while(vertices)
    {
        edge* tempEdge;
        // free the memory of the neighbor list of that vertex
        while(vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;
        }
        // free that vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex;
    }
}

void Graph::addVertex(char data)
{
    if(numVertices >= maxVertices)
    {
        cout << "Max number of vertices reached. Can't add!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices; // add at the beg of the vertices list
    vertices = newVertex; // make it the new head of the vertex list
    newVertex->aHead = nullptr;

    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // find src and dest vertices
    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }
    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't add an edge" << endl;
        return;
    }

    // Adj list - undirected graph
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Adj Matrix
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}



void Graph::removeEdge(char src, char dest){
    vertex* srcV = vertices;
    vertex* destV = vertices; //grab source and dest for the edge

    while (srcV && srcV->data != src){
        srcV = srcV->vNext;
    }

    while (destV && destV->data != dest){
        destV = destV->vNext;
    }
    if (!srcV || !destV){//stop if one end is missing
        cout << "no edge found"<<endl;
        return;
    }

    //start walking
    edge* curr = srcV->aHead;
    edge* prev = nullptr;
    while (curr && curr->dest->data != dest){
        prev = curr;
        curr = curr->eNext;
    }
    if (curr){
        if (prev){//check if head or not and delete accordingly for the source
            prev->eNext = curr->eNext;
        } else{
            srcV->aHead = curr->eNext;
        }
        delete curr;
    }

    //now same thing for the dest
    curr = destV->aHead;
    prev = nullptr;
    while (curr && curr->dest->data != src){
        prev = curr;
        curr = curr->eNext;
    }
    if (curr){
        if (prev){
            prev->eNext = curr->eNext;
        } else{
            destV->aHead = curr->eNext;
        }
        delete curr;
    }

    //update the aj list
    int srcIndex = src - 'A';
    int destIndex = dest - 'A';
    if ((srcIndex >= 0 && srcIndex < maxVertices) && (destIndex >= 0 && destIndex < maxVertices)){
        adjMatrix[srcIndex][destIndex] = 0;
        adjMatrix[destIndex][srcIndex] = 0;
        cout<<"Updated ["<<srcIndex<<"]["<<destIndex<<"]\n";
    }


}//done and checked

vertex* findVertex(vertex* head, char data)
{
    vertex* v = head;
    while (v && v->data != data)
    {
        v = v->vNext;
    }
    return v;
}

void Graph::bfsL(char start){
    for (int i = 0; i < maxVertices; i++)
        visited[i] = false;

    vertex* startV = findVertex(vertices, start);
    if (!startV){//check if it even exists
        cout<<"ERROR, cant start because vertices cannot be found.\n";
        return;
    }

    int startIndex = start - 'A';
    if (startIndex < 0 || startIndex >= maxVertices){ //check if in range
        cout<<"out of range.\n";
        return;
    }

    Queue q;
    string labelStr; //character equivalent for queue
    //since i used string for the old queue, we have to make it work though it complicates things
    visited[startIndex] = true;
    labelStr = string(1, start); //char equivalent for my implmentation not worth it
    q.enqueue(labelStr);

    cout<<"bfs list starting from "<<start<<": ";

    while (!q.isEmpty()){
        string currentStr = q.dequeue();
        char currentLabel = currentStr[0];
        int currentIndex = currentLabel - 'A';

        cout<<currentLabel<<" ";

        vertex* currentVertex = findVertex(vertices, currentLabel);
        if (!currentVertex){
            continue; //doesn't break the loop but if somehow an error it skips it but probably could break
        }

        for (edge* e = currentVertex->aHead; e != nullptr; e = e->eNext){
            char nLabel = e->dest->data;
            int nIndex = nLabel - 'A';

            if ((nIndex >= 0 && nIndex < maxVertices) && (!visited[nIndex])){
                visited[nIndex] = true;
                labelStr = string(1, nLabel);
                q.enqueue(labelStr);
            }
        }
    }
    cout << endl;

}


void Graph::bfsM(char start){
    for (int i = 0; i < maxVertices; i++){
        visited[i] = false; //none are visited yet
    }

    int startIndex = start - 'A';
    if (startIndex < 0 || startIndex >= maxVertices){
        cout << "Out of range" << endl;
        return;//range check
    }

    if (!findVertex(vertices, start)){
        cout << "Index not found" << endl;
        return;//vertex check
    }

    Queue q;
    string iStr;

    visited[startIndex] = true;
    iStr = to_string(startIndex);
    q.enqueue(iStr);

    cout<<"bfs aj matrix starting from "<<start<<": ";

    while(!q.isEmpty()){
        string vStr = q.dequeue();
        int v = stoi(vStr);//note v is current in the queue or honestly any stoi

        cout<<char('A' + v) << " ";

        for (int i = 0; i < maxVertices; i++){
            if (adjMatrix[v][i] != 0 && !visited[i]){
                visited[i] = true;
                iStr = to_string(i);
                q.enqueue(iStr);
            }
        }
    }
    cout<<endl;
}

void Graph::dfsL(char start){
    for (int i = 0; i < maxVertices; ++i)
        visited[i] = false;

    if (!findVertex(vertices, start))
    {
        cout << "Vertex not found endl";
        return;
    }

    int startIndex = start - 'A';
    if (startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Out of range";
        return;
    }

    Stack st;
    string labelStr;

    labelStr = string(1, start);
    st.push(labelStr);

    cout<<"DFS list from "<<start<<": ";

    while (!st.isEmpty()){
        string vStr = st.pop();
        char vLabel = vStr[0];
        int vIndex = vLabel - 'A';

        if (vIndex < 0 || vIndex >= maxVertices){
            continue;
        }
        if (!visited[vIndex]){
            visited[vIndex] = true;
            cout<<vLabel<<" ";

            vertex* v = findVertex(vertices, vLabel);
            if(!v){
                continue;
            }

            for (edge* e = v->aHead; e != nullptr; e = e->eNext){
                char nLabel = e->dest->data;
                int nIndex = nLabel - 'A';

                if (nIndex >= 0 && nIndex < maxVertices && !visited[nIndex]){
                    labelStr = string(1, nLabel);
                    st.push(labelStr);
                }
            }
        }
    }
    cout<<endl;
}

void Graph::dfsM(char start){
    for (int i = 0; i < maxVertices; ++i)
        visited[i] = false;

    if (!findVertex(vertices, start))
    {
        cout << "Vertex not found endl";
        return;
    }

    int startIndex = start - 'A';
    if (startIndex < 0 || startIndex >= maxVertices)
    {
        cout << "Out of range";
        return;
    }

    Stack st;
    string iStr;

    iStr = to_string(startIndex);
    st.push(iStr);

    cout<<"DFS aj matrix from "<<start<<": ";

    while(!st.isEmpty()){
        string vStr = st.pop();
        int v = stoi(vStr);

        if (!visited[v]){
            visited[v] = true;
            cout<<char('A' + v) << " ";

            for (int i = maxVertices - 1; i >= 0; i--){
                if (adjMatrix[v][i] != 0 && !visited[i]){
                    iStr = to_string(i);
                    st.push(iStr);
                }
            }
        }
    }
    cout<<endl;
}

int Graph::connectedComponents(){
    for (int i = 0; i < maxVertices; ++i)
        visited[i] = false;

    int count = 0;

    for (vertex* v = vertices; v != nullptr; v = v->vNext){
        int index = v->data - 'A';
        if (index < 0 || index >= maxVertices){
            continue;
        }
        if (!visited[index]){
            count++;
            cout<<"Part " <<count<<": ";

            Queue q;
            string labelStr;

            visited[index] = true;
            labelStr = string(1, v->data);
            q.enqueue(labelStr);

            while (!q.isEmpty())
            {
                string currentStr = q.dequeue();
                char currentLabel = currentStr[0];
                int cIndex = currentLabel - 'A';

                cout << currentLabel << " ";

                vertex* currVertex = findVertex(vertices, currentLabel);
                if (!currVertex){
                    continue;
                }

                for (edge* e = currVertex->aHead; e != nullptr; e = e->eNext){
                    char nLabel = e->dest->data;
                    int nIndex = nLabel - 'A';

                    if (nIndex >= 0 && nIndex < maxVertices && !visited[nIndex]){
                        visited[nIndex] = true;
                        labelStr = string(1, nLabel);
                        q.enqueue(labelStr);
                    }
                }
            }
            cout<<endl;
            
        }
    }
    cout<<"Total connections: "<<count<<endl;
    return count;
}

void Graph::removeVertex(char data)
{
    // find the vertex
    vertex* temp = vertices;
    vertex* prev = nullptr;

    while(temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }
    
    if(!temp)
    {
        cout << "Vertex not found - can't remove" << endl;
        return;
    }

    // remove that vertex from the adj list of all other vertices
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while(e)
        {
            if(e->dest->data == data)
            {
                if(prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // remove the vertex
    if(prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;

    // Adj matrix
    int index = temp->data - 'A';
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;
}

void Graph::displayList()
{
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for(edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " (" << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
    cout << endl;
}

void Graph::displayMatrix()
{
    cout << "     ";
    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " "; // column headers
    }
    cout << endl;
    cout << "   ";
    
    for(int i = 0; i < maxVertices; i++)
    {
        cout << "-----";
    }
    cout << endl;

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " |"; // row header
        for(int j = 0; j < maxVertices; j++)
        {
            cout << setw(3) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}