#!/usr/bin/env python

"""
If you dont put your personal data here, the submission will not be accepted
Group    : 421
Subgroup : 02
Name 1: Pol
NIU  1: 1397770
Name 2: Josep
NIU  2: 1397823
Remarks:
"""


import functools 
import sys

@functools.total_ordering
#Generates all comparisson operators for a class if equality and
#grater is implemeted
class DCNode(object):
    """Class that exposes 3 properties: left, right, and data.
    The class implements also the logic needed to experimentaly measure 
    complexity and break infinite loops.
    """
    __complexity__=0#static variable counting all access to the data
    @staticmethod
    def __updateComplexity__():
        DCNode.__complexity__+=1 #imcrement global acces counter
        if DCNode.__complexity__>1000**2:#if we have more than 1,000,000 access
            raise Exception('Limit of 1,000,000 exceded')#we raise an exception

    @staticmethod
    def resetComplexity():#reseting variable
        DCNode.__complexity__=0

    def __init__(self,k):
        """Generates a node.
        
        The node is constructed as if the list has a single element
        
        Args:
            k (object): the actual value that will be stored in the node
        """
        DCNode.__updateComplexity__()
        self.__right = self.__left = self
        self.__data = k

    @property
    def right(self):
        DCNode.__updateComplexity__()
        return self.__right

    @property
    def left(self):
        DCNode.__updateComplexity__()
        return self.__left

    @property
    def data(self):
        DCNode.__updateComplexity__()
        return self.__data

    def __str__(self):
        DCNode.__updateComplexity__()
        return str(self.__data) + (' <-> '*(self.__right!=self))

    @right.setter
    def right(self, rn):
        DCNode.__updateComplexity__()
        self.__right = rn

    @left.setter
    def left(self, ln):
        DCNode.__updateComplexity__()
        self.__left = ln

    @data.setter
    def data(self, kn):
        DCNode.__updateComplexity__()
        self.__data = kn

    def __lt__(self,dcn):
        """Implements operator <

        Args:
            self (DCNode):
            dcn (DCNode):

        return:
            True if self.data < dcn.data
        """
        DCNode.__updateComplexity__()
        return self.__data < dcn.__data

    def __eq__(self,dcn):
        """Implements operator ==

        Args:
            self (DCNode):
            dcn (DCNode):

        return:
            True if self.data == dcn.data
        """
        DCNode.__updateComplexity__()
        return dcn and (self.__data == dcn.__data)


