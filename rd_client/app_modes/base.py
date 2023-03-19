import logging

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
    def run(self):
        """Entry point of the program.

        Params:
            verbose (bool): Enable logging.
        """
        pass


    def _log_msg(self, _type: int, msg: str):
        """Write a report into logging file."""
        if not self._verbose:
            return

        fnc = LOG_FUN.get(_type)
        if fnc:
            fnc(msg)
