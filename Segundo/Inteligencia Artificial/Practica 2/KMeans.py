
"""

@author: Bernat Gili Chillon, Pol Gomez Nogues
"""
import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as axes3d
from sklearn.decomposition import PCA
import sklearn.discriminant_analysis



def distance(X,C):
    """@brief   Calculates the distance between each pixel and each centroid 

    @param  X  numpy array PxD 1st set of data points (usually data points)
    @param  C  numpy array KxD 2nd set of data points (usually cluster centroids points)

    @return dist: PxK numpy array position ij is the distance between the 
    	i-th point of the first set an the j-th point of the second set
    """
#########################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#########################################################
    from scipy.spatial.distance import cdist
    return cdist(X, C, 'euclidean') # ~ 6 vegades mes rapid
    return np.array([np.sqrt(np.sum((X[i] - C)** 2, 1)) for i in range(X.shape[0])])
    

class KMeans():
    
    def __init__(self, X, K, options=None):
        """@brief   Constructor of KMeans class
        
        @param  X   LIST    input data
        @param  K   INT     number of centroids
        @param  options DICT dctionary with options
        """
        
        self._init_X(X)                                    # LIST data coordinates
        self._init_options(options)                        # DICT options
        self._init_rest(K)                                 # Initializes de rest of the object
        
#############################################################
##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
#############################################################

        
    def _init_X(self, X):
        """@brief Initialization of all pixels
        
        @param  X   LIST    list of all pixel values. Usually it will be a numpy 
                            array containing an image NxMx3

        sets X an as an array of data in vector form (PxD  where P=N*M and D=3 in the above example)
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        self.X = X.reshape((reduce(lambda x, y : x*y, X.shape[:-1]), X.shape[-1])).astype(float)
        
            
    def _init_options(self, options):
        """@brief Initialization of options in case some fields are left undefined
        
        @param  options DICT dctionary with options

			sets de options parameters
        """
        if options == None:
            options = {}
        if not 'km_init' in options:
            options['km_init'] = 'first'
        if not 'verbose' in options:
            options['verbose'] = False
        if not 'tolerance' in options:
            options['tolerance'] = 0
        if not 'max_iter' in options:
            options['max_iter'] = np.inf
        if not 'fitting' in options:
            options['fitting'] = 'Fisher'

        self.options = options
        
#############################################################
##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
#############################################################

        
    def _init_rest(self, K):
        """@brief   Initialization of the remainig data in the class.
        
        @param  options DICT dctionary with options
        """
        self.K = K                                             # INT number of clusters
        if self.K > 0:
            self._init_centroids()                             # LIST centroids coordinates
            self.old_centroids = np.empty_like(self.centroids) # LIST coordinates of centroids from previous iteration
            self.clusters = np.zeros(len(self.X))              # LIST list that assignes each element of X into a cluster
            self._cluster_points()                             # sets the first cluster assignation
        self.num_iter = 0                                      # INT current iteration
            
#############################################################
##  THIS FUNCTION CAN BE MODIFIED FROM THIS POINT, if needed
#############################################################


    def _init_centroids(self):
        """@brief Initialization of centroids
        depends on self.options['km_init']
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        if self.options['km_init'].lower() == 'first':
            self.centroids = np.array([self.X[i] for i in range(self.K)])
        elif self.options['km_init'].lower() == 'random':
            self.centroids = np.random.rand(self.K,self.X.shape[1])
        else:
            self.centroids = np.random.rand(self.K,self.X.shape[1])
        
        
    def _cluster_points(self):
        """@brief   Calculates the closest centroid of all points in X
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        self.clusters = np.argmin(distance(self.X, self.centroids), 1)


    def _get_centroids(self):
        """@brief   Calculates coordinates of centroids based on the coordinates 
                    of all the points assigned to the centroid
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        self.old_centroids = self.centroids.copy()
        for i in range(self.centroids.shape[0]):
            lst = [self.X[x[0]] for x in enumerate(self.clusters) if x[1] == i]
            self.centroids[i] = np.mean(lst if len(lst) else [float(0)], 0) 


    def _converges(self):
        """@brief   Checks if there is a difference between current and old centroids
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        return np.isclose(self.old_centroids, self.centroids, self.options['tolerance'], equal_nan = True).all()
       
     
    def _iterate(self, show_first_time=True):
        """@brief   One iteration of K-Means algorithm. This method should 
                    reassigne all the points from X to their closest centroids
                    and based on that, calculate the new position of centroids.
        """
        self.num_iter += 1
        self._cluster_points()
        self._get_centroids()
        if self.options['verbose']:
            self.plot(show_first_time)


    def run(self):
        """@brief   Runs K-Means algorithm until it converges or until the number
                    of iterations is smaller than the maximum number of iterations.=
        """
        if self.K==0:
            self.bestK()
            return        
        
        self._iterate(True)
        self.options['max_iter'] = np.inf
        if self.options['max_iter'] > self.num_iter:
            while not self._converges() :
                self._iterate(False)
      
      
    def bestK(self):
        """@brief   Runs K-Means multiple times to find the best K for the current 
                    data given the 'fitting' method. In cas of Fisher elbow method 
                    is recommended.
                    
                    at the end, self.centroids and self.clusters contains the 
                    information for the best K. NO need to rerun KMeans.
           @return B is the best K found.
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################
        best_fit = []
        for i in range(1, 10): # limit to... ?
            self = KMeans(self.X, i, self.options)
            self.run()        
            best_fit += [self.fitting()]
        return min(enumerate(best_fit), key = lambda x : x[1])[0]

        
    def fitting(self):
        """@brief  return a value describing how well the current kmeans fits the data
        """
#######################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#######################################################

        if self.options['fitting'].lower() == 'fisher':
            
            uk = [(1 / float(self.X.shape[0])) * sum([self.X[i] for i in self.clusters if i == n]) for n in range(self.K)]
            u = (1 / float(self.X.shape[0])) * sum([self.X[i] for i in range(self.X.shape[0])])
            cluster_count = [float(len([i for i in self.clusters if i == n])) for n in range(self.K)]

            between_var = (1 / float(self.K)) * sum([(1 / float(cluster_count[n])) * sum([np.sqrt((self.X[i] - uk[n]) ** 2) for i in range(self.X.shape[0]) if i == n]) for n in range(self.K)])
            within_var = (1 / float(self.K)) * sum([np.sqrt((uk[n] - u) ** 2) for n in range(self.K)])
            
            return within_var / between_var     
        else:
            return np.random.rand(1)


    def plot(self, first_time=True):
        """@brief   Plots the results
        """

        #markersshape = 'ov^<>1234sp*hH+xDd'	
        markerscolor = 'bgrcmybgrcmybgrcmyk'
        if first_time:
            plt.gcf().add_subplot(111, projection='3d')
            plt.ion()
            plt.show()

        if self.X.shape[1]>3:
            if not hasattr(self, 'pca'):
                self.pca = PCA(n_components=3)
                self.pca.fit(self.X)
            Xt = self.pca.transform(self.X)
            Ct = self.pca.transform(self.centroids)
        else:
            Xt=self.X
            Ct=self.centroids

        for k in range(self.K):
            plt.gca().plot(Xt[self.clusters==k,0], Xt[self.clusters==k,1], Xt[self.clusters==k,2], '.'+markerscolor[k])
            plt.gca().plot(Ct[k,0:1], Ct[k,1:2], Ct[k,2:3], 'o'+'k',markersize=12)

        if first_time:
            plt.xlabel('dim 1')
            plt.ylabel('dim 2')
            plt.gca().set_zlabel('dim 3')
        plt.draw()
        plt.pause(0.01)