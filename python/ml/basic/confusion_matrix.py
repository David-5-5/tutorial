
# Importing the dataset.
from sklearn.datasets import fetch_openml
mnist = fetch_openml('mnist_784', version=1)
  
# Creating independent and dependent variables.
X, y = mnist['data'], mnist['target']
  
# Splitting the data into training set and test set.
X_train, X_test, y_train, y_test = X[:60000], X[60000:], y[:60000], y[60000:]
  
"""
The training set is already shuffled for us, which is good as this guarantees that all
cross-validation folds will be similar.
"""
  
# Training a binary classifier.
y_train_5 = (y_train == 5) # True for all 5s, False for all other digits.
y_test_5 = (y_test == 5)
  
"""
Building a dumb classifier that just classifies every single image in the “not-5” class.
"""
  
from sklearn.model_selection import cross_val_score
from sklearn.base import BaseEstimator
import numpy as np
class Never5Classifier(BaseEstimator):
    def fit(self, X, y=None):
        pass
    def predict(self, X):
        return np.zeros((len(X), 1), dtype=bool)

never_5_clf = Never5Classifier()
ret = cross_val_score(never_5_clf, X_train, y_train_5, cv=3, scoring="accuracy")
print(ret)

# Creating some predictions.
from sklearn.model_selection import cross_val_predict
y_train_pred = cross_val_predict(never_5_clf, X_train, y_train_5, cv=3)
  
"""
You could make predictions on the test set, but use the test set only at the very end of your project, once you have a classifier that you are ready to launch.
"""
  
# Constructing the confusion matrix.
from sklearn.metrics import confusion_matrix
print(confusion_matrix(y_train_5, y_train_pred))

from sklearn.metrics import precision_score, recall_score
print(precision_score(y_train_5, y_train_pred))
print(recall_score(y_train_5, y_train_pred))

from sklearn.metrics import f1_score
print(f1_score(y_train_5, y_train_pred))