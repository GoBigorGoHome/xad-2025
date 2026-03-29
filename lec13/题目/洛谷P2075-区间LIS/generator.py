from cyaron import *
from random import randint

# io.input_writeln(graph.to_str(output=Edge.unweighted_edge)) # 输出无权图，以每条边u v一行的格式

def random_seq(a, b, n):
    return [randint(a, b) for _ in range(n)]



in_file = "killer.in"
f_ = open(in_file, 'w+')
f_.close()
f = IO(in_file)  # .out是临时文件
# 以下是造数据的代码
n = randint(1, 15)
q = randint(1, 10)
p = list(range(1, n + 1))
random.shuffle(p)
f.input_writeln(n, q)
f.input_writeln(p)
for _ in range(q):
    l = randint(1, n)
    r = randint(l, n)
    f.input_writeln(l, r)
