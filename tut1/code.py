import sys
import numpy as np
import random
import math

def lu(A):
    # print(A)
    N = A.shape[0]
    a11 = A[0][0]
    if A.shape == (1, 1):
        return np.ones((1, 1)), A

    aDash = A[1:,1:]
    wT = np.reshape(A[0,1:], (1, N-1))
    v = np.reshape(A[1:,0], (N-1, 1))

    # print(aDash, wT, v)

    LU = aDash - np.dot(v, wT)/a11
    lDash, uDash = lu(LU)

    # print(lDash.shape)
    # print(uDash.shape)    

    L = np.hstack((v/a11, lDash))
    # print("after hstack l shape ", L.shape)
    L = np.vstack((np.zeros((1, N)), L))
    L[0][0] = 1
    # print(L.shape)

    U = np.hstack(((np.zeros((N-1, 1))), uDash))
    # print("after hstack u shape ", U.shape)
    # print("WT shape",wT.shape)
    wT = np.hstack(([[a11]],wT))
    # print("WT",wT,wT[0,:])
    U = np.vstack((wT, U))
    # print(U.shape)

    return L, U

def det(A):
    L, U = lu(A)
    return L.diagonal().prod()*U.diagonal().prod()


sys.stdin = open("input.txt", "r")

N = int(input())
M = int(input())

Q = np.zeros((N, M))

for i in range(M):
    u = int(input())
    v = int(input())
    Q[u-1][i] = 1
    Q[v-1][i] = -1

L = np.matmul(Q, np.transpose(Q))
# print(L)
i = random.randint(0, N-1)
j = random.randint(0, N-1)
# print(i, j)
L = np.delete(L, i, 0)
L = np.delete(L, j, 1)
print(L)
print(det(L)*math.pow(-1, i+j))

