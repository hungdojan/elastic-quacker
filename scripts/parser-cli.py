import argparse
import os
import logging
import sys

from rd_parser.error import ErrorCode
from rd_parser.key_seqv_parser import KeySeqvParser

def process_args() -> tuple[str|None, str|None]:
    """Process arguments.

    Returns:
        tuple[str|None, str|None]: Filename of input and output file, respectively when defined.
    """
    parser = argparse.ArgumentParser('RubberDucky script parser')
    parser.add_argument('-i', '--input', action='store', metavar='filename',
                        nargs=1, help='Source RubberDucky script file.')
    parser.add_argument('-o', '--output', action='store', metavar='filename',
                        nargs=1, help='Generated output filename.')
    parser.add_argument('-l', '--log_file', action='store', metavar='filename',
                        nargs='?', help='Log filename. Defaults to "parser.log"',
                        default='parser.log', const='parser.log')
    args = parser.parse_args()
    in_file, out_file = None, None

    # check received arguments
    if args.input is not None:
        if not os.path.exists(args.input[0]):
            sys.stderr.write(f'File {args.input[0]} does not exists\n')
            sys.exit(ErrorCode.INPUT_FILE_NOT_FOUND)
        in_file = args.input[0]

    out_file = args.output[0] if args.output is not None else None

    # init logging
    logging.basicConfig(filename=args.log_file,
                        filemode='w',
                        format='%(levelname)s :: %(message)s',
                        level=logging.DEBUG)

    return in_file, out_file


def main():
    # process arguments
    in_filename, out_filename = process_args()
    in_f = open(in_filename, 'r') if in_filename else sys.stdin
    out_f = open(out_filename, 'w') if out_filename else sys.stdout

    ksp = KeySeqvParser(in_f, out_f)
    ksp.parse_content()
    ksp.generate_output_file()


if __name__ == '__main__':
    main()
