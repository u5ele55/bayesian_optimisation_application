from bayesian_optimization.utils.kernels import *
from bayesian_optimization.utils.utilities import Utilities


def cov_matrix(x1, x2, cov_function) -> np.ndarray:
    return np.array([[cov_function(a, b) for a in x1] for b in x2])


class GPR:
    # Перенес задание параметров в init для простоты
    def __init__(self,
                 kernel=SquaredExponentialKernel(),
                 noise: float = 3e-7):
        # fit surrogate model using dataset
        self.covariance_L = None
        self.covariance_matrix = None
        self.data_x = np.array([])
        self.data_y = np.array([])
        self.noise = noise
        self.covariance_function = kernel

    def fit(self, data_x: np.ndarray, data_y: np.ndarray):
        self.data_x = data_x
        self.data_y = data_y
        self.covariance_matrix = cov_matrix(data_x, data_x, self.covariance_function) + self.noise * np.identity(len(self.data_x))
        self.covariance_L = Utilities.choletsky_decomposition(self.covariance_matrix)

    def predict(self, at_values: np.ndarray) -> dict:
        # function to predict output at new input values. Store the mean and covariance matrix in memory.
        k_lower_left = cov_matrix(
            self.data_x, at_values, self.covariance_function)
        k_lower_right = cov_matrix(
            at_values, at_values, self.covariance_function
        )

        cov_inv_times_data_y = np.zeros(self.data_y.size)
        Utilities.solve_using_choletsky(self.covariance_L, self.data_y, cov_inv_times_data_y)
        # Mean.
        mean_at_values = np.dot(
            k_lower_left,
            cov_inv_times_data_y
        ).flatten()

        cov_inv_times_k_lower_left = np.zeros((self.data_x.shape[0], k_lower_left.shape[0]))
        Utilities.solve_matrix_choletsky(self.covariance_L, k_lower_left.T, cov_inv_times_k_lower_left)

        # Covariance.
        cov_at_values = k_lower_right - np.dot(
            k_lower_left,
            cov_inv_times_k_lower_left
        )

        # Adding value larger than machine epsilon to ensure positive semi definite
        cov_at_values = cov_at_values + 3e-7 * np.ones(
            np.shape(cov_at_values)[0]
        )

        var_at_values = np.diag(cov_at_values)

        return {
            'mean': mean_at_values,
            'covariance_matrix': cov_at_values,
            'variance': var_at_values
        }
