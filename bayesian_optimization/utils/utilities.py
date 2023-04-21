import numpy as np


class Utilities:
    @staticmethod
    def choletsky_decomposition(matrix) -> np.ndarray:
        """Performs a Cholesky decomposition of `matrix`, which must
        be a symmetric and positive definite matrix. The function
        returns the lower variant triangular matrix, L."""
        n = len(matrix)

        # Create zero matrix for L
        L = np.zeros((n, n))

        # Perform the Cholesky decomposition
        for i in range(n):
            for k in range(i + 1):
                tmp_sum = sum(L[i][j] * L[k][j] for j in range(k))

                if i == k:  # Diagonal elements
                    L[i][k] = np.sqrt(matrix[i][i] - tmp_sum)
                else:
                    L[i][k] = (1.0 / L[k][k] * (matrix[i][k] - tmp_sum))
        return L

    @staticmethod
    def solve_using_choletsky(L: np.ndarray, m: np.ndarray, answer: np.ndarray):
        """Solve equation `L * L.T * x = m` for x, where `L` is a lower variant triangular matrix.
        `answer` will be changed to solution vector"""
        assert L.shape[0] == m.size and m.size == answer.size, "Everything must have the same size"

        # First we need to solve Ly = m
        y = np.zeros(m.size)
        for i in range(m.size):
            # y[0] = m[0] / L[0][0]
            # y[0]*L[i][0] + y[1]*L[i][1] + ... + y[i]*L[i][i] = m[i]
            y[i] = (m[i] - sum(y[j] * L[i][j] for j in range(i))) / L[i][i]

        # Now we have to solve L.T * x = y
        for i in range(m.size - 1, -1, -1):
            # answer[n-1] = y[n-1] / L.T[n-1][n-1]
            # ans[i]*L.T[i][i] + ans[i+1]*L.T[i][i+1] + ... + ans[n-1]*L.T[i][n-1] = y[i]
            answer[i] = (y[i] - sum(answer[j] * L[j][i] for j in range(i + 1, m.size))) / L[i][i]

    @staticmethod
    def solve_matrix_choletsky(L: np.ndarray, B: np.ndarray, X: np.ndarray):
        """Solve equation `L * L.T * X = B` for matrix X. `X` will be changed"""
        assert L.shape[0] == B.shape[0] and L.shape[0] == X.shape[0] and X.shape[1] == B.shape[1], \
            "You messed up sizes!"
        for i in range(B.shape[1]):
            Utilities.solve_using_choletsky(L, B[:, i], X[:, i])
