import csv
from itertools import product
from typing import DefaultDict

EPS = 'ε'

table = []
with open('lltable.txt', newline='') as f:
    reader = csv.reader(f, delimiter='`')
    table = [*reader]

top_level = [i[0] for i in table[1:]]
print(top_level)

next_level = table[0][1:]
print(next_level)


def parse_transformation(rule):
    rule = rule[rule.index('::= ') + 4:]
    return [i if i != EPS else 'EPS' for i in rule.split()]


table_map = DefaultDict(dict)

for (nonterminal,
     terminal), transformation in zip(product(top_level, next_level),
                                      (i for row in table[1:]
                                       for i in row[1:])):
    if transformation:
        table_map[nonterminal][terminal] = parse_transformation(transformation)

table_map = {k: v for k, v in table_map.items()}

# from pprint import pformat

# s = pformat(table_map, sort_dicts=False, width=150)
# s = s.replace("'", '"')

# import re

# s = re.sub(r'([^"])\["', r'\1{"', s)
# s = re.sub(r'"\]([^"])', r'"}\1', s)


def vec(v):
    s = ""
    for i in v:
        s += f'"{i}", '
    return s


def mid_lvl(v):
    s = ""
    for k, v in v.items():
        s += f'\t\t{{"{k}", {{ {vec(v)} }}}},\n'
    return s


s = "{\n"
for k, v in table_map.items():
    s += f'\t{{"{k}", {{{mid_lvl(v)}}} }},\n'
s += "\n}"

with open('../src/c_table.hpp', 'w+') as f:
    f.write(f"""#include <string>
#include <unordered_map>
#include <vector>

const unordered_map<string, unordered_map<string, vector<string>>>table_map{s};
""")
