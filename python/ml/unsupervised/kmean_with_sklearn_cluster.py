
# import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from sklearn.datasets import load_iris
from sklearn.cluster import KMeans

# Load the Dataset
X, y = load_iris(return_X_y=True)


# Find optimum number of cluster
# 找到将数据分成的理想组数是任何无监督算法的基本阶段。计算理想 k 值的最常用技术之一是弯头法。
# Finding the ideal number of groups to divide the data into is a basic stage
# in any unsupervised algorithm. One of the most common techniques for figuring
# out this ideal value of k is the elbow approach.
sse = [] #SUM OF SQUARED ERROR
for k in range(1,11):
    km = KMeans(n_clusters=k, random_state=2)
    km.fit(X)
    sse.append(km.inertia_)

# Igore seaborn, install seaborn fail
# sns.set_style("whitegrid")
# g=sns.lineplot(x=range(1,11), y=sse)
  
# g.set(xlabel ="Number of cluster (k)", 
#       ylabel = "Sum Squared Error", 
#       title ='Elbow Method')
  
# plt.show()

kmeans = KMeans(n_clusters = 3, random_state = 2)
kmeans.fit(X)

kmeans.cluster_centers_

pred = kmeans.fit_predict(X)
pred


plt.figure(figsize=(12,5))
plt.subplot(1,2,1)
plt.scatter(X[:,0],X[:,1],c = pred, cmap=cm.Accent)
plt.grid(True)
for center in kmeans.cluster_centers_:
    center = center[:2]
    plt.scatter(center[0],center[1],marker = '^',c = 'red')
plt.xlabel("petal length (cm)")
plt.ylabel("petal width (cm)")
      
plt.subplot(1,2,2)   
plt.scatter(X[:,2],X[:,3],c = pred, cmap=cm.Accent)
plt.grid(True)
for center in kmeans.cluster_centers_:
    center = center[2:4]
    plt.scatter(center[0],center[1],marker = '^',c = 'red')
plt.xlabel("sepal length (cm)")
plt.ylabel("sepal width (cm)")
plt.show()