class DCList(object):
    def __init__(self,dataList=[]):
        """Generates a Double-linked Circular List.

        Args:
            dataList (list): the list will be initialised so that __head 
            contains the first element of the list
        """
        self.__head = None
        for data in dataList:
            self.insertBefore(data)

    @property
    def min(self):
        """Provides the minimum datum in the list.
        Complexity O(n)
        """
        #Variables
        dade = self.__head.data
        nextNod = self.__head.right

        #Vamos recorriendo y asignando el valor minimo
        while (nextNod != self.__head):
            
            if(nextNod.data < dade):
                dade = nextNod.data
                
            nextNod = nextNod.right

        #Retornamos valor min
        return dade  

    @property
    def length(self):
        """Counts the size of the list.
        Complexity O(n)
        """

        #Comprobamos que el inicial este vacio, si lo esta retorna 0 ya que la lista esta empty
        if self.__head == None:
            return 0

        #Declaracion de aux y sumatorio
        nextNod = self.__head.right
        suma = 0

        #While que recorre lista sumando
        while (nextNode != self.__head):
            suma += 1
            nextNode = nextNode.right

        #Retorna suma
        return suma 

    @property
    def head(self):
        return self.__head

    @property
    def tail(self):
        return self.__head.left

    @property
    def empty(self):
        return self.length == 0


    def insertAfter(self ,data, after=None):
        """Inserts a new node after the given list node.
        
        Args:
            data (object): any python object that has == and < operators 
            defined
            after (DCNode): the list node after which the new node will be 
            inserted. If after is not specified, self.__head will be used.
        """
        #Comprueba si head esta vacio, si lo esta asigna todo al head
        if(self.__head==None):
            self.__head=DCNode(data)
            self.__head.right=self.__head
            self.__head.left=self.__head

        else:
            #Mira si after esta empty
            if(after!=None):
                nextNode=after
                
            else:             
                nextNode=self.__head
                
            #Fa les conexiones pertinents del nou node
            aux = nextNode.right
            nextNode.right = DCNode(data)
            aux.left = nextNode.right

            #Interconcta tota la llista
            nextNode.right.left = nextNode
            nextNode.right.right = aux

        #Retorna la lista nueva
        return self

    def insertBefore(self,data,before=None):
        """Inserts a new node before the given list node.

        Args:
            data (object): any python object that has == and < operators 
            defined
            before (DCNode): the list node before which the new node will be 
            inserted. If before is not specified, self.__head will be used.
        """
        ####igual que adalt
        ##Comproba que cabeza estigui buit, si ho esta asigna el nou node com a
        ##self.__head
        if(self.__head is None):
            self.__head = DCNode(data)
            self.__head.left = self.__head
            self.__head.right = self.__head
            
        else:
            #Comproba que el node a asignar sigui none
            if(before==None):
                nodeAux=self.__head
                
            else:
                nodeAux=before
                
            #Crea el nou node y asigna    
            dataN = nodeAux.left
            nodeAux.left = DCNode(data)
            dataN.right = nodeAux.left

            #Estableix conexions
            nodeAux.left.left = dataN
            nodeAux.left.right = nodeAux

        #Retorna la llista nova    
        return self

    def rotate(self,pos=1):
        """Moves the head of the list.
        
        Args:
            pos (int): the amount of nodes to move. Positive values move the
            head clockwise (right) and negative values counter-clockwise (left).
        """
        
        #Si pos es positiu gira cap a dreta
        if(pos>0):
            for itera in range(0, pos):
                self.__head = self.__head.right

        #Si pos es negatiu gira esquerra
        elif(pos<0):
            for itera in range(pos, 0):
                self.__head = self.__head.left
                
        #Retorna llista girada
        #No es necesari el 0, ja que es queda a la mateixa posicio
        return self

    def remove(self,index=0):
        """Removes a list node.
        
        Args:
            index (int): an integer identifiying the element to be removed.
            The node to removed is identified by _getIndexPtr
        """

        #Comandos de control
        nodeAux = self._getIndexPtr(index)
        nodeAux.right.left = nodeAux.left
        nodeAux.left.right = nodeAux.right

        #Mira si es el elemento que nos interesa, si lo es lo pone a None
        if(nodeAux is self.__head):
            self.__head = self.__head.right if nodeAux.right is not self.__head else None

        #Retorna la nueva lista
        return self

    def __str__(self):
        """Returns a string with a drawing of the list
        """
        if self.__head==None:
            return '(\)'
        if self.length==1:
            return ' +-> '+str(self.__head)+' <-+\n +---'+('-'*len(str(self.__head)))+'---+'
        res = str(self.__head)
        ptr = self.__head.right
        while ptr != self.__head:
            res+=str(ptr)
            ptr=ptr.right
        res='\n +-> '+res[:-5]+' <-+\n +'+(len(res)*'-')+'-+\n'
        return res

    def __repr__(self):
        """Returns a string with the python expression generating a DCList
        Identical to self.
        """
        if self.__head==None:
            dataList=[]
        else:
            dataList=[self.__head.data]
            ptr=self.__head.right
            while ptr != self.__head:
                dataList.append(ptr.data)
                ptr=ptr.right
        return str(self.__class__)[8:-2]+'('+str(dataList)+')'

    def _getIndexPtr(self,index):
        """Returns a DCNode at a specific distance from the list head.
        If the list is empty an exception is thrown.
            
        Args:
            index (int): the number of nodes away from the head. If index is
            positive the list is traversed towards the right, if negative
            the list is traversed towards the left.
        """
        #Nodo auxiliar con la cabesa
        nodeAux=self.__head

        #Mira cap a on es el index i rota segons si es positiu o negatiu
        if(index>0):
            for iterad in range(0, index):
                nodeAux=nodeAux.right
        elif(index<0):
            for iterad in range(0, index):
                nodeAux=nodeAux.left

        #Retorna el node
        return nodeAux

    def index(self,value):
        """Returns the position of the first node towards the right that has
        data == value. If the list is empty or value doesn't exist in the 
        list, an exception is thrown
        
        Args:
            value (object)
        """
        #Variables
        nextNod = self.__head.right
        pos =0
        if(self.__head.data!=value):
            
        #Vamos recorriendo y asignando el valor minimo
            while ((nextNod != self.__head)and(nextNod.data!=value)):               
                pos +=1
                nextNod = nextNod.right
            pos +=1
            
        return pos


    def merge(self, dcList):
        """Merges two lists into a single one. So the the following is always 
        True:
        repr(DCList([1,2,3]).merge([4,5,6]))==repr(DCList([1,2,3,4,5,6]))

        Args:
            dcList (DCList): the list to be merged with self. dcList will be
            incosistent after the score.
        """
        return self

    def __getitem__(self,index):
        """Implements the [] operator for reading.
        Complexinty O(abs(index))
        
        There are no boundaries, the 10th position of a list with three 
        elements will return the data of the right to the head in the head.
        
        Args:
            index (int): The position to be accessed. The node to removed is
            identified by _getIndexPtr.
        """
        return self._getIndexPtr(index).data

    def __setitem__(self,key,value):
        """Implements the [] operator for writing.
        Complexinty O(abs(key))
        
        There are no boundaries, the 10th position of a list with three 
        elements will affect the data of the right to the head in the head.
        
        Args:
            index (int): The position to be accessed. The node to removed is
            identified by _getIndexPtr.
            value (object): the value that will be assigned.
        """
        self._getIndexPtr(key).data=value



alphabet='abcdefghijklmnopqrstuvwxyz '
invAlphabet={alphabet[k]:k for k in range(len('abcdefghijklmnopqrstuvwxyz '))}

