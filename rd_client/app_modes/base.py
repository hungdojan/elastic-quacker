import logging
import sys

from abc import ABC, abstractmethod

LOG_FUN = {
    logging.WARN: logging.warn,
    logging.ERROR: logging.error,
    logging.INFO: logging.info,
    logging.DEBUG: logging.debug
}

class BaseMode(ABC):

    def __init__(self, verbose: bool):
        self._verbose = verbose

    @abstractmethod
    def run(self) -> int:
        """Entry point of the program.

        Params:
            verbose (bool): Enable logging.

        Return:
            int: Error code; 0 for no error
        """
        pass


    def _log_msg(self, _type: int, msg: str):
        """Write a report into logging file."""
        if not self._verbose:
            return

        fnc = LOG_FUN.get(_type)
        if fnc:
            fnc(msg)


    def _display_nonverbose_error_msg(self):
        if not self._verbose:
            sys.stderr.write(
                'Error occured. Toggle -v flag to see the error message.\n'
            )
