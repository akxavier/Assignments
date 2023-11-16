import pandas as pd
import numpy as np

columns = ['pclass', 'age', 'gender', 'survived']
test_data = pd.read_csv("Assignment_test.csv", names=columns)

with open('probabilities.txt', 'r') as file:
    lines = file.readlines()
    prior_probabilities = eval(lines[0])
    feature_stats = eval(lines[1])


def predict(features):
    probabilities = {label: np.log(prior_prob)
                     for label, prior_prob in prior_probabilities.items()}
    for feature, categories in feature_stats.items():
        for category, likelihoods in categories.items():
            if features[feature] == category:
                for label, likelihood in likelihoods.items():
                    probabilities[label] += np.log(likelihood)

    return max(probabilities, key=probabilities.get)


predictions = test_data.apply(predict, axis=1)

tp = len(test_data[(predictions == 'yes') &
                   (test_data['survived'] == 'yes')])
tn = len(test_data[(predictions == 'no') &
                   (test_data['survived'] == 'no')])
fp = len(test_data[(predictions == 'yes') &
                   (test_data['survived'] == 'no')])
fn = len(test_data[(predictions == 'no') &
                   (test_data['survived'] == 'yes')])

confusion_matrix_result = np.array([[tp, fn], [fp, tn]])
print(confusion_matrix_result)

accuracy = (tp + tn) / len(test_data)
precision = tp / (tp + fp)
recall = tp / (tp + fn)

print(f'Accuracy: {accuracy}')
print(f'Precision: {precision}')
print(f'Recall: {recall}')
