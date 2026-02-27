

# 素性测试

问题：给定一个奇数 $n \ge 3$，判断 $n$ 是不是素数。

> how to determine whether a large odd integer $n$ is prime.



为什么要考虑这个问题？

为了找大素数。

> Many applications, such as cryptography, call for finding large "random" primes. Fortunately, large primes are not too rare, so that it is feasible to test random integers of the appropriate size until you find one that is prime.

## 试除

> The most obvious idea is to look for factors of $n$, but no efficient factoring algorithm is known.\



> One simple approach to the problem of testing for primality is **trial division**: try dividing $n$ by each integer $2, 3, 5, 7, 9,\dots, \lfloor\sqrt{n}\rfloor$, skipping even integers greater than $2$. 



## 费马测试

费马小定理：若 $n$ 是素数，那么对每个 $a = 1, \dots, n - 1$ 都有 $a^{n - 1} = 1 \pmod{n}$。

实际上，对于每个奇数 $n$ 都有 $1^{n-1} = 1 \pmod{n}$ 和 $(n-1)^{n-1} = 1\pmod{n}$。

费马测试：选一个整数 $a$（$2 \le a \le n - 2$），检查 $a^{n-1} = 1\pmod{n}$ 是否成立。

若不成立，那么 $n$ 是合数。若成立，那么 $n$ 可能是素数。



## Miller-Rabin 测试

原理：如果 $n$ 是素数那么 $x^2 = 1 \pmod{n}$ 的解只有 $x = \pm 1 \pmod{n}$。

> 实际上，我们有
> $$
> x^2 = 1 \pmod {n}\ 的解只有 \pm 1 \pmod{n} \iff n 是素数或素数幂
> $$

想法：

- 令 $n - 1 = 2^t u$，这里 $t \ge 1$ 而 $u$ 是奇数。
- 选一个整数 $a$（$2 \le a \le n - 2$）
- 考虑序列 $x = (x_0, x_1, \dots, x_t)$：$x_0 = a^u$，$x_i = (x_{i-1})^{2} = (x_0)^{2^i}$（$1 \le i \le t$）。

如果 $n$ 是素数，那么对于任意 $1 \le a \le n-1$，序列 $x = (x_0, x_1, \dots, x_t)$ 必是下列两种情况之一

1. $x_0 = 1$，那么 $x = (1, 1, \dots, 1)$。$x$ 的每一项都是 $1$。

2. $x_0 \ne 1$，那么 $x = (,\dots, -1, 1, \dots, 1)$。存在某一项 $x_i = -1$（$0 \le i < t$）并且 $x_i$ 之后的项都是 $1$ 而 $x_i$ 之前的项都不是 $\pm 1$。

反过来，如果存在 $1 \le a \le n-1$ 使得序列 $x$ 不是上述两种情况，也就是

3. $x_0 \ne 1$ 且 $\forall\, 0 \le i < t$，$x_i \ne -1$

那么 $n$ 不是素数。



Miller-Rabin 测试：随机选择一个 $2 \le a \le n - 2$，计算序列 $x$。如果 $x$ 是情况 1 或情况 2，就判断 $n$ 是素数，否则 $n$ 一定是合数。

### 估计 Miller-Rabin 测试出错的概率

也就是说，假设 $n$ 是合数，使得序列 $x$ 是情况 1 或 2 的 $a$ 有多少个？

> 此时我们称 $n$ 是一个 strong pseudoprime base $a$.



设奇数 $n$ 是合数，$n = u \cdot 2^t$。有多少个 $a$ 使得序列 $x$ 是情况 1？也就是使得 $a^{u} = 1 \pmod{n}$。









对于任意 $a = 1, \dots, n-1$，序列 $x = (x_0, x_1, \dots, x_t)$ 必是下列三种情况之一

-  $x_0 = 1$。那么 $x = (1, 1, \dots, 1)$。$x$ 的每一项都是 $1$。
- $x_0 \ne 1$ 并且存在 $0 \le i < t$ 使得 $x_i = -1$ 。不难看出这样的 $i$ 唯一。此时 $x = (,\dots, -1, 1, \dots, 1)$。
- 
