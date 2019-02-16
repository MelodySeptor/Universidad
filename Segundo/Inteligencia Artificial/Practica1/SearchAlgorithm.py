# This file contains all the required routines to make an A* search algorithm.
#
__authors__='Bernat Gili Chillon, Pol Gomez Nogues'
__group__='DX18.02'
# _________________________________________________________________________________________
# Intel.ligencia Artificial
# Grau en Enginyeria Informatica
# Curs 2016- 2017
# Universitat Autonoma de Barcelona
# _______________________________________________________________________________________

from SubwayMap import *
from collections import defaultdict
from math import sqrt


class Node:
    # __init__ Constructor of Node Class.
    def __init__(self, station, father):
        """
        __init__: 	Constructor of the Node class
        :param
                - station: STATION information of the Station of this Node
                - father: NODE (see Node definition) of his father
        """
        
        self.station = station      # STATION information of the Station of this Node
        self.g = 0                  # REAL cost - depending on the type of preference -
                                    # to get from the origin to this Node
        self.h = 0                  # REAL heuristic value to get from the origin to this Node
        self.f = 0                  # REAL evaluate function
        if father == None:
            self.parentsID = []
        else:
            self.parentsID = [father.station.id]
            self.parentsID.extend(father.parentsID)         # TUPLE OF NODES (from the origin to its father)
        self.father = father        # NODE pointer to his father
        self.time = 0               # REAL time required to get from the origin to this Node
                                    # [optional] Only useful for GUI
        self.num_stopStation = 0    # INTEGER number of stops stations made from the origin to this Node
                                    # [optional] Only useful for GUI
        self.walk = 0               # REAL distance made from the origin to this Node
                                    # [optional] Only useful for GUI
        self.transfers = 0          # INTEGER number of transfers made from the origin to this Node
                                    # [optional] Only useful for GUI

    def setEvaluation(self):
        """
        setEvaluation: 	Calculates the Evaluation Function. Actualizes .f value
       
        """
        self.f = self.g + self.h

    def setHeuristic(self, typePreference, node_destination, city):
        """"
        setHeuristic: 	Calculates the heuristic depending on the preference selected
        :params
                - typePreference: INTEGER Value to indicate the preference selected: 
                                0 - Null Heuristic
                                1 - minimum Time
                                2 - minimum Distance 
                                3 - minimum Transfers
                                4 - minimum Stops
                - node_destination: PATH of the destination station
                - city: CITYINFO with the information of the city (see CityInfo class definition)
        """
        def euclidean_distance(st1, st2):
            x = st1.x - st2.x
            y = st1.y - st2.y
            return sqrt(x * x + y * y)

        if(typePreference == 0): #null
            return 
        elif(typePreference == 1): #minium time
            self.h = euclidean_distance(node_destination.station, self.station) / city.max_velocity
        elif(typePreference == 2): #minium distance
            self.h = euclidean_distance(node_destination.station, self.station)
        elif(typePreference == 3): #minium transfers
            self.h = int(node_destination.station.line != self.station.line)
        elif(typePreference == 4): #minium stops
            self.h = int(node_destination.station.name != self.station.name)
        else: 
            #raise ValueError("typePreference out of limits (0, ..., 4)");
            pass

    def setRealCost(self, costTable):
        """
        setRealCost: 	Calculates the real cost depending on the preference selected
        :params
                 - costTable: DICTIONARY. Relates each station with their adjacency an their real cost. NOTE that this
                             cost can be in terms of any preference.
        """
        if(not costTable.has_key(self.station.id) or not costTable[self.station.id].has_key(self.father.station.id)):
            self.g = 0
        else:                                                                       
            self.g = 0 if self.father is None else self.father.g + costTable[self.station.id][self.father.station.id]


def Expand(fatherNode, stationList, typePreference, node_destination, costTable, city):
    """
    Expand: It expands a node and returns the list of connected stations (childrenList)
    :params
            - fatherNode: NODE of the current node that should be expanded
            - stationList: LIST of the stations of a city. (- id, destinationDic, name, line, x, y -)
            - typePreference: INTEGER Value to indicate the preference selected:
                            0 - Null Heuristic
                            1 - minimum Time
                            2 - minimum Distance
                            3 - minimum Transfers
                            4 - minimum Stops
            - node_destination: NODE (see Node definition) of the destination
            - costTable: DICTIONARY. Relates each station with their adjacency an their real cost. NOTE that this
                            cost can be in terms of any preference.
            - city: CITYINFO with the information of the city (see CityInfo class definition)
    :returns
            - childrenList:  LIST of the set of child Nodes for this current node (fatherNode)

    """

    childs = [Node(stationList[id-1], fatherNode) for id in city.adjacency[fatherNode.station.id].viewkeys()]

    for node in childs:

        node.setHeuristic(typePreference, node_destination, city) # h
        node.setRealCost(costTable) # g
        node.setEvaluation() # f = g + h

        node.time = node.station.destinationDic[fatherNode.station.id]
        node.transfers = int(node.station.line == fatherNode.station.line)
        node.num_stopStation = int(node.station.name == fatherNode.station.name)
        node.walk = 0 if node.station.name == fatherNode.station.name else city.velocity_lines[fatherNode.station.line -1] * node.time # velocity = distance / time -> distance = velocity * time

    return childs

