import pandas as pd
import numpy as np

url = "Assignment_train.csv"
df = pd.read_csv(url)

X = df[['pclass', 'age', 'gender']]
y = df['survived']

feature_stats = {}

prior_probabilities = y.value_counts(normalize=True).to_dict()

for feature in X.columns:
    feature_stats[feature] = {}
    for category in X[feature].unique():
        feature_stats[feature][category] = {}
        for label in y.unique():
            count = np.sum((X[feature] == category) & (y == label))
            total_count = len(y[y == label])
            likelihood = (count + 1) / (total_count +
                                        len(X[feature].unique()))  # Laplacian correction
            feature_stats[feature][category][label] = likelihood

with open('probabilities.txt', 'w') as file:
    file.write(str(prior_probabilities))
    file.write('\n')
    file.write(str(feature_stats))
