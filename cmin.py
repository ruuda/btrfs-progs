#!/usr/bin/env python3

import sys
import hashlib
from collections import defaultdict
from typing import Dict, NamedTuple

file_len = 114294784

class Mutation(NamedTuple):
    offset: bytes
    value: int

def load(fname: str) -> Dict[int, int]:
    mutations = {}
    with open(fname, 'rb') as f:
        while True:
            data = f.read(5)
            if len(data) == 0:
                return mutations

            data = data + bytes(b'\0' * (5 - len(data)))
            assert len(data) == 5

            offset = int.from_bytes(data[:4], byteorder='big')
            offset = min(file_len - 1, offset)
            value = data[4]

            mutations[offset] = value


def normalize(mutations: Dict[int, int]) -> bytes:
    data = b''
    for offset, value in sorted(mutations.items()):
        data = data + offset.to_bytes(4, byteorder='big') + bytes([value])
        assert len(data) % 5 == 0
    return data


def main() -> None:
    normed_mutations = set()
    all_mutations = set()

    # Collect all input mutations.
    for fname in sys.argv[1:]:
        mutations = load(fname)
        normed_mutations.add(normalize(mutations))
        for offset, value in mutations.items():
            all_mutations.add((offset, value))

    # Add normed mutations for every individual byte that is part of an example.
    for offset, value in all_mutations:
        normed_mutations.add(normalize({offset: value}))

    normed_mutations_list = list(normed_mutations)
    normed_mutations_list.sort()

    for data in normed_mutations_list:
        name = hashlib.sha224(data).hexdigest()[:30]
        with open(f'cmin/{name}', 'wb') as f:
            print(name, len(data))
            f.write(data)


main()
