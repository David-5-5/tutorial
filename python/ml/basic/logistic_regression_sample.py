import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression

# dataset = pd.read_csv("User_Data.csv")

# Now, to predict whether a user will purchase the product or not, one needs
# to find out the relationship between Age and Estimated Salary. Here User ID
# and Gender are not important factors for finding out this. 
# 现在，要预测用户是否会购买该产品，需要找出年龄和预计工资之间的关系
# 此处 User ID 和 Gender 不是找出这一点的重要因素。

# input
# x = dataset.iloc[:, [2, 3]].values
  
# output
# y = dataset.iloc[:, 4].values

# generate 2d classification dataset
from sklearn.datasets import make_classification
x, y = make_classification(n_samples = 200,
                           n_features=2,
                           n_redundant=0,
                           n_informative=2,
                           n_repeated=0,
                           n_classes =2,
                           n_clusters_per_class=1)

# Splitting the dataset to train and test. 75% of data is used for training
# the model and 25% of it is used to test the performance of our model.
# 拆分数据集以进行训练和测试。75% 的数据用于训练模型，25% 的数据用于测试我们模型的性能。  
xtrain, xtest, ytrain, ytest = train_test_split(
    x, y, test_size=0.25, random_state=0)

# Now, it is very important to perform feature scaling here because Age and
# Estimated Salary values lie in different ranges. If we don’t scale the features
# then the Estimated Salary feature will dominate the Age feature when the model
# finds the nearest neighbor to a data point in the data space.
# 现在，在这里执行特征缩放非常重要，因为 Age 和 Estimated Salary 值位于不同的范围内。如果我们
# 不缩放特征，那么当模型找到数据空间中数据点的最近邻居时，估计工资特征将支配年龄特征。 

sc_x = StandardScaler()
xtrain = sc_x.fit_transform(xtrain)
xtest = sc_x.transform(xtest)
  
print (xtrain[0:10, :])


classifier = LogisticRegression(random_state = 0)
classifier.fit(xtrain, ytrain)

# After training the model, it is time to use it to do predictions on testing data. 
y_pred = classifier.predict(xtest)


from sklearn.metrics import confusion_matrix

cm = confusion_matrix(ytest, y_pred)
print ("Confusion Matrix : \n", cm)

from sklearn.metrics import accuracy_score
  
print ("Accuracy : ", accuracy_score(ytest, y_pred))


# Visualizing the performance of our model. 
from matplotlib.colors import ListedColormap
  
X_set, y_set = xtest, ytest
X1, X2 = np.meshgrid(np.arange(start = X_set[:, 0].min() - 1, 
                               stop = X_set[:, 0].max() + 1, step = 0.01),
                     np.arange(start = X_set[:, 1].min() - 1, 
                               stop = X_set[:, 1].max() + 1, step = 0.01))

plt.contourf(X1, X2, classifier.predict(
             np.array([X1.ravel(), X2.ravel()]).T).reshape(
             X1.shape), alpha = 0.75, cmap = ListedColormap(('red', 'green')))
  
plt.xlim(X1.min(), X1.max())
plt.ylim(X2.min(), X2.max())
  
for i, j in enumerate(np.unique(y_set)):
    plt.scatter(X_set[y_set == j, 0], X_set[y_set == j, 1],
                c = ListedColormap(('red', 'green'))(i), label = j)
      
plt.title('Classifier (Test set)')
plt.xlabel('Age')
plt.ylabel('Estimated Salary')
plt.legend()
plt.show()


