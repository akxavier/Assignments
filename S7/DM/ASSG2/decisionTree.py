import pandas as pd
import numpy as np
import math


class Node:
    def __init__(self, value):
        self.value = value
        self.children = {}


class DecisionTree:
    def __init__(self):
        self.root = None

    def entropy(self, data, target_name):
        # Calculate the entropy of a dataset
        entropy = 0
        total_samples = len(data)

        for label in data[target_name].unique():
            label_count = len(data[data[target_name] == label])
            label_probability = label_count / total_samples
            entropy -= label_probability * math.log(label_probability)

        return entropy

    def information_gain(self, data, feature_name, target_name):
        # Calculate the information gain
        total_entropy = self.entropy(data, target_name)
        unique_values = data[feature_name].unique()
        weighted_entropy = 0

        for value in unique_values:
            subset = data[data[feature_name] == value]
            probability = len(subset) / len(data)
            weighted_entropy += probability * self.entropy(subset, target_name)

        return total_entropy - weighted_entropy

    def find_best_split(self, data, features, target_name):
        # Find the best feature to split on based on information gain
        best_feature = None
        max_information_gain = -1

        for feature in features:
            gain = self.information_gain(data, feature, target_name)
            if gain > max_information_gain:
                max_information_gain = gain
                best_feature = feature

        return best_feature

    def build_tree(self, data, features, target_name, parent_data=None):
        # build the Decision Tree
        if len(data) == 0:
            return Node(parent_data[target_name].mode()[0])

        if len(data[target_name].unique()) == 1:
            return Node(data[target_name].iloc[0])

        if len(features) == 0:
            return Node(data[target_name].mode()[0])

        best_feature = self.find_best_split(data, features, target_name)
        root = Node(best_feature)
        unique_values = data[best_feature].unique()

        for value in unique_values:
            subset = data[data[best_feature] == value]
            root.children[value] = self.build_tree(
                subset, [f for f in features if f != best_feature], target_name, data)

        return root

    def train(self, data, target_name, features):
        self.root = self.build_tree(data, features, target_name)

    def predict_example(self, node, sample):
        if len(node.children) == 0:
            return node.value
        value = sample[node.value]
        if value in node.children:
            return self.predict_example(node.children[value], sample)
        else:
            return list(node.children.values())[0].value

    def predict(self, data):
        predictions = [self.predict_example(
            self.root, sample) for _, sample in data.iterrows()]
        return pd.Series(predictions)


if __name__ == '__main__':
    # Load the training dataset
    train_data = pd.read_csv('Assignment_train.csv')
    target_name = 'survived'
    features = ['pclass', 'gender', 'age']

    # Load the test dataset
    columns = ['pclass', 'age', 'gender', 'survived']
    test_data = pd.read_csv('Assignment_test.csv', names=columns)

    decision_tree = DecisionTree()
    decision_tree.train(train_data, target_name, features)

    predictions = decision_tree.predict(test_data)

    tp = len(test_data[(predictions == 'yes') &
             (test_data[target_name] == 'yes')])
    tn = len(test_data[(predictions == 'no') &
             (test_data[target_name] == 'no')])
    fp = len(test_data[(predictions == 'yes') &
             (test_data[target_name] == 'no')])
    fn = len(test_data[(predictions == 'no') &
             (test_data[target_name] == 'yes')])

    confusion_matrix_result = np.array([[tp, fn], [fp, tn]])
    print(confusion_matrix_result)

    accuracy = (tp + tn) / len(test_data)
    precision = tp / (tp + fp)
    recall = tp / (tp + fn)

    print(f'Accuracy: {accuracy}')
    print(f'Precision: {precision}')
    print(f'Recall: {recall}')
