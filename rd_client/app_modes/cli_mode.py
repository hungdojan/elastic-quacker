import logging
import sys

from rd_client.parser.error import ParserError
from rd_client.parser import KeySeqvParser

from .base import BaseMode
from datetime import datetime

HEADER_CONTENT = \
"""/**
 * @brief Defines key sequence for Linux systems.
 *
 * This particular set of key sequence was generated by rd_parser module.
 *
 * This source code serves as submission to my bachelor thesis topic
 * "Implement Rubber Duckies on Available USB Devices and Make a Practical Test"
 * at FIT, BUT 2022/23.
 *
 * @author Hung Do
 * @date {}
 */
#include "key_seqv.h"

/// List of key sequences for (my) Linux system
struct key_seqv_t key_seqvs[] = {{
""".format(datetime.strftime(datetime.today(), '%d/%m/%Y'))

FOOTER_CONTENT = \
"""};
"""

class CliMode(BaseMode):

    def __init__(self, input_path: str|None, output_path: str|None, verbose: bool):

        super().__init__(verbose)
        # input file
        if input_path:
            self._in_f = open(input_path, 'r')
        else:
            self._in_f = sys.stdin

        # output file
        if output_path:
            self._out_f = open(output_path, 'w')
        else:
            self._out_f = sys.stdout


    def run(self) -> int:
        ksp = KeySeqvParser(self._verbose)

        self._log_msg(logging.INFO, '------ Start parsing script ------')
        try:
            # parse the file/from stdin
            with self._in_f as f:
                for i, line in enumerate(f):
                    ksp.parse_line(line, i)
            ksp.set_last()
        except ParserError:
            self._log_msg(logging.ERROR, 'Terminating application')
            self._display_nonverbose_error_msg()
            return 1

        self._log_msg(logging.INFO, '------- Writing to output -------')
        # write into output file/stdout
        with self._out_f as f:
            f.write(HEADER_CONTENT)
            for ks in ksp.lof_keyseqvs:
                f.write(str(ks))
            f.write(FOOTER_CONTENT)
        self._log_msg(logging.INFO, '-------- Writing finished --------')
        self._log_msg(logging.INFO, f'Number of key sequences: {len(ksp.lof_keyseqvs)}')
        return 0
