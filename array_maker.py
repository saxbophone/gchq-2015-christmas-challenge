"""
Simple Python script that reads in 25 rows of space-separated numbers from the
command line and outputs these as a C struct initialiser for use in puzzle.inc.
"""

lines = []

for _ in range(25):
    data = raw_input()
    nums = data.split()
    if len(nums) < 9:
        for __ in range(9 - len(nums)):
            nums.append('0')
    line = '{ ' + '{},'.format(', '.join(nums)).rstrip(',') + ' },'
    lines.append(line)

lines = '\n'.join(lines)
print(lines)