def RemoveCycles(childrenList):
    """
        RemoveCycles: It removes from childrenList the set of childrens that include some cycles in their path.
        :params
                - childrenList: LIST of the set of child Nodes for a certain Node
        :returns
                - listWithoutCycles:  LIST of the set of child Nodes for a certain Node which not includes cycles
    """
    return [child for child in childrenList if child.station.id not in child.parentsID]
    
def RemoveRedundantPaths(childrenList, nodeList, partialCostTable):
    """
        RemoveRedundantPaths:   It removes the Redundant Paths. They are not optimal solution!
                                If a node is visited and have a lower g in this moment, TCP is updated.
                                In case of having a higher value, we should remove this child.
                                If a node is not yet visited, we should include to the TCP.
        :params
                - childrenList: LIST of NODES, set of childs that should be studied if they contain rendundant path
                                or not.
                - nodeList : LIST of NODES to be visited
                - partialCostTable: DICTIONARY of the minimum g to get each key (Node) from the origin Node
        :returns
                - childrenList: LIST of NODES, set of childs without rendundant path.
                - nodeList: LIST of NODES to be visited updated (without redundant paths)
                - partialCostTable: DICTIONARY of the minimum g to get each key (Node) from the origin Node (updated)
    """
    for node in childrenList:
        if not partialCostTable.has_key(node.station.id):
            partialCostTable[node.station.id] = node.g
        elif node.g < partialCostTable[node.station.id]:
            partialCostTable[node.station.id] = node.g
            nodeList = [x for x in nodeList if x.station.id != node.station.id]
        elif node.g > partialCostTable[node.station.id]:
            childrenList = [x for x in childrenList if x != node]
    return childrenList, nodeList, partialCostTable

def sorted_insertion(nodeList,childrenList):
    """ Sorted_insertion: 	It inserts each of the elements of childrenList into the nodeList.
						    The insertion must be sorted depending on the evaluation function value.
							
	    : params:
		    - nodeList : LIST of NODES to be visited
		    - childrenList: LIST of NODES, set of childs that should be studied if they contain rendundant path
                                or not.
	    :returns
                - nodeList: sorted LIST of NODES to be visited updated with the childrenList included 
    """
    return sorted(nodeList + childrenList, key = lambda x : x.f)

def setCostTable(typePreference, stationList, city):
    """
    setCostTable :      Real cost of a travel.
    :param
            - typePreference: INTEGER Value to indicate the preference selected:
                                0 - Adjacency
                                1 - minimum Time
                                2 - minimum Distance
                                3 - minimum Transfers
                                4 - minimum Stops
            - stationList: LIST of the stations of a city. (- id, destinationDic, name, line, x, y -)
            - city: CITYINFO with the information of the city (see CityInfo class definition)
    :return:
            - costTable: DICTIONARY. Relates each station with their adjacency an their g, depending on the
                                 type of Preference Selected.
    """
    def make_cost_table(cost_table, func):
        for st in stationList:
            for dest_st in [stationList[pos-1] for pos in city.adjacency[st.id].keys()]:
                value = func(st, dest_st)
                cost_table[st.id][dest_st.id] = value
                cost_table[dest_st.id][st.id] = value

    cost_table = defaultdict(dict)

    if typePreference == 0: # null
        pass
    elif typePreference == 1: # minium time
        make_cost_table(cost_table, lambda st, dest_st : st.destinationDic[dest_st.id])
    elif typePreference == 2: # minium distance
        make_cost_table(cost_table, lambda st, dest_st : 0 if st.name == dest_st.name else city.velocity_lines[st.line -1] * st.destinationDic[dest_st.id]) # vel * time
    elif typePreference == 3: # minium transfers
        make_cost_table(cost_table, lambda st, dest_st : int(st.line != dest_st.line))
    elif typePreference == 4: # minium stops
        make_cost_table(cost_table, lambda st, dest_st : int(st.line == dest_st.line))
    else:
        pass
        #raise ValueError("typePreference out of limits (0, ..., 4)");

    return cost_table

