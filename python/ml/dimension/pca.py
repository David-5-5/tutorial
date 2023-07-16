import pandas as pd
import numpy as np
 
# Here we are using inbuilt dataset of scikit learn
from sklearn.datasets import load_breast_cancer
 
# instantiating
cancer = load_breast_cancer(as_frame=True)
# creating dataframe
df = cancer.frame
 
# checking shape
print('Original Dataframe shape :',df.shape)
 
# Input features
X = df[cancer['feature_names']]
print('Inputs Dataframe shape   :', X.shape)

# Mean
X_mean = X.mean()

# Standard deviation 
X_std = X.std()
 
# Standardization 标准化数据
Z = (X - X_mean) / X_std

# covariance 协方差矩阵
c = Z.cov()
 
# Plot the covariance matrix
import matplotlib.pyplot as plt
import seaborn as sns
sns.heatmap(c)
plt.show()

# linalg.eig() 计算方形矩阵的特征值和特征向量
eigenvalues, eigenvectors = np.linalg.eig(c)
print('Eigen values:\n', eigenvalues)
print('Eigen values Shape:', eigenvalues.shape)
print('Eigen Vector Shape:', eigenvectors.shape)


# 按降序对特征值进行排序，并相应地对相应的特征向量进行排序。
# Index the eigenvalues in descending order
idx = eigenvalues.argsort()[::-1]
 
# Sort the eigenvalues in descending order
eigenvalues = eigenvalues[idx]
 
# sort the corresponding eigenvectors accordingly
eigenvectors = eigenvectors[:,idx]

# 解释方差是一个术语，通过选择主成分而不是原始特征空间来保留的总方差量。
# cumsum的作用主要就是计算轴向的累加和
explained_var = np.cumsum(eigenvalues) / np.sum(eigenvalues)
explained_var

# 确定主成分的数量
# 可以考虑选择的任何值的主成分的数量，也可以通过限制解释的方差来考虑。
# 本例中解释的方差大于等于 50%。
n_components = np.argmax(explained_var >= 0.50) + 1
n_components # n_components = 2

# 将数据投影到选定的主成分上
# 1. 找到投影矩阵，它是对应于数据协方差矩阵的最大特征值的特征向量矩阵。它将高维数据集投影到低维子空间上
# 2. 数据的协方差矩阵的特征向量称为数据的主轴，数据实例在这些主轴上的投影称为主分量。

# PCA component or unit matrix
# eigenvectors 30 * 30 matrix, u is 30 * 2 matrix
u = eigenvectors[:,:n_components]
pca_component = pd.DataFrame(u,
                             index = cancer['feature_names'],
                             columns = ['PC1','PC2']
                            )
 
# plotting heatmap
plt.figure(figsize =(5, 7))
sns.heatmap(pca_component)
plt.title('PCA Component')
plt.show()

# 通过仅保留占大部分方差的轴（维度）并丢弃所有其他轴（维度）来获得降维

# Matrix multiplication or dot Product
Z_pca = Z @ pca_component
 
Z_pca = pd.DataFrame(Z_pca.values,
                     columns = ['PCA1','PCA2']
                            )
Z_pca.head()


# Importing PCA
from sklearn.decomposition import PCA
 
# Let's say, components = 2
pca = PCA(n_components=2)
pca.fit(Z)
x_pca = pca.transform(Z)
 
# Create the dataframe
df_pca1 = pd.DataFrame(x_pca,
                       columns=['PC{}'.
                       format(i+1)
                        for i in range(n_components)])
df_pca1.head()


# giving a larger plot
plt.figure(figsize=(8, 6))
 
plt.scatter(x_pca[:, 0], x_pca[:, 1],
            c=cancer['target'],
            cmap='plasma')
 
# labeling x and y axes
plt.xlabel('First Principal Component')
plt.ylabel('Second Principal Component')
plt.show()


# components
pca.components_
