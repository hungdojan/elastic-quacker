import logging
import socket
import sys

from .base import BaseMode
from rd_client.parser import KeySeqvParser

class NetworkMode(BaseMode):
    """Cli mode for sending RubberDucky script to RubberDucky device using
        network's server-client method."""

    def __init__(self, input_file: str|None, port: int, ip_addr: str, verbose: bool):
        super().__init__(verbose)
        self._port = port
        self._host = ip_addr

        # input file
        if input_file:
            self._in_f = open(input_file, 'r')
        else:
            self._in_f = sys.stdin


    def run(self):
        ksp = KeySeqvParser(self._verbose)

        # opening socket
        client_socket = socket.socket()
        client_socket.connect((self._host, self._port))

        # reading file
        with self._in_f as f:
            for i, line in enumerate(f):
                ksp.parse_line(line, i)
        ksp.set_last()

        # sending data to RubberDucky
        for ks in ksp.lof_keyseqvs:
            client_socket.send(ks.to_bytes())
            if self._verbose:
                # TODO: log sent data
                pass
            recv_msg = client_socket.recv(200)
            if self._verbose:
                logging.info(recv_msg)

        client_socket.close()
