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

from pprint import pformat

s = pformat(table_map, sort_dicts=False, width=150)
s = s.replace("'", '"')

import re

s = re.sub(r'([^"])\["', r'\1{"', s)
s = re.sub(r'"\]([^"])', r'"}\1', s)

with open('c_table', 'w+') as f:
    f.write(
        f"const unordered_map<string, unordered_map<string, vector<string>>table_map = {s};"
    )
