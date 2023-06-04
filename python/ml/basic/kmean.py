import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs


X,y = make_blobs(n_samples = 500,n_features = 2,centers = 3,random_state = 23)
  
fig = plt.figure(0)
plt.grid(True)
plt.scatter(X[:,0],X[:,1])
plt.show()

k = 3
clusters = {}
np.random.seed(23)

for inx in range(k):
    center = 2 * (2 * np.random.random((X.shape[1])) - 1)
    points = []
    cluster = {
        'center' : center,
        'points'  : []
    }
    clusters[inx] = cluster
clusters

plt.scatter(X[:,0],X[:,1])
plt.grid(True)
for i in clusters:
    center = clusters[i]['center']
    plt.scatter(center[0],center[1],marker = '*',c = 'red')
plt.show()


def distance(p1,p2):
    return np.sqrt(np.sum((p1-p2)**2))



#Implementing E step 
def assign_clusters(X, clusters):
    for idx in range(X.shape[0]):
        dist = []
          
        curr_x = X[idx]
          
        for i in range(k):
            dis = distance(curr_x,clusters[i]['center'])
            dist.append(dis)
        curr_cluster = np.argmin(dist)
        clusters[curr_cluster]['points'].append(curr_x)
    return clusters


#Implementing the M-Step
def update_clusters(X, clusters):
    for i in range(k):
        points = np.array(clusters[i]['points'])
        if points.shape[0] > 0:
            new_center = points.mean(axis =0)
            clusters[i]['center'] = new_center
              
            clusters[i]['points'] = []
    return clusters


def pred_cluster(X, clusters):
    '''
    预测数据点的集群
    '''
    pred = []
    for i in range(X.shape[0]):
        dist = []
        for j in range(k):
            dist.append(distance(X[i],clusters[j]['center']))
        pred.append(np.argmin(dist))
    return pred

# 分配、更新和预测聚类中心
clusters = assign_clusters(X,clusters)
clusters = update_clusters(X,clusters)
pred = pred_cluster(X,clusters)


# 绘制数据点及其预测的聚类中心
plt.scatter(X[:,0],X[:,1],c = pred)
for i in clusters:
    center = clusters[i]['center']
    plt.scatter(center[0],center[1],marker = '^',c = 'red')
plt.show()


from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters = 3, random_state = 2)
kmeans.fit(X)

kmeans.cluster_centers_

pred2 = kmeans.fit_predict(X)
pred2
plt.subplot(1,2,1)
plt.scatter(X[:,0],X[:,1],c = pred)
plt.subplot(1,2,2)
plt.scatter(X[:,0],X[:,1],c = pred2)
plt.show()