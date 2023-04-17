import argparse
import logging
import os
import sys

from typing import Any
from rd_client import __version__
from rd_client.app_modes import *
from rd_client.parser import ErrorCode


def __process_args() -> dict[str, Any]:
    """Process arguments.

    Returns dict structure: {
        'host':     (str) IP address of the RubberDucky device,
        'input':    (str|None) File path to input file,
        'log_file': (str|None) File path to log file,
        'network':  (bool) Enable server-client mode,
        'output':   (str|None) File path to output file,
        'port':     (int) RubberDucky server application port,
        'tui':      (bool) Enable interactive mode,
        'verbose':  (bool) Enable logging.
    }

    Returns:
        dict[str, Any]: Returns dictionary of processed arguments.
    """
    parser = argparse.ArgumentParser('RubberDucky script parser',
                                     formatter_class=lambda prog: argparse.HelpFormatter(prog, max_help_position=40))

    parser.add_argument('--version', action='version', version=f'%(prog)s {__version__}')
    parser.add_argument('-H', '--host', action='store', metavar='IP address',
                        help='IP address of the RubberDucky device.')
    parser.add_argument('-i', '--input', action='store', metavar='filename',
                        help='Source RubberDucky script file.')
    parser.add_argument('-l', '--log_file', action='store', metavar='filename',
                        help='Log filename. Defaults to STDERR.')
    parser.add_argument('-n', '--network', action='store_true',
                        help='Upload script using networking.')
    parser.add_argument('-o', '--output', action='store', metavar='filename',
                        help='Generated output filename.')
    parser.add_argument('-p', '--port', action='store', metavar='PORT',
                        help='Application port of the RubberDucky device. Defaults to 5000.',
                        default=5000, type=int)
    parser.add_argument('-t', '--tui', action='store_true',
                        help='Open program in interactive mode.')
    parser.add_argument('-v', '--verbose', action='store_true',
                        help='Enable logging.')
    args = parser.parse_args()

    # check received arguments
    if args.input is not None:
        if not os.path.exists(args.input):
            sys.stderr.write(f'File "{args.input}" does not exists\n')
            sys.exit(ErrorCode.INPUT_FILE_NOT_FOUND)

    # init logging
    if args.verbose:
        if args.log_file:
            logging.basicConfig(filename=args.log_file,
                                filemode='w',
                                format='%(levelname)s :: %(message)s',
                                level=logging.DEBUG)
        else:
            logging.basicConfig(stream=sys.stderr,
                                filemode='w',
                                format='%(levelname)s :: %(message)s',
                                level=logging.DEBUG)

    return vars(args)


def get_mode() -> BaseMode:
    """Factory function that returns AppMode based on given arguments."""

    args = __process_args()

    # return selected mode
    if args['tui']:
        # interactive mode
        return TuiMode(args['verbose'])
    if args['network']:
        # communication with RubberDucky using network (wifi)
        return NetworkMode(args['input'], args['port'], args['host'], args['verbose'])
    # cli script parsing to C-file source code
    return CliMode(args['input'], args['output'], args['verbose'])
