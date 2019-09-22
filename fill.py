#!/usr/bin/env python3

from itertools import cycle

file_len = 114294784
values = cycle([0x77, 0xff, 0xaa, 0xcc])

for off_a in range(0, file_len, 4096 * 2):
    for off_b in (1, 31):
        off = off_a + off_b
        value = next(values)
        fname = f'{off:04x}{value:02x}'
        content = off.to_bytes(4, byteorder='big') + bytes([value])
        with open(f'inputs/{fname}', 'wb') as f:
            print(fname)
            f.write(content)