def coord2station(coord, stationList):
    """
    coord2station :      From coordinates, it searches the closest station.
    :param
            - coord:  LIST of two REAL values, which refer to the coordinates of a point in the city.
            - stationList: LIST of the stations of a city. (- id, destinationDic, name, line, x, y -)

    :return:
            - possible_origins: List of the Indexes of the stationList structure, which corresponds to the closest
            station
    """
    #return [st.id for st in stationList if st.x == coord[0] and st.y == coord[1]]    
    #most dumb algorythm in this file
    def euclidian_distance(coord1, coord2):
        x = coord1[0] - coord2[0]
        y = coord1[1] - coord2[1]
        return sqrt(x * x + y * y)
    st_list = [(euclidian_distance((st.x, st.y), coord), st.id) for st in stationList]
    st_list = [st[1] for st in st_list if st[0] < 20.0]
    st_list = [st for st in range(len(stationList)) if stationList[st].id in st_list]
    return st_list if len(st_list) else [0]

def AstarAlgorithm(stationList, coord_origin, coord_destination, typePreference, city, flag_redundants):
    """
    AstarAlgorithm: main function. It is the connection between the GUI and the AStar search code.
    INPUTS:
            - stationList: LIST of the stations of a city. (- id, name, destinationDic, line, x, y -)
            - coord_origin: TUPLE of two values referring to the origin coordinates
            - coord_destination: TUPLE of two values referring to the destination coordinates
            - typePreference: INTEGER Value to indicate the preference selected:
                                0 - Adjacency
                                1 - minimum Time
                                2 - minimum Distance
                                3 - minimum Transfers
                                4 - minimum Stops
            - city: CITYINFO with the information of the city (see CityInfo class definition)
            - flag_redundants: [0/1]. Flag to indicate if the algorithm has to remove the redundant paths (1) or not (0)

    OUTPUTS:
            - time: REAL total required time to make the route
            - distance: REAL total distance made in the route
            - transfers: INTEGER total transfers made in the route
            - stopStations: INTEGER total stops made in the route
            - num_expanded_nodes: INTEGER total expanded nodes to get the optimal path
            - depth: INTEGER depth of the solution
            - visitedNodes: LIST of INTEGERS, IDs of the stations corresponding to the visited nodes
            - idsOptimalPath: LIST of INTEGERS, IDs of the stations corresponding to the optimal path
            (from origin to destination)
            - min_distance_origin: REAL the distance of the origin_coordinates to the closest station
            - min_distance_destination: REAL the distance of the destination_coordinates to the closest station

            EXAMPLE:
            return optimalPath.time, optimalPath.walk, optimalPath.transfers,optimalPath.num_stopStation,
            len(expandedList), len(idsOptimalPath), visitedNodes, idsOptimalPath, min_distance_origin,
            min_distance_destination
    """
    
    def euclidean_distance(st, coord):
        x = st.x - coord[0]
        y = st.y - coord[1]
        return sqrt(x * x + y * y)
    def ordered_insertion(E, last_path, list_paths, func): # sorted_insertion() is not good for this, and sorted() gives type problems with the lambda function
        for node in E:
            i = 0
            for i in range(len(list_paths)):
                if func(list_paths[i][0]) > func(node):
                    break
            list_paths.insert(i, [node] + last_path)
        return list_paths

    typePreference = int(typePreference) # cost table WON'T be created without this because you're passing a fck%&#$! string instead of an int, BUT it will give different results than the pdf

    node_end = Node(stationList[coord2station(coord_destination, stationList)[0]], None)
    node_begin = Node(stationList[coord2station(coord_origin, stationList)[0]], None)
    cost_table = setCostTable(typePreference, stationList, city)

    list_paths = [[node_begin]]
    visited_nodes = []
    partial_cost_table = {}
    min_distance_origin = euclidean_distance(node_begin.station, coord_origin)
    min_distance_destination = euclidean_distance(node_end.station, coord_destination)

    while len(list_paths) and list_paths[0][0].station.id != node_end.station.id:
        C = list_paths[0]
        visited_nodes += [C[0].station.id]
        E = Expand(C[0], stationList, typePreference, node_end, cost_table, city)
        E = RemoveCycles(E)
        if flag_redundants == 1:
            E, ignored, partial_cost_table = RemoveRedundantPaths(E, list_paths[0] if len(list_paths) else [], partial_cost_table) 
        list_paths = ordered_insertion(E, list_paths[0], list_paths[1:], lambda x : x.f)
    
    ids_optimal_path = [node.station.id for node in reversed(list_paths[0])]
    time = sum([x.time for x in list_paths[0]])
    walk = sum([x.walk for x in list_paths[0]])
    transfers = sum([x.transfers for x in list_paths[0]])
    num_stopStation = sum([x.num_stopStation for x in list_paths[0]])
    
    return time, walk, \
           transfers, num_stopStation, \
           len(visited_nodes), len(list_paths[0])-1, \
           visited_nodes, ids_optimal_path, \
           min_distance_origin, min_distance_destination









