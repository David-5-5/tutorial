#import the necessary libraries
from sklearn.datasets import load_breast_cancer
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
# load the breast cancer dataset
def binomial():
    '''
    Binomial Logistic regression: 
    target variable can have only 2 possible types: “0” or “1” which may
    represent “win” vs “loss”, “pass” vs “fail”, “dead” vs “alive”, etc.
    In this case sigmoid functions are used, which is already discussed above.
    '''
    X, y = load_breast_cancer(return_X_y=True)
    # split the train and test dataset
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20,
                                                        random_state=23)
    # LogisticRegression
    clf = LogisticRegression(random_state=0)
    clf.fit(X_train, y_train)
    # Prediction
    y_pred = clf.predict(X_test)
    
    acc = accuracy_score(y_test, y_pred)
    print("Logistic Regression model accuracy (in %):", acc*100)


from sklearn import datasets, linear_model, metrics

def multinomial():
    '''
    Multinomial Logistic Regression:
    target variable can have 3 or more possible types which are not ordered
    (i.e. types have no quantitative significance) like “disease A” vs 
    “disease B” vs “disease C”. In this case, the softmax function is used
    in place of the sigmoid function. 
    '''
    # load the digit dataset
    digits = datasets.load_digits()
    
    # defining feature matrix(X) and response vector(y)
    X = digits.data
    y = digits.target
    
    # splitting X and y into training and testing sets
    from sklearn.model_selection import train_test_split
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4,
                                                        random_state=1)
    
    # create logistic regression object
    reg = linear_model.LogisticRegression()
    
    # train the model using the training sets
    reg.fit(X_train, y_train)
    
    # making predictions on the testing set
    y_pred = reg.predict(X_test)
    
    # comparing actual response values (y_test) with predicted response values (y_pred)
    print("Logistic Regression model accuracy(in %):", 
    metrics.accuracy_score(y_test, y_pred)*100)

binomial()
multinomial()