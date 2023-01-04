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
    min = X.min

if __name__ == "__main__":
	# load the dataset
	dataset = loadCSV('./python/ml/basic/logr/dataset1.csv')
	X = dataset[:,0:-1]
	Y = dataset[:, -1:]
	X = normalize(X)
    