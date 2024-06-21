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
