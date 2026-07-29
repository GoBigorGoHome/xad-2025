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
    elif id < 3:
        n = randint(1, 1000)
        q = randint(1, 1000)
    elif id == 3:
        n = 1000
        q = 1000
    elif id < 9:
        n = randint(1, maxn)
        q = randint(1, maxn)
    else:
        n = maxn
        q = maxn
    p = list(range(1, n + 1))
    shuffle(p)

    f.input_writeln(n, q)
    f.input_writeln(p)
    for _ in range(q):
        if _ == q - 1:
            type = randint(0, 1)
        else:
            type = randint(0, 3)
        l = randint(1, n)
        r = randint(l, n)
        if type < 2:
            x = randint(1, int(1e6))
            f.input_writeln(type, l, r, x)
        else:
            f.input_writeln(type, l, r)




if __name__ == "__main__":
    gen_test('sample.in', 1)