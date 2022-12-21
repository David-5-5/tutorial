
# This code may not run on GFG IDE
# as required modules not found.
  
# import required modules
import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_regression
  
# Create data set.
x, y = make_regression(n_samples=100, n_features=1,
                       n_informative=1, noise=10, random_state=10)
  
# Plot the generated data set.
plt.scatter(x, y, s=30, marker='o')
plt.xlabel("Feature_1 --->")
plt.ylabel("Target_Variable --->")
plt.title('Simple Linear Regression')
plt.show()
  
# Convert  target variable array from 1d to 2d.
y = y.reshape(100, 1)


# code
  
# Adding x0=1 to each instance
x_new = np.array([np.ones(len(x)), x.flatten()]).T
  
# Using Normal Equation.
theta_best_values = np.linalg.inv(x_new.T.dot(x_new)).dot(x_new.T).dot(y)
  
# Display best values obtained.
print(theta_best_values)

# sample data instance.
x_sample = np.array([[-2], [4]])
  
# Adding x0=1 to each instance.
x_sample_new = np.array([np.ones(len(x_sample)), x_sample.flatten()]).T
  
# Display the sample.
print("Before adding x0:\n", x_sample)
print("After adding x0:\n", x_sample_new)


# code
# predict the values for given data instance.
predict_value=x_sample_new.dot(theta_best_values)
print(predict_value)


# code

# Plot the output.
plt.scatter(x,y,s=30,marker='o')
plt.plot(x_sample,predict_value,c='red')
plt.plot()
plt.xlabel("Feature_1 --->")
plt.ylabel("Target_Variable --->")
plt.title('Simple Linear Regression')
plt.show()

# code

# Verification.
from sklearn.linear_model import LinearRegression
lr=LinearRegression()    # Object.
lr.fit(x,y)              # fit method.

# Print obtained theta values.
print("Best value of theta:",lr.intercept_,lr.coef_,sep='\n')

#predict.
print("predicted value:",lr.predict(x_sample),sep='\n')