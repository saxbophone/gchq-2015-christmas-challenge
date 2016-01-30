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
