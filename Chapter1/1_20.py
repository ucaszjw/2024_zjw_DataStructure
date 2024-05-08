n, x_0 = map(int, input().split())
p = list(map(int, input().split()))
result = p[n]
for i in range(n - 1, -1, -1):
    result = result * x_0 + p[i]
print(result)