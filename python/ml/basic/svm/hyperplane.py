
# Separating Hyperplanes in SVM, example from geeksforgeeks
# for detail, refer to https://www.geeksforgeeks.org/separating-hyperplanes-in-svm/
# Import Necessary libraries/functions
import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
 
# define the dataset
X = np.array([[1,1],
             [2,0],
             [2,3]])
Y = np.array([0,0,1])
 
# define support vector classifier with linear kernel
 
clf = SVC(gamma='auto', kernel ='linear')
 
# fit the above data in SVC
clf.fit(X,Y)
 
# plot the decision boundary ,data points,support vector etcv
w = clf.coef_[0]
a = -w[0] / w[1]
 
xx = np.linspace(0,12)
yy = a * xx - clf.intercept_[0] / w[1]
y_neg = a * xx - clf.intercept_[0] / w[1] + 1
y_pos = a * xx - clf.intercept_[0] / w[1] - 1
plt.figure(1,figsize= (15, 10))
plt.plot(xx, yy, 'k',
         label=f"Decision Boundary (y ={w[0]}x1  + {w[1]}x2  {clf.intercept_[0] })")
plt.plot(xx, y_neg, 'b-.',
         label=f"Neg Decision Boundary (-1 ={w[0]}x1  + {w[1]}x2  {clf.intercept_[0] })")
plt.plot(xx, y_pos, 'r-.',
         label=f"Pos Decision Boundary (1 ={w[0]}x1  + {w[1]}x2  {clf.intercept_[0] })")
 
for i in range(3):
  if (Y[i]==0):
      plt.scatter(X[i][0], X[i][1],color='red', marker='o', label='negative')
  else:
      plt.scatter(X[i][0], X[i][1],color='green', marker='x', label='positive')
plt.legend()
plt.show()
 
# calculate margin
print(f'Margin : {2.0 /np.sqrt(np.sum(clf.coef_ ** 2)) }')