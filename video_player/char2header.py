
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


def compress(data):
    compressed_data = []

    i = 0
    l = len(data)
    while True:
        if i+7 < l and data[i] == data[i+1] == data[i+2] == data[i+3] == data[i+4] == data[i+5] == data[i+6] == data[i+7]:
            compressed_data.append(32 if data[i] == 0 else 33)
            i += 8
        elif i+3 < l and data[i] == data[i+1] == data[i+2] == data[i+3]:
            compressed_data.append(34 if data[i] == 0 else 35)
            i += 4
        elif i+2 < l and data[i] == data[i+1] == data[i+2]:
            compressed_data.append(36 + data[i])
            i += 3
        elif i+1 < l and data[i] == data[i+1]:
            compressed_data.append(36 + 32 + data[i])
            i += 2
        else:
            if i >= l:
                break
            compressed_data.append(data[i])
            i += 1

    return compressed_data


with open('charvideo.txt', 'r', encoding='utf-8') as char_file:
    with open('video_context.h', 'w', encoding='utf-8') as header_file:
        header_file.write(header_begin)
        header_file.write(
            'const unsigned char video_context[] PROGMEM = {\n')
        line = char_file.readline()
        count = 0
        while line:
            print('frame %s' % count)
            count += 1
            if count <= 3:
                line = char_file.readline()
                continue
            grid_array = frame2array(line)
            data = []
            context_to_write = '    '
            for a in grid_array:
                s = str2num(a)
                data.append(s)
            data = compress(data)
            for a in data:
                context_to_write += str(a) + ', '
            context_to_write += '126'
            header_file.write(context_to_write)
            line = char_file.readline()
            if line:
                header_file.write(',\n')
            else:
                header_file.write(',\n    127\n')
        header_file.write('};')

        header_file.write(header_end)
