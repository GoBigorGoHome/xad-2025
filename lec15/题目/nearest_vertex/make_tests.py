from random import randint
from cyaron import *
import os, sys
import shutil
from tqdm import tqdm
import argparse


def compile(filename):
    name, ext = os.path.splitext(filename)
    if ext != '.cpp':
        raise ValueError(f'Not a C++ source file.')
    if sys.platform == "win32":
            stack_size_option = '--stack,'
    else:
            stack_size_option = '-z,stack-size='
    if os.system(f'g++ {filename} -O2 -Wl,{stack_size_option}{512 << 20} -o {name}'):
        raise RuntimeError("Compile error!")


def decomposition(i):
        while i > 0:
            n = random.randint(1, i)
            yield n
            i -= n

def diff(file_1, file_2):
    if sys.platform == "win32":
        return os.system(f"FC {file_1} {file_2} > nul 2>&1")
    else:
        return os.system(f"diff {file_1} {file_2} > /dev/null 2>&1")


def random_seq(a, b, n):
    return [randint(a, b) for _ in range(n)]

def gen_random(n, f):
    f.input_writeln(n)
    s = set()
    for _ in range(n):
        while True:
            l = randint(1, int(1e9))
            r = randint(l, int(1e9))
            if (l, r) not in s:
                s.add((l, r))
                f.input_writeln(l, r)
                break



# 卡掉从叶子往上爬的做法
def naiive_killer_1(f: IO, n, q):
    f.input_writeln(n, q)
    h = n // 2
    a1 = list(range(1, h + 1))
    a2 = random_seq(h + 1, h + 10000, h)
    a = a1 + a2
    f.input_writeln(a)
    for i in range(1, h):
        f.input_writeln(i, i + 1)
    for i in range(h + 1, n + 1):
        f.input_writeln(h, i)
    
    for _ in range(q):
        f.input_writeln(randint(h - 5000, h + 5000))


# def naiive_killer_2(f: IO, n, q):

# tree = Graph.tree(n)
# f.input_writeln(tree.to_str(output=Edge.unweighted_edge)) # 输出无权图，以每条边u v一行的格式

def gen_star(f: IO):
    n = int(1e5)
    q = int(1e5)
    g = Graph(n)
    f.input_writeln(n, q)
    for i in range(2, n + 1):
        f.input_writeln(1, i)
    for _ in range(q):
        type = randint(1, 2)
        if type == 1:
            d = randint(1, int(1e9))
            f.input_writeln(1, 1, d)
        else:
            u = randint(1, n)
            f.input_writeln(2, u)

def gen_random(f: IO, n, q, max_a):
    assert(max_a <= n)
    a = random_seq(1, max_a, n)
    tree = Graph.tree(n)

    v = set(a)
    missing = list(set(range(1, n + 1)) - v)
    if len(missing):
        v.update(random.choices(missing, k=3))

    v = list(v)
    f.input_writeln(n, q)
    f.input_writeln(a)
    f.input_writeln(tree.to_str(output=Edge.unweighted_edge))
    for _ in range(q):
        u = randint(1, n)
        x = random.choice(v)
        f.input_writeln(u, x)


# test_id：测试点编号，从 1 开始。用途：根据测试点编号，决定数据范围或特殊性质
def gen_test(in_file, test_id):
    f_ = open(in_file, 'w+')
    f_.close()
    f = IO(in_file)  # .out是临时文件
    # 以下是造数据的代码
    maxn = int(5e4)
    if test_id == 1:
        gen_random(f, 10, 10, 5)
        return
    if test_id < 5:
        n = randint(1, maxn)
        q = randint(1, maxn)
        gen_random(f, n, q, randint(1, n))
        return
    if test_id == 5:
        gen_random(f, maxn, maxn, maxn)
        return
    
    gen_random(f, maxn, maxn, randint(1, 250))


# n_tests：测试点数量
# prefix：输入输出文件名
def make_zip(task_name, n_tests, time_limit, is_spj, submit_answer, with_fake, test_id_offset):
    tests_dir = os.path.join("tests", task_name)
    if os.path.exists(tests_dir):
        shutil.rmtree(tests_dir)

    os.makedirs(tests_dir) 

    if (submit_answer):
        n_tests = 1
    
    
    # 编译标程
    compile("ac.cpp")
    if with_fake:
       compile("fake.cpp")


    for i in tqdm(range(1 + test_id_offset, n_tests + 1 + test_id_offset)):
        in_file = os.path.abspath(os.path.join(tests_dir, task_name + str(i) + '.in'))
        out_file = os.path.abspath(os.path.join(tests_dir, task_name + str(i) + '.out'))

        if with_fake:
            while True:
                gen_test(in_file, i)
                os.system(f"./ac < {in_file} > {out_file}")
                os.system(f"./fake < {in_file} > fake.out")
                if diff(out_file, "fake.out"):
                    break
        else:
            gen_test(in_file, i)
            os.system(f"./ac < {in_file} > {out_file}")
    
    if is_spj:
        shutil.copy('checker.cpp', tests_dir)
    #生成zip包
    shutil.make_archive(task_name, 'zip', tests_dir) 
    #删除测试数据
    # shutil.rmtree(tests_dir)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process task.')
    parser.add_argument("task_name", type=str)
    parser.add_argument("n_tests", type=int)
    parser.add_argument("time_limit", type=float)
    parser.add_argument('--spj', action='store_true') # 是否spj
    parser.add_argument('--submit-answer', action='store_true', default=False)
    parser.add_argument('--with-fake', action='store_true', default=False)
    parser.add_argument('--test-id-offset', type=int, default=0)
    args = parser.parse_args()
    make_zip(args.task_name, args.n_tests, args.time_limit, args.spj, args.submit_answer, args.with_fake, args.test_id_offset)
    