import numpy as np
import skfuzzy as fuzz
from skfuzzy import control as ctrl
 
# Generate some example data
np.random.seed(0)
data = np.random.rand(100, 2)
 
# Define the number of clusters
n_clusters = 3
 
# Apply fuzzy c-means clustering
cntr, u, u0, d, jm, p, fpc = fuzz.cluster.cmeans(
    data.T, n_clusters, 2, error=0.005, maxiter=1000, init=None
)
 
# Predict cluster membership for each data point
cluster_membership = np.argmax(u, axis=0)
 
# Print the cluster centers
print('Cluster Centers:', cntr)
 
# Print the cluster membership for each data point
print('Cluster Membership:', cluster_membership)