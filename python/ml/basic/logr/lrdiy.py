import csv
import numpy as np
import matplotlib.pyplot as plt


def loadCSV(filename):
	'''
	function to load dataset
	'''
	with open(filename,"r") as csvfile:
		lines = csv.reader(csvfile)
		dataset = list(lines)
		for i in range(len(dataset)):
			dataset[i] = [float(x) for x in dataset[i]]	
	return np.array(dataset)



def normalize(X):
	'''
	function to normalize feature matrix, X
	'''
	mins = np.min(X, axis=0)
	maxs = np.max(X, axis=0)
	norm_x = 1 - (maxs - X)/(maxs-mins)
	return norm_x

def logistic_func(beta, X):
	return 1 / (1 + np.exp(np.dot(X, beta.T)))


def grad_desc(beta, X , Y):
    l = 0.01
    logic = logistic_func(beta, X)
    


if __name__ == "__main__":
	# load the dataset
	dataset = loadCSV('./python/ml/basic/logr/dataset1.csv')

	# normalizing feature matrix
	X = normalize(dataset[:,0:-1])

	# response vector	
	Y = dataset[:, -1:]
    
	# stacking columns with all ones in feature matrix
	# add coef of x0
	X = np.hstack((np.matrix(np.ones(X.shape[0])).T, X))

	# The initial of beta for x
	beta = np.matrix(np.zeros(X.shape[1]))
 	
	grad_desc(beta, X , Y)