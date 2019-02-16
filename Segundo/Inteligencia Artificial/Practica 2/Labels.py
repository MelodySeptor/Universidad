# -*- coding: utf-8 -*-
"""

@author: Bernat Gili Chillon, Pol Gomez Nogues
"""
import re
import numpy as np
import ColorNaming as cn
from skimage import color
import KMeans as km


def NIUs():
    return 1428092, 1397770


def loadGT(fileName):
    """@brief   Loads the file with groundtruth content
    
    @param  fileName  STRING    name of the file with groundtruth
    
    @return groundTruth LIST    list of tuples of ground truth data
                                (Name, [list-of-labels])
    """

    groundTruth = []
    fd = open(fileName, 'r')
    for line in fd:
        splitLine = line.split(' ')[:-1]
        labels = [''.join(sorted(filter(None,re.split('([A-Z][^A-Z]*)',l)))) for l in splitLine[1:]]
        groundTruth.append( (splitLine[0], labels) )
        
    return groundTruth


def evaluate(description, GT, options):
    """@brief   EVALUATION FUNCTION
    @param description LIST of color name lists: contain one lsit of color labels for every images tested
    @param GT LIST images to test and the real color names (see  loadGT)
    @options DICT  contains options to control metric, ...
    @return mean_score,scores mean_score FLOAT is the mean of the scores of each image
                              scores     LIST contain the similiraty between the ground truth list of color names and the obtained
    """
#########################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#########################################################
    scores = [similarityMetric(x[0], x[1][1], options) for x in zip(description, GT)]
    return sum(scores) / len(description), scores


def similarityMetric(Est, GT, options):
    """@brief   SIMILARITY METRIC
    @param Est LIST  list of color names estimated from the image ['red','green',..]
    @param GT LIST list of color names from the ground truth
    @param options DICT  contains options to control metric, ...
    @return S float similarity between label LISTs
    """
    
    if options == None:
        options = {}
    if not 'metric' in options:
        options['metric'] = 'basic'
        
#########################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#########################################################
    if options['metric'].lower() == 'basic':
        return len(np.intersect1d(Est, GT)) / float(len(Est))
    else:
        return 0
    
        
def getLabels(kmeans, options):
    """@brief   Labels all centroids of kmeans object to their color names
    
    @param  kmeans  KMeans      object of the class KMeans
    @param  options DICTIONARY  options necessary for labeling
    
    @return colors  LIST    colors labels of centroids of kmeans object
    @return ind     LIST    indexes of centroids with the same color label
    """

#########################################################
##  YOU MUST REMOVE THE REST OF THE CODE OF THIS FUNCTION
##  AND CHANGE FOR YOUR OWN CODE
#########################################################
##  remind to create composed labels if the probability of 
##  the best color label is less than  options['single_thr']
   
    def extract_color(c_prob):
        color_dict = {}
        thr = options['single_thr']
        while thr >= 0 and len(color_dict) < 2 and sum(c_prob) > 0:
            pos = c_prob.argmax()
            color_dict[cn.colors[pos]] = c_prob[pos]
            thr -= c_prob[pos]
            c_prob[pos] = 0
        return color_dict

    extr_colors = [extract_color(c) for c in kmeans.centroids]
    dual_colors = [['',''] for i in range(len(extr_colors))] 
    
    for i in range(len(extr_colors)):
        dual_colors[i][0] = max(extr_colors[i].viewitems(), key = lambda x : x[1])[0]
        extr_colors[i].pop(dual_colors[i][0], None)
        dual_colors[i][1] = max(extr_colors[i].viewitems(), key = lambda x : x[1])[0] if(len(extr_colors[i])) else ''
    
    order = sorted(enumerate(np.unique(kmeans.clusters, return_counts = True)[1]), key = lambda x : x[1], reverse = True)
    for i in [j for j in range(len(dual_colors)) if j not in [x[0] for x in order]]:
        order += [(i, 0)]
    
    ret_colors = []
    indexes = [(None, ) for i in range(len(dual_colors))]
    for i in range(len(dual_colors)):
        pos = order[i][0]
        buff = "".join(sorted([x for x in dual_colors[pos]]))
        if buff not in ret_colors:
            ret_colors += [buff]
        indexes[ret_colors.index(buff)] += (pos, )
    indexes = [x[1:] for x in indexes if x != (None,)]

    return ret_colors, indexes 


def processImage(im, options):
    """@brief   Finds the colors present on the input image
    
    @param  im      LIST    input image
    @param  options DICTIONARY  dictionary with options
    
    @return colors  LIST    colors of centroids of kmeans object
    @return indexes LIST    indexes of centroids with the same label
    @return kmeans  KMeans  object of the class KMeans
    """

#########################################################
##  YOU MUST ADAPT THE CODE IN THIS FUNCTIONS TO:
##  1- CHANGE THE IMAGE TO THE CORRESPONDING COLOR SPACE FOR KMEANS
##  2- APPLY KMEANS ACCORDING TO 'OPTIONS' PARAMETER
##  3- GET THE NAME LABELS DETECTED ON THE 11 DIMENSIONAL SPACE
#########################################################

##  1- CHANGE THE IMAGE TO THE CORRESPONDING COLOR SPACE FOR KMEANS
    if options['colorspace'].lower() == 'rgb':
        im = im
    elif options['colorspace'].lower() == 'colornaming':
        im = im # color.rgb2?????????
    elif options['colorspace'].lower() == 'lab':
        im = color.rgb2lab(im)
    elif options['colorspace'].lower() == 'hsv':
        im = color.rgb2hsv(im)

##  2- APPLY KMEANS ACCORDING TO 'OPTIONS' PARAMETER
    if options['K'] < 2: # find the best K 
        kmeans = km.KMeans(im, 0, options)
        options['K'] = kmeans.bestK()
    else:
        kmeans = km.KMeans(im, options['K'], options) 
        kmeans.run()

##  3- GET THE NAME LABELS DETECTED ON THE 11 DIMENSIONAL SPACE
    if options['colorspace'].lower() == 'rgb':
        kmeans.centroids = cn.ImColorNamingTSELabDescriptor(kmeans.centroids)
    elif options['colorspace'].lower() == 'colornaming':
        buff_shape = kmeans.centroids.shape
        kmeans.centroids = cn.ImColorNamingTSELabDescriptor(kmeans.centroids)
    elif options['colorspace'].lower() == 'lab':
        buff_shape = kmeans.centroids.shape
        kmeans.centroids = cn.ImColorNamingTSELabDescriptor(color.lab2rgb(kmeans.centroids.reshape((1,-1,3)) * 255.0).reshape(buff_shape))
    elif options['colorspace'].lower() == 'hsv':
        buff_shape = kmeans.centroids.shape
        kmeans.centroids = cn.ImColorNamingTSELabDescriptor(color.hsv2rgb(kmeans.centroids.reshape((1,-1,3))).reshape(buff_shape))


#########################################################
##  THE FOLLOWING 2 END LINES SHOULD BE KEPT UNMODIFIED
#########################################################
    colors, which = getLabels(kmeans, options)   
    return colors, which, kmeans
