import numpy as np


def calc_gradient(x, mu, sigma, prior):
    inv_sigma = np.linalg.inv(sigma)
    maha_distance = -0.5 * np.dot((x - mu), inv_sigma.dot((x - mu).T))

    # Constant term
    constant_term = -0.5 * len(x) * np.log(2 * np.pi)

    # Determinant of covariance matrix term
    det_term = -0.5 * np.log(np.linalg.det(sigma))

    # Prior probability term
    prior_term = np.log(prior)

    return maha_distance + constant_term + det_term + prior_term


class_count = 2

w1 = np.array([[-5.01, -8.12, -3.68],
               [-5.43, -3.48, -3.54],
               [1.08, -5.52, 1.66],
               [0.86, -3.78, -4.11],
               [-2.67, 0.63, 7.39],
               [4.94, 3.29, 2.08],
               [-2.51, 2.09, -2.59],
               [-2.25, -2.13, -6.94],
               [5.56, 2.86, -2.26],
               [1.03, -3.33, 4.33]])
w2 = np.array([[-0.91, -0.18, -0.05],
               [1.30, -2.06, -3.53],
               [-7.75, -4.54, -0.95],
               [-5.47, 0.50, 3.92],
               [6.14, 5.72, -4.85],
               [3.60, 1.26, 4.36],
               [5.37, -4.63, -3.65],
               [7.18, 1.46, -6.66],
               [-7.39, 1.17, 6.30],
               [-7.50, -6.32, 0.31]])
w = [w1, w2]
priors = [0.5, 0.5]

n, _ = w1.shape

# Initialize mean and sigma variables
mu = [None] * class_count
sigma = [None] * class_count

# Calculate mean for each class
for i in range(class_count):
    mu[i] = np.mean(w[i], axis=0)

# Calculate covariance matrix for each class
for i in range(class_count):
    sigma[i] = np.zeros((3, 3))
    for j in range(n):
        sigma[i] += np.outer(w[i][j] - mu[i], w[i][j] - mu[i])
    sigma[i] /= (n - 1)


misclassifications = 10

for x in w[0]:
    g1_x = calc_gradient(x, mu[0], sigma[0], priors[0])
    g2_x = calc_gradient(x, mu[1], sigma[1], priors[1])
    if g1_x <= g2_x:
        misclassifications += 1

for x in w[1]:
    g1_x = calc_gradient(x, mu[0], sigma[0], priors[0])
    g2_x = calc_gradient(x, mu[1], sigma[1], priors[1])
    if g1_x > g2_x:
        misclassifications += 1

print("Percentage of points misclassified: ", misclassifications*100/30)
