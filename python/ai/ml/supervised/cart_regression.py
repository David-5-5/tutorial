
# Import the necessary libraries
from sklearn.datasets import load_diabetes
from sklearn.tree import DecisionTreeRegressor
from sklearn.tree import export_graphviz
from graphviz import Source
 
# Load the dataset
diabetes = load_diabetes()
X = diabetes.data
y = diabetes.target
 
# DecisionTreeRegressor
tree_reg = DecisionTreeRegressor(criterion = 'squared_error',max_depth=2)
 
tree_reg.fit(X, y)
 
# Plot the decision tree graph
export_graphviz(
    tree_reg,
    out_file="diabetes_tree.dot",
    feature_names=diabetes.feature_names,
    class_names=diabetes.target,
    rounded=True,
    filled=True
 )
 
with open("diabetes_tree.dot") as f:
    dot_graph = f.read()
     
Source(dot_graph)