from abc import ABC, abstractmethod

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
