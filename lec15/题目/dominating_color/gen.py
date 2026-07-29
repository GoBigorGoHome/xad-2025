from random import *
from cyaron import *

def randseq(a, b, n):
    return [randint(a, b) for _ in range(n)]


# id：测试点编号，从 1 开始。
def gen_test(in_file, id):
    f = IO(in_file)
    maxn = int(1e5)
    if id == 1:
        n = 10
        q = 10
    elif id == 10:
        n = maxn
        q = maxn
    else:
        n = randint(1, maxn)
        q = randint(1, maxn)

    col = randint(2, 4) # 颜色的数量
    a = choices(sample(range(1, n + 1), k = col), k = n)
    tree = Graph.tree(n)
    f.input_writeln(n, q)
    f.input_writeln(a)
    f.input_writeln(tree.to_str(output=Edge.unweighted_edge))
    
    for _ in range(q):
        u = randint(1, n)
        v = randint(1, n)
        f.input_writeln(u, v)


if __name__ == "__main__":
    gen_test('sample.in', 1)
