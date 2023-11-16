import pandas as pd
from sklearn.tree import DecisionTreeClassifier
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import accuracy_score, precision_score, recall_score

train_data = pd.read_csv('Assignment_train.csv')
columns = ['pclass', 'age', 'gender', 'survived']
test_data = pd.read_csv('Assignment_test.csv', names=columns)

# Perform one-hot encoding
train_data = pd.get_dummies(
    train_data, columns=['pclass', 'age', 'gender'], drop_first=True)
test_data = pd.get_dummies(
    test_data, columns=['pclass', 'age', 'gender'], drop_first=True)

X_train = train_data.drop('survived', axis=1)
y_train = train_data['survived']

X_test = test_data.drop('survived', axis=1)
X_test['pclass_crew'] = 0
y_test = test_data['survived']

X_test = X_test[X_train.columns]

# Train the Decision Tree classifier
decision_tree_classifier = DecisionTreeClassifier(criterion="entropy")
decision_tree_classifier.fit(X_train, y_train)

# Train the Naive Bayes Classifier (Gaussian Naive Bayes)
naive_bayes_classifier = GaussianNB()
naive_bayes_classifier.fit(X_train, y_train)

decision_tree_predictions = decision_tree_classifier.predict(X_test)
naive_bayes_predictions = naive_bayes_classifier.predict(X_test)

# Evaluate the accuracy of both classifiers
dt_accuracy = accuracy_score(y_test, decision_tree_predictions)
dt_precision = precision_score(
    y_test, decision_tree_predictions, average='binary', pos_label='yes')
dt_recall = recall_score(y_test, decision_tree_predictions,
                         average='binary', pos_label='yes')

nb_accuracy = accuracy_score(y_test, naive_bayes_predictions)
nb_precision = precision_score(
    y_test, naive_bayes_predictions, average='binary', pos_label='yes')
nb_recall = recall_score(y_test, naive_bayes_predictions,
                         average='binary', pos_label='yes')

print(
    f"Decision Tree Classifier\n Accuracy: {dt_accuracy}\n Precision: {dt_precision}\n Recall: {dt_recall}\n")
print(
    f"Naive Bayes Classifier\n Accuracy: {nb_accuracy}\n Precision: {nb_precision}\n Recall: {nb_recall}")
