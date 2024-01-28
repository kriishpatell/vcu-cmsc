// Krish Patel
import java.util.Scanner;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;
import java.util.ArrayList;

class Edge{
    int source; 
    int destination; 
    int cost; 

    public Edge(){
        source = 0;
        destination = 0;
        cost = 0;
    }

    public Edge(int source, int destination, int cost){
        this.source = source;
        this.destination = destination;
        this.cost = cost; 
    }
}

public class CMSC401_A3{
    public static List<Edge> findEdges (List<List<Edge>> adjacencyList, int[] parent, int targetNode){
        List<Edge> criticalEdges = new ArrayList<>();
        int current = parent[targetNode]; 
        int finalDest = targetNode; 

        while(current != 0){
            // Iterate through edges of current node
            for(Edge edge : adjacencyList.get(current)){
                if(edge.destination == finalDest){
                    // Add edges to beginning of list 
                    criticalEdges.add(0, edge);
                }
            }
            // Update target node and move to parent
            finalDest = current;
            current = parent[current];
        }
        return criticalEdges; 
    }

    public static int[] dijkstra (List<List<Edge>> adjacencyList, int[] motelCost, int source, int destination, int[] parentNodes){
        // Initialize priorty queue storing edges with all costs
        PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(Comparator.comparingInt(a -> a.cost));
        int listSize = adjacencyList.size(); 
        int[] distance = new int[listSize];

        Arrays.fill(distance, Integer.MAX_VALUE);
        distance[source] = 0; 

        priorityQueue.offer(new Edge(source, source, 0)); 

        // Dijsktra's algorithm main loop
        while(!priorityQueue.isEmpty()){
            // Get minimum cost edge from queue
            Edge scheduledEdge = priorityQueue.poll(); 
            int x = scheduledEdge.destination; 

            // Explore neighboring nodes and update distances and cost accordingly
            for(Edge neighboringNode : adjacencyList.get(x)){
                int y = neighboringNode.destination; 
                int distanceCost = neighboringNode.cost; 
                int motel = motelCost[y]; 
                int totalCost = distanceCost + motel; 

                // Update distance and parent node if a shorter path is found
                if(distance[x] != Integer.MAX_VALUE && totalCost + distance[x] < distance[y]){
                    parentNodes[y] = x; 
                    distance[y] = totalCost + distance[x];
                    // Add updated edge to queue to further iterate
                    priorityQueue.offer(new Edge(x, y, distance[y]));  
                }
            }
        }
        return distance;
    }
    public static void main (String[] args){
        // Initialize scanner and find number of cities and highways
        Scanner scr = new Scanner(System.in);
        int numCities = scr.nextInt();
        int numRoads = scr.nextInt();

        List<List<Edge>> adjacencyList = new ArrayList<>(); 
        for(int i = 0; i <= numCities; i++){
            adjacencyList.add(new ArrayList<>()); 
        }

        // Create array for cost between cities and their values
        int[] motelCost = new int[numCities + 1];
        motelCost[1] = 0;
        motelCost[2] = 0;
        
        for(int i = 3; i <= numCities; i++){
            int vertex = scr.nextInt();
            motelCost[vertex] = scr.nextInt(); 
        }

        // Read input for roads to construct graph 
        for(int i = 0; i < numRoads; i++){
            int start = scr.nextInt();
            int end = scr.nextInt();
            int cost = scr.nextInt();
            adjacencyList.get(start).add(new Edge(start, end, cost));
            adjacencyList.get(end).add(new Edge(end, start, cost)); 
        }

        int parentNodeSize = adjacencyList.size(); 
        int parentNodes[] = new int[parentNodeSize]; 
        
        // Find shortest paths using Dijkstra's algorithm and store in list
        int shortestPathList[] = dijkstra(adjacencyList, motelCost, 1, 2, parentNodes);
        List<Edge> edgeList = findEdges(adjacencyList, parentNodes, 2); 
        
        // Find the shortest path and 
        int shortestPath = shortestPathList[2]; 
        int secondShortestPath = Integer.MAX_VALUE;

        // Iterate through each edge in graph to recalculate shortest edge
        for(Edge edge : edgeList){
            int x = edge.source; 
            int y = edge.destination; 

            adjacencyList.get(x).removeIf(z -> z.destination == y);
            adjacencyList.get(y).removeIf(z -> z.destination == x);

            int[] finalDistance = dijkstra(adjacencyList, motelCost, 1, 2, parentNodes);
            int finalDistanceEdge = finalDistance[2]; 

            // Compare if second shortest edge is actually second shortest edge
            if(finalDistanceEdge < secondShortestPath && finalDistanceEdge > shortestPath){
                secondShortestPath = finalDistanceEdge;
            }
        }

        System.out.println(secondShortestPath); 
        scr.close();
    }
}