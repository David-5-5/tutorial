
# The example from https://www.geeksforgeeks.org/getting-started-with-classification/
# Python program to perform classification on Iris dataset
 
# Run this program on your local Python interpreter
# provided you have installed the required libraries
 
# Importing the required libraries
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn import datasets
from sklearn import svm
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB
from xgboost import XGBClassifier


# import the iris dataset
iris = datasets.load_iris()
X = iris.data
y = iris.target
 
# splitting X and y into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.3, random_state=1)
 
# GAUSSIAN NAIVE BAYES
gnb = GaussianNB()
# train the model
gnb.fit(X_train, y_train)
# make predictions
gnb_pred = gnb.predict(X_test)
# print the accuracy
print("Accuracy of Gaussian Naive Bayes: ", accuracy_score(y_test, gnb_pred))
 
# DECISION TREE CLASSIFIER
dt = DecisionTreeClassifier(random_state=0)
# train the model
dt.fit(X_train, y_train)
# make predictions
dt_pred = dt.predict(X_test)
# print the accuracy
print("Accuracy of Decision Tree Classifier: ", accuracy_score(y_test, dt_pred))
 
# SUPPORT VECTOR MACHINE
svm_clf = svm.SVC(kernel='linear')  # Linear Kernel
# train the model
svm_clf.fit(X_train, y_train)
# make predictions
svm_clf_pred = svm_clf.predict(X_test)
# print the accuracy
print("Accuracy of Support Vector Machine: ", accuracy_score(y_test, svm_clf_pred))


bst = XGBClassifier(n_estimators=2, max_depth=2, learning_rate=1, objective='binary:logistic')
bst.fit(X_train, y_train)
bst_preds = bst.predict(X_test)
# print the accuracy
print("Accuracy of XGBoost: ",accuracy_score(y_test, bst_preds))