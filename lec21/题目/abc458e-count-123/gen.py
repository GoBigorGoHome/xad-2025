from random import *
from cyaron import *

def randseq(a, b, n):
    return [randint(a, b) for _ in range(n)]


# id：测试点编号，从 1 开始。
def gen_test(in_file, id):
    f = IO(in_file)
    l = 1
    if id <= 3:
        r = 10
    elif id <= 5:
        r = 20
    elif id < 10:
        r = int(1e6)
    else:
        l = int(1e6)
        r = int(1e6)
    x1 = randint(l, r)
    x2 = randint(l, r)
    x3 = randint(l, r)
    f.input_writeln(x1, x2, x3)


if __name__ == "__main__":
    gen_test('sample.in', 1) #这是为了单独运行此脚本，生成一组小数据，检查格式是否正确。
    