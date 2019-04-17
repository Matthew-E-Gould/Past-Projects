INFINITY = 1000000
INVALID_NODE = -1

##Class that stores all the details of a node in a network
class Node:
        previous = INVALID_NODE #Stores previous node
        distFromSource = INFINITY #Stores distance from source
        visited = False #Stores if the node has been visited or not
        
##Function that recreates the matrix in the given .txt file
def populateNetwork(FILE_NAME):
        network = []
        networkFile = open(FILE_NAME, "r")
        for line in networkFile:
                network.append(map(int, line.strip('\r\n').split(',')))
        return network
##Function that finds the route in a given .txt file
def findRoute(FILE_NAME):
        route = []
        routeNumber = []
        networkFile = open(FILE_NAME, "r")
        for line in networkFile:
                routeLetter = (map(str, line.strip('\r\n').split('>')))
        routeNumber.append(ord(routeLetter[0]) - 65)
        routeNumber.append(ord(routeLetter[1]) - 65)
        route.append(routeNumber)
        route.append(routeLetter)
        return route
##Function that creates a list of nodes,
 #each index will be a node class which means that the list can store the infomation about each node.
 #This function will also pre-fill the START_NODE's values
def populateNodeTable(network, START_NODE):
        nodeTable = []
        for line in network:
                nodeTable.append(Node())
        nodeTable[START_NODE].distFromSource = 0
        nodeTable[START_NODE].visited = True
        return nodeTable
##Using the network matrix and the nodeTable list, this function works out which nodes are connected to the currentNode
def returnNearNeighbours(network, nodeTable, currentNode):
        nearNeighbours = []
        for node, value in enumerate(network[currentNode]):
                if value != 0 and nodeTable[node].visited==False:
                        nearNeighbours.append(node)
        return nearNeighbours
##Funtion that works out which nodes are suitable to be the next node in Dijkstras Alogirthm
def calculateTentative(network, currentNode, nodeTable):
        NN = returnNearNeighbours(network, nodeTable, currentNode)
        for nodeIndex in NN:
                tentativeDist = nodeTable[currentNode].distFromSource + network[currentNode][nodeIndex]
                if tentativeDist < nodeTable[nodeIndex].distFromSource:
                        nodeTable[nodeIndex].distFromSource = tentativeDist
                        nodeTable[nodeIndex].previous = currentNode
        return nodeTable
##Function that calculates which node is the next in Dijkstras Alogirthm
def returnNextNode(nodeTable):
        shortDistFromSrc = INFINITY
        currentNode = INVALID_NODE
        for nodeIndex, node in enumerate(nodeTable):
                if(node.distFromSource < shortDistFromSrc and node.visited == False):   ##makes sure that that the next node is the closest
                                                                                         #and hasn't been visited before
                        currentNode = nodeIndex
                        shortDistFromSrc = node.distFromSource
        return currentNode
##Function that connects calculateTentative and returnNextNode in a while loop to return the shortest path.
 #Function loops until the path is found.
def calculateShortestPath(currentNode, END_NODE, network, nodeTable):
        while currentNode != END_NODE:
                calculateTentative(network, currentNode, nodeTable)
                currentNode = returnNextNode(nodeTable)
                nodeTable[currentNode].visited = True
        return nodeTable[END_NODE].distFromSource
##Function that acts as the retracing stage of Dijkstras Alogirthm.
 #Function will continually loop untill retracing has complete, function uses (class) node.previous to retrace steps
def createPath(nodeTable, END_NODE):
        path = []
        currentNode = END_NODE
        while currentNode != INVALID_NODE:
                path.insert(0,currentNode)
                currentNode = nodeTable[currentNode].previous
        return path
##
##
if __name__ == '__main__':
        
#File Initialisation:
        NETWORK_FILE_NAME = "network.txt"       #Stores the network file name in a constant, placed here so the file is easy to change
        ROUTE_FILE_NAME = "route.txt"   #Stores the route file name in a constant, placed here so the file is easy to change
#Reading Files:
        network = populateNetwork(NETWORK_FILE_NAME)#Creates network[]
        route = findRoute(ROUTE_FILE_NAME)#Creates route[]. route stores start and end points in both str and int form

#Dijkstra Initialisation:
        currentNode = START_NODE = route[0][0]  #Stores start node in a constant which is then passed on to currentNode
        END_NODE = route[0][1]                  #Stores end node in a constant        
#Dijkstra Function Runs:       
        nodeTable = populateNodeTable(network, START_NODE)#Creates nodeTable[]
        nodeTable = calculateTentative(network, currentNode, nodeTable)#Updates nodeTable
        currentNode = returnNextNode(nodeTable)#Updates currentNode
        totalDistance = calculateShortestPath(currentNode, END_NODE, network, nodeTable) #Works out totalDistance and updates nodeTable
        path = createPath(nodeTable, END_NODE)#Creates path[]

#Max Flow Initialisation:
#Max Flow Function Runs:
        
#Outputs:
        print 'Route:', route[1][0], '->', route[1][1]
        print 'Path: ', path, '(Expected: 1,0,3,5)'
        print 'Dist: ', totalDistance, '(Expected: 4)'

        print '=DEBUG='
        print 'network:', network
        print 'route:', route
        
        
