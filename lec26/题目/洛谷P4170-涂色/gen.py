from random import *
from cyaron import *

def randseq(a, b, n):
    return [randint(a, b) for _ in range(n)]


# id：测试点编号，从 1 开始。
def gen_test(in_file, id):
    f = IO(in_file)
    n = randint(1, 10)
    s = String.random(n)
    f.input_writeln(s)

    return f



if __name__ == "__main__":
    gen_test('sample.in', 1) #这是为了单独运行此脚本，生成一组小数据，检查格式是否正确。