class Enigma:
    """This class implements the principal of the enigma cryptographioc machine
    """
    ROTORS_LIST=[[21,23,2,0,6,11,5,16,24,20,1,26,15,13,25,7,10,22,3,17,14,4,12,19,18,8,9],
                 [10,7,25,3,16,19,17,5,21,13,11,24,15,0,20,22,6,23,2,9,1,26,18,8,14,12,4],
                 [18,15,26,0,6,10,14,7,11,16,3,9,22,24,17,25,13,23,19,12,2,5,20,8,4,1,21],
                 [23,9,5,17,7,14,18,25,22,26,10,20,2,8,3,6,13,24,12,15,11,4,21,1,16,0,19],
                 [22,10,24,21,8,16,12,1,20,9,3,15,19,2,4,0,11,26,25,6,13,5,14,23,7,17,18]]

    def __init__(self,activeRotors=[0],initialKeys=[0]):
        """Creates an enigma machine. And sets the initial state of the 
        rotors
            
        Args:
            activeRotors (list): python array with 3 integers between 0 and 4
            initialKeys (list): python array with 3 integers containing the 
            initial offset of the rotors
        """
        self.setRotorsAndKeys(activeRotors,initialKeys)

    def setRotorsAndKeys(self,activeRototrs,presharedKeys):
        """Sets the initial state of the rotors.
            
        Args:
            activeRotors (list): python array with 3 integers between 0 and 4
            initialKeys (list): python array with 3 integers containing the 
            initial offset of the rotors
        """
        self.__rotorCounter=0
        self.__rotors=[]
        for rotorId in activeRototrs:
            forward=Enigma.ROTORS_LIST[rotorId]
            backward=[0]*len(forward)
            for k in range(len(forward)):
                backward[forward[k]]=forward.index(k)
            self.__rotors.append(DCList(forward))
        for rotorPos in range(len(self.__rotors)):
            self.__rotors[rotorPos].rotate(presharedKeys[rotorPos])

    def __incrementDisks__(self,offset=1):
        """Implements the rotor clock-like rotation that changes the state 
        of the machine after every letter.
        
        Args:
            offset (int): the number of steps to rotate the fastes rotor 
            after every letter ciphering/deciphering.
        """
        self.__rotorCounter+=offset
        incrementCheck=1
        for k in range(len(self.__rotors)):
            self.__rotors[k].rotate(self.__rotorCounter%incrementCheck ==0)
            incrementCheck*=len(alphabet)

    def getCipheredLetter(self,letter):
        """Implements the forward pass of a single letter through all the rotors
        
        Args:
            letter (int): a number in [0,27) representing the input symbol
        
        return:
            int: a number in [0,27) representing the output symbol
        """
        return ''

    def getDecipheredLetter(self,letter):
        """Implements the backward pass of a single letter through all the rotors
        
        Args:
            letter (int): a number in [0,27) representing the ciphered symbol
        
        return:
            int: a number in [0,27) representing the deciphered symbol
        """
        return ''

    def getCiphered(self,text):
        """Encodes a string with text to a cipher.
        
        Args:
            text (str): the text to be ciphered. All symbols outsibe the 
            symbol alphabet are ignored.
        
        return:
            str: A string with the cipher.
        """
        res=''
        for letter in [let for let in text.lower() if let in alphabet]:
            res+=self.getCipheredLetter(letter)
        return res

    def getDeciphered(self,cipher):
        """Decodes a string with ciphered-text to the initial message.
        
        Args:
            text (str): the ciphered text to be deciphered.
        
        return:
            str: A string with the deciphered text.
        """
        res=''
        for letter in [let for let in cipher.lower() if let in alphabet]:
            res+=self.getDecipheredLetter(letter)
        return res


def main():
    keys=[0,0,0];rotors=[2,0,1]
    if len(sys.argv)==1 or sys.argv[1] not in ['cipher','decipher']:
        print sys.argv[0]+" usage:\n\n\t"+sys.argv[0]+" cipher|decipher [inputfile] [outputfile] [(rotors) (keys)]"
        print "\nIf input or output files are not specified, standard input and output are used."
        print "rotors and keys must be a single string parameter with a python expression"
        sys.exit(0)
    fout=sys.stdout
    fin=sys.stdin
    if len(sys.argv)>2:
        if sys.argv[2]!='stdin':
            fin=open(sys.argv[1])
    if len(sys.argv)>3:
        if sys.argv[3]!='stdout':
            fout=open(sys.argv[2],'w')
    if len(sys.argv)==5:
        keys,rotors=eval(sys.argv[4])
    e = Enigma(keys,rotors)
    text=''.join([ch if ch in alphabet else ' ' for ch in fin.read()])
    if sys.argv[1]=='cipher':
        fout.write(e.getCiphered(text.lower().strip()))
    else:#sys.argv[1]=='decipher'
        fout.write(e.getDeciphered(text.lower().strip()))
    fout.write('\n')

if __name__=='__main__':
    main()
