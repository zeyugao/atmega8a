
def frame2array(frame):

    grid_array = []
    for j in range(2):
        for i in range(4):
            for line in range(8):
                grid_array.append(
                    frame[j*8*20+line*20+i*5:j*8*20+line*20+i*5 + 5])

    return grid_array


def str2num(s):
    ret = 0
    for i in range(5):
        ret += int(s[i]) << (4-i)
    return ret


header_begin = '''
// Auto generated, don't modify
#ifndef VIDEO_CONTEXT_H
#define VIDEO_CONTEXT_H

'''

header_end = '''
#endif // VIDEO_CONTEXT_H
'''

with open('charvideo.txt', 'r', encoding='utf-8') as char_file:
    with open('video_context.h', 'w', encoding='utf-8') as header_file:
        header_file.write(header_begin)
        header_file.write('unsigned char video_context[][64] = {\n')
        line = char_file.readline()
        count = 0
        while line:
            print('line %s' % count)
            count += 1
            grid_array = frame2array(line)
            header_file.write('    {')
            context_to_write = ''
            for a in grid_array:
                s = str2num(a)
                context_to_write += str(s) + ', '
            context_to_write = context_to_write[:-2]
            header_file.write(context_to_write)
            header_file.write('}')
            line = char_file.readline()
            if line:
                header_file.write(',\n')
            else:
                header_file.write('\n')
        header_file.write('};')

        header_file.write(header_end)
