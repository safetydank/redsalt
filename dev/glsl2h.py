from __future__ import with_statement
import sys
from os.path import basename, splitext

def glsl2h(infile, outfile):
    with file(infile) as fi:
        with file(outfile, 'w') as fo:
            fo.write('const char shader_%s[] = ' % splitext(basename(infile))[0])
            for line in fi.readlines():
                fo.write('"%s"\n' % line.rstrip('\r\n'))
            fo.write(';')

    # print 'glsl2h: Infile %s Outfile %s' % (infile, outfile)
    
if __name__ == '__main__':
    glsl2h(sys.argv[1], sys.argv[2])

