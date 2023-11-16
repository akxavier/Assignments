import pandas as pd
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import GridSearchCV
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
# Add pclass_crew because 'crew' value not present in test data
X_test['pclass_crew'] = 0
y_test = test_data['survived']

X_test = X_test[X_train.columns]

rf_classifier = RandomForestClassifier(random_state=12)

param_grid = {
    'n_estimators': [10, 20, 30],  # Number of trees
    'max_depth': [None, 5, 10, 20],  # Maximum depth of trees
    # Minimum samples required to split a node
    'min_samples_split': [2, 5, 10],
    # Minimum samples required at each leaf node
    'min_samples_leaf': [1, 2, 4]
}

grid_search = GridSearchCV(estimator=rf_classifier,
                           param_grid=param_grid, cv=5, scoring='accuracy')
grid_search.fit(X_train, y_train)

# Get the best parameters and best model from the Grid Search
best_params = grid_search.best_params_
best_model = grid_search.best_estimator_

# Use the best model to make predictions on the test set
y_pred = best_model.predict(X_test)

accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, average='binary', pos_label='yes')
recall = recall_score(y_test, y_pred, average='binary', pos_label='yes')
print(f'Best Parameters: {best_params}')
print(
    f'Best Model\n Accuracy: {accuracy}\n Precision: {precision}\n Recall: {recall}')
